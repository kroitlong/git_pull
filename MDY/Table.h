#pragma once

#include<iostream>
#include<exception>
#include"Dlist.h"
//一个数据库应当是一个容器，用于存储数据，管理对象是数据，因此其操作应该是对数据的
//#include"container.h"
//#include< >--->>可能包含的库

//----------------------------------------------
//可能的准备工作：
/*变量定义
  名字空间引用
  模板定义
*/
//进行table类的封装，该类继承dlist

//template<>--?可能用到
class table : public dlist < ~ > {
//----类型----------------------------------------
//----------------------------------公有的类型定义
public:

//----------------------------------私有属性
private:

//----------------------------------共有属性
public:

//----------------------------------类的构造函数和析构函数
    table() {

    }
    ~table() {

    }
//----------------------------------类的抽象方法
//继承dlist后要可能重写方法，也可能用的模板参数传入
    //作为表table，应该含有：
    /*1.insert--在某行之后插入数据

      2.add_end--在某位插入数据    

      3.add_start--在首位插入数据  //可以考虑将这两个同第一个合并

      4.delect--删除某行数据

      5.select--根据索引查找某个数据
    */

    //---------------------------------------------------------------
    //注：因为我们将这个文本文件抽象为表了，所以锁定某个对象时应该有两个参数，行和列

};
