#pragma once

#include <iostream>
#include <vector>
#include <cstring>
#include <sstream>
#include <cstdlib>
#include <unordered_map>
#include <fstream>
#include "Dlist.h"


class table {
//----类型----------------------------------------
public:
    dlist<unordered_map<string, vector<string>>> column_list;
private:

    //用这个键值对来存所有的数据
    unordered_map<string, vector<string>> table_column;
    string table_dir;
    string table_name;
    //特殊的values，并非为模板，而是一个带括号的字符串，有用，勿删
    string values_t;
    //values用来存放该表的所有列名
    vector<string> values;

public:

    //传条件和名字的构造函数
    table(const string &name, vector<string> &vec) {
        this->table_name = name;
        this->values = vec;
    }

    //传名字和路径的构造函数
    table(const string &name, const string &dir) {
        this->table_name = name;
        this->table_dir = dir;
    }

    //复制构造函数
    table(const table &tb) {
        this->column_list = tb.column_list;
        this->table_column = tb.table_column;
        this->table_dir = tb.table_dir;
        this->table_name = tb.table_name;
        this->values = tb.values;
        this->values_t=tb.values_t;
    }

    //默认的构造函数
    table() {}
    ~table() {}

    //获取当前对象路径
    string get_dir() {
        return this->table_dir;
    }

    //设置路径
    void set_dir(const string &str ) {
        this->table_dir = str;
    }

    //获取值
    vector<string> get_values() {
        return this->values;
    }
    //设置值
    void set_values(vector<string> &vec) {
        this->values = vec;
    }

    //设置特殊values
    void set_values_t(const string &str) {
        this->values_t = str;
    }

    //获取特殊values
    string get_values_t() {
        return this->values_t;
    }

    //原始的show函数，用于输出整张表
    void show() {
        cout << "show done1" << endl;
    }

    //重载的show函数，用于输出列名为str的整列及其索引值
    void show(const string &str) {
        cout << "show done2" << endl;
    }

    //重载的show函数，用于输出str1列值为str2的这整行
    void show(const string &str1, const string &str2) {
        cout << "show done3" << endl;
    }

    //插入函数
    void insert_data(vector<string> &vec) {
        for (size_t i = 0; i < vec.size(); i++) {
            cout << vec[i] << " ";
        }
    }

    //显示该表列名用于提示用户输入规范
    void show_column() {
        cout << "Please match this patten when you insert the values:" << endl;
        for (size_t i = 0; i < values.size(); i++) {
            cout << values[i] << " ";
        }
    }

    //默认的clear函数，用于清空该表
    void clear() {
        cout << "clear successfully" << endl;
    }

    //重载的clear函数，用于删除列名str1=值str2的这一行
    void clear(const string &str1, const string &str2) {
        cout << str2 << "=" << str1 << endl;
        cout << "clear successfully" << endl;
    }

    string get_name() {
        return this->table_name;
    }

//----------------------------------公有的类型定义
//public:
//     const int inf = 0x3f3f3f3f;  //用来标志查找表的下标查没查找到
//     struct Tables {
//         string name;
//         string pathName;
//         vector<string> colName;//列名称
//         vector<string> type;
//         vector<string> value;
//         FILE *fp;
//         /*
//         //定义结构对象的实例化方法
//         Tables(string table_name,vector<string> column_name , vector<string> column_type){
//             //这里我感觉很迷，我们这里肯定要实例化一个表对象的
//             //我们可以在myCreateTable()函数里面进行实例化传入参数拼接路径创建文件。
//             //但是让我惊奇的是我访问不到这个prepath属性，不知道兄弟是怎么定义结构的

//         }
//         */



//     };
//     vector<Tables *> tab; //这个是指向各个表的指针 由上层的数据库给出
//     string prePath;         //这个是由数据库给出的到数据库的路径

// //----------------------------------私有属性
// private:

// //----------------------------------共有属性
// public:

// //----------------------------------类的构造函数和析构函数
//     table(vector<Tables *>out_tab,string prePath) {
//         for(int i=0; i< out_tab.size() ;i++){
//             this.tab.push_back(out_tab[i]);
//         }
//         this.prePath=prePath;
//     }
//     ~table() {

//     }
// //----------------------------------类的抽象方法
// //继承dlist后要可能重写方法，也可能用的模板参数传入
//     //作为表table，应该含有：
//     /*1.insert--默认在表的最后一行后插入数据，设置一个指针指向最后一行即可

//       2.delect--删除某行数据

//       3.select--根据索引查找某个数据
//     */

//     //---------------------------------------------------------------
//     //注：因为我们将这个文本文件抽象为表了，所以锁定某个对象时应该有两个参数，行和列

//     void myDropTable(string tableName) {//删除表
//         tableName += ".txt";
//         string pathName = prePath + tableName;
//         if (0 != access(pathName.c_str(), 0))
//             cout << "该表不存在!" << endl;
//         else {
//             for (int i = 0; i < tab.size(); i++)
//                 if (tab[i]->name == tableName) {
//                     if (tab[i]->fp != NULL)
//                         fclose(tab[i]->fp);
//                     delete tab[i];
//                     tab.erase(tab.begin() + i);
//                 }
//             remove(pathName.c_str());
//             cout << "删除成功!" << endl;
//         }
//     }
//     void myCreateTable(string table_name,vector<string> column_name , vector<string> column_type){
//         string fire_dir = prePath + tableName;
//         //添加一个表节点到我们的集合中去
//         //实例化一个表结构对象
//         struct Tables new_node = new Tables();//我们先动态实例化一个节点对象
//         for(int i=0; i< column_name.size();i++){
//             //将传入的列名列表传入到节点里面去
//             new_node.colName[i]=column_name[i];
//             new_node.type[i]=column_type[i];
//         }
//         new_node.name=table_name;
//         //打开对应的文件，将节点的文件指针指向创建的文件
//         new_node.fp=fopen(fire_dir.c_str(),"a");
//         this.tab.push_back(new_node);
//         cout<< "success create table!"<< endl;
//     }


//     //void myInsert(string tableName, string value) { //插入数据
//     void myInsert(string tableName, vector<string> value, vector<string>input_type) { //插入数据
//     //在具体插入值的时候我们将input_type列表里面的值与类对象的type列表进行对比：
//     //如果两者长度不一致，则报错
//     //依次比较两者里面的元素，如果有一个不相同，则报错
//         int pos = inf;      //pos用来定位目标表的下标
//         for (int i = 0; i < tab.size(); i++)
//             if (tab[i]->name == tableName) {
//                 pos = i; break;
//             }
//         if (input_type.size()!==tab[pos]->type.size()){
//           cout <<"the num of the column is not correct! "<< endl;
//           return;
//           }else{
//             for(int i=0,i<input_type.size();i++){
//               if((input_type[i].compare(tab[pos]->type[i]))!=0){
//                 cout << "the property of the element is not correct" << endl;
//                 return;
//               }
//             }
//           }
//         //执行完以上所有操作之后我们才能保证我们要插入的值的属性是与表对象最开始定义的属性是一致的
//         stringstream ss(value);
//         string tmp2; ss >> tmp2;
//         tab[pos]->fp = fopen(tab[pos]->pathName.c_str(), "a");  //打开目标文件，写入数据
//         /*
//         for (int i = 0; i < tab[pos]->type.size(); i++) {
//             string tmp = tab[pos]->type[i];
//             //匹配出每个数据的类型 从每一个列 从左往右遍历插入
//             //将固定的目标类型分离出
//             if (tmp == "int") {
//                 int x; ss >> x;
//                 fprintf(tab[pos]->fp, "%d", x);
//             } else if (tmp == "float") {
//                 float x; ss >> x;
//                 fprintf(tab[pos]->fp, "%f", x);
//             } else if (tmp == "double") {
//                 double x; ss >> x;
//                 fprintf(tab[pos]->fp, "%f", x);
//             } else if (tmp == "char") {
//                 if (tab[pos]->size[i] == 1) {
//                     char x; ss >> x;
//                     fprintf(tab[pos]->fp, "%c", x);
//                 } else {
//                     int cnt = tab[pos]->size[i];
//                     char *x = new char[cnt];
//                     ss >> x;
//                     fprintf(tab[pos]->fp, "%s", x);
//                     delete x;
//                 }
//             }
//             */
//           //向文件里面插入值
//           for(int i=0; i<type.size();i++){
//             //判断写入值的类型
//             if(input_value[i].compare("int")==0){
//               int x; ss >> x;
//               fprintf(tab[pos]->fp, "%d", x);
//             }else if(input_value[i].compare("string")==0){
//               int cnt = tab[pos]->size[i];
//               char *x = new char[cnt];
//               ss >> x;
//               fprintf(tab[pos]->fp, "%s", x);
//               delete x;
//             }

//             if (i != tab[pos]->type.size() - 1)
//                 fprintf(tab[pos]->fp, "%c", ' ');
//             //每个数据之间以空格区分开
//           }
//         fprintf(tab[pos]->fp, "%c", '\n');//添加完成 追加换行符
//         fclose(tab[pos]->fp);
//         cout << "插入成功!" << endl;
//     }


//     //将删除数据的信息 即表的列信息给出在iswhere中
//     void myDelete(string tableName, string isWhere) { //删除数据

//         int pos = inf;    //pos用来定位目标表的下标
//         for (int i = 0; i < tab.size(); i++)
//             if (tab[i]->name == tableName) {
//                 pos = i; break;
//             }
//         stringstream ss(isWhere);
//         int wherePos = inf;
//         string typeName, toValue, whr, deng;
//         ss >> whr >> typeName >> deng >> toValue;
//         //找到删除列的位置
//         for (int i = 0; i < tab[pos]->colName.size(); i++) {
//             //
//             if (tab[pos]->colName[i] == typeName) {
//                 wherePos = i;
//                 break;
//             }
//         }
//         string pathName2 = prePath + "tmp.txt";
//         FILE *tmpfptr = fopen(pathName2.c_str(), "w");
//         char sentence[1024];
//         tab[pos]->fp = fopen(tab[pos]->pathName.c_str(), "r");
//         fgets(sentence, 1024, tab[pos]->fp);
//         fputs(sentence, tmpfptr);
//         bool flag = true;
//         //判断是否是整个表的删除
//         if (toValue.length() == 3 && tolower(toValue[0]) == 'a' && tolower(toValue[1]) == 'l' && tolower(toValue[2]) == '1')
//             flag = false;
//         if (flag) {
//             while (!feof(tab[pos]->fp)) {
//                 memset(sentence, 0, sizeof(sentence));
//                 fgets(sentence, 1024, tab[pos]->fp);
//                 stringstream myTmp(sentence);

//                 string x;
//                 for (int i = 0; i <= wherePos; i++)
//                     myTmp >> x;
//                 if (x == toValue) continue;
//                 fputs(sentence, tmpfptr);
//             }
//         }
//         fclose(tmpfptr);
//         fclose(tab[pos]->fp);
//         remove(tab[pos]->pathName.c_str());
//         if (0 == rename(pathName2.c_str(), tab[pos]->pathName.c_str()))
//             cout << "删除成功!" << endl;
//         else
//             cout << "删除失败!" << endl;
//     }


//     void myUpdate(string tableName, string toColName, string newValue, string isWhere) { //更新数据

//         int pos = inf;

//         for (int i = 0; i < tab.size(); i++)

//             if (tab[i]->name == tableName) {
//                 pos = i; break;
//             }


//         stringstream ss(isWhere);
//         int wherePos = inf, updataPos = inf;
//         string typeName, toValue, whr, deng;
//         ss >> whr >> typeName >> deng >> toValue;

//         for (int i = 0; i < tab[pos]->colName.size(); i++) //找到范围对应的colName下标
//             if (tab[pos]->colName[i] == typeName) {
//                 wherePos = i;
//                 break;
//             }
//         for (int i = 0; i < tab[pos]->colName.size(); i++) //找到需要修改的colName下标
//             if (tab[pos]->colName[i] == toColName) {
//                 updataPos = i;
//                 break;
//             }
//         string pathName2 = prePath + "tmp.txt";
//         FILE *tmpfptr = fopen(pathName2.c_str(), "w");
//         char sentence[1024];
//         tab[pos]->fp = fopen(tab[pos]->pathName.c_str(), "r");
//         fgets(sentence, 1024, tab[pos]->fp);
//         fputs(sentence, tmpfptr);
//         bool flag = true;
//         if (toValue.length() == 3 && tolower(toValue[0]) == 'a' && tolower(toValue[1]) == 'l' && tolower(toValue[2]) == 'l')
//             flag = false;
//         if (!flag) {//全部修改
//             while (!feof(tab[pos]->fp)) {
//                 for (int i = 0; i < tab[pos]->type.size(); i++) {
//                     string tmp = tab[pos]->type[i];
//                     //cout << "tmp:" << tmp << endl;
//                     if (tmp == "int") {
//                         int x; fscanf(tab[pos]->fp, "%d", &x);
//                         if (i == updataPos)
//                             x = atoi(newValue.c_str());
//                         fprintf(tmpfptr, "%d", x);
//                     } else if (tmp == "float") {
//                         float x; fscanf(tab[pos]->fp, "%f", &x);
//                         if (i == updataPos)
//                             x = atof(newValue.c_str());
//                         fprintf(tmpfptr, "%f", x);
//                     } else if (tmp == "double") {
//                         double x; fscanf(tab[pos]->fp, "%lf", &x);
//                         if (i == updataPos)
//                             x = atof(newValue.c_str());
//                         fprintf(tmpfptr, "%f ", x);
//                     } else if (tmp == "char") {
//                         if (tab[pos]->size[i] == 1) {
//                             char x; fscanf(tab[pos]->fp, "%c", &x);
//                             if (i == updataPos)
//                                 x = newValue[0];
//                             fprintf(tmpfptr, "%c", x);
//                         } else {
//                             int cnt = tab[pos]->size[i];
//                             char *x = new char[cnt];
//                             fscanf(tab[pos]->fp, "%s", x);
//                             if (i == updataPos) {
//                                 strcpy(x, newValue.c_str());
//                                 x[newValue.length()] = NULL;
//                             }
//                             fprintf(tmpfptr, "%s", x);
//                             delete x;
//                         }
//                     }
//                     if (i != tab[pos]->type.size() - 1)
//                         fprintf(tmpfptr, "%c", ' ');
//                 }
//                 fprintf(tmpfptr, "%c", '\n');
//             }
//         } else { //范围内修改
//             while (!feof(tab[pos]->fp)) {
//                 memset(sentence, 0, sizeof(sentence));
//                 fgets(sentence, 1024, tab[pos]->fp);
//                 stringstream myTmp(sentence);
//                 string x;
//                 for (int i = 0; i <= wherePos; i++)
//                     myTmp >> x;
//                 if (x == toValue) {
//                     stringstream myTmp2(sentence);
//                     string input;
//                     input.clear();
//                     for (int i = 0; i < tab[pos]->colName.size(); i++) {
//                         myTmp2 >> x;
//                         if (i == updataPos)
//                             input += newValue;
//                         else
//                             input += x;
//                         if (i != tab[pos]->colName.size() - 1)
//                             input += " ";
//                         else
//                             input += "\n";
//                     }
//                     //cout << "input = " << input;
//                     fputs(input.c_str(), tmpfptr);
//                 } else
//                     fputs(sentence, tmpfptr);
//             }
//         }
//         fclose(tmpfptr);
//         fclose(tab[pos]->fp);
//         remove(tab[pos]->pathName.c_str());
//         if (0 == rename(pathName2.c_str(), tab[pos]->pathName.c_str()))
//             cout << "更新成功!" << endl;
//         else
//             cout << "更新失败!" << endl;
//     }


//     void myQuery(string toColName, string tableName, string isWhere = "") {//查询数据

//         int pos = inf;
//         for (int i = 0; i < tab.size(); i++)
//             if (tab[i]->name == tableName) {
//                 pos = i; break;
//             }

//         tab[pos]->fp = fopen(tab[pos]->pathName.c_str(), "r");

//         char contant[1024];

//         fgets(contant, sizeof(contant), tab[pos]->fp);
//         if (isWhere == "") {//全输出
//             int len = strlen(contant);
//             for (int i = 0; i < len; i++)
//                 if (contant[i] == ';')
//                     contant[i] = ' ';
//             stringstream ss(contant);
//             string x;
//             for (int i = 0; i < tab[pos]->size.size(); i++) {//先输出colNames
//                 int width = 15;
//                 if (tab[pos]->size[i] != 1)
//                     width = tab[pos]->size[i];
//                 ss >> x;
//                 cout << left << setw(width) << x;
//                 ss >> x;
//                 ss >> x;
//             }
//             cout << endl;

//             while (!feof(tab[pos]->fp)) {
//                 memset(contant, 0, sizeof(contant));
//                 fgets(contant, sizeof(contant), tab[pos]->fp);
//                 if (strlen(contant) == 0)break;
//                 stringstream out(contant);
//                 string x;
//                 for (int i = 0; i < tab[pos]->type.size(); i++) {
//                     out >> x;
//                     int width = 15;
//                     if (tab[pos]->size[i] != 1)
//                         width = tab[pos]->size[i];
//                     string tmp = tab[pos]->type[i];
//                     if (tmp == "int")
//                         cout << left << setw(width) << atoi(x.c_str());
//                     else if (tmp == "float" || tmp == "double")
//                         cout << left << setw(width) << atof(x.c_str());
//                     else if (tmp == "char")
//                         cout << left << setw(width) << x;
//                 }
//                 cout << endl;
//             }
//         } else {
//             stringstream ss(isWhere);
//             int wherePos = inf, aimPos = inf;
//             string typeName, toValue, whr, deng;
//             ss >> whr >> typeName >> deng >> toValue;
//             for (int i = 0; i < tab[pos]->colName.size(); i++) //找到规定范围colName下标
//                 if (tab[pos]->colName[i] == typeName) {
//                     wherePos = i;
//                     break;
//                 }
//             for (int i = 0; i < tab[pos]->colName.size(); i++) //找到规定范围colName下标
//                 if (tab[pos]->colName[i] == toColName) {
//                     aimPos = i;
//                     break;
//                 }
//             while (!feof(tab[pos]->fp)) {
//                 memset(contant, 0, sizeof(contant));
//                 fgets(contant, sizeof(contant), tab[pos]->fp);
//                 stringstream myTmp(contant);
//                 string x, check, out;
//                 for (int i = 0; i < tab[pos]->colName.size(); i++) {
//                     myTmp >> x;
//                     if (i == wherePos)check = x;
//                     if (i == aimPos)out = x;
//                 }
//                 if (check == toValue) {
//                     int width = 15;
//                     if (tab[pos]->size[aimPos] != 1)
//                         width = tab[pos]->size[aimPos];
//                     string tmp = tab[pos]->type[aimPos];
//                     if (tmp == "int")
//                         cout << left << setw(width) << atoi(out.c_str()) << endl;
//                     else if (tmp == "float")
//                         cout << left << setw(width) << atof(out.c_str()) << endl;
//                     else if (tmp == "double")
//                         cout << left << setw(width) << atof(out.c_str()) << endl;
//                     else if (tmp == "char")
//                         cout << left << setw(width) << out << endl;
//                 }
//             }
//         }
//         fclose(tab[pos]->fp);
//     }
};


