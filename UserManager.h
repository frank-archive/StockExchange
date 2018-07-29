#pragma once
#include "public_header.h"
class UserManager {
	std::unordered_map<std::string, class User> pool;
	FILE *user_info, *buffer;
	void readFromString(std::string &temp);
public:
	UserManager();

	User *getUser(std::string username);
	bool addUser(std::string username, std::string password, bool isAdmin);
	bool deleteUser(std::string username);
	
	void fullUpdate();//完整更新存储文件（编码存储）
	void readBuffer();//从缓存中故障恢复
	void writeBuffer(User a);//写入缓存

	~UserManager();
};