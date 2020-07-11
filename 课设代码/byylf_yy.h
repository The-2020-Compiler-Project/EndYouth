#pragma once//递归子程序翻译法
#ifndef byylf_yy_H
#define byylf_yy_H
#include<iostream>
#include<string>
#include<stack>
#include <strstream>
#include"symbol_table.h"//符号表操作
#include "parse.h"
using namespace std;


#define MAX 100


struct Target {//四元式操作对象，可为不同类型
    string target_s;
    int target_i;
    float target_f;
};



/*程序区*/
//将i转换为string类型
string int_string();
//复合语句，不用返回，不用传值（全局变量）
void compound_sentence();
//值参表子程序（有缺陷）
void value_parameter();
//有返回值函数调用语句子程序（有缺陷）
void value_function_call();
//无返回值函数调用语句子程序（有缺陷）
void novalue_function_call();
//因子子程序
void factor_();
//项子程序
void item();
//表达式子程序
void expresion();
//赋值语句子程序
void assignment_sentence();
//写语句子程序
void write_sentence();
//读语句子程序
void read_sentence();
//返回语句子程序
void return_sentence();
//参数表子程序
void parameter_list(ParamList p1);
//有返回值函数定义子程序
void value_function();
//无返回值函数定义子程序
void novalue_function();
//条件语句
void conditonal_sentence();
//条件
void condition();
//循环语句
void loop_sentence();
//语句
void sentence();
//程序
void program();
//变量定义
void var_df();
//声明头部
void head_state();
//主函数
void main_function();
void byylf_yy();
#endif