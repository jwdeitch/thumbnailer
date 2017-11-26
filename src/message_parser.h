#ifndef THUMBNAILER_MESSAGE_PARSER_H
#define THUMBNAILER_MESSAGE_PARSER_H

#include <string>
#include "string_utils.h"

using namespace std;

struct Message {
public:
	Message() : id(random_str(10)) {};
	string id;
	const string working_directory = "/tmp/";
	
	string remote_path;
	enum Type {
		Video,
		Audio
	};
	string local_path;

	string getThumbnailFileName(const int &thumb_number) {
		return working_directory + id + "/thumb-" + to_string(thumb_number) + ".png";
	};

	string getInputDocumentFilePath() {
		return working_directory + id + "/input" + get_file_extension(remote_path);
	}
};


#endif //THUMBNAILER_MESSAGE_PARSER_H
