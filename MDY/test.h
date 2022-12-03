#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

class person {
private:
    string name;
    string gender;
    int age;

public:
   //传值的构造函数
    person(string &name, string &gender, int &age) {
        this->name = name;
        this->gender = gender;
        this->age = age;
    }
    //传类对象的构造函数
    person(const person &l) {
        this->name = l.name;
        this->gender = l.gender;
        this->age = l.age;
    }
    //默认构造函数
    person(){}
    ~person() {}
    //请注意，这个get_name用于得到当前类对象的name数据，可以看作table和database的名字，如果你看懂了dlist就可以按自己的
    //想法命名，否则请在database.h等要用到链表的类的被管理对象下添加一个名为get_name的函数
    string get_name() {
        return this->name;
    }

    string get_gender() {
        return this->gender;
    }
    
    int get_age() {
        return this->age;
    }
};