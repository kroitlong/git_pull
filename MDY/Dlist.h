#pragma once
//同样采用双向链表-----该头文件就是对dlist头文件的一个简化
//该头文件可能还需要依照后续头文件的需求进行更改

#include <iostream>
#include <exception>
#include <initializer_list>
#include "container.h"

//-----------------------------------------------------

//——————>>注意每个数据库（文件）可以为一个节点，每张表也应当是一个节点，表的每一行也应该是一个节点
//由此可见，之后的几个类应当继承Dlist类,并使用dlist类来进行节点的操作

//value_t作为传入的模板，对于MDYS而言是database即文件夹，对于database而言是table即文本文件，对于table而言是行数或列数即int

template < typename value_t >
class dlist: public container < value_t > {
//-----------------------------------------------------公有的类型定义
public:
  using value_type = typename container<value_t>::value_type;
  using pointer = typename container<value_t>::pointer;
  using reference = typename container<value_t>::reference;
  using callback = void (value_type&);

//-----------------------------------------------------结点的定义——本质上由模板给出
private:

  struct node {
    value_type data//数据域，可以是一个数据库，也可以是一个表，也可以是表中的数据，由模板给出

    node *next = nullptr, *prior = nullptr; //指针域

    //指定默认构造函数
    node() = default;

    //调用该构造函数通过传参直接创建一个带有前驱，后继，数据的结点 
    node(node *n, node *p, value_type d) :next(n), prior(p),data(d) {}

  }

  node head, tail;    //头尾节点
  size_t length;      //节点数

  using nodeptr_t = node*;    //定义节点指针类型
  using range = nodeptr_t;

//内部的操作，用于提高代码的重用性

  //获取当前结点的内容
  reference _get(const nodeptr_t p) try {
    if (empty()) //链表空时抛出异常
    throw std::out_of_range("empty list");

    return p->data;
  } catch (std::out_of_range &e) { //捕获异常
    std::cout << e.what() << std::endl;
    exit(1);
  }

  //将节点p插入到节点pre之后--此时并未给出p的next和prior，会在调用该函数声明结点p时显示给出
  void _push(const nodeptr_t pre, const nodeptr_t p) noexcept {
    pre->next->prior = p;
    pre->next = p;

    ++length;
  }

  //在节点pre之后删除一个节点
  void _pop(const nodeptr_t pre) try {
    if (empty())
    throw std::out_of_range("empty list");

    auto p = pre->next;
    pre->next = p->next;
    p->next->prior = pre;
    delete p;

    --length;
    } catch (std::out_of_range &e) {
      std::cout << e.what() << std::endl;
      exit(1);
    }

public:
//----------------------------------------------类的构造函数和析构函数
  //默认构造函数
  dlist() {
    init();
  }

  //重载的构造函数，使之可以一次性创建多个数据-----压入的数据类型也是由模板给出，体现了模板的优点
  dlist(const std::initializer_list<value_type> &l) noexcept : dlist() {
    for (auto &v : l)
    //这里使用尾插法，可同时插入多个结点
    push_back(v);
  }

//----------------------------------类的抽象方法
  //作为链表，应该含有：
  
  //查找结点，a表示第几个结点，找到该节点并返回该节点
  node find(int a) {
    int flag=1;
    auto p = head.next;
    for (; flag<a; p = p->next,++flag)
    ;
    return p;
  }

  //初始化链表l-----一般只在构造函数时调用
  void init() noexcept {
    length = 0;
    head.next = &tail;
    tail.prior = &head;
  }
  
  //链表的头插
  void push_front(const value_type &v) {
    _push(&head, new node(head.next, &head, v));
  }

  //链表的尾插
  void push_back(const value_type &v) {
    _push(tail.prior, new node(&tail, tail.prior, v));
  }

  //得到指定第num结点的数据
  value_type get(int num){
    //运用查找函数找到第num个结点
    auto p=find(num);
    return _get(p);
  }

//------一般database和MDYS都不要求在指定结点插入，只有table类需要在指定行或列之间插入数据-------

  //4.链表指定在节点num后插入
  void push(int num ,const value_type &v){

    //运用查找函数，找到该结点
    auto p=find(num); 
    _push(p,new node(&tail, tail.prior, v))

  }

  //5.链表指定删除第num号节点
  void pop(int num){
    //运用查找函数，找到该结点
    auto p=find(num-1);
    //因为_pop函数是删除参数后面的一个结点，所有num-1
    _pop(p);
    
  }

  // 销毁链表--先这样，等会试试能不能用迭代器完成
  void destroy() noexcept {
    for (auto p = head.next; p != &tail; p = head.next) {
    head.next = p->next;
    delete p;
    }

    init();
  }

  /*析构函数，会删除整个链表-----因为是数据库，函数结束后貌似不能将资源析构掉？
  ~dlist() {
  destroy();
  }
  */
//-------------------------------------------------------------------------
//迭代器设定
//定义迭代器类
//在外部类里声明友元，使外部类能访问iterator的内部私有成员

//------------------还没想好迭代器怎么用，先使用find函数即可---------------------
//-------------------------------------------------------------------------


// friend class iterator; 

// class iterator {
// public:
//   //container类型使dlist
//   using container_t = dlist;
//   //typename关键词告诉编译器将后面的东西解释为类型名
//   using value_type = typename container_t::value_type;
//   using reference = typename container_t::reference;
//   using difference_type = typename container_t::difference_type;

// private:
//   using range = typename container_t::range;

//   //这个迭代器实际上是一个原生指针的包装类
//   //所以，迭代器内部有一个指向容器存储的指针
//   //p用于指向结点
//   range p;
//   //cp用于指向该容器本身
//   container_t *cp;

// public:
//   //构造器和析构器
//   iterator(range r = nullptr, container_t *pc = nullptr) noexcept : p(r), cp(pc) {}
//   ~iterator() noexcept {}
// //-------------运算符重载，其中itr.p理解为range------------------
//   //重载的!=运算符

//   bool operator!=(const iterator &itr) const {
//     return p != itr.p;
//   }

//   //重载的<运算符
//   //这个是指从当前p指向结点开始，
//   //带const是为了把常量指针this转换成常指针常量
//   //转换的意义在于this指针默认是常量指针，不能把他默认初始化为另一个常量对象，所以要先把this转换从常指针常量，此时在其他地方用const声明对象时就不会报错了
//   bool operator<(const iterator &itr) const {
//     if (p == itr.p) return false;

//     range t = p;
//     while (t != &cp->tail && t != itr.p) t = t->next;
//     return t == itr.p ? true : false;
//   }

//   //重载的++运算符
//    constexpr iterator &operator++() {
//     p = p->next; //内部指针后移
//     return *this;
//   }

//   //重载的--运算符
//   constexpr iterator &operator--() {
//     p = p->prior; //内部指针前移
//     return *this;
//   }

//   //重载的*运算符
//   reference operator*() {
//    return p->data;
//   }

//   //重载的->运算符
//   auto operator->() {
//     return p;
//   }

//   operator range() {
//     return p;
//   }


// constexpr iterator begin() {
//   return iterator(head.next, this);
// }

// constexpr iterator end() {
//   return iterator(&tail, this);
// }

};
