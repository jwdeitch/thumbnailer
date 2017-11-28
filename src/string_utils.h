#ifndef THUMBNAILER_STRING_UTILS_H
#define THUMBNAILER_STRING_UTILS_H

#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

// https://stackoverflow.com/a/21842943/4603498
string random_str(size_t length);

string get_file_extension(string const &subject);

#endif //THUMBNAILER_STRING_UTILS_H
