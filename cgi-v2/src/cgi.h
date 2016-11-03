#ifndef CGI_H
#define CGI_H

#include <atomic>
#include <fcgi_config.h>
#include <fcgio.h>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

class CGI {
public:
	CGI(int argc, char **argv);

	int run();

private:
	static void sighandler(int signal);
	void threadFunc(int id);

	static std::atomic<bool> enableRun;

	std::string socketPath;
	int socketHandle;
	std::mutex threadMutex;
	unsigned int threadCount;
	std::vector<std::thread *> threadList;
};

#endif // CGI_H
