#include "cgi.h"
#include <csignal>
#include <cstdlib>
#include <iostream>
#include <libgen.h>
#include <unistd.h>

#include "common.h"
#include "webupload.h"

using namespace std;

std::atomic<bool> CGI::enableRun;
std::string CGI::cfgWorkDir;

CGI::CGI() {}

int CGI::run(int argc, char **argv) {
	int ret;

	socketPath = "/tmp/petro-upload-sock";
	threadCount = 5;

	cfgWorkDir = dirname(argv[0]);
	enableRun = true;

	// std::signal(SIGINT, sighandler);
	// std::signal(SIGABRT, sighandler);
	// std::signal(SIGKILL, sighandler);

	// Params
	int c;

	while ((c = getopt(argc, argv, "hd:")) != -1) {
		switch (c) {
		case 'h':
			// Print help
			help();
			return 0;
		case 'd':
			cfgWorkDir = optarg;
			break;
		default:
			abort();
		}
	}

	ret = FCGX_Init();
	if (0 != ret) {
		cerr << "Error FCGX_Init " << ret << endl;
		return 1;
	}

	socketHandle = FCGX_OpenSocket(socketPath.c_str(), 64);
	if (socketHandle < 0) {
		cerr << "Cant open socket " << socketPath << ", error " << errno << endl;
		return 2;
	}
	cout << "Started listen " << socketPath << endl;

	cout << "Starting threads: " << threadCount << endl;
	cout << "Using upload root dir: " << cfgWorkDir << endl;

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

	cout << "Stopping threads" << endl;

	for (thread *t : threadList) {
		t->join();
		delete t;
	}
	threadList.clear();

	return 0;
}

void CGI::sighandler(int signal) {
	cerr << "Signal " << signal << " catched" << endl;

	// Stop threads
	enableRun = false;
}

void CGI::help() {
	cout << "Usage: " << endl;
	cout << "-h       : help" << endl;
	cout << "-d <dir> : upload root directory" << endl;
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

		cout << "Accepted [" << id << "]: " << FCGX_GetParam("REMOTE_ADDR", request.envp) << " " << FCGX_GetParam("REQUEST_URI", request.envp) << endl;

		// Detect - what worker we should run?
		string scriptName = FCGX_GetParam("SCRIPT_NAME", request.envp);
		scriptName = strTrim(scriptName, "/");

		cout << "z1: " << scriptName << endl;

		vector<string> scriptNamePath = strExplode(scriptName, "/");

		// Check - we are api? And select proper worker
		bool requestPrecessed = false;
		if (scriptNamePath.size() > 1 && string("api") == scriptNamePath[0]) {
			// Select worker
			if (string("u") == scriptNamePath[1]) {
				requestPrecessed = true;
				// Upload worker
				WebUpload upload;
				upload.init(&request);
				upload.handleRequest();
			}
		}

		if (!requestPrecessed) {
			cout << "Invalid request" << endl;
			FCGX_PutS("Status: 400\r\n", request.out);
			FCGX_PutS("\r\n", request.out);
			FCGX_PutS("Invalid request", request.out);
		}

		FCGX_Finish_r(&request);
	}

	cout << "Stopping thread #" << id << endl;
}
