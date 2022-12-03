#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <fstream>
#include <dirent.h>
#include <stdlib.h>
#include <vector>
#include "Dlist.h"
#include "Account.h"


fstream ofile("/mnt/e/test/c++/MDY/.account.idx", ios::app | ios::out);
fstream ifile("/mnt/e/test/c++/MDY/.account.idx", ios::in);
//MDYS用于管理所有的账户对象
class MDYS {
//----类型----------------------------------------
private:
    //下面函数用于将txt文件的内容写入hash表中，逐行写入，账户密码分开写入,同时建立起对应的链表
    void write() {
        string acc_t;
        string pass_t;
        string dir_t;
        string txt_dir;
        getline(ifile, acc_t, ' ');
        getline(ifile, pass_t, ' ');
        getline(ifile, dir_t, ' ');
        getline(ifile, txt_dir, '\n');
        account_t act(acc_t, atol(pass_t.c_str()), dir_t, txt_dir);
        account_list.push_front(act);
        MDYS_map.insert(make_pair(acc_t, atol(pass_t.c_str())));
    }
    //账户名字和对应密码都放在account.txt文件中的
    unordered_map<string, long> MDYS_map;

public:

    //所有账户的创建路径
    string folderPath = "/mnt/e/test/c++/MDY/All_Account/";
    //我们账户对象管理的数据库链表
    dlist<account_t> account_list;
    //flag表示账户是否创建成功
    bool flag = false;

    //该类的构造比较简单，不会创建默认账户，只有调用create函数才会进行创建--暂定
    MDYS() {
        ifile.peek();
        while (!ifile.eof()) {
            write();
        }
        ifile.close();
    }
    //复制构造函数
    MDYS(const MDYS &mdys) {
        this->folderPath = mdys.folderPath;
        this->account_list = mdys.account_list;
        this->MDYS_map = mdys.MDYS_map;
        this->flag = mdys.flag;
    }

    ~MDYS() {
        MDYS_map.clear();
    }

    //设置账户,返回创建是否成功
    bool set_account(const string &name) try {
        //如果该账户已经存在，则抛出异常
        if (MDYS_map.find(name) != nullptr)
            throw name;
        //先创建具体文件和存储database信息的txt文件
        const string command1 = "mkdir " + folderPath + name;
        const string command2 = "touch " + folderPath + name + "/" + name + ".idx";
        //txt文件路径
        const string txt_dir = folderPath + name + "/" + name + ".idx";
        const string dir = folderPath + name;
        system(command1.c_str());
        system(command2.c_str());
        MDYS_map.insert(make_pair(name, 0));
        ofile << MDYS_map.find(name)->first << " ";
        //再创建对象并加入链表
        account_t at(name, dir, txt_dir);
        account_list.push_front(at);
        flag = true;
        return flag;
    } catch (const string &account) {
        cout << "The Account \"" << account << "\" already exist!!!" << endl;
        return flag;
    }

    //设置密码
    bool set_password(const string &str, const long &num) {
        auto p = account_list.find(str);
        (p->data).set_password(num);
        MDYS_map[str] = num;
        ofile << MDYS_map.find(str)->second << " " << (p->data).get_dir() << " " << (p->data).get_txt_dir() << endl;
        ofile.close();
        flag = true;
        return flag;
    }

    //进行哈希表的匹配
    //其中hash.find返回一个键为name的迭代器，该迭代器相当于一个指针指向该键值对，first为键，second为值,返回true表示匹配成功
    bool match(const string &name, const long &num) {
        if (MDYS_map[name] == num) flag = true;
        return flag;
    }
};
