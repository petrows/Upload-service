
#include "cgi.h"

int main (int argc, char ** argv)
{
	CGI cgi(argc, argv);
	int ret = 0;
	ret = cgi.run();

	return ret;
}
