#include <string>
#include <iostream>
#include <vector>
#include <sstream>
// #include "Table.h"
// #include "DataBase.h"
// #include "MDYS.h"
// #include "Dlist.h"
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
public:
    //定义一个字符串分割函数，用于对用户输入的数据库语句进行分割，方便后续处理
    void split(string &str, vector<string> &res) {
        for (auto it1 = str.begin(); it1 != str.end(); it1++) {
            *it1 = tolower(*it1);
        }
        //istringstream函数，位于sstring库中，构造函数参数为string，用于将string中的字符提取出来，得到一个字符串流
        istringstream is(str);

        string temp;
        //getline函数，接受一个字符流，将其传入temp对象中
        while (getline(is, temp, ' '))
            res.push_back(temp);//stoi(temp)转整型
        //循环结束后res内则是一个个被分解的字符串。
        return ;
    }

    void database_operation(string str) {
        //这个方法用来根据用户输入的数据库事务语句来进行数据库操作。
        //我们先将用户的输入语句进行拆分
        vector<string> database_operation;

        split(str, database_operation);
        //下面就是设置接口的地方，输出数字只是用于测试用
        if (database_operation[0].compare(Select) == 0) {
            //Select <row_num> from <table> [where<cond>], select <tbname>
            cout << "1" << endl;
            //-----------------------------------------------select有关的操作，分别是对表查列和对库查表
        } else if (database_operation[0].compare(Drop) == 0) {
            //Drop database <dbname>, drop table <tbname>
            cout << "2" << endl;
            //-----------------------------------------------drop有关的操作，分别是删库和删表
        } else if (database_operation[0].compare(Create) == 0) {
            //Create database <dbname>，create table <tbname>
            cout << "3" << endl;
            //-----------------------------------------------create有关的操作，分别是建库和建表，都默认从最后一个开始建
        } else if (database_operation[0].compare(Insert) == 0) {
            //Insert <tbname> values(<const_value>[,const_value...])
            cout << "4" << endl;
            //-----------------------------------------------insert有关的操作，只有对表插数据，默认从最后一行插入,在select table之后操作
        } else if (database_operation[0].compare(Delete) == 0) {
            //Delect <row_num> from <tbname>
            cout << "5" << endl;
            //-----------------------------------------------delete有关的操作，只有对表删数据，删除指定行的数据
        } else if (database_operation[0].compare(Use) == 0) {
            //Use <dbname>
            cout << "6" << endl;
            //-----------------------------------------------切换数据库即进入该数据库，之后对表的操作都是对该数据库而言的
        } else if (database_operation[0].compare(Showall) == 0) {
            //showall
            cout << "7" << endl;
            //-----------------------------------------------用来输出整个数据库结构
        } else cout << "Erroe Command, Please Check The Menu Again " << endl;
    }



    void show() { //此方法用于数据库界面的展示以及用户的交互

        cout << "Please enter the password :(don't have a account? please enter Create )"  << endl;
        getline(cin, input);
        if (input.compare("\n") != 0) {
            if (input.compare(Create) == 0) { //表示用户想要创建一个账户，一个账户对应一个MDYS，应当将账户和password用键值对存起来
            
                //创建账户的操作
            } else {
                //表示input是用户输入的密码

                //验证密码的操作
                //log_flag表时登录状态
                log_flag = true;
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
//当退出上面的循环的时候，表示退出了函数，此处不可退出数据库，退出操作在主函数中
        return ;

    }
};
//测试用的
// int main(void) {
//     present l;
//     l.show();
//     return 0;
// }