#pragma once

#include<iostream>
#include<exception>
#include <string>
#include <fstream>
#include <unordered_map>
#include "Table.h"
#include "Dlist.h"


//一个数据库应当是一个容器，用于存储表，管理对象是表，因此其操作应该是对表的
//---------------------------------------------------------

//还没看，请修正后发给我整合
using namespace std;

fstream Dofile;
fstream Difile;

class database {
private:
//下面函数用于将txt文件的内容写入hash表中，逐行写入，账户密码分开写入,同时建立起对应的链表
    void write() {
        string name;
        string dir_t;
        string values;
        vector<string> vec;
        getline(Difile, name, ' ');
        getline(Difile, dir_t, ' ');
        getline(Difile, values, '\n');
        table tb(name, dir_t);
        tb.set_values_t(values);
        vec.emplace(vec.begin(), dir_t);
        vec.emplace(vec.begin() + 1, values);
        table_list.push_front(tb);
        table_map.insert(make_pair(name, vec));
    }
    //数据库对象的名字
    string database_name;
    //对象的路径
    string path;
    string database_txt_dir;
public:
    dlist<table> table_list;
    //下面的vector<string>存两个东西，路径和values
    unordered_map<string, vector<string>> table_map;
    //传值的构造函数
    database(const string &database_name, const string &path, const string &txt_dir)noexcept {
        this->database_name = database_name;
        this->path = path;
        this->database_txt_dir = txt_dir;
    }
    //传类对象的构造函数
    database(const database &p) {
        this->database_name = p.database_name;
        this->path = p.path;
        this->table_list = p.table_list;
        this->database_txt_dir = p.database_txt_dir;
        this->table_map = p.table_map;
    }
    //默认构造函数
    database() {}
    ~database() {
        table_map.clear();
    }

    //向哈希表输入，同时完成链表初始化
    void set_map() {
        //刚创建文件流时必须使用peek方法才能判断是否为空
        //测试通过
        //cout<<database_txt_dir<<endl;
        Difile.open(this->database_txt_dir, ios::in);
        Difile.peek();
        while (!Difile.eof()) {
            write();
            Difile.peek();
        }
        Difile.close();
    }

    //write_txt用来写txt便于每次的链表建立
    void write_txt(const string &name) {
        // cout<< database_map.find(name)->first << " " << database_map.find(name)->second << endl;
        Dofile.open(this->database_txt_dir, ios::app | ios::out);
        Dofile << table_map.find(name)->first << " " << (table_map.find(name)->second)[0] << " " << (table_map.find(name)->second)[1] << endl;
        Dofile.close();
    }

    string get_name() {
        return this->database_name;
    }

    string get_dir() {
        return this->path;
    }

    void set_name(const string &str) {
        this->database_name = str;
    }

    void set_path(const string &str) {
        this->path = str;
    }


    void set_txt_dir(const string &str) {
        this->database_txt_dir = str;
    }

    string get_txt_dir() {
        return this->database_txt_dir;
    }
};
