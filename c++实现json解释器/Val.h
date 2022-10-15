#ifndef VAL_H
#define VAL_H


#include <bits/stdc++.h>
using namespace std;
#define INT 0
#define DOU 1
#define STR 2
#define BOOL 3
#define LIST 4
#define DICT 5
class Val
{
public:
    int INT_VAL;
    double DOU_VAL;
    string STR_VAL;
    bool BOOL_VAL;
    int type;
    vector<Val> List;
    map<Val, Val> dict;
    void del();
    
    Val();
    ~Val();
    Val(const int &x);
    Val(const double &x);
    Val(const string &x);
    Val(const char *x);
    Val(const bool &x);
    Val(initializer_list<Val> l);
    void add(Val x);
    void put(Val key,Val value);
    Val &operator[](Val i)
    {
        if (i.type == LIST)
            return List[i.INT_VAL];
        else
            return dict[i];
    }
    string str();
};

stringstream ss;
Val parser_val();
Val parser_num();
Val parser_str();
Val parser_bool();
Val parser_arr();
Val parser_map();
#endif