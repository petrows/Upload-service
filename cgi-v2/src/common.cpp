#include "common.h"
#include "md5.h"

#include <cstring>
#include <algorithm>
#include <functional>

using namespace std;

string strMd5(string &in)
{
	MD5 context;
	context.update ((unsigned char*)in.c_str(), in.length());
	context.finalize ();
	return std::string(context.hex_digest());
}


vector<string> strExplode(string &s, const char *delm, size_t max)
{
	vector<string> ret;
	string curr = "";
	size_t	pos1 = 0;

	size_t ssize = ::strlen(delm);

	for (unsigned int x=0; x<s.size(); x++)
	{
		// Search next delimeter
		pos1 = s.find(delm, x);

		if (max && ret.size() >= max - 1)
			pos1 = string::npos;

		if (string::npos == pos1)
		{
			// No ending...
			// Adding whole other string to the Array
			ret.push_back(s.substr(x));
			break; // All done
		}
		// Found some...
		ret.push_back(s.substr(x, pos1-x));
		x = (pos1 + ssize) - 1;
	}
	if (string::npos != pos1) ret.push_back(""); // Delimeter was at the end, add real empty line

	return ret;
}

string strLower(string &s)
{
	string out(s.size(), 0);
	std::transform(s.begin(), s.end(), out.begin(), ::tolower);
	return out;
}

string strUrlDecode(string &s)
{
	string ret;
	char * retbuf = new char[s.size()+1]; retbuf[0] = 0;
	for (unsigned int x=0,n=0; x<s.size(); x++,n++)
	{
		if (s[x] == '%' && x<=(s.size()-2))
		{
			int ch = 0;
			char sbuf[3];
			sbuf[0] = s[x+1];
			sbuf[1] = s[x+2];
			sbuf[2] = 0;
			sscanf(sbuf,"%X", &ch);
			retbuf[n] = ch;
			retbuf[n+1] = 0;
			x = x+2;
			continue;
		} else if (s[x] == '+') {
			retbuf[n] = ' ';
		} else {
			retbuf[n] = s[x];
		}
		retbuf[n+1] = 0;
	}
	ret = retbuf;
	delete[] retbuf;
	return ret;
}

string strLtrim(const string &sIn, const char *search)
{
	string s = sIn;
	if (NULL == search) {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
	} else {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), [&search] (const char &c) { const char *z = search; while (*z) { if (*z == c) return false; z++; } return true; } ));
	}

	return s;
}

string strRtrim(const string &sIn, const char * search)
{
	string s = sIn;
	if (NULL == search) {
		s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	} else {
		s.erase(std::find_if(s.rbegin(), s.rend(), [&search] (const char &c) { const char *z = search; while (*z) { if (*z == c) return false; z++; } return true; } ).base(), s.end());
	}

	return s;
}

string strTrim(const string &sIn, const char * search)
{
	return strLtrim(strRtrim(sIn, search), search);
}
