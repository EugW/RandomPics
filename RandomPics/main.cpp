#include "RandomPics.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    RandomPics w;
    w.show();
    return a.exec();
}
