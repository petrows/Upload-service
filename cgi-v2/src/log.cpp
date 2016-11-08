#include "log.h"

#include <chrono>
#include <iostream>
#include <math.h>
#include <mutex>

using namespace std;

static mutex LogMutex;

Log::Log(const char *fl, int ln, Log::Level lvl) : callFile(fl), callLine(ln), callLevel(lvl) {
	static uint64_t tms_start;

	chrono::milliseconds ms = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch());

	if (0 == tms_start)
		tms_start = ms.count();

	// Search the last '/' in string
	const char *last_slash = NULL;
	for (const char *ptr = fl; *ptr != 0x00; ptr++) {
		if ('/' == *ptr || '\\' == *ptr)
			last_slash = ptr;
	}
	if (NULL != last_slash) {
		callFile = last_slash + 1;
	}

	callTms = ms.count() - tms_start;
}

Log::~Log() {
	LogMutex.lock();
	char msg_title[128];
	std::snprintf(msg_title, 128, "%07.03f %s %s:%d \e[%dm", (double)callTms / 1000.0, getLevelxt(callLevel), callFile, callLine, getLevelColor(callLevel));

	cout << msg_title << strm.str() << "\e[0m" << endl;

	LogMutex.unlock();
}

string Log::formatPtr(void *ptr) {
	char buf[64];
	std::snprintf(buf, 64, "%p", ptr);
	return string(buf);
}

string Log::formatHex32(uint32_t num) {
	char buf[64];
	std::snprintf(buf, 64, "0x%08X", num);
	return string(buf);
}

const uint8_t Log::getLevelColor(Log::Level lvl) {
	switch (lvl) {
	case LOG_DBG:
		return 35;
		break;
	case LOG_MSG:
		return 32;
		break;
	case LOG_WRN:
	case LOG_ERR:
		return 31;
		break;
	}
	return 0;
}

const char *Log::getLevelxt(Log::Level lvl) {
	switch (lvl) {
	case LOG_DBG:
		return "DBG";
		break;
	case LOG_MSG:
		return "MSG";
		break;
	case LOG_WRN:
		return "WRN";
		break;
	case LOG_ERR:
		return "ERR";
		break;
	}
	return "???";
}

std::ostream &operator<<(std::ostream &o, const std::stringstream &s) {
	o << s.str().c_str();
	return o;
}

std::ostream &operator<<(std::ostream &o, const std::string &s) {
	o << s.c_str();
	return o;
}
