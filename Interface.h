#pragma once
#include"public_header.h"
class Interface {
	void suLogin();
	void userLogin();
	void addUser();
	void query();

	void printTable(struct Stock*);
public:
	Interface();
	~Interface();
};