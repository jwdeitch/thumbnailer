#include "string_utils.h"
#include <ctime>

// https://stackoverflow.com/a/12468109/4603498
string random_str(size_t length) {
	auto randchar = []() -> char {
		const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ123456789";
		const size_t max_index = (sizeof(charset) - 1);
		return charset[random() % max_index];
	};
	std::string str(length, 0);
	std::generate_n(str.begin(), length, randchar);
	return str;
}

string get_file_extension(string const &subject) {
	return subject.substr(subject.find_last_of("."));
}