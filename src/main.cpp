#include <iostream>
#include <restd.h>
#include <thread>
#include "Download.h"
#include "message_parser.h"
#include "videothumbnailer.h"
#include "filmstripfilter.h"

using namespace ffmpegthumbnailer;

class router : public restd::http_controller {

protected:
	restd::json NotFound = {
			{"error", "not found"}
	};

public:

	// GET /
	void index(restd::http_request &req, restd::http_response &resp) {
		resp.json({"msg", "Thumbnailer API index"});
	}

	// POST /video
	void video(restd::http_request &req, restd::http_response &resp) {

		bool filmStripOverlay = false;
		bool preferEmbeddedMetadata = false;
		string seekTime;
		string inputFile;
		string outputFile;
		string imageFormat;

		restd::log(restd::DEBUG, "Incoming Request: %s", req.body.c_str());

		auto payload = restd::json::parse(req.body.c_str());

		auto path = payload["path"].get<string>();

		restd::log(restd::DEBUG, "Downloading: %s", path.c_str());
		auto working_path = Download::Http(path);

		restd::log(restd::DEBUG, "Thumbnailing: %s", path.c_str());
		ffmpegthumbnailer::VideoThumbnailer videoThumbnailer(0,
															 true, //workaround issues
															 true, //maintain aspect rat.
															 8, //img quality
															 false); //smart frame det.;

		ThumbnailerImageType imageType = Png;

		videoThumbnailer.setThumbnailSize("128"); // thumbnail size
		videoThumbnailer.setLogCallback([](ThumbnailerLogLevel lvl, const std::string &msg) {
			if (lvl == ThumbnailerLogLevelInfo)
				std::cout << msg << std::endl;
			else
				std::cerr << msg << std::endl;
		});

		restd::log(restd::DEBUG, "Finished: %s", path.c_str());

		FilmStripFilter *filmStripFilter = nullptr;

		if (filmStripOverlay) {
			filmStripFilter = new FilmStripFilter();
			videoThumbnailer.addFilter(filmStripFilter);
		}

		videoThumbnailer.setPreferEmbeddedMetadata(preferEmbeddedMetadata);

		restd::log(restd::DEBUG, "working path: %s", working_path.c_str());
		int seekPercentage = 0;
		while (seekPercentage != 100) {
			if (!seekTime.empty()) {
				videoThumbnailer.setSeekTime(seekTime);
			} else {
				videoThumbnailer.setSeekPercentage(seekPercentage);
			}
			string thumb_out_name = "OUTPUT-" + to_string(seekPercentage) + ".png";
			videoThumbnailer.generateThumbnail(working_path,
											   imageType,
											   thumb_out_name);
			restd::log(restd::DEBUG, "Thumbnail written: %s", thumb_out_name.c_str());
			seekPercentage = seekPercentage + 10;
		}

		delete filmStripFilter;

	};
};

int main() {
	std::string address = "127.0.0.1";
	unsigned short port = 8080;
	restd::log_level_t llevel = restd::DEBUG;
	int c;

	try {
		restd::set_log_level(llevel);
		restd::set_log_fp(stdout);
		restd::set_log_dateformat("%c");

		restd::crash_manager::init();

		restd::http_server server(address.c_str(), port, std::thread::hardware_concurrency());

		router hw;

		RESTD_ROUTE(server, restd::GET, "/", hw, router::index);
		RESTD_ROUTE(server, restd::POST, "/video", hw, router::video);

		server.start();
	}
	catch (const exception &e) {
		restd::log(restd::CRITICAL, "Exception: %s", e.what());
	}

	return 0;
};