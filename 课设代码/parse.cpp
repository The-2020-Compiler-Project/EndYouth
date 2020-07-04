#include "parse.h"

static treenode *entitypara_list();           ///�����Զ��庯���Ĳ���
static treenode *BUER_stmt();                 ///�����������
static treenode *newlnodestmt(Stmtkind stmt); ///�������ṹ���
static treenode *newlnodeexp(Expkind exp);    ///������ʽ�ṹ���
static treenode *term();                      ///���˳�������ʽ
static treenode *factor();                    ///��Ҫ���ڼӼ��Ѿ����͵ȼ�ģ��
static treenode *structure_stmt();            ///һ�������{}
static treenode *instmt_sequence();           ///���ṹ����
static treenode *for_stmt();                  ///for���
static treenode *while_stmt();                ///while���
static treenode *if_stmt();                   ///if���
static treenode *switch_stmt();               ///switch���
static treenode *case_stmt();                 ///case���
static treenode *break_stmt();                ///break���
static treenode *default_stmt();              ///default���
static treenode *statement();                 ///�������
static treenode *definepara_stmt();           ///�������
static treenode *quotepara_list();            ///�������õĲ���
static treenode *exp2();                      ///��������
static treenode *fun_apply();                 ///��������
static treenode *assign_stmt();               ///��ֵ���
static treenode *define_assign();             ///�������
static treenode *exp();                       ///��������ĸ���ģ��
static treenode *simple_exp();                ///���򵥵�����ģ��
static treenode *input_para_list();           ///����Ĳ���
static treenode *struct_stmt();               ///�ṹ�����
int isin_first_instmt_sequence();             ///token�Ƿ������������
void parse_printtree();                       ///��������﷨��
void printtree(treenode *lnode);
void printnode(treenode *lnode);
void parse();                        ///�﷨������ʼ
void gettoken();                     ///��ȡtoken
void match(string expectedtoken); ///ƥ��
int count_row();                     ///����token������������Ҫ�����������
int isdtype();                       ///�Ƿ��Ƕ�������
int iscomparison_op();               ///�ж��Ƿ��ǱȽ������

int mainno = 0;                                  /**�����ж�main�����ĸ���**/
int ptokenno = 0;                                /**��ǰ�Ǻŵļ��������ӵ�0����ʼ�����Ƕ�Ӧ��ǰ�Ǻŵ�ǰһ��**/
int printtree_t = 0;                             /**����﷨���Ĳ���**/
treenode *tree_root;                             /**�﷨���ĸ�**/
string dtype[4] = {"INT", "FLOAT", "CHAR", "DOUBLE"}; /**������������ֵ����VOID���⣩������**/

///ƥ��ʷ���ʶ���token,��ȡ��һ���Ǻ�
void match(string expectedtoken)
{

    if (expectedtoken == token)
    {
        gettoken();
    }
    else
    {
        printf("error");
    }
}
/**��ý��**/
void gettoken()
{
    token = token_table[ptokenno].code;
    ptokenno++;
}

///����Ǻ�λ��Դ�������һ��
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
    treenode *newtemp = NULL; //��һ����
    treenode *temp = NULL;    //��ǰ��
    treenode *root = NULL;    //�����
    treenode *dakuohao;       //������
    gettoken();
    int root_tag = 0; ///���ڸ��ڵ���ж�

    while (ptokenno < tokenno)
    {
        if (isdtype() || (token == STRUCT))
        {
            if (token == INT && token_table[ptokenno].tokenval == MAIN)
            {
                root_tag++;
                newtemp = newlnodestmt(maink);
                match(INT);
                match(MAIN);
                match(L_XI);
                if (token != R_XI)
                {
                    newtemp->child[1] = entitypara_list(); ///�����б�
                }
                match(R_XI);
                if (token != L_DA)
                {
                    printf("error", count_row());
                }
                else
                {
                    newtemp->child[2] = structure_stmt(); /**����ʵ��ṹ**/
                }
                mainno++;
            }
            else if (token_table[ptokenno].tokenval == ID && token_table[ptokenno + 1].tokenval == L_XI) ///�Զ��庯��
            {
                root_tag++;
                newtemp = newlnodestmt(funck); ///��̬����һ�����ṹ�Ľڵ�
                match(token);
                treenode *j = newlnodeexp(idk);
                match(ID);
                newtemp->child[0] = j; ///�Զ��庯����
                match(L_XI);

                if (token != R_XI)
                {
                    newtemp->child[1] = entitypara_list(); ///�����б�
                }

                match(R_XI);
                if (token != FENH && token != L_DA)
                {
                    printf("error missing&& function error\n");
                }

                else
                {
                    newtemp->child[2] = structure_stmt();
                }
            }
            else if (token == STRUCT && token_table[ptokenno].tokenval == ID && token_table[ptokenno + 1].tokenval == L_DA)
            {
                root_tag++;
                newtemp = newlnodestmt(structk);
                match(token);
                treenode *j = newlnodeexp(idk);
                match(ID);
                newtemp->child[0] = j;

                if (token == L_DA)
                {
                    newtemp->child[1] = structure_stmt(); ///����Ϊ�˼򻯸�ֵ
                }
            }
            else ///��������--ȫ��  if(token==ID)
            {
                root_tag++;
                newtemp = newlnodestmt(defineparak);

                match(token);

                if (token != ID)
                {
                    printf("������������\n", count_row());
                }

                newtemp->child[0] = define_assign();

                if (token != FENH)
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
            if (token == ID)
            {
                printf("δ����\n");
            }
            else
            {
                printf("�Ƿ�188\n");
            }
        }
    }
    if (mainno != 1)
    {
        printf("error\n", count_row());
    }

    tree_root = root;
    ///��ӡ�����﷨��
    parse_printtree();
}

/**����һ�����ṹ�Ľڵ�
if for while return assign fun define main define**/
treenode *newlnodestmt(Stmtkind stmt)
{
    /**Ϊ�½���ʼ��**/
    treenode *t = (treenode *)malloc(sizeof(treenode));
    t->nodekind = stmtk;
    t->kind.stmt = stmt;
    t->lineno = count_row();
    int i;
    for (i = 0; i < 4; i++)
        t->child[i] = NULL;
    t->sibling = NULL;

    if (stmt == maink) /**�����������**/
    {
        t->dtype = token;
    }

    if (stmt == defineparak) /**����Ƕ���**/
    {
        t->dtype = token;
    }

    if (stmt == funck)
    {
        if (isdtype())
            t->dtype = token;
    }
    return t;
}

///�������Զ��庯���Ĳ���  ���� fun(int a,int b)
treenode *entitypara_list()
{
    treenode *t;
    treenode *temp;
    treenode *temp1;
    treenode *newtemp;

    temp = newlnodestmt(defineparak);
    t = temp; ///�Ȱѷ��ص��׵�ַ����ס
    if (isdtype())
    {
        match(token);
    }
    else
    {
        printf("error ������������");
    }

    newtemp = newlnodeexp(idk);
    match(ID);
    temp->child[0] = newtemp;

    while (token == DOUH) /// ��ֹһ������ʱ
    {
        match(DOUH);
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
        match(ID);
        temp1->child[0] = newtemp;
        temp->sibling = temp1; ///����bug ע������ָ��ı任
        temp = temp1;
    }

    if (token != R_XI)
    {
        printf("error !  ���Ų�ƥ�䣡��");
    }

    return t;
}

/**
*����һ����ʽ�ṹexpk�Ľڵ㣬������ݵ���������
*opk(+ - * / ����һЩ��ϵ������),constk,idk
**/
///����������������ʶ��������������������idk����
treenode *newlnodeexp(Expkind exp)
{
    ///��ʼ��
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

    ///���Ϊ������
    if (exp == opk)
    {
        t->attr.op = token;
    }

    ///���Ϊ����
    if (exp == constk)
    {
        t->attr.val = token_table[ptokenno - 1].numval;
    }

    ///���Ϊ������������������ʶ����
    if (exp == idk && token_table[ptokenno].tokenval != DIAN)
    {
        strcpy(t->attr.name, token_table[ptokenno - 1].stringval);
    }

    ///���ڼӽ����� Ϊstruct���ͷ���
    if (exp = idk && token_table[ptokenno].tokenval == DIAN)
    {
        char struct_temp1[100] = {'\0'};
        //char struct_temp2[100]= {'\0'};
        char struct_temp3[100] = {'\0'};
        char struct_temp4[100] = {'\0'};
        strcpy(struct_temp1, token_table[ptokenno - 1].stringval);
        //strcpy(struct_temp2,token_table[ptokenno].stringval);
        strcpy(struct_temp3, token_table[ptokenno + 1].stringval);
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
        strcpy(t->attr.name, struct_temp4);
    }
    return t;
}

/***********************************************************
* ����:�Դ����ſ�ʼ��һ����ṹ
        ���磺 for if  while  main fun
**********************************************************/
treenode *structure_stmt()
{
    treenode *t = NULL;
    treenode *temp = NULL;
    treenode *newtemp;
    int k = 0;
    match(L_DA);
    while (isin_first_instmt_sequence()) /**��ǰToken�Ƿ���instmt-sequence�Ķ��弯����**/
    {
        k++;
        newtemp = instmt_sequence(); ///��ʼ���Ե����

        if (temp != NULL)
        {
            temp->sibling = newtemp;
        }

        temp = newtemp;
        if (k == 1)
        {
            t = temp; ///��ͷ���̶�ס �Ա㷵��
        }
    }
    match(R_DA);
    return t;
}
///Ϊ���ж��ǲ�����Щ������ for if while ���� ����
int isin_first_instmt_sequence()
{
    tokentype first_instmt[20] = {FOR, WHILE, IF, INT, FLOAT,
                                  CHAR, DOUBLE, ID, RETURN,
                                  STRUCT, SWITCH, CASE, BREAK,
                                  DEFAULT};
    int i = 0;
    for (i = 0; i < 20; i++)
    {
        if (token == first_instmt[i])
            return 1;
    }
    return 0;
}

/**FOR IF WHILE ���� PRINTF SCANF��� RETURN �ȵ�**/
treenode *instmt_sequence()
{
    treenode *t = NULL;

    switch (token)
    {
    /**forѭ�� !!**/
    case FOR:
    {
        t = for_stmt();
        break;
    }
    /**IF��� !!**/
    case IF:
    {
        t = if_stmt();
        break;
    }
    /**while��� !!**/
    case WHILE:
    {
        t = while_stmt();
        break;
    }
    /**struct��� !!**/
    case SWITCH:
    {
        t = switch_stmt();
        break;
    }
        /**case��� !!**/
    case CASE:
    {
        t = case_stmt();
        break;
    }
        /**case��� !!**/
    case BREAK:
    {
        t = break_stmt();
        break;
    }
    case DEFAULT:
    {
        t = default_stmt();
        break;
    }
    default:
    {
        t = statement(); ///  ��ͨ����кܶ�--�������ã����壬��ֵ return�ȵ�
        if (token != FENH)
        {
            printf("missing ';' %d ", count_row()); ///���Ϊ������䣻��ӡ��������䣬������ж���û�зֺ�
        }
        else
        {
            match(FENH);
        }
        break;
    }
    }
    return t;
}

///for���
treenode *for_stmt()
{
    treenode *t = NULL;
    treenode *temp;

    t = newlnodestmt(fork);

    match(FOR);
    match(L_XI);

    if (token != FENH)
    {
        if (token == INT)
        {
            t->child[0] = definepara_stmt();
        }
        else
        {
            t->child[0] = exp2();
        }
    }

    match(FENH);
    if (token != FENH)
    {
        if (token_table[ptokenno].tokenval == EQUAL)
        {
            printf("warning!! ����Ϊ��ֵ��ʽ");
        }
        else
        {
            t->child[1] = exp2();
        }
    }

    match(FENH);

    if (token != R_XI)
    {
        t->child[2] = exp2();
    }

    match(R_XI);

    if (token == FENH)
    {
        match(FENH);
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
    match(IF);
    match(L_XI);
    if (token_table[ptokenno].tokenval == EQUAL && token_table[ptokenno + 1].tokenval != EQUAL)
    {
        printf("warning");
    }
    t->child[0] = BUER_stmt();
    match(R_XI);
    t->child[1] = structure_stmt();

    if (token == ELSE && token_table[ptokenno].tokenval == IF)
    {
        match(ELSE);
        t->child[2] = if_stmt();
        ifelse_tag = 1;
    }
    if (token == ELSE && token_table[ptokenno].tokenval != IF)
    {
        match(ELSE);
        t->child[2] = structure_stmt();
    }

    return t;
}
treenode *BUER_stmt()
{
    treenode *t;
    treenode *t1;
    treenode *t2;
    if (token_table[ptokenno + 2].tokenval == ADE || token_table[ptokenno + 3].tokenval == ADE ||
        token_table[ptokenno + 2].tokenval == HUO || token_table[ptokenno + 3].tokenval == HUO)
    {
    }
    else
    {
        t = exp2();
    }
}
///��Ҫ����FOR ,IF while ,�㲻֪���Ǹ�ֵ���ǹ�ϵ���㡣
treenode *exp2()
{
    treenode *t;
    if (token == ID && token_table[ptokenno].tokenval == EQUAL)
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
 * ����:	while���
 **********************************************************/
treenode *while_stmt()
{
    treenode *t = newlnodestmt(whilek);
    match(WHILE);
    match(L_XI);
    t->child[0] = exp2();
    match(R_XI);
    if (token == L_DA)
        t->child[1] = structure_stmt();
    return t; ///!!!���bug ���˺þ�ѽ������
}
/***********************************************************
 * ����:	switch���
 **********************************************************/
treenode *switch_stmt()
{
    treenode *t = newlnodestmt(switchk);
    match(SWITCH);
    match(L_XI);
    t->child[0] = exp2();
    match(R_XI);
    if (token == L_DA)
    {
        t->child[1] = structure_stmt();
    }
    return t;
}
///����case����
treenode *case_stmt()
{
    treenode *t = newlnodestmt(casek);
    match(CASE);
    treenode *j = newlnodeexp(idk);
    t->child[0] = j;
    match(ID);
    match(MAOH);
    if (token == L_DA)
    {
        t->child[1] = structure_stmt();
    }
    return t;
}
///����break���
treenode *break_stmt()
{
    treenode *t = newlnodestmt(breakk);
    match(BREAK);
    match(FENH);
    return t;
}
///����default���
treenode *default_stmt()
{
    treenode *t = newlnodestmt(defaultk);
    match(DEFAULT);
    match(MAOH);
    if (token == L_DA)
    {
        t->child[0] = structure_stmt();
    }
    return t;
}
treenode *statement()
{
    treenode *t = NULL;
    /**�����dtype����Ϊ�������**/
    if (isdtype())
    {
        t = definepara_stmt();
    }
    else if (token == RETURN)
    {
        t = newlnodestmt(returnk);
        match(RETURN);
        t->child[0] = exp();
    }
    else if (token == STRUCT)
    {
        t = definepara_stmt();
    }
    else if (token == ID) /**��������,���鶨�壬�����ĸ�ֵ**/
    {
        int tag_array = array_judge(ptokenno);

        if (token_table[ptokenno].tokenval == EQUAL || tag_array == 1)
        {
            t = assign_stmt(); ///����������ֵ(��������Ϊ�������õĽ��)
        }
        else if (token_table[ptokenno].tokenval == L_XI)
        {
            t = fun_apply(); /// ��������
        }
        else if (token_table[ptokenno].tokenval == DIAN && token_table[ptokenno + 2].tokenval == EQUAL)
        {
            t = assign_stmt();
        }
        else ///if()��д  �о���������
        {
            t = exp();
        }
    }
    return t;
}
/***********************************************************
 * ����:	��������  fun(a,b)
 **********************************************************/
treenode *fun_apply()
{
    treenode *t;
    t = newlnodestmt(funck);
    treenode *temp1 = newlnodeexp(idk);
    match(ID);
    match(L_XI);
    treenode *temp2 = input_para_list();
    t->child[0] = temp1;
    t->child[1] = temp2;
    match(R_XI);
    return t;
}

///�����б� �����ں���������Ĳ��� ����fun(1,2)
treenode *input_para_list()
{
    treenode *t;
    treenode *temp;
    temp = factor();
    t = temp;
    while (token == DOUH)
    {
        match(DOUH);
        temp->sibling = factor();
        temp = temp->sibling;
    }
    return t;
}
int array_judge(int p)
{
    if (token_table[p].tokenval == L_ZH)
    {
        int i;
        for (i = p + 1; i < 1000; i++) ///��bug����������
        {
            if (token_table[i].tokenval == R_ZH)
            {
                return 1;
            }
        }
        return -1;
    }
    return -1;
}

/**�жϵ�ǰ�Ǻ��Ƿ��Ǳ�����������ֵ����VOID���⣩**/
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

/**�������**/
treenode *definepara_stmt()
{
    treenode *t = NULL;
    t = newlnodestmt(defineparak);

    if (isdtype())
    {
        match(token); //dtype
    }
    else if (token == STRUCT)
    {
        match(token);
        match(ID); ///������struct XX match��
    }

    else
        printf("arguement has no type", count_row());

    t->child[0] = define_assign();
    return t;
}

/**������ֵ����  ����Ķ���,��ʼ������ʼ���Ͷ����ͬʱ����**/
treenode *define_assign()
{
    treenode *t = NULL;
    treenode *temp = NULL;
    treenode *newtemp;
    int k = 0;

    if (token_table[ptokenno].tokenval == FENH)
    {
        k++;
        newtemp = newlnodeexp(idk);
        match(ID);
        //match(FENH);
        return t = newtemp;
    }
    /**֧�ֱ��������ʼ�������������**/
    while (token_table[ptokenno].tokenval == EQUAL || token_table[ptokenno].tokenval == DOUH || token_table[ptokenno].tokenval == FENH || token_table[ptokenno].tokenval == L_ZH)

    {
        switch (token_table[ptokenno].tokenval)
        {

        case EQUAL: /**��ֵ���**/
        {
            k++;
            newtemp = assign_stmt();
            if (temp != NULL)
            {
                temp->sibling = newtemp;
            }
            temp = newtemp;
            if (token == DOUH)
            {
                match(DOUH);
            }
            if (k == 1)
            {
                t = temp;
            }
            break;
        }
        case DOUH:
        {
            k++;
            newtemp = newlnodeexp(idk);
            match(ID);
            match(DOUH);
            if (temp != NULL)
            {
                temp->sibling = newtemp;
            }
            temp = newtemp;
            if (k == 1)
            {
                t = temp;
            }
            break;
        }

        case FENH:
        {
            k++;
            newtemp = newlnodeexp(idk);
            match(ID);
            if (temp != NULL)
            {
                temp->sibling = newtemp;
            }
            temp = newtemp;
            if (k == 1)
            {
                t = temp;
            }
            break;
        }
        case L_ZH: ///���鲿�֣���
        {
            k++;

            newtemp = newlnodestmt(define_arrayk);
            treenode *t1 = newlnodeexp(idk);
            match(ID);
            newtemp->child[0] = t1;

            match(L_ZH);
            if (token != NUM && token != R_ZH) ///һЩ�������
            {
                printf("error!!���鶨������");
            }
            if (token == NUM)
            {
                treenode *t2 = newlnodeexp(constk);
                match(NUM);
                newtemp->child[1] = t2;
            }
            match(R_ZH);
            if (temp != NULL)
            {
                temp->sibling = newtemp;
            }
            temp = newtemp;
            if (token == DOUH)
            {
                match(DOUH);
            }
            if (k == 1)
            {
                t = temp;
            }
            break;
        }
        default:
        {
            printf("there should be assignment statement or variable", count_row());
        }
        }
    }
    return t;
}

/**��ֵ���  ����ĸ�ֵ���ڼӽ�����������**/
treenode *assign_stmt()
{
    treenode *t1;
    if (token_table[ptokenno].tokenval == L_ZH) ///���鸳ֵ  ����a[1] a[2]
    {
        t1 = newlnodeexp(cite_arrayk);
        treenode *t2 = newlnodeexp(idk);
        match(ID);
        t1->child[0] = t2;
        match(L_ZH);
        t1->child[1] = exp2(); ///ֱ����factor������ֽṹ�ˣ�
        match(R_ZH);
    }
    else if (token_table[ptokenno].tokenval == DIAN) ///Ϊstruct�ṹר�Ŷ���
    {
        t1 = newlnodeexp(idk);
        match(ID);
        match(DIAN);
        match(ID);
    }
    else
    {
        t1 = newlnodeexp(idk);
        match(ID);
    }
    match(EQUAL); ///����Ҫ��=ƥ���op

    ///opk=EQUAL
    treenode *t = newlnodestmt(assignk);
    t->child[0] = t1;
    t->child[1] = exp();
    return t;
}

///  simple_exp conpare simple_exp   ||simple_exp
treenode *exp()
{
    treenode *t;
    treenode *temp;

    temp = simple_exp();
    ///�򵥱��ʽ
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
    tokentype compare_op[6] = {SMALLER, SMALLEREQU,
                               BIGGER, BIGGEREQU,
                               NOTEQU, IFEQU}; //< <= > >= != ==
    int i;
    for (i = 0; i < 6; i++)
    {
        if (token == compare_op[i])
        {
            return 1;
        }
    }
    return 0; ///û��ƥ����
}

///�򵥱��ʽ �Ӽ�
treenode *simple_exp()
{
    treenode *t = NULL;
    treenode *newtemp;
    treenode *temp;

    temp = term();

    ///�ӷ���������
    while (token == PLUS || token == MINUS)
    {
        newtemp = newlnodeexp(opk);
        match(token);
        ///�ӽڵ�ֱ�Ϊ��������term
        newtemp->child[0] = temp;
        newtemp->child[1] = term();
        temp = newtemp;
    }
    t = temp;
    return t;
}

///��Ҫ�ǳ˳�
treenode *term()
{
    treenode *t = NULL;
    treenode *temp;
    treenode *newtemp;

    temp = factor();

    while (token == TIMES || token == DIVIDE)
    {
        newtemp = newlnodeexp(opk);
        match(token);
        newtemp->child[0] = temp;
        newtemp->child[1] = factor();
        temp = newtemp;
    }

    return t = temp;
}

///������ĵ�ģ��
treenode *factor()
{
    treenode *t = NULL;
    switch (token)
    {
    ///�����ŵı��ʽ
    case L_XI:
    {
        match(L_XI);
        t = exp();
        match(R_XI);
        break;
    }

    ///����---����Ϊ����������䣬����Ϊ���飬����Ϊ��ͨ����
    case ID:
    {
        if (token_table[ptokenno].tokenval == L_XI) ///��������
        {
            t = fun_apply();
        }
        else if (token_table[ptokenno].tokenval == L_ZH) ///����
        {
            t = newlnodeexp(cite_arrayk);
            treenode *temp1 = newlnodeexp(idk);
            match(ID);
            match(L_ZH);
            treenode *temp2 = exp2(); ///����С��Χfactor ����;
            t->child[0] = temp1;
            t->child[1] = temp2;
            match(L_ZH);
        }
        else ///��ͨ����
        {
            t = newlnodeexp(idk);
            match(ID);
        }
        break;
    }

    ///����
    case NUM:
    {
        t = newlnodeexp(constk);
        t->attr.val = token_table[ptokenno - 1].numval;
        match(NUM);
        break;
    }
    }
    return t;
}

/** ** **** **** *****   *******       ��������﷨���Ĺ���  *******   *****  ******   *****/

void parse_printtree()
{
    treenode *t = tree_root;
    printtree(t);
}

///��
void printtree(treenode *lnode)
{
    int i;
    treenode *pnode;
    int TAG = printtree_t;
    for (i = 0; i < TAG; i++)
        printf("        ");
    printnode(lnode);
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
///��ӡ���
void printnode(treenode *lnode)
{
    if (lnode->nodekind == expk) ///���ʽ���
    {

        switch (lnode->kind.exp)
        {
        case idk:
        {
            printf("id=  [%s]", lnode->attr.name);
            break;
        }
        case opk:
        {
            token = lnode->attr.op;
            printf("op=  [%s]", tokenstring()); ///tokenstring()����Ҫ����
            break;
        }
        case constk:
        {
            printf("num=  [%g]", lnode->attr.val);
            break;
        }
        case cite_arrayk:
        {
            printf("array_id'[%s]'", lnode->child[0]->attr.name);
            break;
        }
        }
    }
    else if (lnode->nodekind == stmtk) ///stmtk  //�������
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
            printf("assign:");
            break;
        }
        case funck:
        {
            token = lnode->dtype;
            if (lnode->child[2] != NULL)
            {
                printf("function : type is");
                printf(" [%s]", tokenstring());
            }
            else
            {
                printf("callfunc :");
            }

            break;
        }
        case defineparak:
        {
            token = lnode->dtype;
            printf("definepara : ");
            printf("[%s]", tokenstring());
            break;
        }
        case maink:
        {
            printf("[main]");
            break;
        }
        case define_arrayk:
        {
            printf("definearray");
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
        default:
            printf("error1!!!");
        }
    }
    else
    {
        printf("�ڵ����󣡣�");
    }
}
