#!/bin/bash

g++ main.cpp -o ../download.cgi

echo -e "\033[0;31m  COMPILE DONE \033[m";

echo "";

declare -x CONTENT_LENGTH="1024"
declare -x REMOTE_ADDR="192.168.0.201"
declare -x QUERY_STRING="code=b1b84832e1653e3ec46b1a42e767188d&num=0&dcode=5b404a81&name=file.ass"
declare -x HTTP_USER_AGENT="Mozilla/5.0 (X11; Linux i686; rv:2.0) Gecko/20100101 Firefox/4.0"
						   
../download.cgi
