#include "ThreadParams.h"

ThreadParams::ThreadParams(std::string url, std::string key, QLabel* lbl, QLabel* prg, QLabel* prgb, QLabel* prge, bool* isBusy) {
	this->src_url = url;
	this->url_key = key;
	this->holder = lbl;
	this->prog = prg;
	this->progb = prgb;
	this->proge = prge;
	this->isBusy = isBusy;
}
