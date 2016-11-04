
#include "cgi.h"

int main(int argc, char **argv) {
	CGI cgi;
	int ret = 0;
	ret = cgi.run(argc, argv);

	return ret;
}
