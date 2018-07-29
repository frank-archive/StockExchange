#include"SuperUser.h"
#include"sockets.h"
#include"Stock.h"
#include"User.h"
using namespace std;

bool SuperUser::setStockPrice(std::string id, float p) {
	if (stock_pool.pool.find(id) == stock_pool.pool.end())return false;
	stock_pool.pool[id].price_log.push_back(p);
	return true;
}


User * SuperUser::addUser(std::string username, std::string password, bool isAdmin) {
	if (user_manager.addUser(username, password, isAdmin))
		return user_manager.getUser(username);
	return 0;
}

bool SuperUser::setBalance(std::string username, float b) {
	if (user_manager.getUser(username)) {
		user_manager.getUser(username)->balance = b;
		return true;
	}
	return false;
}

bool SuperUser::deleteUser(std::string username) {
	return user_manager.deleteUser(username);
}
