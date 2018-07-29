#pragma once
#include"public_header.h"

//存储格式:"     username1,password1,identity1;username2,password2,identity2; "
//即: 逗号分隔单个用户信息，分号分隔各用户

class User {
	std::string username, password;
	bool is_admin;
	
public:
	std::unordered_map<std::string, int>owned_stocks;
	float balance;
	User() {}
	User(std::string u, std::string p, bool id) :username(u), password(p), is_admin(id) {}
	bool checkPwd(std::string p);
	bool editPwd(std::string p);

	bool buy(std::string id, int amount);
	bool sell(std::string id, int amount);
	//*************管理员操作****************
	bool addStock(std::string id, std::string name, float init_price, int amount);
	bool editStock(std::string id, std::string new_name, std::string new_id);
	bool toggleStock(std::string id);
	//*****************************************

	std::string toString();
	~User() {}
};
