#include "Download.h"

string Download::Http(const string &remote_path) {
	CURL *curl;
	FILE *fp;
	string outfilename = "/tmp/" + random_str(10) + get_file_extension(remote_path);
	curl = curl_easy_init();
	if (curl) {
		fp = fopen(outfilename.c_str(), "wb");
		curl_easy_setopt(curl, CURLOPT_URL, remote_path.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, fwrite);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
		if (curl_easy_perform(curl) != CURLE_OK) {
			throw exception();
		}
		curl_easy_cleanup(curl);
		fclose(fp);
	}
	return outfilename;
}