#ifndef THUMBNAILER_DOWNLOADER_H
#define THUMBNAILER_DOWNLOADER_H

#include <string>
#include <curl/curl.h>
#include <restd.h>
#include <curl/easy.h>
#include <curl/curlbuild.h>
#include "message_parser.h"

using namespace std;

class Download {
public:
	static void Http(Message *msg);
};


#endif //THUMBNAILER_DOWNLOADER_H
