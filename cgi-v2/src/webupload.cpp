#include "webupload.h"
#include <iostream>

using namespace std;

WebUpload::WebUpload() {}

void WebUpload::handleRequest() {
	cout << "Cookie: " << cookie["PHPSESSID"] << endl;
	cout << "Get: " << get["api"] << endl;
}
