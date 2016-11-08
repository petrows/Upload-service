#include "webdownload.h"
#include "cgi.h"
#include "common.h"
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <sys/stat.h>

#define BUFF_SIZE (1 * 1024 * 1024)

using namespace std;
WebDownload::WebDownload() : mode(DOWNLOAD_NORMAL), uploadFileId(0) {}

void WebDownload::handleRequest() {
	replyHeaders << "Connection: close\r\n";

	// Detect - what worker we should run?
	string scriptName = FCGX_GetParam("SCRIPT_NAME", request->envp);
	scriptName = strTrim(scriptName, "/");

	vector<string> scriptNamePath = strExplode(scriptName, "/");

	string modeStr = scriptNamePath[1];
	if (string("f") == modeStr) {
		mode = DOWNLOAD_FORCE;
	}

	uploadHash = scriptNamePath[2];
	uploadFileId = std::atoi(scriptNamePath[3].c_str());
	uploadFileHash = scriptNamePath[4];
	uploadFileName = scriptNamePath[5];

	fileInfoContentType = "application/x-force-download";

	// Clean the options
	uploadHash.erase(remove_if(uploadHash.begin(), uploadHash.end(), std::not1(std::ptr_fun<int, int>(std::isxdigit))), uploadHash.end());

	if (32 != uploadHash.size()) {
		ERR << logHeader() << "Wrong hash " << uploadHash;
		return printError(404, "File Not Found");
	}

	// Check file access
	string filePath = CGI::cfgWorkDir + "/d/" + uploadHash.substr(0, 2) + "/" + uploadHash.substr(2, uploadHash.length() - 2);
	string filePathConfig = filePath + "/" + to_string(uploadFileId) + ".inf";
	string filePathData = filePath + "/" + to_string(uploadFileId) + ".dat";

	// Read config
	ifstream fileConfigPath(filePathConfig);
	string configStr((std::istreambuf_iterator<char>(fileConfigPath)), std::istreambuf_iterator<char>());

	if (configStr.empty()) {
		ERR << logHeader() << "Cant read " << filePathConfig;
		return printError(404, "File Not Found");
	}

	vector<string> fileInfo = strExplode(configStr, "\n");

	if (fileInfo.size() < 5) {
		ERR << logHeader() << "Config error line size";
		return printError(404, "File Not Found");
	}

	fileInfoSize = std::atoll(fileInfo[3].c_str());
	fileInfoHash = fileInfo[4];

	if (DOWNLOAD_NORMAL == mode)
		fileInfoContentType = fileInfo[1];

	// All is okay, now download it
	replyHeaders << "Content-Length: " << fileInfoSize << "\r\n";
	replyHeaders << "Content-Type: " << fileInfoContentType << "\r\n";

	finishHeaders();

	// Now send file data
	// Okay, seems to be all Okay
	FILE *f = fopen64(filePathData.c_str(), "r");
	if (!f) {
		ERR << logHeader() << "Can topen file " << filePathData;
		return printError(404, "File Not Found");
	}

	ERR << logHeader() << "Start download file " << uploadFileName << "(" << fileInfoSize << ")";
	chrono::milliseconds timeStart = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch());

	char *fileBuf = new char[BUFF_SIZE];
	int rs = 0;
	while (!feof(f)) {
		rs = fread(fileBuf, 1, BUFF_SIZE, f);
		FCGX_PutStr(fileBuf, rs, request->out);
	}
	fclose(f);
	delete[] fileBuf;

	chrono::milliseconds timeStop = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch());

	DBG << logHeader() << "Downloading file done, time " << (timeStop.count() - timeStart.count()) << " ms";
}

void WebDownload::printError(int code, string msg) {
	httpReturnCode = code;
	replyHeaders << "Content-type: text/html\r\n";

	finishHeaders();

	stringstream ans;

	ans << "Error: <b>" << msg << "</b>\n";
	for (int x = 0; x < 1024; x++) {
		ans << "\n\n\n\n";
	}

	FCGX_PutS(ans.str().c_str(), request->out);
}
