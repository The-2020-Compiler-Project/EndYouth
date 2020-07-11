#include "byylf_cf.h"
Token token_table[1000];

int ct_num = 0;
//常数处理机对应表
int number[9][6] = {{1, 2, 3, 0, 0, 0}, {0, 0, 3, 0, 0, 0}, {0, 0, 3, 0, 0, 0}, {0, 0, 3, 4, 6, 9}, {0, 0, 5, 0, 0, 0}, {0, 0, 5, 0, 6, 9}, {7, 7, 8, 0, 0, 0}, {0, 0, 8, 0, 0, 0}, {0, 0, 8, 0, 0, 9}};

//关键字表
string keywords[] = {"const", "int", "float", "char", "bool", "void", "main", "if", "else", "do", "while", "for", "scanf", "printf", "return", "switch", "case", "default", "struct", "break", "continue"};

//界符表
string punctuation[] = {"+", "-", "*", "/", "<", "<=", ">", ">=", "==", "!=", "=", ";", ",", "(", ")", "[", "]", "{", "}", "||", "&&", ":"};

//标识符表
string idenfr[1000];
int use_idenfr = 0;

//字符表
string charcon[500];
int use_charcon = 0;

//字符串表
string stringcon[500];
int use_stringcon = 0;

//整型常量表
int intcon[500];
int use_intcon = 0;

//浮点型常量表
float floatcon[500];
int use_floatcon = 0;
//填写Token序列表，同时如果监测到为常数，使用常数转换机对常数进行处理
void parse1(string t, int loc, Token token_table[])
{
    token_table[ct_num].code = t;
    token_table[ct_num++].loc = loc;
}
//查找关键字，标识符表,填写Token序列表
void search_keyoide(string t, Token token_table[])
{
    string code;
    int loc;
    int flag_key = 0, flag_id = 0;
    for (int i = 0; i < 21; i++)
    {
        if (t == keywords[i])
        {
            loc = i;
            switch (i)
            {
                case 0:
                    code = "CONSTTK";
                    break;
                case 1:
                    code = "INTTK";
                    break;
                case 2:
                    code = "FLOATTK";
                    break;
                case 3:
                    code = "CHARTK";
                    break;
                case 4:
                    code = "BOOLTK";
                    break;
                case 5:
                    code = "VOIDTK";
                    break;
                case 6:
                    code = "MAINTK";
                    break;
                case 7:
                    code = "IFTK";
                    break;
                case 8:
                    code = "ELSETK";
                    break;
                case 9:
                    code = "DOTK";
                    break;
                case 10:
                    code = "WHILETK";
                    break;
                case 11:
                    code = "FORTK";
                    break;
                case 12:
                    code = "SCANFTK";
                    break;
                case 13:
                    code = "PRINTFTK";
                    break;
                case 14:
                    code = "RETURNTK";
                    break;
                case 15:
                    code = "SWITCHTK";
                    break;
                case 16:
                    code = "CASETK";
                    break;
                case 17:
                    code = "DEFALUTTK";
                    break;
                case 18:
                    code = "STRUCTTK";
                    break;
                case 19:
                    code = "BREAKTK";
                    break;
                case 20:
                    code = "CONTINUETK";
                    break;
            }
            flag_key = 1;
        }
        if (flag_key == 1)
            break;
    }
    if (flag_key == 0) //不是关键字
    {
        code = "IDENFR";
        for (int i = 0; i < use_idenfr; i++) //是否在标识符表中
        {
            if (t == idenfr[i])
            {
                loc = i;
                flag_id = 1;
            }
            if (flag_id == 1)
                break;
        }
        if (flag_id == 0) //不在标识符表中,填入
        {
            idenfr[use_idenfr++] = t;
            loc = use_idenfr - 1;
        }
    }
    parse1(code, loc, token_table); //填写Token序列表，同时如果监测到为常数，使用常数转换机对常数进行处理
}
//查整型表，返回下标
int search_int(int i)
{
    int flag_int = 0, loc;
    for (int j = 0; j < use_intcon; j++)
    {
        if (i == intcon[i])
        {
            loc = j;
            flag_int = 1;
        }
        if (flag_int == 1)
            break;
    }
    if (flag_int == 0)
    {
        intcon[use_intcon++] = i;
        loc = use_intcon - 1;
    }
    return loc;
}
//查浮点型表，返回下标
int search_float(float i)
{
    int flag_float = 0, loc;
    for (int j = 0; j < use_floatcon; j++)
    {
        if (i == floatcon[j])
        {
            loc = j;
            flag_float = 1;
        }
        if (flag_float == 1)
            break;
    }
    if (flag_float == 0)
    {
        floatcon[use_floatcon++] = i;
        loc = use_floatcon - 1;
    }
    return loc;
}
//查字符表
void search_char(string ch, Token token_table[])
{
    int flag_char = 0, loc;
    for (int i = 0; i < use_charcon; i++)
    {
        if (ch == charcon[i])
        {
            loc = i;
            flag_char = 1;
        }
        if (flag_char == 1)
            break;
    }
    if (flag_char == 0)
    {
        charcon[use_charcon++] = ch;
        loc = use_charcon - 1;
    }
    parse1("CHARCON", loc, token_table);
}
//查字符串表
void search_string(string s, Token token_table[])
{
    int flag_string = 0, loc;
    for (int i = 0; i < use_stringcon; i++)
    {
        if (s == stringcon[i])
        {
            loc = i;
            flag_string = 1;
        }
        if (flag_string == 1)
            break;
    }
    if (flag_string == 0)
    {
        stringcon[use_stringcon++] = s;
        loc = use_stringcon - 1;
    }
    parse1("STRCON", loc, token_table);
}
//常数处理机，返回常数
float string_to_num(string t)
{
    //返回数为float型，在调用它的函数中进行调整
    int n, m, p, s, y, e, i = 0, j;
    float num;
    string jin = "#";
    t += jin;

    int state = 1;
    while (state != 10)
    {
        switch (state)
        {
            case 1:
                n = 0;
                m = 0;
                p = 0;
                s = 0;
                y = 1;
                e = 1;
                num = 0;
                break;
            case 2:
                y = 1;
                break;
            case 3:
                y = -1;
                break;
            case 4:
                n = 10 * n + t[i - 1] - 48;
                break;
            case 5:
                s = 1;
                break;
            case 6:
                n = 10 * n + t[i - 1] - 48;
                m++;
                break;
            case 7:
                s = 1;
                break;
            case 8:
                if (t[i - 1] == '-')
                    e = -1;
                break;
            case 9:
                p = 10 * p + t[i - 1] - 48;
                break;
        }
        switch (t[i++])
        {
            case '+':
                if (t[i - 2] == e)
                    j = 6;
                else
                    j = 0;
                break;
            case '-':
                if (t[i - 2] == e)
                    j = 6;
                else
                    j = 1;
                break;
            case '.':
                j = 3;
                break;
            case 'e':
                j = 4;
                break;
            case '#':
                j = 5;
                break;
            default:
                j = 2;
                break;
        }
        if (number[state - 1][j] == 0)
            cout << "error" << endl;
        else
            state = number[state - 1][j] + 1;
        if (state == 10)
            num = y * n * pow(10, e * p - m);
    }
    return num;
}
//根据state_before确定,返回类别码
void state_to_code(int state_before, string t, Token token_table[])
{
    int loc; //位置
    int i;
    float f;
    switch (state_before)
    {
        case 2:
            parse1("PLUS", 0, token_table);
            break;
        case 3:
            parse1("MINU", 1, token_table);
            break;
        case 4:                                 //整型
            i = (int)string_to_num(t);          //统一返回浮点型，整型的在此进行调整
            loc = search_int(i);                //查询并填写
            parse1("INTCON", loc, token_table); //整型分类码
            break;
        case 6: //浮点或者科学计数的
        case 9:
            f = string_to_num(t);
            loc = search_float(f);                //查询并填写
            parse1("FLOATCON", loc, token_table); //浮点数分类码
            break;
        case 10:
            parse1("MULT", 2, token_table);
            break;
        case 11:
            parse1("DIV", 3, token_table);
            break;
        case 12:
            parse1("LSS", 4, token_table);
            break;
        case 13:
            parse1("LEQ", 5, token_table);
            break;
        case 14:
            parse1("GRE", 6, token_table);
            break;
        case 15:
            parse1("GEQ", 7, token_table);
            break;
        case 16:
            parse1("ASSIGN", 10, token_table);
            break;
        case 17:
            parse1("EQL", 8, token_table);
            break;
        case 19:
            parse1("NEQ", 9, token_table);
            break;
        case 20:
            parse1("SEMICN", 11, token_table);
            break;
        case 21:
            parse1("COMMA", 12, token_table);
            break;
        case 22:
            parse1("LPARENT", 13, token_table);
            break;
        case 23:
            parse1("RPARENT", 14, token_table);
            break;
        case 24:
            parse1("LBRACK", 15, token_table);
            break;
        case 25:
            parse1("RBRACK", 16, token_table);
            break;
        case 26:
            parse1("LBRACE", 17, token_table);
            break;
        case 27:
            parse1("RBRACE", 18, token_table);
            break;
        case 30: //字符
            search_char(t, token_table);
            break;
        case 33: //字符串
            search_string(t, token_table);
            break;
        case 34: //查标识符，关键字
        case 35:
            search_keyoide(t, token_table);
            break;
        case 37:
            parse1("ORTK", 19, token_table);
            break;
        case 39:
            parse1("ANDTK", 20, token_table);
            break;
        case 40:
            parse1("COLONTK", 21, token_table);
            break;
        case 41:
            parse1("POINTTK", 22, token_table);
            break;
        default:
            break;
    }
}
//根据当前状态和当前待处理数据，返回下一个状态
int state_change(int now_state, char now_ch)
{
    int next_state = 0; //下一个状态
    switch (now_state)
    {
        case 1:
            if (now_ch <= '9' && now_ch >= '0')
                next_state = 4;
            else if (now_ch <= 'Z' && now_ch >= 'A' || now_ch <= 'z' && now_ch >= 'a' || now_ch == '_')
                next_state = 34;
            else
                next_state = 1;
            switch (now_ch)
            {
                case '+':
                    next_state = 2;
                    break;
                case '-':
                    next_state = 3;
                    break;
                case '*':
                    next_state = 10;
                    break;
                case '/':
                    next_state = 11;
                    break;
                case '<':
                    next_state = 12;
                    break;
                case '>':
                    next_state = 14;
                    break;
                case '=':
                    next_state = 16;
                    break;
                case '!':
                    next_state = 18;
                    break;
                case ';':
                    next_state = 20;
                    break;
                case ',':
                    next_state = 21;
                    break;
                case '(':
                    next_state = 22;
                    break;
                case ')':
                    next_state = 23;
                    break;
                case '[':
                    next_state = 24;
                    break;
                case ']':
                    next_state = 25;
                    break;
                case '{':
                    next_state = 26;
                    break;
                case '}':
                    next_state = 27;
                    break;
                case '|':
                    next_state = 36;
                    break;
                case '&':
                    next_state = 38;
                    break;
                case ':':
                    next_state = 40;
                    break;
                case '.':
                    next_state = 41;
                    break;
                case 39: //单引号
                    next_state = 28;
                    break;
                case '"':
                    next_state = 31;
                    break;
                default:
                    break;
            }
            break;
        case 2:
        case 3:
            if (now_ch <= '9' && now_ch >= '0')
                next_state = 4;
            else
                next_state = 0;
            break;
        case 4:
            if (now_ch <= '9' && now_ch >= '0')
                next_state = 4;
            else if (now_ch == '.')
                next_state = 5;
            else if (now_ch == 'e' || now_ch == 'E')
                next_state = 7;
            else
                next_state = 0;
            break;
        case 5:
            if (now_ch <= '9' && now_ch >= '0')
                next_state = 6;
            //此处可能出现错误，待处理
            break;
        case 6:
            if (now_ch <= '9' && now_ch >= '0')
                next_state = 6;
            else if (now_ch == 'e')
                next_state = 7;
            //此处可能出现错误，待处理
            break;
        case 7:
            if (now_ch <= '9' && now_ch >= '0')
                next_state = 9;
            else if (now_ch == '+' || now_ch == '-')
                next_state = 8;
            //此处可能出现错误，待处理
            break;
        case 8:
            if (now_ch <= '9' && now_ch >= '0')
                next_state = 9;
            //此处可能出现错误，待处理
            break;
        case 9:
            if (now_ch <= '9' && now_ch >= '0')
                next_state = 9;
            else
                next_state = 0;
            break;
        case 12:
            if (now_ch == '=')
                next_state = 13;
            else
                next_state = 0;
            break;
        case 14:
            if (now_ch == '=')
                next_state = 15;
            else
                next_state = 0;
            break;
        case 16:
            if (now_ch == '=')
                next_state = 17;
            else
                next_state = 0;
            break;
        case 18:
            if (now_ch == '=')
                next_state = 19;
            //此处有些问题待处理
            break;
        case 28:
            if (now_ch != 32)
                next_state = 29; //单个字符可为任意的,除空格
            break;
        case 29:
            if (now_ch == 39)
                next_state = 30;
            //此处可能出现错误，待处理
            break;
        case 31:
            if (now_ch == 32 || now_ch == 33 || now_ch <= 126 && now_ch >= 35)
                next_state = 32;
            //此处可能出现错误，待处理
            break;
        case 32:
            if (now_ch == 32 || now_ch == 33 || now_ch <= 126 && now_ch >= 35)
                next_state = 32;
            else if (now_ch == '"')
                next_state = 33;
            break;
        case 34:
            if (now_ch <= 'Z' && now_ch >= 'A' || now_ch <= 'z' && now_ch >= 'a' || now_ch == '_')
                next_state = 34;
            else if (now_ch <= '9' && now_ch >= '0')
                next_state = 35;
            else
                next_state = 0;
            break;
        case 35:
            if (now_ch <= 'Z' && now_ch >= 'A' || now_ch <= 'z' && now_ch >= 'a' || now_ch == '_' || now_ch <= '9' && now_ch >= '0')
                next_state = 35;
            else
                next_state = 0;
            break;
        case 36:
            if (now_ch == '|')
                next_state = 37;
            //此处可能出现错误，待处理
            break;
        case 38:
            if (now_ch == '&')
                next_state = 39;
            //此处可能出现错误，待处理
            break;
        case 10:
        case 11:
        case 13:
        case 15:
        case 17:
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
        case 25:
        case 26:
        case 27:
        case 30:
        case 33:
        case 37:
        case 39:
        case 40:
        case 41:
            next_state = 0;
            break;
        default:
            next_state = 0;
            break;
    }
    return next_state;
}

void byylf_cf()
{
    ifstream file; //从文件中获得待处理数据
    string sta = "", stb;
    file.open("../test.txt", ios::in);
    if (!file.good())
    {
        cout << "文件打开失败！！";
        return;
    }
    while (!file.eof())
    {
        getline(file, stb);
        sta += stb;
    }
    int state = 1, state_before = 1;
    string t = ""; //保存当前的
    int i = 0;     //循环条件
    while (i <= sta.length())
    {                                    //挨个处理待处理数据
        char ch = sta[i];                //一个待处理的数据
        state_before = state;            //保存当前状态，用这个进行后续工作
        state = state_change(state, ch); //状态转移函数
        if (state)
        { //若还未到达结束状态
            if (ch == ' ')
            {
                if (t[0] == '"')
                    t = t + ch; //保存好已经被处理过的字符
            }
            else if (ch != 13 && ch != 9)
                t = t + ch; //保存好已经被处理过的字符
        }
        else
        {                                                //到达结束状态
            state_to_code(state_before, t, token_table); //根据state_before确定类别码
            i--;                                         //防止遗漏待处理数据
            state = 1;
            t = ""; //重置state和t
        }
        i++;
    }
    for (i = 0; i < ct_num && ct_num < 1000; i++)
        cout << token_table[i].code << "  " << token_table[i].loc << endl;
    cout << "token的数量：" << ct_num << endl;
    cout<< "关键字表"<<endl;
    for(int i=0;i< 21;i++)
    {
        cout<<i<<": "<<keywords[i]<<endl;
    }
    cout<< "界符表"<<endl;

    for(int i=0;i< 22;i++)
    {
        cout<<i<<": "<<punctuation[i]<<endl;
    }
    cout<< "标识符表"<<endl;

    for(int i=0;i< use_idenfr;i++)
    {
        cout<<i<<": "<<idenfr[i]<<endl;
    }
    cout<< "字符表"<<endl;

    for(int i=0;i< use_charcon;i++)
    {
        cout<<i<<": "<<charcon[i]<<endl;
    }
    cout<< "常数表"<<endl;

    for(int i=0;i< use_intcon;i++)
    {
        cout<<i<<": "<<intcon[i]<<endl;
    }
    cout<< "字符串表"<<endl;

    for(int i=0;i< use_stringcon;i++)
    {
        cout<<i<<": "<<stringcon[i]<<endl;
    }
    cout<< "浮点数表"<<endl;

    for(int i=0;i< use_floatcon;i++)
    {
        cout<<i<<": "<<floatcon[i]<<endl;
    }

}
