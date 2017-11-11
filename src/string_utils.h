#ifndef THUMBNAILER_STRING_UTILS_H
#define THUMBNAILER_STRING_UTILS_H

#include <string>

using namespace std;

// https://stackoverflow.com/a/21842943/4603498
string random_str(size_t length) {
	const char *charmap = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ123456789";
	const size_t charmapLength = strlen(charmap);
	auto generator = [&]() { return charmap[random() % charmapLength]; };
	string result;
	result.reserve(length);
	generate_n(back_inserter(result), length, generator);
	return result;
}

string get_file_extension(string const &subject) {
	return subject.substr(subject.find_last_of("."));
}

#endif //THUMBNAILER_STRING_UTILS_H
