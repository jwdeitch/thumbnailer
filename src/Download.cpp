#include "Download.h"

void Download::Http(Message *msg) {
	printf("hello");
	restd::log(restd::DEBUG, "Downloading: %s", *msg->remote_path.c_str());
	CURL *curl;
	FILE *fp;
	curl = curl_easy_init();
	if (curl) {
		fp = fopen(msg->getInputDocumentFilePath().c_str(), "wb");
		curl_easy_setopt(curl, CURLOPT_URL, *msg->remote_path.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, fwrite);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
		if (curl_easy_perform(curl) != CURLE_OK) {
			throw exception();
		}
		curl_easy_cleanup(curl);
		fclose(fp);
	}
}