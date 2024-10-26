#ifndef SYNTAX_H
#define SYNTAX_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <typeinfo>
#include <regex>
using namespace std;
class scopeTableInstance
{
    public:
    string name;
    string type;
    int scope;
    scopeTableInstance() {}
    scopeTableInstance(string n, string t, int s)
    {
        this->name = n;
        this->type = t;
        this->scope = s;
    }
};
class memberTableInstance
{
    public:
    string name;
    string type;
    string type_modifier;
    string access_modif;
    string class_name;
    memberTableInstance() {}
    memberTableInstance(string n, string t, string ac, string ty, string cn)
    {
        this->name = n;
        this->type = t;
        this->access_modif = ac;
        this->type_modifier = ty;
        this->class_name = cn;
    }
};
class defTableInstance
{
    public:
    string name;
    string type;
    string access_modif;
    string parent;
    string type_modifier;
    defTableInstance() {}
    vector<memberTableInstance> memberTable;
    defTableInstance(string n, string t, string ac, string p, string ty)
    {
        this->name = n;
        this->type = t;
        this->access_modif = ac;
        this->parent = p;
        this->type_modifier = ty;
    }
};
class Syntax
{
public:
    int i = 0;
    vector<tuple<string, string, int>> token;

    vector<int> stack;
    int scope = 0;
    int currentScope = 0;
    string CCN;
    defTableInstance CCR;
    vector<defTableInstance> defTable;
    vector<scopeTableInstance> scopeTable;

    void createScope();
    void destroyScope();
    bool insert_DT(string name,string type,string access_modif,string parent,string type_modifier);

    bool insert_ST(string name,string type,string scope);

    bool insert_MT(string name,string type,string access_modif,string type_modifier,string class_name);

    string lookUp_ST(string name);

    defTableInstance lookUp_DT(string name);

    memberTableInstance lookUp_MT(string name,string class_name);

    string lookUp_func_ST(string name,string PL);

    string lookUp_func_MT(string name,string PL,string class_name);

    string compatibilityCheck(string LeftOp,string RightOp,string Operator);

    string compatibilitytest(string OpType,string Operator);


    void checkSyntax();
    void print();
    bool start();
    bool defs();
    bool declare();
    bool init();
    bool value();
    bool body();
    bool MST();
    bool SST();
    bool declaration();
    bool decl_right();
    bool decl_left();
    bool object_decl();
    bool obj();
    bool list_access();
    bool list_decl();
    bool list_end();
    bool list_size();
    bool list_size1();
    bool set_decl();
    bool set_init();
    bool set_next();
    bool args();
    bool args_next();
    bool a2();
    bool a3();
    bool a4();
    bool conditional_st();
    bool Else();
    bool flow_control();
    bool function();
    bool func1();
    bool parameter();
    bool para1();
    bool type();
    bool Return();
    bool Ret1();
    bool exception_handling();
    bool err();
    bool for_loop();
    bool f1();
    bool f2();
    bool f3();
    bool while_loop();
    bool expression();
    bool OR();
    bool AND();
    bool AND1();
    bool RO();
    bool RO1();
    bool PM();
    bool PM1();
    bool MDM();
    bool MDM1();
    bool end();
    bool exp_decl();
    bool structure();
    bool Class();
    bool inherit();
    bool access_modifier();
    bool class_outer_body();
    bool class_outer_MST();
    bool class_outer_SST();
    bool class_declare();
    bool class_init();
    bool fn();
    bool class_function();
    bool class_func1();
    bool a();
    bool op();
    bool class_constructor();
    bool class_body();
    bool class_MST();
    bool class_SST();
    bool super_this();
    bool class_declaration();
    bool this_decl();
    bool class_decl_left();
    bool class_decl_right();
    bool class_list_access();
    bool class_list_decl();
    bool class_list_end();
    bool class_list_size();
    bool class_list_size1();
    bool class_set_decl();
    bool class_set_init();
    bool class_set_next();
    bool class_args();
    bool class_args_next();
    bool class_a2();
    bool class_a3();
    bool class_a4();
    bool class_conditional_st();
    bool class_else();
    bool class_return();
    bool class_ret1();
    bool class_exception_handling();
    bool class_for_loop();
    bool class_f1();
    bool class_f2();
    bool class_f3();
    bool class_while();
    bool class_expression();
    bool class_OR();
    bool class_AND();
    bool class_AND1();
    bool class_RO();
    bool class_RO1();
    bool class_PM();
    bool class_PM1();
    bool class_MDM();
    bool class_MDM1();
    bool class_end();
    bool class_exp_decl();
};

#endif
