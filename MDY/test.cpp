//这个文件没啥意义，只是用来试函数的
#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include <sys/stat.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/io.h>
#include <errno.h>
#include <fstream>
using namespace std;
string strcmp(const vector<string> &res, int a, int b) {
    string str;
    for (int i = a; i < b; i++) {
        str = str + res[i];
    }
    return str;
}

int main(void) {
    //-----------------------------------------------------------
    // string line;
    // getline(cin,line);
    // for (auto it1 = line.begin(); it1 != line.end(); it1++)
    // {
    //  *it1 = tolower(*it1);
    // }

    // istringstream is(line);
    // string str;
    // vector<string> res;
    // while(getline(is,str,' '))
    // res.push_back(str);

    // cout<<res[3]<<endl;
    // for(auto i=0;i<res.size();i++){
    //     cout<<res[i]<<endl;
    // }
    // return 1 ;

    //-----------------------------------------------------------
    //建立一行hash_map，一个char(即账户名)，对应一个int(即密码)
    // unordered_map<string, long> Account;
    // string account;
    // long password;

    // char ch;
    // while (ch != 'q') {
    //     cout << "please enter the account_name: ";
    //     getline(cin, account);
    //     ch=account.at(0);
    //     cout << "please set the password: ";
    //     cin >> password;
    //     getchar();
    //     cout <<endl;
    //     Account.insert(pair<string, long>(account, password));

    // }
    // for(unordered_map<string,long>::iterator it=Account.begin();it!=Account.end();it++){
    //     cout<<it->first<<" : "<<it->second<<endl;
    // }
    // return 0;
    //------------------------------------------------------------

    //这玩意很邪门儿，因为我的是linux终端，所以路径长这个样，如果你是windows的终端，请修改路径
    // const string folderPath = "/mnt/e/test/c++/MDY/All_Account/";
    // string database;

    // cout << "输入文件夹名称： ";
    // getline(cin, database);

    // const string command = "mkdir " + folderPath + database;
    // system(command.c_str());
    // cout << endl;
    // cout << command << endl;

    // if (0 != access(folderPath.c_str(), 0))
    // {
    //     // if this folder not exist, create a new one.
    //     mkdir(command.c_str(),S_IRWXU);   // 返回 0 表示创建成功，-1 表示失败
    //     //换成 ::_mkdir  ::_access 也行，不知道什么意思
    // }

    //--------------------------------------------------------------
    // fstream file;
    // file.open("/mnt/e/test/c++/MDY/HashMap.txt",ios::out|ios::app);
    // file<<1234<<" "<<"hello"<<endl;
    // file.close();

    //--------------------------------------------------------------


    vector<string> str = {"nihao", "world", "=", "and", "fuck", "you", " ", "mm"};
    string st;
    st = strcmp(str, 2, str.size()-1);
    cout << st << endl;


    return 0;


}