#include "Interface.h"
#include"SuperUser.h"
#include"User.h"
#include"Stock.h"
#include"sockets.h"
using namespace std;

void Interface::suLogin() {
	system("cls");
	printf("输入su密码:");
	string pwd; pwd = readPassword();
	if (pwd != "1234567890") {
		printf("密码不正确，程序重启。");
		return;
	}
	char f = 0;
	SuperUser instance;
	
	while(1){
		system("cls");
		printf("已登录su\n");
		f = 0;
		printf("1.调整股票价格\n2.删除用户\n3.修改用户余额\n4.返回\n");
		printf("请输入数字:");
		while (!isalnum(f))f = getchar();
		while (f<'1' || f>'4') { printf("请输入正确数字:"); getchar(); f = getchar(); }
		string buffer1; float buffer3;
		switch (f) {
		case '1'://调整股票价格
			printf("请输入股票代码:"); getchar();
			cin >> buffer1;
			printf("请输入修改后价格:"); 
			cin >> buffer3;
			if (instance.setStockPrice(buffer1, buffer3))printf("成功\n");
			else printf("失败\n");
			break;
		case '2'://删除用户
			printf("请输入要删除的用户名:");
			cin >> buffer1;
			if(instance.deleteUser(buffer1))printf("成功\n");
			else printf("失败，可能没有此用户\n");
			break;
		case '3':
			printf("输入用户名:"); cin >> buffer1;
			printf("输入余额:"); cin >> buffer3;
			if (instance.setBalance(buffer1, buffer3))printf("成功\n");
			else printf("查无此用户\n");
			break;
		case '4':
			return;
		}
		system("pause");
	}
}

void Interface::userLogin() {
	string username, password; char f = 0;
	printf("请输入用户名:"); cin >> username;
	User *target = user_manager.getUser(username);
	printf("请输入密码:"); password = readPassword();
	if (target->checkPwd(password) == false) {
		printf("密码错误，重启程序");
		return;
	}
	while (1) {
		system("cls");
		f = 0;
		printf("已登录%s\n", username.c_str());
		printf("1.修改密码\n2.查询股票\n3.买入股票\n4.卖出股票\n5.返回\n");
		printf("管理员行为：\n6.添加股票\n7.修改股票代码、名称\n8.切换股票停售、在售状态\n");
		printf("请输入一个指令:");
		while (!isalnum(f))f = getchar();
		while (f<'1' || f>'8') { printf("请输入正确数字:"); getchar(); f = getchar(); }
		string buffer1, buffer2, buffer5; float buffer3; int buffer4;
		switch (f) {
		case '1'://修改密码
			printf("请输入新密码:"); cin >> password;
			if (target->editPwd(password))printf("成功\n");
			else printf("失败，密码不符合要求\n");
			break;
		case '2'://查询股票
			query();
			break;

		case '3'://购买股票
			printf("输入股票代码:"); cin >> buffer1;
			printf("输入购买数量:"); cin >> buffer4;
			if (target->buy(buffer1, buffer4))printf("购买成功\n");
			else printf("购买失败，有以下几种可能：\n股票代码有误\n股票关闭交易\n余额不足\n市场中股票不足\n");
			break;
		case '4'://出售股票
			printf("输入股票代码"); cin >> buffer1;
			printf("输入出售数量:"); cin >> buffer4;
			if (target->sell(buffer1, buffer4))printf("出售成功\n");
			else printf("出售失败，有以下几种可能：\n股票代码有误\n股票关闭交易\n拥有股票不足\n");
			break;

		case '5':return;//返回

		case '6'://新增股票
			printf("新股票代码:"); cin >> buffer1;
			printf("新股票名称:"); cin >> buffer2;
			printf("首发价格:"); cin >> buffer3;
			printf("发行数量:"); cin >> buffer4;
			if (target->addStock(buffer1, buffer2, buffer3, buffer4))
				printf("成功\n");
			else printf("用户不是管理员，操作失败\n");
			break;

		case '7'://修改股票
			printf("股票代码:"); cin >> buffer1;
			printf("股票新代码(不填则为不修改):"); cin >> buffer2;
			printf("股票新名称(必须修改):"); cin >> buffer5;
			if (buffer2.size() == 0)buffer2 = buffer1;
			if (buffer5.size() == 0) {
				printf("输入错误\n");
				break;
			}
			if (target->editStock(buffer1, buffer5, buffer2))
				printf("成功\n");
			else printf("用户不是管理员，操作失败\n");
			break;
		case '8'://切换状态
			printf("股票代码:"); cin >> buffer1;
			if (target->toggleStock(buffer1))
				printf("成功\n");
			else printf("用户不是管理员，操作失败\n");
			break;
		}
		system("pause");
	}
}

void Interface::addUser() {
	string username, password;
	SuperUser inst;
	printf("请输入用户名:");
	cin >> username;
	printf("请输入密码:");
	cin >> password;
	printf("是管理员么？(y/n)"); getchar(); char c = getchar(); getchar();
	if (c == 'y') {
		printf("su密码:");
		string pwd = readPassword();
		if (pwd != "1234567890") {
			printf("su密码错误\n");
			return;
		}
	}
	inst.addUser(username, password, c == 'y' ? 1 : 0);
}

void Interface::query() {
	system("cls");
	printf("欢迎来到查询系统\n");
	string id, name;
	printf("请输入股票代码（可以不完整）:"); cin >> id;
	vector<Stock*>list;
	for (unordered_map<std::string, Stock>::iterator i = stock_pool.pool.begin();
		i != stock_pool.pool.end(); i++)
		if (i->second.id.find(id) == 0)list.push_back(&i->second);//找出所有股票代码以id开头的股票
	
	if (list.size() == 0) {
		printf("未找到任何股票信息\n");
		return;
	}
	printf("找到了下列股票:\n");
	for (int i = 0; i < list.size(); i++) 
		printf("%d . %s\n", i + 1, list[i]->name.c_str());
	printf("请选择股票:");
	int n = 0; cin >> n;

	printTable(list[n - 1]);
}

void Interface::printTable(Stock *i){
	printf("---------------------------价格走势图-----------------------------\n");
	vector<float>temp = i->price_log;
	float max_price=0, min_price=99999999.9f;
	for (int i = 0; i < temp.size(); i++) {
		if (temp[i] < min_price)min_price = temp[i];
		if (temp[i] > max_price)max_price = temp[i];
	}
	int cnt = 0;
	for (float i = max_price; i >= min_price-0.3; i -= 0.1) {
		if (cnt++ % 4 == 0)cout << setiosflags(ios::right) << setw(3) << i << setw(1) << '|';
		else cout << setw(4) << '|';
		for (int j = 0; j < temp.size(); j++)
			if (temp[j] - i < 0.001&&temp[j]-i>-0.001)cout << setiosflags(ios::right) << setw(3 * j+1) << "*";
		cout << '\n';
	}
	printf("---");
	for (int i = 0; i < temp.size(); i++)printf("---");
	printf("\n");
	cout << "day 1";
	for (int i = 2; i <= temp.size(); i++)
		cout << setiosflags(ios::right) << setw(3) << i;
	printf("\n\n\n\n\n\n\n");
}

Interface::Interface() {
	char f = 0;
	system("cls");
	printf("\n\n\n\n\n**********************WELCOME!***********************\n\n\n\n\n\n");
	printf("*********TO STOCK EXCHANGE SIMULATION PROGRAM!***********\n\n\n\n");
	printf("请选择功能:\n1.超级用户登陆\n2.登陆账户\n3.注册用户\n");
	printf("请输入数字:");
	while (!isalnum(f))f = getchar();
	while (f<'1' || f>'3') { printf("请输入有效数字:"); getchar(); f = getchar(); }
	getchar();
	switch (f) {
	case '1':suLogin(); break;
	case '2':userLogin(); break;
	case '3':addUser(); break;
	}
}

Interface::~Interface() {
	user_manager.fullUpdate();
	stock_pool.fullUpdate();
}
