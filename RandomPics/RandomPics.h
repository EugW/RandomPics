#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_RandomPics.h"

class RandomPics : public QMainWindow
{
    Q_OBJECT

public:
    RandomPics(QWidget *parent = Q_NULLPTR);
    void beginFetch(std::string src_url, std::string url_key);
private slots:
    void handleButtonDog();
    void handleButtonCat();
    void handleButtonBW();
private:
    Ui::RandomPicsClass ui;
};
