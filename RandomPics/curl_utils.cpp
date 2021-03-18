#include "curl_utils.h"
#include "curl/curl.h"
#include "qbytearray.h"

QLabel* prog;

size_t stringWriteFunction(void* ptr, size_t size, size_t nmemb, std::string* data) {
    data->append((char*)ptr, size * nmemb);
    return size * nmemb;
}

int progress_callback(void* clientp, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow) {
    if (dlnow != 0 && dltotal != 0) {
        std::string res;
        res += " ";
        for (int i = 0; i < ((double)dlnow / ((double)dltotal)) * 57; i++) {
            res += "\\ ";
        }
        res += std::to_string((int)((double)dlnow / ((double)dltotal) * 100));
        res += "%";
        prog->setText(QString::fromStdString(res));
    }
    return 0;
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

QImage fileRequest(std::string url, std::string ext, QLabel* prg, QLabel* prgb, QLabel* prge) {
    prog = prg;
    prgb->setText("[");
    prge->setText("     ]");
    auto handler = curl_easy_init();
    curl_easy_setopt(handler, CURLOPT_URL, url.c_str());
    curl_easy_setopt(handler, CURLOPT_WRITEFUNCTION, stringWriteFunction);
    curl_easy_setopt(handler, CURLOPT_XFERINFOFUNCTION, progress_callback);
    curl_easy_setopt(handler, CURLOPT_NOPROGRESS, 0L);
    std::string data;
    curl_easy_setopt(handler, CURLOPT_WRITEDATA, &data);
    curl_easy_perform(handler);
    curl_easy_cleanup(handler);
    prog->setText("");
    prgb->setText("");
    prge->setText("");
    return QImage::fromData(QByteArray::fromStdString(data), ext.c_str());
}
