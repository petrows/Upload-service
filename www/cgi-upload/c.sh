#!/bin/bash

g++ -Wall main.cpp md5.cpp -o ../upload.cgi

echo -e "\033[0;31m  COMPILE DONE \033[m";

echo "";

declare -x CONTENT_LENGTH="1005001234567890"
declare -x REMOTE_ADDR="192.168.0.201"
declare -x HTTP_COOKIE="auth=MTpRcW9GaUZlbVY5SXlIVWRIMVdsbU5wR0hveHM9; usid=e8a3f1ef6b6a0268cf10fc9a8e9af837; PHPSESSID=2br1186jd00usiafcr4hf4mj42"
declare -x QUERY_STRING="s=50e869ba68e8adbdb30acbc01a892e2c&qqfile=-436597_182253821.jpg&id=1"
declare -x HTTP_USER_AGENT="Mozilla/5.0 (X11; Linux i686; rv:2.0) Gecko/20100101 Firefox/4.0"
						   
cat main.cpp | ../upload.cgi
