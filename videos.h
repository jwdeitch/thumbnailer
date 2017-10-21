#ifndef THUMBNAILER_VIDEOS_H
#define THUMBNAILER_VIDEOS_H

#include "videothumbnailer.h"
#include "stringoperations.h"
#include "filmstripfilter.h"
#include <vector>
#include <string>

using namespace std;
using namespace ffmpegthumbnailer;

class Videos {
	vector<string> makeThumbnails();
};


#endif //THUMBNAILER_VIDEOS_H
