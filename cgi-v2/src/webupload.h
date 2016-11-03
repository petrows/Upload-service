#ifndef WEBUPLOAD_H
#define WEBUPLOAD_H

#include "webworker.h"

class WebUpload : public WebWorker
{
public:
	WebUpload();

	// WebWorker interface
public:
	void handleRequest();
};

#endif // WEBUPLOAD_H
