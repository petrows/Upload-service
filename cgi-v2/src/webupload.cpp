#include "webupload.h"
#include "cgi.h"
#include "common.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <sys/stat.h>
#include <chrono>

#define BUFF_SIZE (1 * 1024 * 1024)

using namespace std;

WebUpload::WebUpload() {}

void WebUpload::handleRequest() {
	replyHeaders << "Connection: close\r\n";

	lk = strMd5(cookie["auth"]);

	apiMode = API_JSON;
	if ("1" == get["api"]) {
		apiMode = API_XML;
	}

	if (!checkSid()) {
		printError(101, "Session error");
		return;
	}

	fileSize = 0;
	if (FCGX_GetParam("CONTENT_LENGTH", request->envp))
		fileSize = ::strtoull(FCGX_GetParam("CONTENT_LENGTH", request->envp), NULL, 10);

	if (!fileSize) {
		printError(102, "Content-length header missing");
		return;
	}
	if (!fileMax && fileSize > this->fileMax) {
		printError(103, "File is too large");
		return;
	}

	fileId = std::atoi(get["id"].c_str());
	fileName = strUrlDecode(get["qqfile"]);

	// Okay, upload The File
	string filePathId = strMd5(get["s"]);

	if (API_XML == apiMode) {
		filePathId = get["s"] + get["upid"];
		filePathId = strMd5(filePathId);
	}

	stringstream filUploadPath;

	filUploadPath << CGI::cfgWorkDir;
	filUploadPath << "/tmp/upload";
	filUploadPath << "/" << filePathId << "-" << fileId;

	FILE *fileHadle = fopen64(filUploadPath.str().c_str(), "w");
	if (!fileHadle) {
		// Internal error!
		printError(103, "Enable to write TMP file");
		return;
	}

	// Set perms
	chmod(filUploadPath.str().c_str(), 0666);

	DBG << logHeader() << "Uploading file '" << fileName << "', size " << fileSize << ", id " << fileId;
	chrono::milliseconds timeStart = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch());

	// Read file data
	char *fileBuf = new char[BUFF_SIZE];
	unsigned long long read_n = 0;
	unsigned long long read_s = 0;
	while (true) {
		read_s = FCGX_GetStr(fileBuf, BUFF_SIZE, request->in);

		if (read_s <= 0)
			break;

		read_n += read_s;
		fwrite(fileBuf, read_s, 1, fileHadle);
		if (read_n >= fileSize)
			break; // All done...
	}
	fclose(fileHadle);
	delete[] fileBuf;

	chrono::milliseconds timeStop = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch());

	DBG << logHeader() << "Uploading file done, time " << (timeStop.count() - timeStart.count()) << " ms";

	// On done - redirect to the file post-process
	if (API_XML == apiMode) {
		replyHeaders << "Location: /api/upload-done/?" << FCGX_GetParam("QUERY_STRING", request->envp) << "\r\n";
	} else {
		replyHeaders << "Location: /upload/complete/?" << FCGX_GetParam("QUERY_STRING", request->envp) << "\r\n";
	}

	httpReturnCode = 302;
	finishHeaders();
}

void WebUpload::printError(int code, string message) {
	ERR << logHeader() << "Error: " << code << ", " << message;
	httpReturnCode = 401;

	if (API_XML == apiMode) {
		replyHeaders << "Content-type: application/xml\r\n";
	}
	if (API_JSON == apiMode) {
		replyHeaders << "Content-type: application/json\r\n";
	}

	finishHeaders();

	stringstream ans;

	if (API_XML == apiMode) {
		ans << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
		ans << "<api>\n";
		ans << "<error code=\"" << code << "\">" << message << "</error>";
		ans << "</api>\n\n";
	}

	if (API_JSON == apiMode) {
		ans << "{\"code\":" << code << ",\"error\":\"" << message << "\"}";
	}

	FCGX_PutS(ans.str().c_str(), request->out);
}

bool WebUpload::checkSid() {
	// Check user auth...
	if (!get["s"].length())
		return false;

	// Check file
	stringstream filePath;

	filePath << CGI::cfgWorkDir;

	filePath << "/tmp";

	switch (apiMode) {
	case API_XML:
		filePath << "/sid_api";
		break;
	case API_JSON:
		filePath << "/sid";
	}

	filePath << "/" << strMd5(get["s"]);

	ifstream config(filePath.str());
	string configStr((std::istreambuf_iterator<char>(config)), std::istreambuf_iterator<char>());

	vector<string> s_data = strExplode(configStr, ":");
	if (s_data.size() < 5)
	{
		ERR << logHeader() << "Error reading file " << filePath.str();
		return false; // Bad format
	}

	// Check auth vars...
	if (s_data[1] != ip || s_data[2] != get["s"] || s_data[3] != lk) {
		// Error at auth!
		ERR << logHeader() << "Auth error: " << s_data[1] << "!=" << ip << ", " << s_data[2] << "!=" << get["s"] << ", " << s_data[3] << "!=" << lk;
		return false;
	}

	fileMax = strtoull(s_data[4].c_str(), NULL, 10);

	return true;
}
