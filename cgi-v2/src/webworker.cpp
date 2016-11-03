#include "webworker.h"
#include "common.h"

using namespace std;

WebWorker::WebWorker() {}

bool WebWorker::init(FCGX_Request *requestIn) {
  request = requestIn;

  ip = FCGX_GetParam("REMOTE_ADDR", request->envp);

  // Parse cookies
  if (FCGX_GetParam("HTTP_COOKIE", request->envp)) {
	string cookiesString = FCGX_GetParam("HTTP_COOKIE", request->envp);
	vector<string> d1 = strExplode(cookiesString, "; ");
	for (unsigned int x = 0; x < d1.size(); x++) {
	  vector<string> d2 = strExplode(d1[x], "=", 2);
	  if (d2.size() == 2)
		cookie[d2[0]] = strUrlDecode(d2[1]);
	}
  }

  // Parse GET
  if (FCGX_GetParam("QUERY_STRING", request->envp)) {
	string getString = FCGX_GetParam("QUERY_STRING", request->envp);
	vector<string> d1 = strExplode(getString, "&");
	for (unsigned int x = 0; x < d1.size(); x++) {
	  vector<string> d2 = strExplode(d1[x], "=", 2);
	  if (d2.size() == 2)
		get[d2[0]] = strUrlDecode(d2[1]);
	}
  }

  return true;
}
