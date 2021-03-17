#include "RandomPics.h"
#include "curl/curl.h"
#include "curl_utils.h"
#include "nlohmann/json.hpp"
#include <windows.h>

RandomPics::RandomPics(QWidget *parent) : QMainWindow(parent) {
    ui.setupUi(this);
    this->setFixedSize(this->geometry().width(), this->geometry().height());
    connect(ui.pushButtonFetchDog, SIGNAL(clicked()), this, SLOT(handleButtonDog()));
    connect(ui.pushButtonFetchCat, SIGNAL(clicked()), this, SLOT(handleButtonCat()));
}

DWORD WINAPI ParallelDownload(LPVOID params) {
    auto rndPcs = (RandomPics*)params;
    auto parsed = nlohmann::json::parse(stringRequest(rndPcs->src_url));
    auto url = parsed[rndPcs->url_key].get<std::string>();
    std::string ext;
    for (int i = url.length() - 1; i > 0; i--) {
        if (url[i] == '.') {
            break;
        }
        ext += tolower(url[i]);
    }
    if (ext != "4pm") {
        auto image = fileRequest(url, ext);
        rndPcs->setImage(image);
    }
    else rndPcs->setText("Random dog API gave us .mp4 and we don't know what to do with it... yet");
    return 0;
}

void RandomPics::setImage(QImage src) {
    ui.label->setPixmap(QPixmap::fromImage(src).scaled(500, 500, Qt::KeepAspectRatio));
}

void RandomPics::setText(std::string src) {
    ui.label->setText(QString::fromStdString(src));
}

void RandomPics::beginFetch(std::string src_url, std::string url_key) {
    this->src_url = src_url;
    this->url_key = url_key;
    CreateThread(NULL, 0, ParallelDownload, this, 0, NULL);
}

void RandomPics::handleButtonDog() {
    beginFetch("https://random.dog/woof.json", "url");
   
}  

void RandomPics::handleButtonCat() {
    beginFetch("https://aws.random.cat/meow", "file");
}
