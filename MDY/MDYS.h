#pragma once

#include<iostream>
#include<exception>
#include"Dlist.h"
//用于存放所有数据库的大文件，按理说在初始化时生成一个就好
//#include"container.h"
//#include< >--->>可能包含的库

//----------------------------------------------
//可能的准备工作：
/*变量定义
  名字空间引用
  模板定义
*/
//进行MDYS类的封装，该类继承dlist

//template<>--?可能用到
class MDYS: public dlist < ~ > {
//----类型----------------------------------------
//----------------------------------公有的类型定义
public:

//----------------------------------私有属性
private:

//----------------------------------共有属性
public:

//----------------------------------类的构造函数和析构函数
    MDYS() {

    }
    ~MDYS() {

    }
//----------------------------------类的抽象方法
//继承dlist后要可能重写方法，也可能用的模板参数传入
    //作为数据库管理者，应该含有：
    /*1.create_database--创建数据库

      2.drop_database--删除数据库

      3.use--切换数据库

      4.sort--将数据库按首字母顺序排序，便于查找
    */
};