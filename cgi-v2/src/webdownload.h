#ifndef WEBDOWNLOAD_H
#define WEBDOWNLOAD_H

#include "webworker.h"

class WebDownload : public WebWorker {
public:
	WebDownload();
	virtual ~WebDownload() {}

	// WebWorker interface
public:
	void handleRequest();

private:
	enum { DOWNLOAD_NORMAL, DOWNLOAD_FORCE } mode;

	std::string uploadHash;
	unsigned int uploadFileId;
	std::string uploadFileHash;
	std::string uploadFileName;

	unsigned long long fileInfoSize;
	std::string fileInfoHash;
	std::string fileInfoContentType;

	void printError(int code, std::string msg);
};

#endif // WEBDOWNLOAD_H
