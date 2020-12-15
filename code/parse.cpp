
#include "byylf_cf.h"
#include "parse.h"
#include <bits/stdc++.h>
using namespace std;
static treenode *entitypara_list();           //用于自定义函数的参数
static treenode *BUER_stmt();                 //布尔运算语句
static treenode *newlnodestmt(Stmtkind stmt); //申请语句结构结点
static treenode *newlnodeexp(Expkind exp);    //申请算式结构结点
static treenode *term();                      //带乘除的算术式
static treenode *factor();                    //主要对于加减已经更低等级模块
static treenode *structure_stmt();            //一个代码块{}
static treenode *instmt_sequence();           //语句结构集合
static treenode *for_stmt();                  //for语句
static treenode *while_stmt();                //while语句
static treenode *if_stmt();                   //if语句
static treenode *switch_stmt();               //switch语句
static treenode *case_stmt();                 //case语句
static treenode *break_stmt();                //break语句
static treenode *print_stmt();                //printf语句
static treenode *default_stmt();              //default语句
static treenode *statement();                 //基本语句
static treenode *definepara_stmt();           //定义参数
static treenode *quotepara_list();            //函数调用的参数
static treenode *exp2();                      //四则运算
static treenode *fun_apply();                 //函数调用
static treenode *assign_stmt();               //赋值语句
static treenode *define_assign();             //定义语句
static treenode *exp();                       //四则运算的更低模块
static treenode *simple_exp();                //更简单的运算模块
static treenode *input_para_list();           //输入的参数
static treenode *struct_stmt();               //结构体语句
int isin_first_instmt_sequence();             //token是否在语句序列中
void parse_printtree();                       //输出抽象语法树
void printtree(treenode *lnode);
void printnode(treenode *lnode);
void parse();                     //语法分析开始
void gettoken();                  //获取token
void match(string expectedtoken); //匹配
int count_row();                  //计算token所在行数，主要用与语义分析
int isdtype();                    //是否是定义类型
int iscomparison_op();            //判断是否是比较运算符
int array_judge(int p);
int line_num_table[1000];
int lineno;
int tokenno;
string token;
int mainno = 0;                                               /**用于判断main函数的个数**/
int ptokenno = 0;                                             /**当前记号的计数器。从第0个开始，总是对应当前记号的前一个**/
int printtree_t = 0;                                          /**输出语法树的参数**/
treenode *tree_root;                                          /**语法树的根**/
treenode *tree_table[1000];                                   //显示结果的表
int treenum = 0;                                              //根数的数量
string dtype[4] = {"INTTK", "FLOATTK", "CHARTK", "DOUBLETK"}; /**变量或函数返回值（除VO"IDENFR"以外）的类型**/

//匹配词法中识别的token,并取下一个记号
void match(string expectedtoken)
{

    if (expectedtoken == token)
    {
        gettoken();
    }
    else
    {
        printf("dont match");
    }
}
/**获得结点**/
void gettoken()
{
    token = token_table[ptokenno].code;
    ptokenno++;
}

//计算记号位于源代码的哪一行
int count_row()
{
    int i;
    for (i = 1; i <= lineno; i++)
    {
        if ((ptokenno - 1) <= line_num_table[i])
            return i;
    }
}

void parse()
{
    tokenno = ct_num;
    treenode *newtemp = NULL; //下一个点
    treenode *temp = NULL;    //当前点
    treenode *root = NULL;    //根结点
    treenode *dakuohao;       //大括号
    gettoken();
    int root_tag = 0; //用于根节点的判断

    while (ptokenno < tokenno)
    {
        if (isdtype() || (token == "STRUCTTK"))
        {
            if (token == "INTTK" && token_table[ptokenno].code == "MAINTK") //int main
            {

                root_tag++;
                newtemp = newlnodestmt(maink);
                match("INTTK");   //int
                match("MAINTK");  //main
                match("LPARENT"); //(
                if (token != "RPARENT")
                {
                    newtemp->child[1] = entitypara_list(); //参数列表
                }
                match("RPARENT");
                if (token != "LBRACE")
                {
                    printf("error", count_row());
                }
                else
                {
                    newtemp->child[2] = structure_stmt(); /**函数实体结构**/
                }
                mainno++;
            }
            else if (token_table[ptokenno].code == "IDENFR" && token_table[ptokenno + 1].code == "LPARENT") //自定义函数
            {
                root_tag++;
                newtemp = newlnodestmt(funck); //动态申请一条语句结构的节点
                match(token);
                treenode *j = newlnodeexp(idk);
                match("IDENFR");
                newtemp->child[0] = j; //自定义函数名
                match("LPARENT");

                if (token != "RPARENT")
                {
                    newtemp->child[1] = entitypara_list(); //参数列表
                }

                match("RPARENT");
                if (token != "SEMICN" && token != "LBRACE")
                {
                    printf("error missing && function error\n");
                }

                else
                {
                    newtemp->child[2] = structure_stmt();
                }
            }
            else if (token == "STRUCTTK" && token_table[ptokenno].code == "IDENFR" && token_table[ptokenno + 1].code == "LBRACE")
            {
                root_tag++;
                newtemp = newlnodestmt(structk);
                match(token);
                treenode *j = newlnodeexp(idk);
                match("IDENFR");
                newtemp->child[0] = j;

                if (token == "LBRACE")
                {
                    newtemp->child[1] = structure_stmt(); //这里为了简化赋值
                }
            }
            else //变量声明--全局  if(token=="IDENFR")
            {
                root_tag++;
                newtemp = newlnodestmt(defineparak);

                match(token);

                if (token != "IDENFR")
                {
                    printf("变量定义有误\n", count_row());
                }

                newtemp->child[0] = define_assign();

                if (token != "SEMICN")
                {
                    printf("error ;", count_row);
                }
                else
                    match(token);
            }

            if (temp != NULL)
                temp->sibling = newtemp;
            temp = newtemp;

            if (root_tag == 1)
                root = temp;
        }

        else
        {
            if (token == "IDENFR")
            {
                printf("未定义\n");
            }
            else
            {
                printf("error\n");
            }
        }
    }
    if (mainno != 1)
    {
        printf("没有主函数\n", count_row());
    }

    tree_root = root;
    //打印抽象语法树
    parse_printtree();
    cout << "语法树的数量：" << treenum << endl;
    //    for(int i=0;i<treenum;i++)
    //        printnode(tree_table[i]);
}

/**申请一条语句结构的节点
if for while return assign fun define main define**/
treenode *newlnodestmt(Stmtkind stmt)
{
    /**为新结点初始化**/
    treenode *t = (treenode *)malloc(sizeof(treenode));
    t->nodekind = stmtk;
    t->kind.stmt = stmt;
    t->lineno = count_row();
    int i;
    for (i = 0; i < 4; i++)
        t->child[i] = NULL;
    t->sibling = NULL;
    if (stmt == maink) /**如果是主函数**/
    {
        t->attr.code = token;
    }

    if (stmt == defineparak) /**如果是定义**/
    {
        t->attr.code = token;
    }

    if (stmt == funck)
    {
        if (isdtype())
            t->attr.code = token;
    }
    return t;
}

//服务于自定义函数的参数  形如 fun(int a,int b)
treenode *entitypara_list()
{
    treenode *t;
    treenode *temp;
    treenode *temp1;
    treenode *newtemp;

    temp = newlnodestmt(defineparak);
    t = temp; //先把返回的首地址控制住
    if (isdtype())
    {
        match(token);
    }
    else
    {
        printf("error 函数参数有误");
    }

    newtemp = newlnodeexp(idk);
    match("IDENFR");
    temp->child[0] = newtemp;

    while (token == "COMMA") // 不止一个参数时
    {
        match("COMMA");
        temp1 = newlnodestmt(defineparak);

        if (isdtype())
        {
            match(token);
        }
        else
        {
            printf("error ");
        }

        newtemp = newlnodeexp(idk);
        match("IDENFR");
        temp1->child[0] = newtemp;
        temp->sibling = temp1; //出过bug 注意这里指针的变换
        temp = temp1;
    }

    if (token != "RPARENT")
    {
        printf("error !  括号不匹配！！");
    }

    return t;
}

/**
*申请一条算式结构expk的节点，语句内容的类型如下
*opk(+ - * / 还有一些关系操作符),constk,idk
**/

//操作符，常量，标识符（变量名，函数名（idk））
treenode *newlnodeexp(Expkind exp)
{
    //初始化
    treenode *t = (treenode *)malloc(sizeof(treenode));
    t->nodekind = expk;
    t->kind.exp = exp;
    t->lineno = count_row();
    int i;
    for (i = 0; i < 4; i++)
    {
        t->child[i] = NULL;
    }

    t->sibling = NULL;
    //    cout<< token_table[ptokenno-1].loc;

    //如果为操作符
    if (exp == opk)
    {
        t->attr.code = token;
    }

    //如果为常量
    if (exp == constk)
    {
        t->attr.code = token_table[ptokenno - 1].code;
        //        cout<<token_table[ptokenno - 1].code<<endl;
        t->attr.loc = token_table[ptokenno - 1].loc;
        //        cout<<intcon[t->attr.loc]<<endl;
    }

    //如果为变量名、或函数名（标识符）
    if (exp == idk && token_table[ptokenno].code != ".")
    {
        t->attr.code = token_table[ptokenno - 1].code;
        t->attr.loc = token_table[ptokenno - 1].loc;
    }

    //后期加进来的 为struct类型服务
    if (exp == idk && token_table[ptokenno].code == ".")
    {
        string struct_temp1 = "";
        string struct_temp3 = "";
        string struct_temp4 = "";

        struct_temp1 = token_table[ptokenno - 1].code;
        //strcpy(struct_temp2,token_table[ptokenno].code);
        struct_temp3 = token_table[ptokenno + 1].code;
        int i = 0, j = 0;
        while (struct_temp1[j] != '\0')
        {
            struct_temp4[i] = struct_temp1[j];
            i++;
            j++;
        }
        struct_temp4[i] = '.';
        i++;
        j = 0;
        while (struct_temp3[j] != '\0')
        {
            struct_temp4[i] = struct_temp3[j];
            i++;
            j++;
        }
        t->attr.code = struct_temp4;
    }
    return t;
}

/***********************************************************
* 功能:以大括号开始的一个大结构
        比如： for if  while  main fun
**********************************************************/
treenode *structure_stmt()
{
    treenode *t = NULL;
    treenode *temp = NULL;
    treenode *newtemp;
    int k = 0;
    match("LBRACE");
    while (isin_first_instmt_sequence()) /**当前Token是否在instmt-sequence的定义集合里**/
    {
        k++;
        newtemp = instmt_sequence(); //开始各自的语句

        if (temp != NULL)
        {
            temp->sibling = newtemp;
        }

        temp = newtemp;
        if (k == 1)
        {
            t = temp; //把头结点固定住 以便返回
        }
    }
    match("RBRACE");
    return t;
}
//为了判断是不是这些语句比如 for if while 定义 返回
int isin_first_instmt_sequence()
{
    string first_instmt[15] = {"FORTK", "WHILETK", "IFTK", "INTTK", "FLOATTK",
                               "CHARTK", "DOUBLETK", "IDENFR", "RETURNTK",
                               "STRUCTTK", "SWITCHTK", "CASETK", "BREAKTK",
                               "DEFAUTK", "PRINTFTK"};
    int i = 0;
    for (i = 0; i < 20; i++)
    {
        if (token == first_instmt[i])
            return 1;
    }
    return 0;
}

/**FORTK "IFTK" "WHILETK" 定义 PRINTF SCANF语句 "RETURNTK" 等等**/
treenode *instmt_sequence()
{
    treenode *t = NULL;

    /**for循环 !!**/
    if (token == "FORTK")
    {
        t = for_stmt();
    }
        /**"IFTK"语句 !!**/
    else if (token == "IFTK")
    {
        t = if_stmt();
    }
        /**while语句 !!**/
    else if (token == "WHILETK")
    {
        t = while_stmt();
    }
        /**struct语句 !!**/
    else if (token == "SWITCHTK")
    {
        t = switch_stmt();
    }
        /**case语句 !!**/
    else if (token == "CASETK")
    {
        t = case_stmt();
    }
        /**case语句 !!**/
    else if (token == "BREAKTK")
    {
        t = break_stmt();
    }
    else if (token == "PRINTFTK")
    {
        t = print_stmt();
    }
    else if (token == "DEFAULTTK")
    {
        t = default_stmt();
    }
    else
    {
        t = statement(); //  普通语句有很多--函数调用，定义，赋值 return等等
        if (token != "SEMICN")
        {
            printf("missing ';' %d ", count_row()); //如果为定义语句；打印；输入语句，则后面判断有没有分号
        }
        else
        {
            match("SEMICN");
        }
    }

    return t;
}

//for语句
treenode *for_stmt()
{
    treenode *t = NULL;
    treenode *temp;

    t = newlnodestmt(fork);

    match("FORTK");
    match("LPARENT");

    if (token != "SEMICN")
    {
        if (token == "INTTK")
        {
            t->child[0] = definepara_stmt();
        }
        else
        {
            t->child[0] = exp2();
        }
    }

    match("SEMICN");
    if (token != "SEMICN")
    {
        if (token_table[ptokenno].code == "ASSIGN")
        {
            printf("warning!! 不能为赋值等式");
        }
        else
        {
            t->child[1] = exp2();
        }
    }

    match("SEMICN");

    if (token != "RPARENT")
    {
        t->child[2] = exp2();
    }

    match("RPARENT");

    if (token == "SEMICN")
    {
        match("SEMICN");
        return t;
    }

    t->child[3] = structure_stmt();
    return t;
}

int ifelse_tag = 0;
treenode *if_stmt()
{
    treenode *t;
    t = newlnodestmt(ifk);
    match("IFTK");
    match("LPARENT");
    if (token_table[ptokenno].code == "ASSIGN" && token_table[ptokenno + 1].code != "ASSIGN")
    {
        printf("warning");
    }
    t->child[0] = BUER_stmt();
    match("RPARENT");
    t->child[1] = structure_stmt();

    if (token == "ELSETK" && token_table[ptokenno].code == "IFTK")
    {
        match("ELSETK");
        t->child[2] = if_stmt();
        ifelse_tag = 1;
    }
    if (token == "ELSETK" && token_table[ptokenno].code != "IFTK")
    {
        match("ELSETK");
        t->child[2] = structure_stmt();
    }

    return t;
}
treenode *BUER_stmt()
{
    treenode *t;
    treenode *t1;
    treenode *t2;
    if (token_table[ptokenno + 2].code == "ANDTK" || token_table[ptokenno + 3].code == "ANDTK" ||
        token_table[ptokenno + 2].code == "ORTK" || token_table[ptokenno + 3].code == "ORTK")
    {
    }
    else
    {
        t = exp2();
    }
    return t;
}
//主要用于FORTK ,"IFTK" while ,你不知道是赋值还是关系运算。
treenode *exp2()
{
    treenode *t;
    if (token == "IDENFR" && token_table[ptokenno].code == "ASSIGN")
    {
        t = assign_stmt();
    }
    else
    {
        t = exp();
    }
    return t;
}

/***********************************************************
 * 功能:	while语句
 **********************************************************/
treenode *while_stmt()
{
    treenode *t = newlnodestmt(whilek);
    match("WHILETK");
    match("LPARENT");
    t->child[0] = exp2();
    match("RPARENT");
    if (token == "LBRACE")
        t->child[1] = structure_stmt();
    return t; //!!!这个bug 找了好久呀！！！
}
/***********************************************************
 * 功能:	switch语句
 **********************************************************/
treenode *switch_stmt()
{
    treenode *t = newlnodestmt(switchk);
    match("SWITCHTK");
    match("LPARENT");
    t->child[0] = exp2();
    match("RPARENT");
    if (token == "LBRACE")
    {
        t->child[1] = structure_stmt();
    }
    return t;
}
//用于case语句段
treenode *case_stmt()
{
    treenode *t = newlnodestmt(casek);
    match("CASETK");
    treenode *j = newlnodeexp(constk);
    if (token == "IDENFR")
    {
        treenode *j = newlnodeexp(idk);
    }

    t->child[0] = j;
    if (token == "IDENFR")
        match("IDENFR");
    else
        match("INTCON");
    match("COLONTK");
    if (token == "LBRACE")
    {
        t->child[1] = structure_stmt();
    }
    return t;
}
//用于break语句
treenode *break_stmt()
{
    treenode *t = newlnodestmt(breakk);
    match("BREAKTK");
    match("SEMICN");
    return t;
}
treenode *print_stmt()
{
    treenode *t = newlnodestmt(printk);
    match("PRINTFTK");
    match("LPARENT");
    treenode *j = newlnodeexp(constk);
    t->child[0] = j;
    match("STRCON");
    match("RPARENT");
    match("SEMICN");
    return t;
}
//用于default语句
treenode *default_stmt()
{
    treenode *t = newlnodestmt(defaultk);
    match("DEFAUTK");
    match("COLONTK");
    if (token == "LBRACE")
    {
        t->child[0] = structure_stmt();
    }
    return t;
}
treenode *statement()
{
    treenode *t = NULL;
    /**如果是dtype，则为定义语句**/
    if (isdtype())
    {
        t = definepara_stmt();
    }
    else if (token == "RETURNTK")
    {
        t = newlnodestmt(returnk);
        match("RETURNTK");
        t->child[0] = exp();
    }
    else if (token == "STRUCTTK")
    {
        t = definepara_stmt();
    }
    else if (token == "IDENFR") /**函数调用,数组定义，变量的赋值**/
    {
        int tag_array = array_judge(ptokenno);

        if (token_table[ptokenno].code == "ASSIGN" || tag_array == 1)
        {
            t = assign_stmt(); //数组或变量赋值(变量可能为函数调用的结果)
        }
        else if (token_table[ptokenno].code == "LPARENT")
        {
            t = fun_apply(); // 函数调用
        }
        else if (token_table[ptokenno].code == "POINTTK" && token_table[ptokenno + 2].code == "ASSIGN")
        {
            t = assign_stmt();
        }
        else //if()待写  感觉不用条件
        {
            t = exp();
        }
    }
    return t;
}
/***********************************************************
 * 功能:	函数调用  fun(a,b)
 **********************************************************/
treenode *fun_apply()
{
    treenode *t;
    t = newlnodestmt(funck);
    treenode *temp1 = newlnodeexp(idk);
    match("IDENFR");
    match("LPARENT");
    treenode *temp2 = input_para_list();
    t->child[0] = temp1;
    t->child[1] = temp2;
    match("RPARENT");
    return t;
}

//参数列表 服务于函数调用里的参数 比如fun(1,2)
treenode *input_para_list()
{
    treenode *t;
    treenode *temp;
    temp = factor();
    t = temp;
    while (token == "COMMA")
    {
        match("COMMA");
        temp->sibling = factor();
        temp = temp->sibling;
    }
    return t;
}
int array_judge(int p)
{
    if (token_table[p].code == "LBRACK")
    {
        int i;
        for (i = p + 1; i < 1000; i++) //有bug！！。。。
        {
            if (token_table[i].code == "RBRACK")
            {
                return 1;
            }
        }
        return -1;
    }
    return -1;
}

/**判断当前记号是否是变量或函数返回值（除VO"IDENFR"以外）**/
int isdtype()
{
    int i = 0;
    for (; i < 4; i++)
    {
        if (token == dtype[i])
            return 1;
    }
    return 0;
}

/**定义语句**/
treenode *definepara_stmt()
{
    treenode *t = NULL;
    t = newlnodestmt(defineparak);

    if (isdtype())
    {
        match(token); //dtype
    }
    else if (token == "STRUCTTK")
    {
        match(token);
        match("IDENFR"); //把整个struct XX match掉
    }

    else
        printf("arguement has no type", count_row());

    t->child[0] = define_assign();
    return t;
}

/**变量赋值定义  数组的定义,初始化，初始化和定义的同时进行**/
treenode *define_assign()
{
    treenode *t = NULL;
    treenode *temp = NULL;
    treenode *newtemp;
    int k = 0;

    if (token_table[ptokenno].code == "SEMICN")
    {
        k++;
        newtemp = newlnodeexp(idk);
        match("IDENFR");
        //        newtemp -> loc = token_table[ptokenno-2].loc;
        //match("SEMICN");
        return t = newtemp;
    }
    /**支持变量定义初始化，连续定义等**/
    while (token_table[ptokenno].code == "ASSIGN" || token_table[ptokenno].code == "COMMA" || token_table[ptokenno].code == "SEMICN" || token_table[ptokenno].code == "LBRACK")

    {

        if (token_table[ptokenno].code == "ASSIGN") /**赋值语句**/
        {
            k++;
            newtemp = assign_stmt();
            if (temp != NULL)
            {
                temp->sibling = newtemp;
            }
            temp = newtemp;
            if (token == "COMMA")
            {
                match("COMMA");
            }
            if (k == 1)
            {
                t = temp;
            }
        }
        else if (token_table[ptokenno].code == "COMMA")
        {
            k++;
            newtemp = newlnodeexp(idk);
            match("IDENFR");
            match("COMMA");
            if (temp != NULL)
            {
                temp->sibling = newtemp;
            }
            temp = newtemp;
            if (k == 1)
            {
                t = temp;
            }
        }

        else if (token_table[ptokenno].code == "SEMICN")
        {
            k++;
            newtemp = newlnodeexp(idk);
            match("IDENFR");
            if (temp != NULL)
            {
                temp->sibling = newtemp;
            }
            temp = newtemp;
            if (k == 1)
            {
                t = temp;
            }
        }
        else if (token_table[ptokenno].code == "LBRACK") //数组部分！！
        {
            k++;

            newtemp = newlnodestmt(define_arrayk);
            treenode *t1 = newlnodeexp(idk);
            match("IDENFR");
            newtemp->child[0] = t1;

            match("LBRACK");
            if (token != "INTCON" && token != "RBRACK") //一些语义分析
            {
                printf("error!!数组定义有误");
            }
            if (token == "INTCON")
            {
                treenode *t2 = newlnodeexp(constk);
                match("INTCON");
                newtemp->child[1] = t2;
            }
            match("RBRACK");
            if (temp != NULL)
            {
                temp->sibling = newtemp;
            }
            temp = newtemp;
            if (token == "COMMA")
            {
                match("COMMA");
            }
            if (k == 1)
            {
                t = temp;
            }
        }
        else
        {
            printf("there should be assignment statement or variable", count_row());
        }
    }
    return t;
}

/**赋值语句  数组的赋值后期加进来！！！！**/
treenode *assign_stmt()
{
    treenode *t1;
    if (token_table[ptokenno].code == "LBRACK") //数组赋值  形如a[1] a[2]
    {
        t1 = newlnodeexp(cite_arrayk);
        treenode *t2 = newlnodeexp(idk);
        match("IDENFR");
        t1->child[0] = t2;
        match("LBRACK");
        t1->child[1] = exp2(); //直接是factor里的数字结构了；
        match("RBRACK");
    }
    else if (token_table[ptokenno].code == "POINTTK") //为struct结构专门定义
    {
        t1 = newlnodeexp(idk);
        match("IDENFR");
        match("POINTTK");
        match("IDENFR");
    }
    else
    {
        t1 = newlnodeexp(idk);
        match("IDENFR");
    }
    match("ASSIGN"); //不需要将=匹配成op

    //opk="ASSIGN"
    treenode *t = newlnodestmt(assignk);
    t->child[0] = t1;
    t->child[1] = exp();
    return t;
}

//  simple_exp conpare simple_exp   ||simple_exp
treenode *exp()
{
    treenode *t;
    treenode *temp;

    temp = simple_exp();
    //简单表达式
    if (iscomparison_op())
    {
        t = newlnodeexp(opk);
        match(token);
        t->child[0] = temp;
        t->child[1] = simple_exp();
    }
    else
    {
        t = temp;
    }

    return t;
}

int iscomparison_op()
{
    string compare_op[6] = {"LSS", "LEQ",
                            "GRE", "GEQ",
                            "NEQ", "EQL"}; //< <= > >= != ==
    int i;
    for (i = 0; i < 6; i++)
    {
        if (token == compare_op[i])
        {
            return 1;
        }
    }
    return 0; //没有匹配上
}

//简单表达式 加减
treenode *simple_exp()
{
    treenode *t = NULL;
    treenode *newtemp;
    treenode *temp;

    temp = term();

    //加法或减法语句
    while (token == "PLUS" || token == "MINU")
    {
        newtemp = newlnodeexp(opk);
        match(token);
        //子节点分别为左右两个term
        newtemp->child[0] = temp;
        newtemp->child[1] = term();
        temp = newtemp;
    }
    t = temp;
    return t;
}

//主要是乘除
treenode *term()
{
    treenode *t = NULL;
    treenode *temp;
    treenode *newtemp;

    temp = factor();

    while (token == "MULT" || token == "DIV")
    {
        newtemp = newlnodeexp(opk);
        match(token);
        newtemp->child[0] = temp;
        newtemp->child[1] = factor();
        temp = newtemp;
    }

    return t = temp;
}

//最基本的单模块
treenode *factor()
{
    treenode *t = NULL;

    //带括号的表达式
    if (token == "LPARENT")
    {
        match("LPARENT");
        t = exp();
        match("RPARENT");
    }

    //变量---可能为函数调用语句，可能为数组，可能为普通变量
    if (token == "IDENFR")
    {
        if (token_table[ptokenno].code == "LPARENT") //函数调用
        {
            t = fun_apply();
        }
        else if (token_table[ptokenno].code == "LBRACK") //数组
        {
            t = newlnodeexp(cite_arrayk);
            treenode *temp1 = newlnodeexp(idk);
            match("IDENFR");
            match("LBRACK");
            treenode *temp2 = exp2(); //可缩小范围factor 即可;
            t->child[0] = temp1;
            t->child[1] = temp2;
            match("LBRACK");
        }
        else //普通变量
        {
            t = newlnodeexp(idk);
            match("IDENFR");
        }
    }

    //数字
    if (token == "INTCON")
    {
        t = newlnodeexp(constk);
        t->attr.code = token_table[ptokenno - 1].code;
        t->attr.loc = token_table[ptokenno - 1].loc;

        match("INTCON");
    }
    else if (token == "FLOATCON")
    {
        t = newlnodeexp(constk);
        t->attr.code = token_table[ptokenno - 1].code;
        t->attr.loc = token_table[ptokenno - 1].loc;

        match("FLOATCON");
    }
    else if (token == "CHARCON")
    {
        t = newlnodeexp(constk);
        t->attr.code = token_table[ptokenno - 1].code;
        t->attr.loc = token_table[ptokenno - 1].loc;

        match("CHARCON");
    }

    return t;
}

/** ** **** **** *****   *******       输出抽象语法树的过程  *******   *****  ******   *****/

void parse_printtree()
{
    treenode *t = tree_root;
    printtree(t);
}

//树
void printtree(treenode *lnode)
{
    int i;
    treenode *pnode;
    int TAG = printtree_t;
    for (i = 0; i < TAG; i++)
        printf("        ");
    printnode(lnode);
    tree_table[treenum++] = lnode;
    printf("\n");
    printtree_t++;
    for (i = 0; i < 4; i++)
        if (lnode->child[i] != NULL)
        {
            pnode = lnode;
            lnode = lnode->child[i];
            printtree(lnode);
            printtree_t--;
            lnode = pnode;
        }
    if (lnode->sibling != NULL)
    {
        lnode = lnode->sibling;
        printtree_t = TAG;
        printtree(lnode);
    }
}
//打印结点
void printnode(treenode *lnode)
{
    if (lnode->nodekind == expk) //表达式结点
    {

        switch (lnode->kind.exp)
        {
            case idk:
            {
                //            cout<<idenfr[lnode->attr.loc] ;
                //                cout<<lnode->attr.loc<<endl;
                cout << "id= \"" << idenfr[lnode->attr.loc] << "\"";
                break;
            }
            case opk:
            {
                token = lnode->attr.code;
                cout << "op=  " << token << endl;
                break;
            }
            case constk:
            {
                //                cout<<lnode->attr.loc<<endl;
                if (lnode->attr.code == "INTCON")
                    cout << "num= " << intcon[lnode->attr.loc] << endl;
                else if (lnode->attr.code == "FLOATCON")
                    cout << "num= " << floatcon[lnode->attr.loc] << endl;
                else if (lnode->attr.code == "CHARCON")
                    cout << "char = " << charcon[lnode->attr.loc] << endl;
                else if (lnode->attr.code == "STRCON")
                    cout << "string = " << stringcon[lnode->attr.loc] << endl;
            }
                //            case cite_arrayk:
                //            {
                //                cout<<"array_id :"<< lnode->child[0]->attr.code;
                //                break;
                //            }
        }
    }
    else if (lnode->nodekind == stmtk) //stmtk  //函数结点
    {
        switch (lnode->kind.stmt)
        {
            case ifk:
            {
                printf("[if]");
                break;
            }
            case fork:
            {
                printf("[for]");
                break;
            }
            case whilek:
            {
                printf("[while]");
                break;
            }

            case returnk:
            {
                printf("[return]");
                break;
            }

            case assignk:
            {
                printf("[assign:]");
                break;
            }
            case funck:
            {
                token = lnode->attr.code;
                if (lnode->child[2] != NULL)
                {
                    printf("function : type is ");
                    cout << token << endl;
                }
                else
                {
                    printf("[callfunc] : ");
                }

                break;
            }
            case defineparak:
            {
                token = lnode->attr.code;
                printf("definepara : ");
                cout << token << endl;
                break;
            }
            case maink:
            {
                printf("[main]");
                break;
            }
            case define_arrayk:
            {
                printf("[definearray]");
                break;
            }
            case structk:
            {
                printf("[struct]");
                break;
            }
            case casek:
            {
                printf("[case]");
                break;
            }
            case breakk:
            {
                printf("[break]");
                break;
            }
            case switchk:
            {
                printf("[switch]");
                break;
            }

            case defaultk:
            {
                printf("[default]");
                break;
            }
            case printk:
            {
                printf("[printf]");
                break;
            }

            default:
                printf("error1!!!");
        }
    }
    else
    {
        printf("节点有误！！");
    }
}
