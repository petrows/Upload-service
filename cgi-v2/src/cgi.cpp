#include "cgi.h"
#include <csignal>
#include <cstdlib>
#include <iostream>
#include <libgen.h>
#include <unistd.h>

#include "common.h"
#include "webdownload.h"
#include "webupload.h"

using namespace std;

std::atomic<bool> CGI::enableRun;
std::string CGI::cfgWorkDir;

CGI::CGI() {}

int CGI::run(int argc, char **argv) {
	int ret;

	socketPath = "/tmp/petro-upload-sock";
	threadCount = 16;

	cfgWorkDir = dirname(argv[0]);
	enableRun = true;

	// std::signal(SIGINT, sighandler);
	// std::signal(SIGABRT, sighandler);
	// std::signal(SIGKILL, sighandler);

	// Params
	int c;

	while ((c = getopt(argc, argv, "hd:p:t:")) != -1) {
		switch (c) {
		case 'h':
			// Print help
			help();
			return 0;
		case 'd':
			cfgWorkDir = optarg;
			break;
		case 'p':
			socketPath = optarg;
			break;
		case 't':
			threadCount = static_cast<unsigned int>(std::atoi(optarg));
			break;
		default:
			abort();
		}
	}

	ret = FCGX_Init();
	if (0 != ret) {
		ERR << "Error FCGX_Init: " << ret;
		return 1;
	}

	socketHandle = FCGX_OpenSocket(socketPath.c_str(), 64);
	if (socketHandle < 0) {
		ERR << "Cant open socket " << socketPath << ", error " << errno;
		return 2;
	}
	MSG << "Started listen " << socketPath;

	MSG << "Starting threads: " << threadCount;
	MSG << "Using upload root dir: " << cfgWorkDir;

	for (unsigned int x = 0; x < threadCount; x++) {
		thread *t = new thread(&CGI::threadFunc, this, x);
		threadList.push_back(t);
	}

	while (enableRun) {
		// Wait for the World end
		usleep(100 * 1000);
	}

	// Ask not accept new connections
	FCGX_ShutdownPending();

	close(socketHandle);

	MSG << "Stopping threads";

	for (thread *t : threadList) {
		t->join();
		delete t;
	}
	threadList.clear();

	return 0;
}

void CGI::sighandler(int signal) {
	WRN << "Signal " << signal << " catched";

	// Stop threads
	enableRun = false;
}

void CGI::help() {
	cout << "Usage: " << endl;
	cout << "-h        : help" << endl;
	cout << "-t <cnt>  : threads count (default 16)" << endl;
	cout << "-d <dir>  : upload root directory" << endl;
	cout << "-p <path> : socket path" << endl;
}

void CGI::threadFunc(int id) {
	int ret;
	FCGX_Request request;
	FCGX_InitRequest(&request, socketHandle, FCGI_FAIL_ACCEPT_ON_INTR);

	while (enableRun) {
		// Accept new request
		threadMutex.lock();
		ret = FCGX_Accept_r(&request);
		threadMutex.unlock();

		if (-1 == ret)
			break; // We cant do this work

		MSG << "Accepted [" << id << "]: " << FCGX_GetParam("REMOTE_ADDR", request.envp) << " " << FCGX_GetParam("REQUEST_URI", request.envp);

		// Detect - what worker we should run?
		string scriptName = FCGX_GetParam("SCRIPT_NAME", request.envp);
		scriptName = strTrim(scriptName, "/");

		vector<string> scriptNamePath = strExplode(scriptName, "/");

		// Check - we are api? And select proper worker
		bool requestPrecessed = false;
		if (scriptNamePath.size() > 1 && string("c") == scriptNamePath[0]) {
			// Select worker
			if (string("u") == scriptNamePath[1]) {
				requestPrecessed = true;
				// Upload worker
				WebUpload upload;
				upload.init(&request);
				upload.handleRequest();
			}
			if (string("d") == scriptNamePath[1] || string("f") == scriptNamePath[1]) {
				requestPrecessed = true;
				// Upload worker
				WebDownload upload;
				upload.init(&request);
				upload.handleRequest();
			}
		}

		if (!requestPrecessed) {
			ERR << "Invalid request " << scriptName;
			FCGX_PutS("Status: 400\r\n", request.out);
			FCGX_PutS("\r\n", request.out);
			FCGX_PutS("Invalid request", request.out);
		}

		FCGX_Finish_r(&request);
	}

	MSG << "Stopping thread #" << id;
}
