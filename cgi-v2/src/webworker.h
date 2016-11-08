#ifndef WEBWORKER_H
#define WEBWORKER_H

#include <fcgi_config.h>
#include <fcgio.h>
#include <map>
#include <string>
#include <sstream>

class WebWorker {
public:
	WebWorker();
	virtual ~WebWorker() {}

	virtual bool init(FCGX_Request *requestIn);
	virtual void handleRequest() = 0;

protected:
	virtual void finishHeaders();
	std::string logHeader();

	int httpReturnCode;
	std::stringstream replyHeaders;

	FCGX_Request *request;
	std::map<std::string, std::string> cookie;
	std::map<std::string, std::string> get;
	std::string ip;
};

#endif // WEBWORKER_H
