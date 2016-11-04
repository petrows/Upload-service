#ifndef WEBUPLOAD_H
#define WEBUPLOAD_H

#include "webworker.h"

class WebUpload : public WebWorker {
public:
	WebUpload();
	virtual ~WebUpload() {}

	// WebWorker interface
public:
	void handleRequest();

private:
	enum { API_XML, API_JSON } apiMode;

	std::string lk;

	int apiUploadId;
	int fileId;
	uint64_t fileSize;
	uint64_t fileMax;

	void printError(int code, std::string message);
	bool checkSid();
};

#endif // WEBUPLOAD_H
