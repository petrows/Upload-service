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
#include <sys/stat.h>

using namespace std;

#define BUFF_SIZE 1*1024*1024

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


class download
{
public:
	string work_dir;
	
	map <string, string> cookie;
	map <string, string> get;
	string ip;
	
	string 	file_code;
	string 	file_name;
	string	content_type;
	string	file_dcode;
	string	file_num;
	unsigned long long	file_size;
	bool	force;
	string	file_path;
	
	void init ()
	{
		// cout << "Connection: close\r\n";
		// cout << "\r\n";
		
		//cout << "Status: 206 Partial Content" << "\r\n";
		//cout << "Content-Range: bytes 2-10/500" << "\r\n";
		//cout << "\r\n";
		
		// return;

		char buf[1024];
		
		this->init_request();
		this->ip.append(getenv("REMOTE_ADDR"));
		
		this->file_code 	= this->get["code"];
		this->file_name 	= this->get["name"];
		this->force			= this->get["force"] == string("1");
		this->content_type 	= "application/x-force-download";
		
		sprintf(buf,"%i",atoi(this->get["num"].c_str()));
		this->file_num	 	= buf;
		
		// Check file code
		for (int x=0; x<this->file_code.length(); x++)
		{
			if ((this->file_code[x] >= 'a' && this->file_code[x] <= 'f') || (this->file_code[x] >= '0' && this->file_code[x] <= '9'))
			{
				
			} else {
				this->file_code[x] = '0';
			}
		}
		
		if (this->file_code.length() != 32 || this->file_name.length() < 3)
		{
			this->http_404();
			return;
		}
		
		this->file_path = this->work_dir + string("/d/") + this->file_code.substr(0,2) + string("/") + this->file_code.substr(2,this->file_code.length()-2) + string("/");
		
		// Check file info
		if (!this->init_info())
		{
			this->http_404();
			return;
		}
		
		// Check Download-code
		if (this->file_dcode != this->get["dcode"])
		{
			this->http_404();
			return;
		}
		
		// Prolong file?
		string lastt_file = this->file_path + this->file_num + string(".dt");
		FILE * tf = fopen64 (lastt_file.c_str(),"w");
		if (tf)
		{
			fwrite("a",1,1,tf);
			fclose(tf);
		}
		chmod (lastt_file.c_str(),0777);
		
		// Okay, seems to be all Okay
		string data_path = this->file_path + this->file_num + string(".dat");
		FILE * f = fopen64 (data_path.c_str(),"r");
		if (!f)
		{
			this->http_404();
			return;
		}
		
		cout << "Content-Length: " << this->file_size << "\r\n";
		cout << "Content-Type: " << this->content_type << "\r\n";
		cout << "\r\n";
		
		char f_buf[BUFF_SIZE];
		int rs = 0;
		while (!feof(f))
		{
			rs = fread(f_buf,1,BUFF_SIZE,f);
			fwrite(f_buf,1,rs,stdout);
		}
		fclose(f);
		
		// cout << "Code out: " << this->file_code << endl;
	}
	void init_request ()
	{
		// Parse GET
		if (getenv("QUERY_STRING"))
		{
			vector<string> d1 = str_explode(getenv("QUERY_STRING"),"&");
			for (int x=0; x<d1.size(); x++)
			{
				vector<string> d2 = str_explode(d1[x],"=",2);
				if (d2.size() == 2)
				{
					this->get[d2[0]] = url_decode(d2[1]);
					// cout << "GET: " << d2[0] << " = " << d2[1] << endl;
				}
			}
		}
		// Parse cookies
		if (getenv("HTTP_COOKIE"))
		{
			vector<string> d1 = str_explode(getenv("HTTP_COOKIE"),"; ");
			for (int x=0; x<d1.size(); x++)
			{
				vector<string> d2 = str_explode(d1[x],"=",2);
				if (d2.size() == 2)
					this->cookie[d2[0]] = url_decode(d2[1]);
			}
		}
	}
        
	bool init_info ()
	{
		string info_path = this->file_path + this->file_num + string(".inf");
		string info_data;

		FILE * f = fopen (info_path.c_str(),"r");
		if (!f)
			return false;

		char buf[1024];
		while (!feof(f))
		{
			fgets(buf,1024,f);
			info_data.append(buf);
			// cout << "Info: " << buf << endl;
		}
		fclose(f);

		vector<string> info_s = str_explode(info_data,"\n");
		if (info_s.size() < 5)
			return false;

		this->file_size = atoll(info_s[3].c_str());
		this->file_dcode = info_s[4];
		
		if (!this->force)
			this->content_type = info_s[1];

		return true;
	}
	
	void http_404 ()
	{
		cout << "Status: 404 Not Found" << "\r\n";
		cout << "Content-Type: text/html" << "\r\n";
		cout << "\r\n";

		cout << "<html><head><title>404 - Not Found</title></head>" << endl;
		cout << "<body>" << endl;
		cout << "<h3>404 - Document Not Found</h3>";
		cout << "<p>Sorry, we cannot find document you requested</p>";
		cout << "</body>";
		cout << "<?html>";
	}
	
};

int main (int argc, char ** argv)
{
	download d;
	d.work_dir = dirname(argv[0]);
	d.init();
	return 0;
}