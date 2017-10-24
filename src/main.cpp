#include <iostream>
#include <restd.h>
#include <thread>
#include <Downloader.h>

struct message {
	string path;
	struct meta {
		string callback;
		restd::json::object_t passThrough;
	};
};

class router : public restd::http_controller {

protected:
	restd::json NotFound = {
			{"error", "not found"}
	};

public:

	// GET /
	void index(restd::http_request &req, restd::http_response &resp) {
		std::stringstream ss;
		ss << "thumbnailer index";

		resp.html(ss.str());
	}

	// POST /video
	void video(restd::http_request &req, restd::http_response &resp) {
		restd::log(restd::DEBUG, "Incoming Request: %s", req.body.c_str());
		auto input_req_doc = restd::json::parse(req.body.c_str());
		message payload = input_req_doc;
		stirng working_path = Downloader::Download(payload["path"])
		restd::log(restd::DEBUG, "Incoming Request: %s", payload.path.c_str());

		resp.json(this->NotFound.dump());
	}
};

int main() {
	std::string address = "127.0.0.1";
	unsigned short port = 8080;
	restd::log_level_t llevel = restd::INFO;
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
}