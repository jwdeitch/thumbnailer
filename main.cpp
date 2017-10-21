#include <iostream>
#include <restd.h>
#include <thread>

class hello_world : public restd::http_controller {
public:

	// GET /
	void index(restd::http_request &req, restd::http_response &resp) {
		std::stringstream ss;
		ss << "thumbnailer index";

		resp.html(ss.str());
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

		hello_world hw;

		RESTD_ROUTE(server, restd::GET, "/", hw, hello_world::index);

		server.start();
	}
	catch (const exception &e) {
		restd::log(restd::CRITICAL, "Exception: %s", e.what());
	}

	return 0;
}