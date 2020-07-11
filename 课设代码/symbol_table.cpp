#include <iostream>

#include <string>

#include <iomanip>
#include "symbol_table.h"
using namespace std;

//标志符数据类型的枚举，整型、实型、字符型、布尔型与枚举型等



#define SIZE 211

#define SHIFT 4

static int hash_(string key)

{
    int temp = 0;

    int i = 0;

    while (key[i] != '\0')

    {
        temp = ((temp << SHIFT) + key[i]) % SIZE;

        ++i;
    }
    return temp;
}




 BucketList Listhash[SIZE];

static ArrayList Arrayhash_[SIZE];

static FunctionList Functionhash_[SIZE];

//量的哈希表插入

void List_insert(string name, int type, long scope, long loc, int flag)

{

    int h = hash_(name);

    List *l;

    l = new List;

    l->name = name;

    l->type = type;

    l->scope = scope;

    l->memloc = loc;

    l->flag = flag;

    l->next = Listhash[h];

    Listhash[h] = l;
}

//量的哈希表修改

void List_delete(string name)

{

    int h = hash_(name);

    Listhash[h] = NULL;
}

//量的哈希表查找

long List_find(string name)

{

    int h = hash_(name);
//    cout<<h<<55555<<endl;
    List *l;

    l = Listhash[h];
    if(l== nullptr)
        return -1;

    return l->memloc;
}

//数组的哈希表插入

void Array_insert(string name, int type, long scope, long loc, int weishu, string spec)

{

    int h = hash_(name);

    Array *l;

    l = new Array;

    l->name = name;

    l->type = type;

    l->scope = scope;

    l->memloc = loc;

    l->weishu = weishu;

    l->spec = spec;

    l->next = Arrayhash_[h];

    Arrayhash_[h] = l;
}

//数组的哈希表修改

void Array_delete(string name)

{

    int h = hash_(name);

    Arrayhash_[h] = NULL;
}

//数组的哈希表查找

long Array_find(string name)

{

    int h = hash_(name);

    Array *l;

    l = Arrayhash_[h];
    if(l== nullptr)
        return -1;
    return l->memloc;
}

//函数的哈希表插入

void Function_insert(string name, int type, ParamList pl, long scope, long loc)

{

    int h = hash_(name);

    Function *l;

    l = new Function;

    l->name = name;

    l->type = type;

    l->pl = pl;

    l->scope = scope;

    l->memloc = loc;

    l->next = Functionhash_[h];

    Functionhash_[h] = l;
}

//函数的哈希表插入

void Function_delete(string name)

{

    int h = hash_(name);

    Functionhash_[h] = NULL;
}

//函数的哈希表查找

long Function_find(string name)

{

    int h = hash_(name);

    Function *l;

    l = Functionhash_[h];

    return l->memloc;
}

//量的打印

void printList()

{

    int i;

    cout << "各种量的符号表" << endl;

    cout << "Name     Type       Scope     Memloc   flag" << endl;

    cout << "---------------------------------------------------" << endl;

    for (i = 0; i < SIZE; i++)

    {

        if (Listhash[i] != NULL)

        {

            BucketList l = Listhash[i];

            while (l != NULL)

            {

                cout << std::left << setw(10) << l->name << std::left << setw(10) << l->type << std::left << setw(10) << l->scope << std::left <<

                    setw(10) << l->memloc << std::left << setw(10) << l->flag << endl;

                l = l->next;
            }
        }
    }
}

//数组的打印

void printArray()

{

    int i;

    cout << "数组的符号表" << endl;

    cout << "Name     Type       Scope     Memloc   Weishu     Spec" << endl;

    cout << "-----------------------------------------------------------" << endl;

    for (i = 0; i < SIZE; i++)

    {

        if (Arrayhash_[i] != NULL)

        {

            ArrayList l = Arrayhash_[i];

            while (l != NULL)

            {

                cout << std::left << setw(10) << l->name << setw(10) << l->type << setw(10) << l->scope <<

                    setw(10) << l->memloc << setw(10) << l->weishu << setw(10) << l->spec << endl;

                l = l->next;
            }
        }
    }
}

//函数的打印

void printFunction()

{

    int i;

    cout << "函数的符号表" << endl;

    cout << "Name     Type       Scope     Memloc" << endl;

    cout << "-----------------------------------------" << endl;

    for (i = 0; i < SIZE; i++)

    {

        if (Functionhash_[i] != NULL)

        {

            FunctionList l = Functionhash_[i];

            while (l != NULL)

            {

                cout << setw(10) << l->name << setw(10) << l->type << setw(10) << l->scope << setw(10) << l->memloc << endl;

                l = l->next;
            }
        }
    }

    cout << "参数列表的符合表" << endl;

    cout << "FunctionName type ParamName" << endl;

    cout << "----------------------------------------" << endl;

    for (i = 0; i < SIZE; i++)

    {

        if (Functionhash_[i] != NULL)

        {

            FunctionList l = Functionhash_[i];

            while (l != NULL)

            {

                ParamList p = l->pl;

                while (p != NULL)

                {

                    cout << setw(13) << l->name << setw(10) << p->type << setw(10) << p->name << endl;

                    p = p->next;
                }

                l = l->next;
            }
        }
    }
}

void symbol_table()

{

//    string name = "afa";
//
//    int type = 1;
//
//    long scope = 101010;
//
//    long loc = 1000220;
//
//    int flag = 1;
//
//    ParamList p1, p2;
//
//    p1 = new Param;
//
//    p2 = new Param;
//
//    p1->name = "a";
//
//    p1->type = 1;
//
//    p1->next = p2;
//
//    p2->name = "b";
//
//    p2->type = 2;
//
//    p2->next = NULL;
//
//    for(int i=0;i<SIZE;i++)
//    {
//        List_insert(name, type, scope, loc, flag);
//    }

//
//    List_insert("fa", 2, 101010, 101011, 2);
//
//    Array_insert("a", 1, 101111, 112132, 2, "2*3");
//
//    Function_insert("A", 1, p1, 1010011, 11111);
//
//    printList();
//
//    printArray();
//
//    printFunction();
//
//    cout << "查找" << endl;
//
//    cout << List_find("fa") << endl;
//
//    cout << "删除" << endl;
//
//    List_delete("fa");
//
//    printList();

}