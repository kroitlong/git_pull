#include<iostream>
#include<cstring>
//#include<>GUI库，目前主流的有QT，MFC,Wxweight等
//包含头文件
#include"present.h"


using namespace std;
//---------------------------------------------------------------------------------
//用图形化窗口创建菜单
int main(void) {
    //-----------------------------------------------------------------------------

    //基本参数定义:看需要涉及到哪些参数

    //图形化窗口定义:包括添加组件，设置布局，添加按钮，添加事件监听器等，用特定按钮表示退出
    //添加的按钮包括：
    /*Create database--创建数据库，一个大的文件夹，里面有若干表文件和表的索引文件

      Drop database--删除数据库，删除某个文件夹，包括其内的所有表

      Use--切换数据库

      Create table--在当前数据库下创建表，同时创建其索引文件

      Drop table--删除当前数据库中的某个表

      Select--在当前文件夹中查询表 --------------- //

      Delect--根据条件（如果有），删除当前表中的元素- // ————————>>这三个是对表的操作

      Insert--在当前表中插入元素------------------//
    */
    //每个按钮点击后应该可以输入相关名称，或用于创建，或用于搜索，点击按钮后执行相应的操作

    //-----------------------------------------------------------------------------
    //相应按钮对应发生的事件：
    /*

    //因为按钮设置的是事件监听器，应当写明点击按钮会发生的事件，
    //实际上每个按钮都会发生对应的事件

    */
   //如果要使用QT进行图形化编程则使用上述思路，先使用命令行方式进行交互
    //------------------------------------------------------------------------------
  cout<<"\n\n"<<"-------------------------------------------------------------------"<<endl;
  cout<<"Welcome to our Micro Database Management System , below is the Menu"<<endl;
  cout<<"-------------------------I AM THE MENU------------------------------"<<endl;
  cout<<"1.The capitalization of command is not required , all character like <>,[],\"\" is not required"<<endl;
  cout<<"2.Below is the Command System >>"<<endl;
  cout<<"\t"<<"[1].To Create a Database, please enter :                 Create Database <dbname>"<<endl;
  cout<<"\t"<<"[2].To choose a specified Database, please enter :       Use <dbname>"<<endl;
  cout<<"\t"<<"[3].To Delete a Database, please enter:                  Drop Database <dbname>"<<endl;
  cout<<"\t"<<"[4].To Create a Table, please enter :                    Create table <tbname>"<<endl;
  cout<<"\t"<<"[5].To choose a specified Table, please enter :          Select <tbname>"<<endl;;
  cout<<"\t"<<"[6].To Delect a Table, please enter :                    Drop table <tbname> from <dbname>"<<endl;
  cout<<"\t"<<"[7].To Insert data in a table, please enter :            Insert <tbname> values"<<endl;
  cout<<"\t"<<"[8].To Delete data in a table, please enter :            Delect <row_num> from <tbname>"<<endl;
  cout<<"\t"<<"[9].To Select data in a table, please enter :            Select <row_num> from <table>"<<endl;
  cout<<"\t"<<"[10].To see the structure of the Database System, please enter:  Showall"<<endl;
  cout<<endl;
  cout<<"3.Attention,each value you insert shall be like this :data1 data2 data3... "<<endl;
  cout<<"---------------------------------------------------------------------"<<endl;
 
  present l;
  l.show();
    //------------------------------------------------------------------------------
    //以下是各个头文件的关系：
    /*
      MDYS-------->>DataBase-------->>table-------->>每行的数据
      管理           管理              管理
      ^              ^                ^
      *              *                *
      子类            子类              子类
      *              *                *         使用
      *----------->Dlist<-------------*<<<<<<---------container
    */
   return 0;
}