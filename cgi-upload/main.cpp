 
#define _FILE_OFFSET_BITS 64
#define FOPEN64 1
#define __USE_LARGEFILE64 1
#define _LARGEFILE_SOURCE
#define _XOPEN_SOURCE 600
#define __STDC_LIMIT_MACROS

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <stdint.h>
#include <sys/stat.h>

#include "md5.h"

using namespace std;

#define BUFF_SIZE 1*1024*1024

string str_md5(string in)
{
	MD5 context;
	context.update ((unsigned char*)in.c_str(), in.length());
	context.finalize ();
	return context.hex_digest();
}

vector<string> str_explode(string s, string delm, size_t max = 0)
{
	vector<string> ret;
	string curr = "";
	size_t	pos1 = 0;

	size_t	ssize = delm.size();

	for (unsigned int x=0; x<s.size(); x++)
	{
		// Search next delimeter
		pos1 = s.find(delm,x);

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
		ret.push_back(s.substr(x,pos1-x));
		x=(pos1 + ssize)-1;
	}
	if (string::npos != pos1) ret.push_back(""); // Delimeter was at the end, add real empty line

	return ret;
}

string str_lower (string s)
{
	char * retbuf = new char[s.size()+1];
	retbuf[0] = 0;
	string ret;
	for (unsigned int x=0; x<s.size(); x++)
	{
		if (s[x] >= 65 && s[x] <= 90)
			retbuf[x] = s[x] + 32;
		else
			retbuf[x] = s[x];
		retbuf[x+1] = 0;
	}
	ret = retbuf;
	delete[] retbuf;
	return ret;
}

string url_decode (string s)
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


class upload
{
public:
	string work_dir;
	
	map <string, string> cookie;
	map <string, string> get;
	string ip;
	string lk;
	
	bool   is_api;
	unsigned int api_up_id;
	
	unsigned int 	file_id;
	unsigned long long	file_size;
	unsigned long long 	file_max;
	
	char tmp_file[1024];
	
	void init ()
	{
		cout << "Connection: close\r\n";
		// cout << "\r\n";
		
		this->is_api = false;
		
		this->init_request();
		this->ip.append(getenv("REMOTE_ADDR"));
		this->lk.append(str_md5(this->cookie["auth"]));
		
		if (this->get["api"] == "1")
			this->is_api = true;
		
		if (!this->check_sid())
		{
			if (is_api)
				this->http_xml_ans("<error code=\"SESSION_ERROR\">Session error: restart your programm.</error>");
			else
				this->http_ans("{error:'Auth error'}");
			return;
		}
		
		this->file_size = 0;
		if (getenv("CONTENT_LENGTH"))
			this->file_size = strtoull(getenv("CONTENT_LENGTH"),NULL,10);
		
		//cout << "Size: " << this->file_size << endl;			
		//printf("Size: %llu\n", this->file_size);
		
		if (!this->file_size)
		{
			this->http_ans("{error:'Invalid request: content-length header missing'}");
			return;
		}
		if (this->file_max && this->file_size > this->file_max)
		{
			this->http_ans("{error:'File is too large!'}");
			return;
		}
		
		this->file_id = atoi(this->get["id"].c_str());
		if (this->is_api)
			this->api_up_id = atoi(this->get["upid"].c_str());
		
		// Okay, upload The File
		string file_id = str_md5(this->get["s"]);
		if (this->is_api)
		{
			char file_id_buf[1024];
			sprintf(file_id_buf,"%s%d",this->get["s"].c_str(),this->api_up_id);
			file_id = str_md5(file_id_buf);
		}
		sprintf(tmp_file,"%s/tmp/upload/%s-%i",this->work_dir.c_str(),file_id.c_str(),this->file_id);
		FILE *upl_file = fopen64(tmp_file,"w");
		if (!upl_file)
		{
			// Internal error!
			this->http_ans("{error:'Internal error! Enable to write TMP file...'}");
			return;
		}
		
		// Set perms
		chmod (tmp_file,0666);
		
		// Read file data
		char f_buf[BUFF_SIZE];
		unsigned long long read_n = 0;
		unsigned long long read_s = 0;
		while (true)
		{
			read_s = fread(f_buf,1,BUFF_SIZE,stdin);
			if (read_s <= 0) break;

			read_n += read_s;
			fwrite(f_buf,read_s,1,upl_file);
			if (read_n >= this->file_size)
				break; // All done...
		
			
		}
		fclose (upl_file);

		// On done - redirect to the file post-process
		if (this->is_api)
		{
			cout << "Location: /api/upload-done/?" << getenv("QUERY_STRING") << "\r\n";
		} else {
			cout << "Location: /upload/complete/?" << getenv("QUERY_STRING") << "\r\n";
		}
		cout << "\r\n";
	}
	void init_request ()
	{
		// Parse GET
		if (getenv("QUERY_STRING"))
		{
			vector<string> d1 = str_explode(getenv("QUERY_STRING"),"&");
			for (unsigned int x=0; x<d1.size(); x++)
			{
				vector<string> d2 = str_explode(d1[x],"=",2);
				if (d2.size() == 2)
					this->get[d2[0]] = url_decode(d2[1]);
			}
		}
		// Parse cookies
		if (getenv("HTTP_COOKIE"))
		{
			vector<string> d1 = str_explode(getenv("HTTP_COOKIE"),"; ");
			for (unsigned int x=0; x<d1.size(); x++)
			{
				vector<string> d2 = str_explode(d1[x],"=",2);
				if (d2.size() == 2)
					this->cookie[d2[0]] = url_decode(d2[1]);
			}
		}
	}
	bool check_sid ()
	{
		// Check user auth...
		if (!this->get["s"].length())
			return false;
		
		// Check file
		char fname[1024];
		string dir_name = "sid";
		if (this->is_api)
			dir_name = "sid_api";
		
		sprintf(fname,"%s/tmp/%s/%s",this->work_dir.c_str(),dir_name.c_str(),str_md5(this->get["s"]).c_str());
		
		// Try to read file
		FILE *f = fopen(fname,"r");
		if (!f)
			return false;
		
		char f_buf[1024];
		fgets(f_buf,1024,f);
		fclose(f);
		
		vector<string> s_data = str_explode(f_buf,":");
		if (s_data.size() < 5) return false; // Bad format
		
/*
		for (int x=0; x<s_data.size(); x++)
			cout << x << " : " << s_data[x] << endl;
		cout << "----------" << endl;
		cout << this->get["s"] << endl;
		cout << this->lk << endl;
*/

		// Check auth vars...
		if (
				s_data[1] != this->ip ||
				s_data[2] != this->get["s"] ||
				s_data[3] != this->lk
		) {
			// Error at auth!
			return false;
		}
		
		this->file_max = strtoull(s_data[4].c_str(),NULL,10);
		
		return true;
	}
	void http_ans (string out)
	{
		//cout << "HTTP/1.0 200 OK\r\n";
		cout << "Content-type: text/plain\r\n";
		cout << "\r\n";
		cout << out;
	}
	void http_xml_ans (string out)
	{
		cout << "Content-type: text/xml\r\n";
		cout << "\r\n";
		cout << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
		cout << "<api>\n";
		cout << out;
		cout << "</api>\n\n";
	}
};

int main (int argc, char ** argv)
{
	upload u;
	u.work_dir = dirname(argv[0]);
	u.init();
	return 0;
}
