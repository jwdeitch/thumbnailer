#include "Download.h"

/*

 We can use this callback if we would like to stream download progress
 back to the user.

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
	cout << "Downloading......" << endl << endl;
	return fwrite(ptr, size, nmemb, stream);
}

*/

void Download::Http(Message *msg) {
	CURL *curl;
	FILE *fp;
	curl = curl_easy_init();
	if (curl) {
		fp = fopen(msg->getInputDocumentFilePath().c_str(), "wb");
		curl_easy_setopt(curl, CURLOPT_URL, msg->remote_path.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, fwrite);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
		if (curl_easy_perform(curl) != CURLE_OK) {
			throw exception();
		}
		curl_easy_cleanup(curl);
		fclose(fp);
	}
}