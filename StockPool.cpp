#define _CRT_SECURE_NO_WARNINGS
#include "StockPool.h"
#include"Stock.h"

using namespace std;
StockPool::StockPool() {
	stock_info = fopen("stock.data", "r+");
	buffer = fopen("Sbuf", "w+");

	string temp = readAll(stock_info);
	temp = base64_decode(temp);
	readFromString(temp);
}

void StockPool::readFromString(string & temp) {
	vector<string> all_user = parse(';', temp);
	for (int i = 0; i < all_user.size(); i++) {
		vector<string> this_stock = parse(',', all_user[i]);
		//根据格式，此处this_user[0]为用户名，this_user[1]为密码
		// if(this_user[2].size()>1)throw exception("input error!");
		vector<float>temp;
		for (int i = 4; i < this_stock.size(); i++)temp.push_back(atof(this_stock[i].c_str()));
		pool[this_stock[0]] =
			Stock(this_stock[0], this_stock[1], atoi(this_stock[2].c_str()), temp);
	}
}

void StockPool::writeBuffer(Stock a) {
	fprintf(buffer, a.toString().c_str());
}

void StockPool::readBuffer() {
	string temp = readAll(buffer);
	readFromString(temp);
}
void StockPool::fullUpdate() {
	string temp;
	for (unordered_map<string, Stock>::iterator i = pool.begin();
		i != pool.end(); i++)  //遍历内存中股票信息
		temp += i->second.toString();
	temp = base64_encode(temp.c_str(), temp.size());
	fclose(stock_info); stock_info = fopen("stock.data", "w");
	fprintf(stock_info, temp.c_str());//写入最终信息
	fclose(stock_info); stock_info = fopen("stock.data", "r+");
}

StockPool::~StockPool() {
	fullUpdate();

	fclose(stock_info);
	fclose(buffer);
}
