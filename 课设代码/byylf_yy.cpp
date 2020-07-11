#include "byylf_yy.h"
int now_outcome = 1; //结果是tnow_outcome
int now_qt = 0;      //四元式计数用
stack<Target> SEM;   //语义栈

int now_w = 0; //记录当前待处理数据位置，方便获得新的待处理数据

//treenode w[MAX];//待处理数据表

/*数据区*/
ParamList temp0;

string int_string()
{
    strstream ss;
    string s;
    ss << now_outcome;
    ss >> s;
    now_outcome++;
    return s;
}
struct Quaternion
{
    string operate; //操作
    //有关选择操作对象的类型，根据其分类码选择
    Target target1; //操作对象1
    Target target2; //操作对象2
    Target outcome; //结果
} QT[MAX];          //四元式结构(存放四元式的表)

//复合语句，不用返回，不用传值（全局变量）
void compound_sentence()
{

    if (w[now_w]->attr.code == "INTTK" || w[now_w]->attr.code == "CHARTK" || w[now_w]->attr.code == "FLOATTK")
        var_df(); //直接进到变量说明子函数

    while (w[now_w]->nodekind == 0 || w[now_w]->attr.code == "DOTK" || w[now_w]->attr.code == "WHILETK" || w[now_w]->attr.code == "FORTK")
    {
        if (w[now_w]->attr.code == "MAINTK")
        {
            cout << "error" << endl;
            return;
        }
        if (w[now_w]->attr.code == "END")
        {
            cout << " 程序结束" << endl;
            return;
        }
        sentence(); //z只要是上面的符合，进到语句的子程序去
    }
}
//值参表子程序（有缺陷）
void value_parameter()
{
    expresion(); //进入表达式子程序
    SEM.pop();   //把结果弹出来，以免积压
    while (w[now_w]->attr.code == "COMMA")
    {
        now_w++;
        if (now_w >= treenum)
            return; //获得新的数据
        expresion();
        SEM.pop(); //把结果弹出来，以免积压
    }
}
//有返回值函数调用语句子程序（有缺陷）
void value_function_call()
{
    if (w[now_w]->attr.code == "IDENFR")
    { //判断为标识符
        long i = -1;
        i = Function_find(idenfr[w[now_w]->attr.loc]); //查找在符号表（函数表）中有没有这个标识符
        if (i != -1)
        {
            Target id;
            id.target_s = idenfr[w[now_w]->attr.loc];
            id.target_i = -10000;
            id.target_f = -10000;
            SEM.push(id); //把标识符压栈，以便后续查符号表--函数表的时候找到对应的函数
            now_w++;
            if (now_w >= treenum)
                return;
            if (now_w >= treenum)
                return; //获得新的数据
            if (w[now_w]->attr.code == "LPARENT")
            {
                now_w++;
                if (now_w >= treenum)
                    if (now_w >= treenum)
                        return;    //获得新的数据
                value_parameter(); //进入值参表子程序
                if (w[now_w]->attr.code == "RPARENT")
                    now_w++;
                if (now_w >= treenum)
                    if (now_w >= treenum)
                        return;
            }
        }
    }
    else
    {
    } //有错误
}
//无返回值函数调用语句子程序（有缺陷）
void novalue_function_call()
{
    if (w[now_w]->attr.code == "IDENFR")
    { //判断为标识符
        long i = -1;
        i = Function_find(idenfr[w[now_w]->attr.loc]); //查找在符号表（函数表）中有没有这个标识符
        if (i != -1)
        {
            Target id;
            id.target_s = idenfr[w[now_w]->attr.loc];
            id.target_i = -10000;
            id.target_f = -10000;
            SEM.push(id); //把标识符压栈，以便后续查符号表--函数表的时候找到对应的函数
            now_w++;
            if (now_w >= treenum)
                return;
            if (now_w >= treenum)
                return; //获得新的数据
            if (w[now_w]->attr.code == "LPARENT")
            {
                now_w++;
                if (now_w >= treenum)
                    if (now_w >= treenum)
                        return;    //获得新的数据
                value_parameter(); //进入值参表子程序
                if (w[now_w]->attr.code == "RPARENT")
                    now_w++;
                if (now_w >= treenum)
                    if (now_w >= treenum)
                        return;
            }
        }
    }
    else
    {
    } //有错误
}
//因子子程序
void factor_()
{
    if (w[now_w]->attr.code == "IDENFR")
    { //判断为标识符
        long i = -1;
        i = List_find(idenfr[w[now_w]->attr.loc]); //查找在符号表中有没有这个标识符
        if (i != -1)
        { //表中有
            Target id;
            id.target_s = idenfr[w[now_w]->attr.loc];
            id.target_i = -10000;
            id.target_f = -10000;
            SEM.push(id); //把标识符压栈
            now_w++;
            if (now_w >= treenum)
            {
                now_w--;
                w[now_w]->attr.code = "END";

                return;
            }

            return;
        }
        else
        {
        } //表中没有，有错误
    }
    else if (w[now_w]->attr.code == "LPARENT")
    { //带括号的表达式
        now_w++;
        if (now_w >= treenum)
            return;
        expresion(); //进入表达式子程序中
        if (w[now_w]->attr.code == "RPARENT")
        {
            now_w++;
            if (now_w >= treenum)
                return;
            if (now_w >= treenum)
                return; //获得新的数据
            return;
        }
        else
        {
        } //有错误
    }
    else if (w[now_w]->attr.code == "INTCON")
    { //整型常量
        Target id;
        id.target_s = "#";
        id.target_i = intcon[w[now_w]->attr.loc];
        id.target_f = -10000;
        SEM.push(id); //把整型常量压栈
        now_w++;
        if (now_w >= treenum)
        {
            now_w--;
            w[now_w]->attr.code = "END";

            return;
        }
        return;
    }
    else if (w[now_w]->attr.code == "CHARTON")
    { //字符型常量
        Target id;
        id.target_s = charcon[w[now_w]->attr.loc];
        id.target_i = -10000;
        id.target_f = -10000;
        SEM.push(id); //把字符型常量压栈
        now_w++;
        if (now_w >= treenum)
            return; //获得新的数据
        return;
    }
    else if (w[now_w]->attr.code == "FLOATCON")
    { //浮点型常量
        Target id;
        id.target_s = "#";
        id.target_i = -10000;
        id.target_f = floatcon[w[now_w]->attr.loc];
        SEM.push(id); //把浮点型常量压栈
        now_w++;
        if (now_w >= treenum)
            return; //获得新的数据
        return;
    }
    else if (w[now_w]->nodekind == 0 && w[now_w]->kind.stmt == 5)
    {                          //有返回值函数调用语句
        value_function_call(); //进入有返回值函数调用子程序
        Target re;
        re = SEM.top();
        SEM.pop(); //将函数的名字出栈
        Target op1 = {"_", -10000, -10000};
        Target op2 = {"_", -10000, -10000};
        QT[now_qt++] = {"jmp", op1, op2, re}; //生成跳转子程序四元式
        Target temp;                          //结果(当前结果只是一个替身)
        string num = int_string();            //将数字转为string
        temp.target_s = "t" + num;
        temp.target_i = -10000;
        temp.target_f = -10000;
        SEM.push(temp); //压栈结果(当前结果只是一个替身)
    }
    else
    {
    } //有错误
}
//项子程序
void item()
{
    factor_(); //进入因子子程序
    while (w[now_w]->attr.code == "MULT" && w[now_w]->attr.code == "DIV")
    {
        if (w[now_w]->attr.code == "MULT")
        {
            now_w++;
            if (now_w >= treenum)
                return;
            item();
            Target op1, op2;
            op2 = SEM.top();
            SEM.pop(); //第二个操作数
            op1 = SEM.top();
            SEM.pop();                 //第一个操作数
            Target temp;               //结果
            string num = int_string(); //将数字转为string
            temp.target_s = "t" + num;
            temp.target_i = -10000;
            temp.target_f = -10000;
            SEM.push(temp);                       //压栈结果
            QT[now_qt++] = {"*", op1, op2, temp}; //生成乘法四元式
        }
        else if (w[now_w]->attr.code == "DIV")
        {
            now_w++;
            if (now_w >= treenum)
                return;
            item();
            Target op1, op2;
            op2 = SEM.top();
            SEM.pop(); //第二个操作数
            op1 = SEM.top();
            SEM.pop();                 //第一个操作数
            Target temp;               //结果
            string num = int_string(); //将数字转为string
            temp.target_s = "t" + num;
            temp.target_i = -10000;
            temp.target_f = -10000;
            SEM.push(temp);                       //压栈结果
            QT[now_qt++] = {"/", op1, op2, temp}; //生成除法四元式
        }
        else
            break;
    }
}
//表达式子程序
void expresion()
{
    if (w[now_w]->attr.code == "PLUS")
    {
        now_w++;
        if (now_w >= treenum)
            return; //获得新的数据
        item();
        Target op1, op2;
        op2 = SEM.top();
        SEM.pop();                   //第二个操作数
        op1 = {"_", -10000, -10000}; //第一个操作数
        Target temp;                 //结果
        string num = int_string();   //将数字转为string
        temp.target_s = "t" + num;
        temp.target_i = -10000;
        temp.target_f = -10000;
        SEM.push(temp);                       //压栈结果
        QT[now_qt++] = {"+", op1, op2, temp}; //生成加法四元式
    }
    else if (w[now_w]->attr.code == "MINU")
    {
        now_w++;
        if (now_w >= treenum)
            return; //获得新的数据
        item();
        Target op1, op2;
        op2 = SEM.top();
        SEM.pop();                   //第二个操作数
        op1 = {"_", -10000, -10000}; //第一个操作数
        Target temp;                 //结果
        string num = int_string();   //将数字转为string
        temp.target_s = "t" + num;
        temp.target_i = -10000;
        temp.target_f = -10000;
        SEM.push(temp);                       //压栈结果
        QT[now_qt++] = {"-", op1, op2, temp}; //生成减法四元式
    }
    else
        item();
    while (w[now_w]->attr.code == "PLUS" && w[now_w]->attr.code == "MINU")
    {
        if (w[now_w]->attr.code == "PLUS")
        {
            now_w++;
            if (now_w >= treenum)
                return;
            if (now_w >= treenum)
                return; //获得新的数据
            item();
            Target op1, op2;
            op2 = SEM.top();
            SEM.pop(); //第二个操作数
            op1 = SEM.top();
            SEM.pop();                 //第一个操作数
            Target temp;               //结果
            string num = int_string(); //将数字转为string
            temp.target_s = "t" + num;
            temp.target_i = -10000;
            temp.target_f = -10000;
            SEM.push(temp);                       //压栈结果
            QT[now_qt++] = {"+", op1, op2, temp}; //生成加法四元式
        }
        else if (w[now_w]->attr.code == "MINU")
        {
            now_w++;
            if (now_w >= treenum)
                return;
            if (now_w >= treenum)
                return; //获得新的数据
            item();
            Target op1, op2;
            op2 = SEM.top();
            SEM.pop(); //第二个操作数
            op1 = SEM.top();
            SEM.pop();                 //第一个操作数
            Target temp;               //结果
            string num = int_string(); //将数字转为string
            temp.target_s = "t" + num;
            temp.target_i = -10000;
            temp.target_f = -10000;
            SEM.push(temp);                       //压栈结果
            QT[now_qt++] = {"-", op1, op2, temp}; //生成减法四元式
        }
        else
            break; //都不是，直接出去
    }
}
//赋值语句子程序
void assignment_sentence()
{
    now_w++;
    if (w[now_w - 4]->kind.stmt == define_arrayk)
        now_w++;
    if (now_w > treenum)
        return;
    if (w[now_w]->attr.code == "IDENFR")
    { //判断为标识符
        long i = -1;
        i = List_find(idenfr[w[now_w]->attr.loc]); //查找在符号表中有没有这个标识符
        if (i != -1)
        {
            Target id;
            id.target_s = idenfr[w[now_w]->attr.loc];
            cout << id.target_s << endl;
            //            id.target_i = -10000;
            //            id.target_f = -10000;
            id.target_i = intcon[w[now_w]->attr.loc];
            id.target_f = floatcon[w[now_w]->attr.loc];
            SEM.push(id); //把标识符压栈
            Target re;
            re = SEM.top();
            SEM.pop();
            now_w++;
            if (now_w >= treenum)
                return;  //获得新的数据
            expresion(); //转到表达式子程序
            Target op1, op2;
            op1 = SEM.top();
            SEM.pop(); //第一个操作数
            op2 = {"#", -10000, -10000};
            //结果
            QT[now_qt++] = {"=", op1, op2, re}; //生成赋值四元式
        }
        else
        {
        } //表中没有，有错误
    }
    else
    {
    } //有错误
}
//写语句子程序
void write_sentence()
{
    if (w[now_w]->attr.code == "PRINTFTK")
    {
        now_w++;
        if (now_w >= treenum)
            return; //获得新的数据
        if (w[now_w]->attr.code == "LPARENT")
        {
            now_w++;
            if (now_w >= treenum)
                return;
            if (now_w >= treenum)
                return; //获得新的数据
            if (w[now_w]->attr.code == "STRCON")
            { //判断为字符串
                long i = -1;
                i = Array_find(stringcon[w[now_w]->attr.loc]); //查找在符号表中有没有这个字符串
                if (i != -1)
                { //存在该字符串
                    Target op1, op2;
                    op1 = {"_", -10000, -10000};
                    op2 = {"_", -10000, -10000};
                    Target re = {stringcon[w[now_w]->attr.loc], -10000, -10000};
                    QT[now_qt++] = {"printf", op1, op2, re}; //生成写语句四元式
                    now_w++;
                    if (now_w >= treenum)
                        return;
                    if (now_w >= treenum)
                        return; //获得新的数据
                    if (w[now_w]->attr.code == "COMMA")
                    {
                        now_w++;
                        if (now_w >= treenum)
                            return;
                        if (now_w >= treenum)
                            return;  //获得新的数据
                        expresion(); //进入表达式子程序
                        Target op1, op2;
                        op1 = {"_", -10000, -10000};
                        op2 = {"_", -10000, -10000};
                        Target re;
                        re = SEM.top();
                        SEM.pop();                               //把表达式的结果出栈，进行四元式生成
                        QT[now_qt++] = {"printf", op1, op2, re}; //生成写语句四元式
                        if (w[now_w]->attr.code == "RPARENT")
                            now_w++;
                        if (now_w >= treenum)
                            return;
                        if (now_w >= treenum)
                            return;
                        else
                        {
                        } //有错误
                    }
                    else if (w[now_w]->attr.code == "RPARENT")
                        now_w++;
                    if (now_w >= treenum)
                        return;
                    if (now_w >= treenum)
                        return;
                    else
                    {
                    } //有错误
                }
            }
            else
            {
                expresion(); //进入表达式子程序
                Target op1, op2;
                op1 = {"_", -10000, -10000};
                op2 = {"_", -10000, -10000};
                Target re;
                re = SEM.top();
                SEM.pop(); //把表达式的结果出栈，进行四元式生成
                QT[now_qt++] = {"printf", op1, op2, re};
                if (w[now_w]->attr.code == "RPARENT")
                    now_w++;
                if (now_w >= treenum)
                    if (now_w >= treenum)
                        return;
                    else
                    {
                    } //有错误
            }
        }
        else
        {
        } //有错误
    }
    else
    {
    } //有错误
}
//读语句子程序
void read_sentence()
{
    if (w[now_w]->attr.code == "SCANFTK")
    {
        now_w++;
        if (now_w >= treenum)
            return; //获得新的数据
        if (w[now_w]->attr.code == "LPARENT")
        {
            now_w++;
            if (now_w >= treenum)
                return;
            if (now_w >= treenum)
                return; //获得新的数据
            if (w[now_w]->attr.code == "IDENFR")
            { //判断为标识符
                long i = -1;
                i = List_find(idenfr[w[now_w]->attr.loc]); //查找在符号表中有没有这个标识符
                if (i != -1)
                { //存在该标识符
                    Target op1, op2;
                    op1 = {"_", -10000, -10000};
                    op2 = {"_", -10000, -10000};
                    Target re = {idenfr[w[now_w]->attr.loc], -10000, -10000};
                    QT[now_qt++] = {"scanf", op1, op2, re}; //生成读语句四元式
                    now_w++;
                    if (now_w >= treenum)
                        return;
                    if (now_w >= treenum)
                        return; //获得新的数据
                    while (w[now_w]->attr.code == "COMMA")
                    {
                        now_w++;
                        if (now_w >= treenum)
                            return;
                        if (now_w >= treenum)
                            return; //获得新的数据
                        if (w[now_w]->attr.code == "IDENFR")
                        { //判断为标识符
                            long i = -1;
                            i = List_find(idenfr[w[now_w]->attr.loc]); //查找在符号表中有没有这个标识符
                            if (i != -1)
                            { //存在该标识符
                                Target op1, op2;
                                op1 = {"_", -10000, -10000};
                                op2 = {"_", -10000, -10000};
                                Target re = {idenfr[w[now_w]->attr.loc], -10000, -10000};
                                QT[now_qt++] = {"scanf", op1, op2, re}; //生成读语句四元式
                                now_w++;
                                if (now_w >= treenum)
                                    return;
                                if (now_w >= treenum)
                                    return; //获得新的数据
                            }
                            else
                            {
                            } //有错误
                        }
                        else
                        {
                        } //有错误
                    }
                }
                else
                {
                } //有错误
            }
            else
            {
            } //有错误
        }
        else
        {
        } //有错误
    }
    else
    {
    } //有错误
}
//返回语句子程序
void return_sentence()
{
    if (w[now_w]->attr.code == "RETURNTK")
    {
        now_w++;
        if (now_w >= treenum)
            return;  //获得新的数据
        expresion(); //进入表达式子程序
        Target re;
        re = SEM.top();
        SEM.pop(); //此处先弹出返回值，后续再考虑要不要弹出
        Target op1, op2;
        op1 = {"_", -10000, -10000};
        op2 = {"_", -10000, -10000};
        QT[now_qt++] = {"return", op1, op2, re}; //生成返回语句四元式
        now_w++;
        if (now_w >= treenum)
        {
            now_w--;
            w[now_w]->attr.code = "END";

            return;
        }

        return;
    }
    else
    {
    } //有错误
}
//参数表子程序
void parameter_list(ParamList p1)
{
    if (w[now_w]->attr.code == "INTTK")
        p1->type = 0; //判断为整型关键字
    else if (w[now_w]->attr.code == "CHARTK")
        p1->type = 1; //判断为整型关键字
    else if (w[now_w]->attr.code == "FLOATTK")
        p1->type = 2; //判断为浮点型关键字
    else if (w[now_w]->attr.code == "CBOOLTK")
        p1->type = 3; //判断为布尔型关键字
    else
        return; //没有参数
    now_w++;
    if (now_w > treenum)
        return;
    if (now_w > treenum)
        return; //获得新的数据
    if (w[now_w]->attr.code == "IDENFR")
    {                                          //判断为标识符
        p1->name = idenfr[w[now_w]->attr.loc]; //保存参数名称
        now_w++;
        if (now_w >= treenum)
            return; //获得新的数据
        ParamList temp = p1;
        while (w[now_w]->attr.code == "COMMA")
        { //逗号
            now_w++;
            if (now_w >= treenum)
                return;
            if (now_w >= treenum)
                return; //获得新的数据
            ParamList nextp = temp0;
            nextp->type = -1;
            nextp->name = "#", nextp->next = NULL;
            temp->next = nextp;
            temp = temp->next;
            if (w[now_w]->attr.code == "INTTK")
                temp->type = 0; //判断为整型关键字
            else if (w[now_w]->attr.code == "CHARTK")
                temp->type = 1; //判断为整型关键字
            else if (w[now_w]->attr.code == "FLOATTK")
                temp->type = 2; //判断为浮点型关键字
            else if (w[now_w]->attr.code == "CBOOLTK")
                temp->type = 3; //判断为布尔型关键字
            else
            {
            } //有错误
            now_w++;
            if (now_w >= treenum)
                return;
            if (now_w >= treenum)
                return; //获得新的数据
            if (w[now_w]->attr.code == "IDENFR")
            {                                            //判断为标识符
                temp->name = idenfr[w[now_w]->attr.loc]; //保存参数名称
                now_w++;
                if (now_w >= treenum)
                    if (now_w >= treenum)
                        return; //获得新的数据
            }
            else
            {
            } //有错误
        }
        return; //不进入循环，直接出函数
    }
    else
    {
    } //有错误
}
void value_function()
{
    head_state(); //进入声明头部子程序

    //;从head_state()出来就加过了
    if (now_w > treenum)
        return; //获得新的数据
    ParamList p1;
    p1 = new Param;
    p1->name = "#";
    p1->type = -1;
    p1->next = NULL;    //初始化第一个参数的信息，参数类型的初始为-1，代表没有类型(void)
    parameter_list(p1); //进入参数表子程序，传过去
    if (now_w > treenum)
        return;
    if (now_w > treenum)
        return;          //获得新的数据
    compound_sentence(); //进入复合语句子程序
    if (now_w > treenum)
        return;
    if (now_w > treenum)
        return; //获得新的数据
    Target temp = SEM.top();
    SEM.pop(); //获得函数名称
    string name = temp.target_s;
    temp = SEM.top();
    SEM.pop(); //获得函数返回值类型
    int type;
    if (temp.target_s == "INTTK")
        type = 0; //判断为整型关键字
    else if (temp.target_s == "CHARTK")
        type = 1; //判断为整型关键字
    else if (temp.target_s == "FLOATTK")
        type = 2; //判断为浮点型关键字
    else if (temp.target_s == "CBOOLTK")
        type = 3;                                    //判断为布尔型关键字
    Function_insert(name, type, p1, 100000, 100001); //最后两个数据有待商讨，把这个函数插入到函数表
    delete (p1);
    return;
}
//无返回值函数定义子程序
void novalue_function()
{
    if (w[now_w]->attr.code == "VOIDTK")
    { //判断为void
        now_w++;
        if (now_w >= treenum)
            return; //获得新的数据
        if (w[now_w]->attr.code == "IDENFR")
        {                                             //判断为标识符
            int type = -1;                            //返回类型为-1，代表没有类型(void)
            string name = idenfr[w[now_w]->attr.loc]; //获得函数名称
            now_w++;
            if (now_w >= treenum)
                if (now_w >= treenum)
                    return; //获得新的数据
            ParamList p1 = temp0;
            p1->name = "#";
            p1->type = -1;
            p1->next = NULL;    //初始化第一个参数的信息，参数类型的初始为-1，代表没有类型(void)
            parameter_list(p1); //进入参数表子程序
            if (now_w >= treenum)
                return;
            if (now_w >= treenum)
                return;          //获得新的数据
            compound_sentence(); //进入复合语句子程序
            if (now_w >= treenum)
                return;
            if (now_w >= treenum)
                return;                                      //获得新的数据
            Function_insert(name, type, p1, 100000, 100001); //最后两个数据有待商讨，把这个函数插入到函数表
            return;
        }
    }
    else
    {
    } //有错误
}
//条件语句
void conditonal_sentence()
{
    if (w[now_w]->attr.code == "IFTK")
    {
        now_w++;
        if (now_w >= treenum)
            return;
        condition();
        QT[now_qt].operate = "if";
        QT[now_qt].target1.target_s = SEM.top().target_s;
        QT[now_qt].target1.target_i = -10000;
        QT[now_qt].target1.target_f = -10000;
        QT[now_qt].target2.target_s = "#";
        QT[now_qt].target2.target_i = -10000;
        QT[now_qt].target2.target_f = -10000;
        QT[now_qt].outcome.target_s = "#";
        QT[now_qt].outcome.target_i = -10000;
        QT[now_qt].outcome.target_f = -10000;
        now_qt++;

        if (now_w >= treenum)
            if (now_w >= treenum)
                return;
        if (w[now_w]->attr.code == "ELSETK")
        {
            QT[now_qt].operate = "el";
            QT[now_qt].target1.target_s = "#";
            QT[now_qt].target1.target_i = -10000;
            QT[now_qt].target1.target_f = -10000;
            QT[now_qt].target2.target_s = "#";
            QT[now_qt].target2.target_i = -10000;
            QT[now_qt].target2.target_f = -10000;
            QT[now_qt].outcome.target_s = "#";
            QT[now_qt].outcome.target_i = -10000;
            QT[now_qt].outcome.target_f = -10000;
            now_qt++;
            now_w++;
            if (now_w >= treenum)
                return;
            if (now_w >= treenum)
                return;
            sentence();
            QT[now_qt].operate = "ie";
            QT[now_qt].target1.target_s = "#";
            QT[now_qt].target1.target_i = -10000;
            QT[now_qt].target1.target_f = -10000;
            QT[now_qt].target2.target_s = "#";
            QT[now_qt].target2.target_i = -10000;
            QT[now_qt].target2.target_f = -10000;
            QT[now_qt].outcome.target_s = "#";
            QT[now_qt].outcome.target_i = -10000;
            QT[now_qt].outcome.target_f = -10000;
            now_qt++;
        }
        else
        {
            QT[now_qt].operate = "ie";
            QT[now_qt].target1.target_s = "#";
            QT[now_qt].target1.target_i = -10000;
            QT[now_qt].target1.target_f = -10000;
            QT[now_qt].target2.target_s = "#";
            QT[now_qt].target2.target_i = -10000;
            QT[now_qt].target2.target_f = -10000;
            QT[now_qt].outcome.target_s = "#";
            QT[now_qt].outcome.target_i = -10000;
            QT[now_qt].outcome.target_f = -10000;
            now_qt++;
        }
        sentence();
    }
    else
        cout << "error w2" << endl;
}
//条件
void condition()
{
    //    expresion();
    if (w[now_w]->attr.code == "LSS")
    {
        now_w++;
        if (now_w >= treenum)
            return;
        expresion();
        expresion();

        QT[now_qt].operate = "<";
        QT[now_qt].target2.target_s = SEM.top().target_s;
        QT[now_qt].target2.target_i = -10000;
        QT[now_qt].target2.target_f = -10000;
        QT[now_qt].outcome.target_i = -10000;
        QT[now_qt].outcome.target_f = -10000;
        SEM.pop();
        QT[now_qt].target1.target_s = SEM.top().target_s;
        QT[now_qt].target1.target_i = -10000;
        QT[now_qt].target1.target_f = -10000;
        SEM.pop();
        QT[now_qt].outcome.target_s = "t" + int_string();
        now_qt++;
        Target wt;
        wt.target_s = QT[now_qt].outcome.target_s; //为了压栈设置的
        SEM.push(wt);
    }
    else if (w[now_w]->attr.code == "LEQ")
    {
        now_w++;
        if (now_w >= treenum)
            return;
        expresion();
        expresion();

        QT[now_qt].operate = "<=";
        QT[now_qt].target2.target_s = SEM.top().target_s;
        QT[now_qt].target2.target_i = -10000;
        QT[now_qt].target2.target_f = -10000;
        QT[now_qt].outcome.target_i = -10000;
        QT[now_qt].outcome.target_f = -10000;
        SEM.pop();
        QT[now_qt].target1.target_s = SEM.top().target_s;
        QT[now_qt].target1.target_i = -10000;
        QT[now_qt].target1.target_f = -10000;
        SEM.pop();
        QT[now_qt].outcome.target_s = "t" + int_string();
        now_qt++;
        Target wt;
        wt.target_s = QT[now_qt].outcome.target_s; //为了压栈设置的
        SEM.push(wt);
    }
    else if (w[now_w]->attr.code == "GRE")
    {
        now_w++;
        if (now_w >= treenum)
            return;
        expresion();
        expresion();
        QT[now_qt].operate = ">";
        QT[now_qt].target2.target_s = "#";
        QT[now_qt].target2.target_i = SEM.top().target_i;
        QT[now_qt].target2.target_f = -10000;
        QT[now_qt].outcome.target_i = -10000;
        QT[now_qt].outcome.target_f = -10000;
        SEM.pop();
        QT[now_qt].target1.target_s = SEM.top().target_s;
        cout << QT[now_qt].target1.target_s << endl;
        QT[now_qt].target1.target_i = -10000;
        QT[now_qt].target1.target_f = -10000;
        SEM.pop();
        QT[now_qt].outcome.target_s = "t" + int_string();
        now_qt++;
        Target wt;
        wt.target_s = QT[now_qt - 1].outcome.target_s; //为了压栈设置的
        SEM.push(wt);
    }
    else if (w[now_w]->attr.code == "GEQ")
    {
        now_w++;
        if (now_w >= treenum)
            return;
        expresion();
        expresion();

        QT[now_qt].operate = ">=";
        QT[now_qt].target2.target_s = SEM.top().target_s;
        QT[now_qt].target2.target_i = -10000;
        QT[now_qt].target2.target_f = -10000;
        QT[now_qt].outcome.target_i = -10000;
        QT[now_qt].outcome.target_f = -10000;
        SEM.pop();
        QT[now_qt].target1.target_s = SEM.top().target_s;
        QT[now_qt].target1.target_i = -10000;
        QT[now_qt].target1.target_f = -10000;
        SEM.pop();
        QT[now_qt].outcome.target_s = "t" + int_string();
        now_qt++;
        Target wt;
        wt.target_s = QT[now_qt].outcome.target_s; //为了压栈设置的
        SEM.push(wt);
    }
    else if (w[now_w]->attr.code == "NEQ")
    {
        now_w++;
        if (now_w >= treenum)
            return;
        expresion();
        QT[now_qt].operate = ">=";
        QT[now_qt].target2.target_s = SEM.top().target_s;
        QT[now_qt].target2.target_i = -10000;
        QT[now_qt].target2.target_f = -10000;
        QT[now_qt].outcome.target_i = -10000;
        QT[now_qt].outcome.target_f = -10000;
        SEM.pop();
        QT[now_qt].target1.target_s = SEM.top().target_s;
        QT[now_qt].target1.target_i = -10000;
        QT[now_qt].target1.target_f = -10000;
        SEM.pop();
        QT[now_qt].outcome.target_s = "t" + int_string();
        now_qt++;
        Target wt;
        wt.target_s = QT[now_qt].outcome.target_s; //为了压栈设置的
        SEM.push(wt);
    }
    else if (w[now_w]->attr.code == "EQL")
    {
        now_w++;
        if (now_w >= treenum)
            return;
        expresion();
        QT[now_qt].operate = "==";
        QT[now_qt].target2.target_s = SEM.top().target_s;
        QT[now_qt].target2.target_i = -10000;
        QT[now_qt].target2.target_f = -10000;
        QT[now_qt].outcome.target_i = -10000;
        QT[now_qt].outcome.target_f = -10000;
        SEM.pop();
        QT[now_qt].target1.target_s = SEM.top().target_s;
        QT[now_qt].target1.target_i = -10000;
        QT[now_qt].target1.target_f = -10000;
        SEM.pop();
        QT[now_qt].outcome.target_s = "t" + int_string();
        now_qt++;
        Target wt;
        wt.target_s = QT[now_qt].outcome.target_s; //为了压栈设置的
        SEM.push(wt);
    }
    else
    {
    } //结束
}
//循环语句

void loop_sentence()
{
    if (w[now_w]->attr.code == "WHILETK")
    {
        QT[now_qt].operate = "wh";
        QT[now_qt].target1.target_s = "#";
        QT[now_qt].target1.target_i = -10000;
        QT[now_qt].target1.target_f = -10000;
        QT[now_qt].target2.target_s = "#";
        QT[now_qt].target2.target_i = -10000;
        QT[now_qt].target2.target_f = -10000;
        QT[now_qt].outcome.target_s = "#";
        QT[now_qt].outcome.target_i = -10000;
        QT[now_qt].outcome.target_f = -10000;
        now_qt++;
        now_w++;
        if (now_w >= treenum)
            return;

        condition();

        QT[now_qt].operate = "do";
        QT[now_qt].target1.target_s = SEM.top().target_s;
        QT[now_qt].target1.target_i = -10000;
        QT[now_qt].target1.target_f = -10000;
        QT[now_qt].target2.target_s = "#";
        QT[now_qt].target2.target_i = -10000;
        QT[now_qt].target2.target_f = -10000;
        QT[now_qt].outcome.target_s = "#";
        QT[now_qt].outcome.target_i = -10000;
        QT[now_qt].outcome.target_f = -10000;
        now_qt++;
        SEM.pop();

        if (now_w >= treenum)
            if (now_w >= treenum)
                return;
        if (now_w >= treenum)
            return;
        QT[now_qt].operate = "we";
        QT[now_qt].target1.target_s = "#";
        QT[now_qt].target1.target_i = -10000;
        QT[now_qt].target1.target_f = -10000;
        QT[now_qt].target2.target_s = "#";
        QT[now_qt].target2.target_i = -10000;
        QT[now_qt].target2.target_f = -10000;
        QT[now_qt].outcome.target_s = "#";
        QT[now_qt].outcome.target_i = -10000;
        QT[now_qt].outcome.target_f = -10000;
        now_qt++;
        sentence();
    }

    else if (w[now_w]->attr.code == "FORTK")
    {
        QT[now_qt].operate = "fo";
        QT[now_qt].target1.target_s = "#";
        QT[now_qt].target1.target_i = -10000;
        QT[now_qt].target1.target_f = -10000;
        QT[now_qt].target2.target_s = "#";
        QT[now_qt].target2.target_i = -10000;
        QT[now_qt].target2.target_f = -10000;
        QT[now_qt].outcome.target_s = "#";
        QT[now_qt].outcome.target_i = -10000;
        QT[now_qt].outcome.target_f = -10000;
        now_qt++;
        now_w++;
        if (now_w >= treenum)
            return;

        if (now_w >= treenum)
            return;
        assignment_sentence();

        if (now_w >= treenum)
            if (now_w >= treenum)
                return;
        condition();
        QT[now_qt].operate = "do";
        QT[now_qt].target1.target_s = SEM.top().target_s;
        QT[now_qt].target1.target_i = -10000;
        QT[now_qt].target1.target_f = -10000;
        QT[now_qt].target2.target_s = "#";
        QT[now_qt].target2.target_i = -10000;
        QT[now_qt].target2.target_f = -10000;
        QT[now_qt].outcome.target_s = "#";
        QT[now_qt].outcome.target_i = -10000;
        QT[now_qt].outcome.target_f = -10000;
        now_qt++;
        SEM.pop();

        if (now_w >= treenum)
            return;
        if (w[now_w]->attr.code == "IDENFR")
        {
            Target wt;
            wt.target_s = idenfr[w[now_w]->attr.loc]; //为了压栈设置的
            SEM.push(wt);
            now_w++;
            if (now_w >= treenum)
                return;
            if (now_w >= treenum)
                return;
            if (w[now_w]->attr.code == "ASSIGN")
            {
                now_w++;
                if (now_w >= treenum)
                    return;
                if (now_w >= treenum)
                    return;
                if (w[now_w]->attr.code == "IDENFR")
                {
                    Target wt;
                    wt.target_s = idenfr[w[now_w]->attr.loc]; //为了压栈设置的
                    SEM.push(wt);
                    now_w++;
                    if (now_w >= treenum)
                        return;
                    if (now_w >= treenum)
                        return;
                    if (w[now_w]->attr.code == "PLUS")
                    {
                        now_w++;
                        if (now_w >= treenum)
                            return;
                        if (now_w >= treenum)
                            return;
                        if (w[now_w]->attr.code == "INTCON" && intcon[w[now_w]->attr.loc] > 0)
                        {
                            QT[now_qt].operate = "+";
                            QT[now_qt].target2.target_s = SEM.top().target_s;
                            QT[now_qt].target2.target_i = -10000;
                            QT[now_qt].target2.target_f = -10000;
                            QT[now_qt].outcome.target_i = -10000;
                            QT[now_qt].outcome.target_f = -10000;
                            SEM.pop();
                            QT[now_qt].target1.target_s = SEM.top().target_s;
                            QT[now_qt].target1.target_i = -10000;
                            QT[now_qt].target1.target_f = -10000;
                            SEM.pop();
                            QT[now_qt].outcome.target_s = "t" + int_string();
                            now_qt++;
                            Target wt;
                            wt.target_s = QT[now_qt].outcome.target_s; //为了压栈设置的
                            SEM.push(wt);
                            now_w++;
                            if (now_w >= treenum)
                                return;
                            if (now_w >= treenum)
                                return;
                            QT[now_qt].operate = ":=";
                            QT[now_qt].target1.target_s = SEM.top().target_s;
                            QT[now_qt].target1.target_i = -10000;
                            QT[now_qt].target1.target_f = -10000;
                            SEM.pop();
                            QT[now_qt].outcome.target_s = SEM.top().target_s;
                            QT[now_qt].outcome.target_i = -10000;
                            QT[now_qt].outcome.target_f = -10000;
                            SEM.pop();
                            QT[now_qt].target2.target_s = "#";
                            QT[now_qt].target2.target_i = -10000;
                            QT[now_qt].target2.target_f = -10000;

                            if (now_w >= treenum)
                                return;
                            if (now_w >= treenum)
                                return;
                            sentence();
                            QT[now_qt].operate = "fe";
                            QT[now_qt].target1.target_s = "#";
                            QT[now_qt].target1.target_i = -10000;
                            QT[now_qt].target1.target_f = -10000;
                            QT[now_qt].target2.target_s = "#";
                            QT[now_qt].target2.target_i = -10000;
                            QT[now_qt].target2.target_f = -10000;
                            QT[now_qt].outcome.target_s = "#";
                            QT[now_qt].outcome.target_i = -10000;
                            QT[now_qt].outcome.target_f = -10000;
                            now_qt++;
                        }
                        else
                            cout << "error w8" << endl;
                    }

                    else if (w[now_w]->attr.code == "MINU")
                    {
                        now_w++;
                        if (now_w >= treenum)
                            return;
                        if (now_w >= treenum)
                            return;
                        if (w[now_w]->attr.code == "INTCON" && intcon[w[now_w]->attr.loc] > 0)
                        {
                            QT[now_qt].operate = "-";
                            QT[now_qt].target2.target_s = SEM.top().target_s;
                            QT[now_qt].target2.target_i = -10000;
                            QT[now_qt].target2.target_f = -10000;
                            QT[now_qt].outcome.target_i = -10000;
                            QT[now_qt].outcome.target_f = -10000;
                            SEM.pop();
                            QT[now_qt].target1.target_s = SEM.top().target_s;
                            QT[now_qt].target1.target_i = -10000;
                            QT[now_qt].target1.target_f = -10000;
                            SEM.pop();
                            QT[now_qt].outcome.target_s = "t" + int_string();
                            now_qt++;
                            Target wt;
                            wt.target_s = QT[now_qt].outcome.target_s; //为了压栈设置的
                            SEM.push(wt);
                            now_w++;
                            if (now_w >= treenum)
                                return;
                            if (now_w >= treenum)
                                return;
                            QT[now_qt].operate = ":=";
                            QT[now_qt].target1.target_s = SEM.top().target_s;
                            QT[now_qt].target1.target_i = -10000;
                            QT[now_qt].target1.target_f = -10000;
                            SEM.pop();
                            QT[now_qt].outcome.target_s = SEM.top().target_s;
                            QT[now_qt].outcome.target_i = -10000;
                            QT[now_qt].outcome.target_f = -10000;
                            SEM.pop();
                            QT[now_qt].target2.target_s = "#";
                            QT[now_qt].target2.target_i = -10000;
                            QT[now_qt].target2.target_f = -10000;

                            if (now_w >= treenum)
                                return;
                            if (now_w >= treenum)
                                return;
                            sentence();
                            QT[now_qt].operate = "fe";
                            QT[now_qt].target1.target_s = "#";
                            QT[now_qt].target1.target_i = -10000;
                            QT[now_qt].target1.target_f = -10000;
                            QT[now_qt].target2.target_s = "#";
                            QT[now_qt].target2.target_i = -10000;
                            QT[now_qt].target2.target_f = -10000;
                            QT[now_qt].outcome.target_s = "#";
                            QT[now_qt].outcome.target_i = -10000;
                            QT[now_qt].outcome.target_f = -10000;
                            now_qt++;
                        }
                        else
                            cout << "error w10" << endl;
                    }
                    else
                        cout << "error w11" << endl;
                }
                else
                    cout << "error w12" << endl;
            }
            else
                cout << "error w13" << endl;
        }
        else
            cout << "error w14" << endl;
    }
    else
        cout << "error w15" << endl;
}
//语句
void sentence()
{
    if (w[now_w]->nodekind == 0 && w[now_w]->attr.code == "IFTK") //条件语句
    {
        conditonal_sentence();
    }
    else if (w[now_w]->attr.code == "DOTK" || w[now_w]->attr.code == "WHILETK" || w[now_w]->attr.code == "FORTK") //循环语句
    {
        loop_sentence();
    }
    else if (w[now_w]->nodekind == 0 && w[now_w]->attr.code == "SCANFTK") //读语句
    {
        read_sentence();
    }
    else if (w[now_w]->nodekind == 0 && w[now_w]->attr.code == "PRINTFTK") //写语句
    {
        write_sentence();
    }
    else if (w[now_w]->nodekind == 0 && w[now_w]->attr.code == "RETURNTK") //返回语句
    {
        return_sentence();
    }
    else if (w[now_w]->nodekind == 0 && w[now_w]->kind.stmt == 4) //赋值语句
    {
        assignment_sentence();
    }
    else if (w[now_w]->nodekind == 0 && w[now_w]->kind.stmt == 5) //有返回值函数调用语句，无返回值函数调用语句
    {
        assignment_sentence();
    }
    else if (w[now_w]->kind.stmt == 6) //判断为变量定义
    {
        var_df();
    }
}
//变量定义
//void var_df()
//{
//    if (w[now_w]->attr.code == "INTTK" || w[now_w]->attr.code == "FLOATTK" || w[now_w]->attr.code == "CHARTK")
//    {
//        int type = 0, flag = 2;
//        if (w[now_w]->attr.code == "INTTK")
//            type = 0;
//        else if (w[now_w]->attr.code == "FLOATTK")
//            type = 1;
//        else if (w[now_w]->attr.code == "CHARTK")
//            type = 2;
//        now_w++;
//        if (now_w >= treenum)
//            return;                               //获得新的数据
//        string name = idenfr[w[now_w]->attr.loc]; //获得名字
//        long i = List_find(name);                 //查找这个标识符有没有在表中出现过
//        if (i == -1)
//            List_insert(name, type, 10000, 10005, flag); //插入符号表表中
//        else
//        {
//        } //有错误
//        now_w++;
//        if (now_w >= treenum)
//            return; //获得新的数据
//        while (w[now_w]->attr.code == "COMMA")
//        {
//            now_w++;
//            if (now_w >= treenum)
//                return;
//            if (now_w >= treenum)
//                return;                               //获得新的数据
//            string name = idenfr[w[now_w]->attr.loc]; //获得名字
//            long i = List_find(name);                 //查找这个标识符有没有在表中出现过
//            if (i != -1)
//                List_insert(name, type, 10000, 10005, flag); //插入符号表表中
//            else
//            {
//            } //有错误
//        }
//        if (now_w >= treenum)
//            return;
//        if (now_w >= treenum)
//            return; //获得新的数据
//        while (w[now_w]->attr.code == "INTTK" || w[now_w]->attr.code == "FLOATTK" || w[now_w]->attr.code == "CHARTK")
//        {
//            int type = 0, flag = 2;
//            if (w[now_w]->attr.code == "INTTK")
//                type = 0;
//            else if (w[now_w]->attr.code == "FLOATTK")
//                type = 1;
//            else if (w[now_w]->attr.code == "CHARTK")
//                type = 2;
//            now_w++;
//            if (now_w >= treenum)
//                if (now_w >= treenum)
//                    return;                           //获得新的数据
//            string name = idenfr[w[now_w]->attr.loc]; //获得名字
//            long i = List_find(name);                 //查找这个标识符有没有在表中出现过
//            if (i != -1)
//                List_insert(name, type, 10000, 10005, flag); //插入符号表表中
//            else
//            {
//            } //有错误
//            now_w++;
//            if (now_w >= treenum)
//                if (now_w >= treenum)
//                    return; //获得新的数据
//            while (w[now_w]->attr.code == "COMMA")
//            {
//                now_w++;
//                if (now_w >= treenum)
//                    return;
//                if (now_w >= treenum)
//                    return;                               //获得新的数据
//                string name = idenfr[w[now_w]->attr.loc]; //获得名字
//                long i = List_find(name);                 //查找这个标识符有没有在表中出现过
//                if (i != -1)
//                    List_insert(name, type, 10000, 10005, flag); //插入符号表表中
//                else
//                {
//                } //有错误
//            }
//        }
//        return; //不是标识符之后出去了
//    }
//    else
//    {
//    } //有问题
//    if(w[now_w]->kind.stmt==8){//判断为数组类型
//        int type = 0, flag = 2;
//        if (w[now_w]->attr.code == "INTTK")
//            type = 0;
//        else if (w[now_w]->attr.code == "FLOATTK")
//            type = 1;
//        else if (w[now_w]->attr.code == "CHARTK")
//            type = 2;
//        now_w++;
//        if (now_w >= treenum)
//            return;                               //获得新的数据
//        string name = idenfr[w[now_w]->attr.loc]; //获得名字
//        long i = Array_find(name);                 //查找这个标识符有没有在数组表中出现过
//        now_w++;//得到其维数信息
//        string spec="1*";//数组大小
//        char c=intcon[w[now_w]->attr.loc]+48;spec+=c;
//        if (i != -1)
//            Array_insert(name, type, 10000, 10005, 1,spec); //插入符号表表中
//        else
//        {
//        } //有错误
//        while(w[now_w]->kind.stmt==8){
//            int type = 0, flag = 2;
//            if (w[now_w]->attr.code == "INTTK")
//                type = 0;
//            else if (w[now_w]->attr.code == "FLOATTK")
//                type = 1;
//            else if (w[now_w]->attr.code == "CHARTK")
//                type = 2;
//            now_w++;
//            if (now_w >= treenum)
//                return;                               //获得新的数据
//            string name = idenfr[w[now_w]->attr.loc]; //获得名字
//            long i = Array_find(name);                 //查找这个标识符有没有在数组表中出现过
//            now_w++;//得到其维数信息
//            string spec="1*";//数组大小
//            char c=intcon[w[now_w]->attr.loc]+48;spec+=c;
//            if (i != -1)
//                Array_insert(name, type, 10000, 10005, 1,spec); //插入符号表表中
//            else
//            {
//            } //有错误
//        }
//    }
//}
//变量定义
void var_df()
{
    while (w[now_w]->attr.code == "INTTK" || w[now_w]->attr.code == "FLOATTK" || w[now_w]->attr.code == "CHARTK")
    {
        int type = 0, flag = 2;
        if (w[now_w]->attr.code == "INTTK")
            type = 0;
        else if (w[now_w]->attr.code == "FLOATTK")
            type = 1;
        else if (w[now_w]->attr.code == "CHARTK")
            type = 2;
        now_w++; //获得新的数据
        if (now_w >= treenum)
            return;                               //获得新的数据
        string name = idenfr[w[now_w]->attr.loc]; //获得名字
        long i = List_find(name);                 //查找这个标识符有没有在表中出现过
        long j = Array_find(name);
        if (i == -1 && j == -1)
        {                                             //表中未出现
            if (w[now_w]->kind.stmt == define_arrayk) //判断为整数
            {

                string spec = "1*";
                string c = to_string(intcon[w[now_w]->attr.loc]); //转换为字符
                //                cout<<c<<endl;
                spec += c;
                Array_insert(name, type, 10000, 10005, 1, spec);
                now_w++; //获得新的数据
                now_w++; //获得新的数据
                now_w++; //获得新的数据
            }
            else
            {
                List_insert(name, type, 10000, 10005, flag); //插入符号表表中
                now_w++;
                continue; //继续
            }
        }
    }
}
//声明头部
void head_state()
{
    if (w[now_w]->attr.code == "INTTK" || w[now_w]->attr.code == "FLOATTK" || w[now_w]->attr.code != "CHARTK")
    {
        Target wt;
        wt.target_s = keywords[w[now_w]->attr.loc]; //为了压栈设置的
        wt.target_i = -10000;
        wt.target_f = -10000;
        SEM.push(wt);
        now_w++;
        if (now_w >= treenum)
            return;
        if (w[now_w]->attr.code == "IDENFR")
        {
            Target wt;
            wt.target_s = idenfr[w[now_w]->attr.loc]; //为了压栈设置的
            wt.target_i = -10000;
            wt.target_f = -10000;
            SEM.push(wt);
            now_w++;
            if (now_w >= treenum)
                return;
            if (now_w >= treenum)
                return;
        }
        else
            cout << "error w20" << endl;
    }
    else
        cout << "error w19" << endl;
}
//主函数子程序
void main_function()
{
    /*获得要处理的数据（暂时缺少一个把树形数据变成表的函数）*/
    if (w[now_w]->attr.code == "MAINTK")
    {
        now_w++;
        if (now_w >= treenum)
            return;          //获得新的数据
        compound_sentence(); //调用复合语句子程序
    }
    else
    { /*出现错误*/
    }
}
//程序
void program()
{
    if (w[now_w]->nodekind == 0 && w[now_w]->kind.stmt == 6) //变量定义
    {
        var_df();
        while (w[now_w - 1]->attr.code != "MAINTK") //如果不是主函数
        {

            if (w[now_w]->attr.code == "INTTK" || w[now_w]->attr.code == "FLOATTK" || w[now_w]->attr.code == "CHARTK")
            {
                value_function();
            }
            else if (w[now_w]->attr.code == "VOIDTK")
            {
                novalue_function();
            }
        }
        main_function();
    }
    else
    {
        while (w[now_w]->attr.code != "MAINTK") //如果不是主函数
        {

            if (w[now_w]->attr.code == "INTTK" || w[now_w]->attr.code != "FLOATTK" || w[now_w]->attr.code != "CHARTK")
            {
                value_function();
            }
            else if (w[now_w]->attr.code == "VOIDTK")
            {
                novalue_function();
            }
        }
        main_function();
    }
}
void print_qt()
{
    for (int i = 0; i < now_qt; i++)
    {
        cout << "(";
        cout << QT[i].operate << ",";
        if (QT[i].target1.target_i != -10000)
            cout << QT[i].target1.target_i << ",";
        else if (QT[i].target1.target_f != -10000)
            cout << QT[i].target1.target_f << ",";
        else if (QT[i].target1.target_s != "#")
            cout << QT[i].target1.target_s << ",";
        else
            cout << " ,";

        if (QT[i].target2.target_i != -10000)
            cout << QT[i].target2.target_i << ",";
        else if (QT[i].target2.target_f != -10000)
            cout << QT[i].target2.target_f << ",";
        else if (QT[i].target2.target_s != "#")
            cout << QT[i].target2.target_s << ",";
        else
            cout << " ,";

        if (QT[i].outcome.target_s != "#")
            cout << QT[i].outcome.target_s << ")" << endl;
        else if (QT[i].outcome.target_f != -10000)
            cout << QT[i].outcome.target_f << ")" << endl;
        else if (QT[i].outcome.target_i != -10000)
            cout << QT[i].outcome.target_i << ")" << endl;

        else
            cout << ")" << endl;
    }
}

//void printf_QT()
//{
//    int i=0;
//    while(now_qt)
//    {
//        cout<<i<<'  ('<<QT[i].operate<<',';
//        if(QT[i].target1.target_s != "#")
//            cout<<QT[i].target1.target_s<<',';
//        else if(QT[i].target1.target_i!=-10000)
//            cout<<QT[i].target1.target_i<<',';
//        else if(QT[i].target1.target_f!=-10000) cout<<QT[i].target1.target_f<<',';
//        if(QT[i].target2.target_s!="#")  cout<<QT[i].target2.target_s<<',';
//        else if(QT[i].target2.target_i!=-10000) cout<<QT[i].target2.target_i<<',';
//        else if(QT[i].target2.target_f!=-10000) cout<<QT[i].target2.target_f<<',';
//        cout<<QT[i].outcome.target_s<<')'<<endl;
//        i++;
//        now_qt--;
//    }
//
//}
void byylf_yy()
{
    //    cout<<w[0]->attr.code<<endl;
    //    cout<<w[0]->kind.stmt<<endl;
    //    cout<<w[1]->attr.code<<endl;
    //    cout<<w[2]->attr.code<<endl;
    //    cout<<w[3]->attr.code<<endl;
    program();
    cout << now_qt << endl;
    print_qt();
    //    printf_QT();
}