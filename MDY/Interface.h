#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
//正则表达式提取库，用来对用户输入的数据库语句里面提取信息
#include <regex>
// #include "Table.h"
// #include "DataBase.h"
// #include "MDYS.h"
// #include "Dlist.h"
using namespace std;

//定义一个字符串分割函数，用于对用户输入的数据库语句进行分割，方便后续处理
void split(string &str, vector<string> &res, const char pattern) {
    for (auto it1 = str.begin(); it1 != str.end(); it1++) {
        *it1 = tolower(*it1);
    }
    //istringstream函数，位于sstring库中，构造函数参数为string，用于将string中的字符提取出来，得到一个字符串流
    istringstream is(str);

    string temp;
    //getline函数，接受一个字符流，将其传入temp对象中
    while (getline(is, temp, pattern))
        res.push_back(temp);//stoi(temp)转整型
    //循环结束后res内则是一个个被分解的字符串。
    return ;
}


class Interface {
private:
    string condition;
    string condition_name;
    string condition_value;
    string column_name;

public:

    //在完成以下三个类编写之后引入,注意区别db和tb哦
    // MDYS account;
    // database db;
    // table tb;

    //正则表达式提取函数，给定一个模式，从字符串里面提取信息，将一个个匹配模式的字符串送入res中,怎么感觉没啥用
    // vector<string> regTest(string s, string pattern) {
    //     auto res = vector<string>();
    //     //r作为一个正则表达式类，其中pattern为正则表达式
    //     regex r(pattern);
    //     //s表示要匹配的字符串，s.cbegin返回指向string首字符的迭代器，c表示const，此处定义一个迭代器.它将反复调用regex_search()来寻找文件中的所有匹配
    //     sregex_iterator pos(s.cbegin(), s.cend(), r), end;
    //     for (; pos != end; ++pos)
    //         res.push_back(pos->str(1));
    //     return res;
    // }

    //create功能接口
    void  excute_create_operation(string type, string name) {
        if (type.compare("database") == 0) {
            // MDYS.database_name = name;//用于确定创建路径
            //创建database_name对应的数据库---调用MDYS类里的方法，创建路径应在当前账户(MDYS)路径下

            cout << "database " << name << " created" << endl;
            cout << endl;

        } else if (type.compare("table") == 0) {
            // db.table_name = name;//用于确定创建路径
            //创建table_name对应的表---调用database类里的方法，创建路径在当前database路径下

            cout << "table " << name << " created" << endl;
            cout << endl;

        }
    }

    //drop功能接口
    void  excute_drop_operation(string type, string name) {
        if (type.compare("database") == 0) { //表示要删除数据库
            // db.database_name = name;//用于确定删除路径
            //删除database_name对应的数据库

            cout << "database " << name << " dropped" << endl;
            cout << endl;
        } else if (type.compare("table") == 0) {
            // tb.table_name = name;//用于确定删除路径
            //删除table_name对应的表

            cout << "table " << name << " dropped" << endl;
            cout << endl;
        }
    }

    //select功能接口
    void  excute_select_operation(string column, string name, string condition_t ) {
        //这里的condition比如说可以是类似于：where(Major='软件工程')同样是由于我们之前拆分语句的原因，我们强制要求where语句里面不能有空格
        //如果有条件，则将条件表示的那行全部输出
        //如果无条件，即column为all，则输出
        condition = condition_t;
        //tb.table_name = name；//用于确定要操作表的路径
        //在all的条件下不应该有condition
        if (column.compare("all") == 0) { //表示查找范围是表的所有列
            if (condition.empty()) {
                //表示无条件查询，输出整张表
                //tb.show()函数用于输出整张表

                cout << "Seleting operation to all : Done" << endl;
                cout << endl;
            } else {
                //在输入为all的条件下，如果还存在condition应该发出警告并让其重新输入,select all from <tbname> where(name='longtao')不应该存在

                cout << "Condition shall not exist if you select all" << endl;
                cout << endl;
            }
        } else { //表示column是我们要查询的列名称
            column_name = column;

            if (condition.empty()) { //表示无条件查询
                //打开table_name对应的文件，把所有的对应列记录读出来
                cout << "Below is all values from " << column << endl;
                cout << endl;
                //tb.show(column)//重载的show函数，用于输出某个·column对应的表
            } else {
                //设置代码页编码为UTF-8,要报错，不知道为什么
                //system("chcp 65001");
                //replace函数，此处参数为迭代器和const string&，表示将从起始位置到结束位置的所有字符替换为const string&
                //将 “where(“ 置为空
                string new_str1 = condition.replace(condition.begin(), condition.begin() + 6, "");
                //此时条件语句变为 ”column_name=‘name’)“ ,并存放在new_str1中
                string new_str2 = new_str1.replace(new_str1.end() - 1, new_str1.end(), "");
                //此时条件语句变为 ”column_name=‘name’“ ,并存放在new_str2中
                auto vc = vector<string>();
                split(new_str2, vc, '='); //将where字句拆分

                for (auto &s : vc) {
                    s.erase(remove( s.begin(), s.end(), '\'' ), s.end());//去除字句两边的'符号，方便在文件里面进行查询
                }

                condition_name = vc[0]; //条件里面的列名
                condition_value = vc[1]; //条件里面的列值

                cout << vc[0] << " : " << vc[1] << endl;
                cout << endl;

                //筛选表文件里面列名为condition_name的列，找到condition_value值的行，并且输出所有行对应列名为cloumn_name的列
                //这样我们就拿到了表名，列名，条件列名，和条件列值
                //筛选整个表文件里面列名为condition_name的列，找到condition_value值的行，并且输出所有的行对应的完整列
            }

        }

    }

    //insert功能接口
    void excute_insert_operation(string name, string values) {
        //这里的insert格式大致为 "insert table_name values(value1，value2，value3...)", values作为后面的整个代表，内部无空格，可以用哈希表
        //tb.table_name = name; //表的名称

        //使用正则表达式将values所有的值检索出来
        //下面两句用于将values括号里的内容剥离出来存入new_str2中
        string new_str1 = values.replace(values.begin(), values.begin() + 7, "");
        string new_str2 = new_str1.replace(new_str1.end() - 1, new_str1.end(), "");

        auto vc = vector<string>();
        split(new_str2, vc, ','); //此时vc里面装的就是我们要插入的一个一个的值
        //打开对应的table_name的表文件

        for (auto &s : vc)
            //依次向文件里面写入记录项，s表示一列的名字
            cout << s << " "; //测试用
        cout << endl;
        cout << endl;
    }

    //delete功能接口,好像’‘去除不了，原因暂不知
    void excute_delete_operation(string name, string condition) {
        /*delete
        功能：根据条件（如果有）删除表中的记录。我们这里要求where的语法同select语句一致,同样不能有空格，比如where(Major='软件工程')
        语法：
        delete from <table_name> [ where <cond> ]，删除满足条件的这一行数据,一般条件应该为索引值即哈希表中键值对中的键
        where 子句：语法同 select 的。
        */
        if (condition.empty()) { //表示无条件删除
            //tb.table_name = name;
            cout << "Delete successfully" << endl;
            cout << endl;
            //删除表table_name里面所有的记录，但是不删除表
        } else {
            //tb.table_name = name;同样要报错
            //system("chcp 65001");
            //将条件剥离出来并存放在new_str2中
            string new_str1 = condition.replace(condition.begin(), condition.begin() + 6, "");
            string new_str2 = new_str1.replace(new_str1.end() - 1, new_str1.end(), "");
            auto vc = vector<string>();
            split(new_str2, vc, '='); //将where字句拆分

            for (auto s : vc) {
                s.erase(remove( s.begin(), s.end(), '\'' ), s.end());
            }

            condition_name = vc[0]; //条件里面的列名
            condition_value = vc[1]; //条件里面的列值
            cout << vc[0] << " : " << vc[1] << endl;
            cout << endl;
        }
        //然后我们执行具体的删除操作：从table_name对应的表里面删除那些condition_name对应的列名值为condition_value的行的所有的数据。

    }

    //use功能接口
    void excute_use_operation(string name) {
        //db.database_name = name;
        //修改路径至名为database_name的数据库
        cout << "Use " << name << " Successfully" << endl;
        cout << endl;
    }

};