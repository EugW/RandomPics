#include "RandomPics.h"
#include "curl/curl.h"
#include "curl_utils.h"
#include "nlohmann/json.hpp"
#include "ThreadParams.h"
#include <windows.h>

RandomPics::RandomPics(QWidget *parent) : QMainWindow(parent) {
    ui.setupUi(this);
    this->setFixedSize(this->geometry().width(), this->geometry().height());
    connect(ui.pushButtonFetchDog, SIGNAL(clicked()), this, SLOT(handleButtonDog()));
    connect(ui.pushButtonFetchCat, SIGNAL(clicked()), this, SLOT(handleButtonCat()));
    connect(ui.pushButtonBW, SIGNAL(clicked()), this, SLOT(handleButtonBW()));
}

DWORD WINAPI ParallelDownload(LPVOID lpParams) {
    auto tParams = (ThreadParams*) lpParams;
    auto parsed = nlohmann::json::parse(stringRequest(tParams->src_url));
    auto url = parsed[tParams->url_key].get<std::string>();
    std::string ext;
    for (int i = url.length() - 1; i > 0; i--) {
        if (url[i] == '.') {
            break;
        }
        ext += tolower(url[i]);
    }
    if (ext != "4pm") {
        auto image = fileRequest(url, ext, tParams->prog, tParams->progb, tParams->proge);
        tParams->holder->setPixmap(QPixmap::fromImage(image).scaled(500, 500, Qt::KeepAspectRatio));
    }
    else tParams->holder->setText("Random dog API gave us .mp4 and we don't know what to do with it... yet");
    return 0;
}

void RandomPics::beginFetch(std::string src_url, std::string url_key) {
    ui.label->setPixmap(QPixmap());
    CreateThread(NULL, 0, ParallelDownload, new ThreadParams(src_url, url_key, ui.label, ui.labelProgress, ui.label_2, ui.label_3), 0, NULL);
}

void RandomPics::handleButtonDog() {
    beginFetch("https://random.dog/woof.json", "url");
}  

void RandomPics::handleButtonCat() {
    beginFetch("https://aws.random.cat/meow", "file");
}

void RandomPics::handleButtonBW() {
    ui.label->setPixmap(QPixmap::fromImage(ui.label->pixmap().toImage().convertToFormat(QImage::Format_Grayscale16)));
}

