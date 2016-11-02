#include "cgi.h"
#include <iostream>
#include <csignal>
#include <cstdlib>
#include <unistd.h>

using namespace  std;

std::atomic<bool> CGI::enableRun;

CGI::CGI(int argc, char **argv)
{
	socketPath = "/tmp/petro-upload-sock";
	threadCount = 5;

	enableRun = true;
}

int CGI::run()
{
	int ret;

	//std::signal(SIGINT, sighandler);
	//std::signal(SIGABRT, sighandler);
	//std::signal(SIGKILL, sighandler);

	ret = FCGX_Init();
	if (0 != ret) {
		cerr << "Error FCGX_Init " << ret << endl;
		return 1;
	}

	socketHandle = FCGX_OpenSocket(socketPath.c_str(), 64);
	if(socketHandle < 0) {
		cerr << "Cant open socket " << socketPath << ", error " << errno << endl;
		return 2;
	}
	cout << "Started listen " << socketPath << endl;

	cout << "Starting threads: " << threadCount << endl;

	for(unsigned int x=0; x<threadCount; x++)
	{
		thread *t = new thread(&CGI::threadFunc, this, x);
		threadList.push_back(t);
	}

	while (enableRun)
	{
		// Wait for the World end
		usleep(100 * 1000);
	}

	// Ask not accept new connections
	FCGX_ShutdownPending();

	close(socketHandle);

	cout << "Stopping threads" << endl;

	for(thread* t : threadList)
	{
		t->join();
		delete t;
	}
	threadList.clear();

	return 0;
}

void CGI::sighandler(int signal)
{
	cerr << "Signal " << signal << " catched" << endl;

	// Stop threads
	enableRun = false;
}

void CGI::threadFunc(int id)
{
	int ret;
	FCGX_Request request;
	FCGX_InitRequest(&request, socketHandle, FCGI_FAIL_ACCEPT_ON_INTR);

	while (enableRun)
	{
		// Accept new request
		threadMutex.lock();
		ret = FCGX_Accept_r(&request);
		threadMutex.unlock();

		if (-1 == ret) break; // We cant do this work

		cout << "Accepted [" << id << "]" << endl;

		//получить значение переменной
		char *server_name = FCGX_GetParam("SERVER_NAME", request.envp);

		//вывести все HTTP-заголовки (каждый заголовок с новой строки)
		FCGX_PutS("Content-type: text/html\r\n", request.out);
		//между заголовками и телом ответа нужно вывести пустую строку
		FCGX_PutS("\r\n", request.out);
		//вывести тело ответа (например - html-код веб-страницы)
		FCGX_PutS("<html>\r\n", request.out);
		FCGX_PutS("<head>\r\n", request.out);
		FCGX_PutS("<title>FastCGI Hello! (multi-threaded C, fcgiapp library)</title>\r\n", request.out);
		FCGX_PutS("</head>\r\n", request.out);
		FCGX_PutS("<body>\r\n", request.out);
		FCGX_PutS("<h1>FastCGI Hello! (multi-threaded C, fcgiapp library)</h1>\r\n", request.out);
		FCGX_PutS("<p>Request accepted from host <i>", request.out);
		FCGX_PutS(server_name ? server_name : "?", request.out);
		FCGX_PutS("</i></p>\r\n", request.out);

		FCGX_PutS("<p>Im a thread <b>", request.out);
		FCGX_PutS(std::to_string(id).c_str(), request.out);
		FCGX_PutS("</b></p>", request.out);

		FCGX_PutS("</body>\r\n", request.out);
		FCGX_PutS("</html>\r\n", request.out);

		//"заснуть" - имитация многопоточной среды
		sleep(2);

		FCGX_Finish_r(&request);
	}

	cout << "Stopping thread #" << id << endl;
}
