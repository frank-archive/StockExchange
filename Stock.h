#pragma once
#include "public_header.h"

//format: "id,name,float,...;"
struct Stock {
	std::string id, name; int remaining;
	bool stopped;//是否停止交易
	std::vector<float>price_log;//数组，记录了历史价格
	Stock() { stopped = 0; }
	Stock(std::string id, std::string n, int a, std::vector<float> p) :id(id), name(n), remaining(a), price_log(p) { stopped = 0; }
	float getCurrentPrice();                                                                                                           //当前价格
	float getHistoryPrice(int days_cnt);                                                                                         //返回days_cnt天前价格
	float getRise();
	void changeIdName(std::string i, std::string n);
	std::string toString();
};