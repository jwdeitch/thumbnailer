#ifndef THUMBNAILER_MESSAGE_PARSER_H
#define THUMBNAILER_MESSAGE_PARSER_H

#include <string>
#include <sys/stat.h>
#include <stdexcept>
#include "string_utils.h"

using namespace std;

struct Message {
public:
	Message() : id(random_str(10)) {
		if (mkdir(this->working_dir().c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0) {
			throw runtime_error(
					"Cannot create directory: " + this->working_dir() + " for the reason: " + strerror(errno)
			);
		}
	};

	string id;

	const string working_directory = "/tmp/";

	string remote_path;

	enum Type {
		Video,
		Audio
	};

	string local_path;

	string working_dir() {
		return working_directory + id;
	};

	string getThumbnailFileName(const int &thumb_number) {
		return this->working_dir() + "/thumb-" + to_string(thumb_number) + ".png";
	};

	string getInputDocumentFilePath() {
		return this->working_dir() + "/input" + get_file_extension(remote_path);
	};

	void writeToS3() {

	}

};


#endif //THUMBNAILER_MESSAGE_PARSER_H
