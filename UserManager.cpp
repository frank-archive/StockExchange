#define _CRT_SECURE_NO_WARNINGS
#include "UserManager.h"
#include"User.h"
using namespace std;
UserManager::UserManager() {
	user_info = fopen("user.data", "r+");
	buffer = fopen("Ubuf", "w+");

	//读取以前的用户
	string temp = readAll(user_info);
	temp = base64_decode(temp);
	readFromString(temp);
}

User *UserManager::getUser(string username) {
	if (pool.find(username) != pool.end())
		return &pool[username];
	else return 0;
}

bool UserManager::addUser(string username, string password, bool isAdmin) {
	if (pool.find(username)!=pool.end())return false;//用户名被占用
	pool[username] = User(username, password, isAdmin);
	writeBuffer(pool[username]);
	return true;
}

bool UserManager::deleteUser(std::string username) {
	if (pool.find(username) == pool.end())return false;
	pool[username].~User();
	pool.erase(username);
	return true;
}

void UserManager::fullUpdate() {
	string temp;
	for (unordered_map<string, User>::iterator i = pool.begin();
		i != pool.end(); i++)  //遍历内存中用户信息
		temp += i->second.toString();

	temp = base64_encode(temp.c_str(), temp.size());
	fclose(user_info); user_info = fopen("user.data", "w");
	fprintf(user_info, temp.c_str());//写入最终信息
	fclose(user_info); user_info = fopen("user.data", "r+");
}

void UserManager::readFromString(string & temp) {
	vector<string> all_user = parse(';', temp);
	for (int i = 0; i < all_user.size(); i++) {
		vector<string> this_user = parse(',', all_user[i]);
		//根据格式，此处this_user[0]为用户名，this_user[1]为密码
		// if(this_user[2].size()>1)throw exception("input error!");
		pool[this_user[0]] =
			User(this_user[0], this_user[1], this_user[2][0] - '0');
		for (int i = 3; i < this_user.size(); i += 2)
			pool[this_user[0]].owned_stocks[this_user[i]] = atoi(this_user[i + 1].c_str());
	}
}

void UserManager::writeBuffer(User a) { 
	fprintf(buffer, a.toString().c_str()); 
}

void UserManager::readBuffer() {
	string temp = readAll(buffer);
	readFromString(temp);
}

UserManager::~UserManager() {
	fullUpdate();

	fclose(user_info);
	fclose(buffer);
}