#pragma once
#include"public_header.h"
//su密码:1234567890
class SuperUser {
public:
	//设置当日价格,无法修改历史价格
	bool setStockPrice(std::string id, float p);
	//注册
	class User *addUser(std::string username, std::string password, bool isAdmin);
	//设置用户余额
	bool setBalance(std::string username, float b);
	//删除用户
	bool deleteUser(std::string username);
};