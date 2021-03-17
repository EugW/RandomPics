#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_RandomPics.h"

class RandomPics : public QMainWindow
{
    Q_OBJECT

public:
    RandomPics(QWidget *parent = Q_NULLPTR);
    void beginFetch(std::string src_url, std::string url_key);
    std::string src_url;
    std::string url_key;
    void setImage(QImage src);
    void setText(std::string txt);
private slots:
    void handleButtonDog();
    void handleButtonCat();
private:
    Ui::RandomPicsClass ui;
};
