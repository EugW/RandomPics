#include <string>
#include <qlabel.h>

#pragma once
class ThreadParams {
public:
	ThreadParams(std::string url, std::string key, QLabel* lbl, QLabel* prg, QLabel* prgb, QLabel* prge);
	std::string src_url;
	std::string url_key;
	QLabel* holder;
	QLabel* prog;
	QLabel* progb;
	QLabel* proge;
};

