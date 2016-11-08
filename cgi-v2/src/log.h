#ifndef LOG_T_H
#define LOG_T_H

#if defined(NDEBUG)
#define DBG LogDummy()
#else
#define DBG Log(__FILE__, __LINE__, Log::LOG_DBG)
#endif
#define MSG Log(__FILE__, __LINE__, Log::LOG_MSG)
#define WRN Log(__FILE__, __LINE__, Log::LOG_WRN)
#define ERR Log(__FILE__, __LINE__, Log::LOG_ERR)

#include <sstream>
#include <string>

class LogDummy
{
public:
	template <class T> LogDummy &operator<<(const T &arg) { return *this; }
};

class Log
{
public:
	enum Level
	{
		LOG_DBG,
		LOG_MSG,
		LOG_WRN,
		LOG_ERR
	};
	Log(const char *fl, int ln, Level lvl);
	~Log();

	template <class T> Log &operator<<(const T &arg)
	{
		strm << arg;
		return *this;
	}

	static std::string formatPtr(void *ptr);
	static std::string formatHex32(uint32_t num);

private:
	static const char *getLevelxt(Level lvl);
	static const uint8_t getLevelColor(Level lvl);

	const char *callFile;
	const int callLine;
	const Level callLevel;
	uint32_t callTms;
	std::stringstream strm;
};

// Common types
std::ostream &operator<<(std::ostream &o, const std::string &s);
std::ostream &operator<<(std::ostream &o, const std::stringstream &s);

#endif // LOG_T_H
