#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_RandomPics.h"

class RandomPics : public QMainWindow
{
    Q_OBJECT

public:
    RandomPics(QWidget *parent = Q_NULLPTR);

private:
    Ui::RandomPicsClass ui;
};
