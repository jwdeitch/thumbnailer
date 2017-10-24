#ifndef THUMBNAILER_DOWNLOADER_H
#define THUMBNAILER_DOWNLOADER_H

#include <string>
#include <curl/curl.h>
#include <curl/easy.h>
#include <curl/curlbuild.h>

using namespace std;

class Downloader {
	static string Download(const string &remote_path);
private:
	static size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream);
};


#endif //THUMBNAILER_DOWNLOADER_H
