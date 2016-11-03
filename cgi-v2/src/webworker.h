#ifndef WEBWORKER_H
#define WEBWORKER_H

#include <string>
#include <map>
#include <fcgio.h>
#include <fcgi_config.h>

class WebWorker
{
public:
	WebWorker();

	virtual bool init(FCGX_Request *requestIn);
	virtual void handleRequest() = 0;

protected:
	FCGX_Request * request;
	std::map<std::string, std::string> cookie;
	std::map<std::string, std::string> get;
	std::string ip;
};

#endif // WEBWORKER_H