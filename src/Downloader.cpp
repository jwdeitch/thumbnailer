#include "Downloader.h"

static size_t Downloader::write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
	size_t written;
	written = fwrite(ptr, size, nmemb, stream);
	return written;
}

static string Downloader::Download(const string &remote_path) {
	CURL *curl;
	FILE *fp;
	CURLcode res;
	char outfilename[FILENAME_MAX] = "/tmp/"; //TODO: extract file extension
	curl = curl_easy_init();
	if (curl) {
		fp = fopen(outfilename, "wb");
		curl_easy_setopt(curl, CURLOPT_URL, remote_path.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		fclose(fp);
	}
	return outfilename;
}