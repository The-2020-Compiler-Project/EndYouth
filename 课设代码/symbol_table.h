#ifndef UNTITLED3_SYMBOL_TABLE_H
#define UNTITLED3_SYMBOL_TABLE_H

#include <bits/stdc++.h>
using namespace std;
#define SIZE 211

#define SHIFT 4
enum
{
    Int,
    Float,
    Char,
    Bool
};
//常量， 变量， 指针
typedef class List

{

    public:
    string name; //标识符名

    int type; //标识符数据类型

    long scope; //标识符作用域信息

    long memloc; //内存中的位置

    int flag; //常量， 变量， 指针的标志（1， 2， 3）

    List *next;

} * BucketList;


//数组

typedef class Array

{

public:
    string name; //标识符名

    int type; //标识符数据类型

    long scope; //标识符作用域信息

    long memloc; //数组首地址

    int weishu; //数组维数

    string spec; //数组大小,a[2][3]--->spec=2*3;

    Array *next;

} * ArrayList;

typedef class Param

{

public:
    int type; //参数类型

    string name; //参数名

    Param *next;

} * ParamList;

//函数

typedef class Function

{

public:
    string name; //函数名

    int type; //返回值类型

    ParamList pl; //参数列表

    long scope; //标识符作用域信息

    long memloc; //函数入口的地址

    Function *next; //异名链表指针

} * FunctionList;



void List_insert(string name, int type, long scope, long loc, int flag);
void List_delete(string name);
long List_find(string name);
void Array_insert(string name, int type, long scope, long loc, int weishu, string spec);
void Array_delete(string name);
long Array_find(string name);
void Function_insert(string name, int type, ParamList pl, long scope, long loc);
void Function_delete(string name);
long Function_find(string name);
void printList();
void printArray();
void printFunction();
void symbol_table();











#endif //UNTITLED3_SYMBOL_TABLE_H
