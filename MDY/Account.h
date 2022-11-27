#pragma once

#include<iostream>
#include<string>
#include<sstream>
#include<unordered_map>
#include<fstream>

using namespace std;

//这个类是用来生成账户的，不必看，账户名字和对应密码都放在HashMap.txt文件中的
unordered_map<string, long> Account;
//该文件用于非临时存放hash表
fstream ofile("/mnt/e/test/c++/MDY/HashMap.txt", ios::app | ios::out);
fstream ifile("/mnt/e/test/c++/MDY/HashMap.txt", ios::in);
bool eof = ifile.eof();
//下面函数用于定位到行
ifstream &seek_to_line(ifstream &in, int line)
//将打开的文件in，定位到line行。
{
    int i;
    char buf[1024];
    in.seekg(0, ios::beg);  //定位到文件开始。
    for (i = 0; i < line; i++) {
        in.getline(buf, sizeof(buf));//读取行。
    }
    return in;

}

class account_t {
private:
    long password;
    //下面函数用于将txt文件的内容写入hash表中，逐行写入，账户密码分开写入
    void write() {
        string acc_t;
        string pass_t;
        getline(ifile, acc_t, ' ');
        getline(ifile, pass_t, '\n');
        Account.insert(make_pair(acc_t, atol(pass_t.c_str())));
    }
public:
    string account;
    bool flag;
    //默认创建目录
    const string folderPath = "/mnt/e/test/c++/MDY/All_Account/";
    //创建文件夹方法


    //该类的构造比较简单，不会创建默认账户，只有调用create函数才会进行创建--暂定
    account_t() {
        flag = false;
        while (!ifile.eof()) {
            write();
        }
    }
    ~account_t() {
        Account.clear();
    }

    //设置账户，如果输入的是create则不创建
    bool set_account(const string &name) try {
        //如果该账户已经存在，则抛出异常
        if (Account.find(name) != nullptr)
            throw name;
        this->account = name;
        const string command = "mkdir " + folderPath + name;
        system(command.c_str());
        Account.insert(make_pair(name, 114514));
        ofile << endl;
        ofile << Account.find(name)->first << " ";
        flag = true;
        return flag;
    } catch (const string &account) {
        cout << "The Account \"" << account << "\" already exist, please rename it!!!" << endl;
        return flag;
    }

    //设置密码
    bool set_password(const long &num) {
        this->password = num;
        Account[account] = num;
        ofile << Account.find(account)->second ;
        flag = true;
        return flag;
    }

    //进行哈希表的匹配
    //其中hash.find返回一个键为name的迭代器，该迭代器相当于一个指针指向该键值对，first为键，second为值,返回true表示匹配成功
    bool match(const string &name, const long &num) {
        if (Account[name] == num) flag = true;
        return flag;
    }

    //用于调试,可以显示当前已经注册的账户及其密码
    void show() {
        for (unordered_map<string, long>::iterator it = Account.begin(); it != Account.end(); it++) {
            cout << it->first << " : " << it->second << endl;
        }
    }


};