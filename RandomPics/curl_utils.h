#include <string>
#include <qimage.h>
#include <qlabel.h>

std::string stringRequest(std::string url);
QImage fileRequest(std::string url, std::string ext, QLabel* prg, QLabel* prgb, QLabel* prge);
