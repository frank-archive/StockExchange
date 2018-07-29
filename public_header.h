#pragma once
#include<cstdlib>
#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<conio.h>
#include<iomanip>

//=======================tools============================

//检查密码是否符合要求
bool examPwd(std::string);
//分割长字符串
std::vector<std::string> parse(char a, std::string word);
//无回显读密码
std::string readPassword();
//base64编码与解码库
static const std::string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";


static inline bool is_base64(unsigned char c);
std::string base64_encode(char const* bytes_to_encode, unsigned int in_len);
std::string base64_decode(std::string const& encoded_string);

//读文件内所有内容
std::string readAll(FILE *f);