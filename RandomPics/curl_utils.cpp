#include "curl_utils.h"
#include "curl/curl.h"
#include "qbytearray.h"

size_t stringWriteFunction(void* ptr, size_t size, size_t nmemb, std::string* data) {
    data->append((char*)ptr, size * nmemb);
    return size * nmemb;
}

std::string stringRequest(std::string url) {
    auto handler = curl_easy_init();
    curl_easy_setopt(handler, CURLOPT_URL, url.c_str());
    curl_easy_setopt(handler, CURLOPT_WRITEFUNCTION, stringWriteFunction);
    std::string response;
    curl_easy_setopt(handler, CURLOPT_WRITEDATA, &response);
    curl_easy_perform(handler);
    curl_easy_cleanup(handler);
    return response;
}

QImage fileRequest(std::string url, std::string ext) {
    auto handler = curl_easy_init();
    curl_easy_setopt(handler, CURLOPT_URL, url.c_str());
    curl_easy_setopt(handler, CURLOPT_WRITEFUNCTION, stringWriteFunction);
    std::string data;
    curl_easy_setopt(handler, CURLOPT_WRITEDATA, &data);
    curl_easy_perform(handler);
    curl_easy_cleanup(handler);
    return QImage::fromData(QByteArray::fromStdString(data), ext.c_str());
}