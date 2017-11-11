#ifndef THUMBNAILER_MESSAGE_PARSER_H
#define THUMBNAILER_MESSAGE_PARSER_H

#include <string>
#include <restd.h>

using namespace std;

struct message {
	string path;
	struct meta {
		string callback;
		restd::json::object_t passThrough;
	};
};


#endif //THUMBNAILER_MESSAGE_PARSER_H
