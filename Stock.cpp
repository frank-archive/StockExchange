#include "Stock.h"
using namespace std;

float Stock::getCurrentPrice() {
	return price_log[price_log.size() - 1];
}

float Stock::getHistoryPrice(int days_cnt) {
	return price_log[price_log.size() - 1 - days_cnt];
}

float Stock::getRise() {
	return (getCurrentPrice() - getHistoryPrice(1)) / getHistoryPrice(1);
}

void Stock::changeIdName(string i, string n) {
	id = i, name = n;
}

string Stock::toString() {
	string ret = id + ',' + name + ',' + to_string(remaining) + ',' + char('0' + stopped);
	for (int i = 0; i < price_log.size(); i++)
		ret += ',' + to_string(price_log[i]);
	return ret + ';';
}
