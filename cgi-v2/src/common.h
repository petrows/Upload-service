#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <vector>
#include "log.h"

std::string strMd5(std::string &in);
std::vector<std::string> strExplode(std::string &s, const char *delm, size_t max = 0);
std::string strLower (std::string &s);
std::string strUrlDecode (std::string &s);
std::string strLtrim(const std::string &sIn, const char *search = NULL);
std::string strRtrim(const std::string &sIn, const char *search = NULL);
std::string strTrim(const std::string &sIn, const char *search = NULL);

#endif // COMMON_H
