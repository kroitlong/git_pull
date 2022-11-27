#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include "Account.h"
#include "Interface.h"
using namespace std;

class present {
private:
    string input;
    string Create = "create";
    string exit = "exit";
    string Delete = "delete";
    string Use = "use";
    string Drop = "drop";
    string Select = "select";
    string Insert = "insert";
    string Showall = "showall";
    string Enter = "enter";
    bool log_flag = false;
    bool exit_flag = false;
    int password;
    Interface inf;
    //重载的字符拼接函数，旨在消除空格
    //@overload
    string strcmp(const vector<string> &res, int a, int b) {
        string str;
        for (int i = a; i < b; i++) {
            str = str + res[i];
        }
        return str;
    }
public:
//构造函数，暂定
    present() {}
    ~present() {}

//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------

    void database_operation(string str) try {
        //这个方法用来根据用户输入的数据库事务语句来进行数据库操作。
        //我们先将用户的输入语句进行拆分，database_operation存放的是指令中有多少的词
        vector<string> database_operation_v;
        split(str, database_operation_v, ' ');
        //-----------------------------------------------select有关的操作，分别是对表查列和对库查表
        if (database_operation_v[0].compare(Select) == 0) {
            //Select <column> from <table> [where<cond>], select函数只用于表，条件不是必须的，条件格式为where(column_name=name)
            if (database_operation_v.size() < 4)throw - 1;
            string column;
            string condition;
            string table_name = database_operation_v[3];
            //表示有条件时，确定condition
            if (database_operation_v.size() > 4) {
                condition = strcmp(database_operation_v, 4, database_operation_v.size());
            } else {
                condition = "";
            }
            column = database_operation_v[1];
            inf.excute_select_operation(column, table_name, condition);

            //-----------------------------------------------drop有关的操作，分别是删库和删表
        } else if (database_operation_v[0].compare(Drop) == 0) {
            //Drop database <dbname>, drop table <tbname>
            if (database_operation_v.size() < 3)throw - 1;
            string  name = database_operation_v[2];
            string  type = database_operation_v[1];
            inf.excute_drop_operation(type, name);

            //-----------------------------------------------create有关的操作，分别是建库和建表，都默认从最后一个开始建
        } else if (database_operation_v[0].compare(Create) == 0) {
            //Create database <dbname>，create table <tbname> (每一列的名字)
            if (database_operation_v.size() < 3)throw - 1;
            string  name = database_operation_v[2];
            string  type = database_operation_v[1];
            inf.excute_create_operation(type, name);

            //-----------------------------------------------insert有关的操作，只有对表插数据，默认从最后一行插入,在select table之后操作
        } else if (database_operation_v[0].compare(Insert) == 0) {
            //Insert <tbname> values(<const_value>[,const_value...])
            //由于我们之前是按照空格符号进行语句的拆分的，所以我们要求values括号里面不能有空格号
            if (database_operation_v.size() < 3)throw - 1;
            string table_name = database_operation_v[1];
            string values = strcmp(database_operation_v, 2, database_operation_v.size());
            inf.excute_insert_operation(table_name, values);

            //-----------------------------------------------delete有关的操作，只有对表删数据，删除指定行的数据
        } else if (database_operation_v[0].compare(Delete) == 0) {
            //Delect from <tbname> [where<cond>],如果忘记指定where条件，则清空表
            string condition;
            if (database_operation_v.size() < 3)throw - 1;
            if (database_operation_v.size() > 4) {
                condition =  strcmp(database_operation_v, 3, database_operation_v.size());
            } else {
                condition = "";
            }
            string table_name = database_operation_v[2];
            inf.excute_delete_operation(table_name, condition);

            //-----------------------------------------------切换数据库即进入该数据库，之后对表的操作都是对该数据库而言的
        } else if (database_operation_v[0].compare(Use) == 0) {
            //Use <dbname>切换数据库操作
            if (database_operation_v.size() < 2)throw - 1;
            string database_name = database_operation_v[1];
            inf.excute_use_operation(database_name);
            //-----------------------------------------------用来输出整个数据库结构
        } else if (database_operation_v[0].compare(Showall) == 0) {
            //showall，系统自带的文件操作管理有相关的指令，不用另写
            //按照层次结构来输出整个数据库里面的表结构.
            cout << "showall now" << endl;

            //退出操作
        } else if (database_operation_v[0].compare(exit) == 0) {

            return;

        } else cout << "Erroe Command, Please Check The Menu Again " << endl;
    } catch (int &e) {
        cout << "Erroe Command, Please Check The Menu Again " << endl;
    }

//------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------

    void show() { //此方法用于数据库界面的展示以及用户的交互
        account_t AC;
        cout << "Please enter the Account_name :(don't have a account? please enter Create )"  << endl;
        getline(cin, input);
        for (auto it1 = input.begin(); it1 != input.end(); it1++) {
            *it1 = tolower(*it1);
        }
        if (input.compare("\n") != 0) {
            if (input.compare(Create) == 0) { //表示用户想要创建一个账户，一个账户对应一个MDYS，应当将账户和password用键值对存起来
                //执行account创建
                while (AC.flag == false) {
                    cout << "Now please set the account_name: ";
                    getline(cin, input);
                    AC.set_account(input);
                }
                //设置账户对应的密码
                cout << "Please set a password(the default password is 114514): ";
                cin >> password;
                getchar();
                AC.set_password(password);
                //调用设置密码函数，将之与先前输入的account合并为一个键值对加入哈希表中。
                log_flag = true;
                //创建账户的操作
            } else {
                //表示input是用户输入的账号
                for (int i = 0; i <= 4; i++) {
                    cout << "Please enter the password" << "(you have " << 5 - i << " choices): ";
                    cin >> password;
                    getchar();
                    //开始比较password和input,调用匹配函数
                    log_flag = AC.match(input, password);
                    //验证成功则进入以input命名的账户(MDYS)里
                    if (log_flag == true) {
                        cout << "Load Successfully!" << endl;
                        break;
                    } else cout << "Wrong password, please try again!!";
                }

                //验证密码的操作
                //我预计实现的操作是用一个专门的文件来存储用户的所有的密码，验证密码的时候就去打开这个专门的文件
                //遍历整个文件，当读取到一行相同的记录时表示验证身份成功
                //log_flag表时登录状态

            }
        }
        if (log_flag == true) {

            while (exit_flag == false) {
                cout << "Enter the command >> ";
                getline(cin, input);
                for (auto it1 = input.begin(); it1 != input.end(); it1++) {
                    *it1 = tolower(*it1);
                }
                if (input.compare(exit) == 0) {
                    exit_flag = true;
                    continue;
                } else {
                    //进行数据库操作
                    database_operation(input);
                    continue;
                }

                log_flag = false;
            }

        }
        AC.show();
        getchar();
        return;

    }
};
//测试    用的
// int main(void) {
//     present l;
//     l.show();
//     return 0;
// }
