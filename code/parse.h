
#include "byylf_cf.h"

typedef enum
{
    stmtk,  //语句
    expk    //表达式
} Nodekind; ///结点类型

typedef enum
{
    ifk,
    fork,
    whilek,
    returnk,
    assignk,
    funck,
    defineparak,
    maink,
    define_arrayk,
    structk,
    switchk,
    casek,
    breakk,
    defaultk,
    printk
} Stmtkind; ///句子类型

typedef enum
{
    opk,
    constk,
    idk,
    cite_arrayk
} Expkind; ///表达式类型

typedef struct treenode
{
    struct treenode *child[4]; //也就for能有四个儿子
    struct treenode *sibling;
    int lineno;
    Nodekind nodekind; //节点类型：语句/表达式
    union
    {
        Stmtkind stmt; //语句
        Expkind exp;   //表达式
    } kind;
    Token attr;
} treenode;

///参考编译原理及实践的树结构的定义
///（Expkind）操作符，常量，标识符（变量名，函数名（idk））
//变量、常量、函数返回值的类型 包括INT,FLOAT,CHAR,DOUBLE,VOID

void parse();
extern Token token_table[100];
extern treenode *tree_table[1000]; //显示结果的表
