#pragma once
#include"public_header.h"
struct StockPool {
	std::unordered_map<std::string, struct Stock>pool;
	FILE *stock_info, *buffer;
	StockPool();
	void readFromString(std::string &temp);
	void writeBuffer(Stock);
	void readBuffer();
	void fullUpdate();
	~StockPool();
};