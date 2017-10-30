#ifndef THUMBNAILER_DOWNLOADER_H
#define THUMBNAILER_DOWNLOADER_H

#include <string>
#include <curl/curl.h>
#include <curl/easy.h>
#include <curl/curlbuild.h>
#include "string_utils.h"

using namespace std;

class Download {
public:
	static string Http(const string &remote_path);
};


#endif //THUMBNAILER_DOWNLOADER_H
