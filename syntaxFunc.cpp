#include "header files\syntax.h"
void Syntax::print()
{
    for (auto &i : token)
    {
        cout << get<0>(i) << " | " << get<1>(i) << " | " << get<2>(i) << endl;
    }
}
void Syntax::checkSyntax()
{
    if (start())
    {
        if (get<0>(token[i]) == "$")
        {
            cout << "No Syntax Error In the Code" << endl;
        }
        else
        {
            cout << "Error at line no :" << get<2>(token[i]) << endl;
        }
    }
    else
    {
        cout << "Error at line no :" << get<2>(token[i]) << endl;
    }
}

bool Syntax::start()
{
    if (get<0>(token[i]) == "class" || get<0>(token[i]) == "interface" || get<0>(token[i]) == "def" || get<0>(token[i]) == "DT" || get<0>(token[i]) == "list" || get<0>(token[i]) == "set" || get<0>(token[i]) == "void")
    {
        if (defs())
        {
            if (get<0>(token[i]) == "void")
            {
                i++;
                if (get<0>(token[i]) == "main")
                {
                    i++;
                    if (get<0>(token[i]) == "(")
                    {
                        i++;
                        if (args())
                        {
                            if (get<0>(token[i]) == ")")
                            {
                                i++;
                                if (get<0>(token[i]) == "{")
                                {
                                    i++;
                                    if (MST())
                                    {
                                        if (get<0>(token[i]) == "}")
                                        {
                                            i++;
                                            if (defs())
                                            {
                                                return true;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}
bool Syntax::defs()
{
    if (get<0>(token[i]) == "DT" || get<0>(token[i]) == "ID" || get<0>(token[i]) == "def" || get<0>(token[i]) == "list" || get<0>(token[i]) == "set" || get<0>(token[i]) == "class" || get<0>(token[i]) == "interface")
    {
        if (function())
        {
            if (defs())
            {
                return true;
            }
        }
        else if (declare())
        {
            if (defs())
            {
                return true;
            }
        }
        else if (get<0>(token[i]) == "ID")
        {
            i++;
            if (declaration())
            {
                if (get<0>(token[i]) == ";")
                {
                    i++;
                    if (defs())
                    {
                        return true;
                    }
                }
            }
        }
        else if (list_decl())
        {
            cout << "111" << endl;
            if (defs())
            {
                return true;
            }
        }
        else if (set_decl())
        {
            cout << "119" << endl;
            if (defs())
            {
                return true;
            }
        }
        else if (Class())
        {
            if (defs())
            {
                return true;
            }
        }
    }
    else if (get<0>(token[i]) == "void" || get<0>(token[i]) == "$")
    {
        return true;
    }
    return false;
}
bool Syntax::args()
{
    if (get<0>(token[i]) == "ID" || get<0>(token[i]) == "int literal" || get<0>(token[i]) == "float literal" || get<0>(token[i]) == "char literal" || get<0>(token[i]) == "string literal" || get<0>(token[i]) == "bool literal" || get<0>(token[i]) == "(")
    {
        if (expression())
        {
            if (args_next())
            {
                return true;
            }
        }
    }
    else if (get<0>(token[i]) == ")")
    {
        return true;
    }
    return false;
}
bool Syntax::args_next()
{
    if (get<0>(token[i]) == ",")
    {
        i++;
        if (args())
        {
            return true;
        }
    }
    else if (get<0>(token[i]) == ")")
    {
        return true;
    }
    return false;
}
bool Syntax::body()
{
    if (get<0>(token[i]) == "{")
    {
        i++;
        if (MST())
        {
            if (get<0>(token[i]) == "}")
            {
                i++;
                return true;
            }
        }
    }
    return false;
}
bool Syntax::MST()
{
    if (get<0>(token[i]) == "DT" || get<0>(token[i]) == "if" || get<0>(token[i]) == "while" || get<0>(token[i]) == "for" || get<0>(token[i]) == "ID" || get<0>(token[i]) == "try" || get<0>(token[i]) == "list" || get<0>(token[i]) == "set" || get<0>(token[i]) == "break" || get<0>(token[i]) == "continue" || get<0>(token[i]) == "return")
    {
        if (SST())
        {
            if (MST())
            {
                return true;
            }
        }
    }
    else if (get<0>(token[i]) == "}")
    {
        return true;
    }
    return false;
}
bool Syntax::SST()
{
    if (get<0>(token[i]) == "DT" || get<0>(token[i]) == "if" || get<0>(token[i]) == "while" || get<0>(token[i]) == "for" || get<0>(token[i]) == "ID" || get<0>(token[i]) == "try" || get<0>(token[i]) == "list" || get<0>(token[i]) == "set" || get<0>(token[i]) == "break" || get<0>(token[i]) == "continue" || get<0>(token[i]) == "return")
    {
        if (declare())
        {
            return true;
        }
        else if (conditional_st())
        {
            return true;
        }
        else if (while_loop())
        {
            return true;
        }
        else if (for_loop())
        {
            return true;
        }
        else if (get<0>(token[i]) == "ID")
        {
            i++;
            if (declaration())
            {
                if (get<0>(token[i]) == ";")
                {
                    i++;
                    return true;
                }
            }
        }
        else if (exception_handling())
        {
            return true;
        }
        else if (list_decl())
        {
            return true;
        }
        else if (set_decl())
        {
            return true;
        }
        else if (flow_control())
        {
            if (get<0>(token[i]) == ";")
            {
                i++;
                return true;
            }
        }
        else if (Return())
        {
            if (get<0>(token[i]) == ";")
            {
                i++;
                return true;
            }
        }
    }
    return false;
}
bool Syntax::expression()
{
    if (get<0>(token[i]) == "ID" || get<0>(token[i]) == "int literal" || get<0>(token[i]) == "float literal" || get<0>(token[i]) == "char literal" || get<0>(token[i]) == "string literal" || get<0>(token[i]) == "bool literal" || get<0>(token[i]) == "(")
    {
        if (AND())
        {
            if (OR())
            {
                return true;
            }
        }
    }
    return false;
}
bool Syntax::AND()
{
    if (get<0>(token[i]) == "ID" || get<0>(token[i]) == "int literal" || get<0>(token[i]) == "float literal" || get<0>(token[i]) == "char literal" || get<0>(token[i]) == "string literal" || get<0>(token[i]) == "bool literal" || get<0>(token[i]) == "(")
    {
        if (RO())
        {
            if (AND1())
            {
                return true;
            }
        }
    }
    return false;
}
bool Syntax::OR()
{
    if (get<0>(token[i]) == "or")
    {
        i++;
        if (AND())
        {
            if (OR())
            {
                return true;
            }
        }
    }
    else if (get<0>(token[i]) == ";" || get<0>(token[i]) == ")" || get<0>(token[i]) == "]" || get<0>(token[i]) == "," || get<0>(token[i]) == "}")
    {
        return true;
    }
    return false;
}
bool Syntax::AND1()
{
    if (get<0>(token[i]) == "and")
    {
        i++;
        if (RO())
        {
            if (AND1())
            {
                return true;
            }
        }
    }
    else if (get<0>(token[i]) == "or" || get<0>(token[i]) == ";" || get<0>(token[i]) == ")" || get<0>(token[i]) == "]" || get<0>(token[i]) == "," || get<0>(token[i]) == "}")
    {
        return true;
    }
    return false;
}
bool Syntax::RO()
{
    if (get<0>(token[i]) == "ID" || get<0>(token[i]) == "int literal" || get<0>(token[i]) == "float literal" || get<0>(token[i]) == "char literal" || get<0>(token[i]) == "string literal" || get<0>(token[i]) == "bool literal" || get<0>(token[i]) == "(")
    {
        if (PM())
        {
            if (RO1())
            {
                return true;
            }
        }
    }
    return false;
}
bool Syntax::RO1()
{
    if (get<0>(token[i]) == "ro")
    {
        i++;
        if (PM())
        {
            if (RO1())
            {
                return true;
            }
        }
    }
    else if (get<0>(token[i]) == "and" || get<0>(token[i]) == "or" || get<0>(token[i]) == ";" || get<0>(token[i]) == ")" || get<0>(token[i]) == "]" || get<0>(token[i]) == "," || get<0>(token[i]) == "}")
    {
        return true;
    }
    return false;
}
bool Syntax::PM()
{
    if (get<0>(token[i]) == "ID" || get<0>(token[i]) == "int literal" || get<0>(token[i]) == "float literal" || get<0>(token[i]) == "char literal" || get<0>(token[i]) == "string literal" || get<0>(token[i]) == "bool literal" || get<0>(token[i]) == "(")
    {
        if (MDM())
        {
            if (PM1())
            {
                return true;
            }
        }
    }
    return false;
}
bool Syntax::PM1()
{
    if (get<0>(token[i]) == "pm")
    {
        i++;
        if (MDM())
        {
            if (PM1())
            {
                return true;
            }
        }
    }
    else if (get<0>(token[i]) == "ro" || get<0>(token[i]) == "and" || get<0>(token[i]) == "or" || get<0>(token[i]) == ";" || get<0>(token[i]) == ")" || get<0>(token[i]) == "]" || get<0>(token[i]) == "," || get<0>(token[i]) == "}")
    {
        return true;
    }
    return false;
}
bool Syntax::MDM()
{
    if (get<0>(token[i]) == "ID" || get<0>(token[i]) == "int literal" || get<0>(token[i]) == "float literal" || get<0>(token[i]) == "char literal" || get<0>(token[i]) == "string literal" || get<0>(token[i]) == "bool literal" || get<0>(token[i]) == "(")
    {
        if (end())
        {
            if (MDM1())
            {
                return true;
            }
        }
    }
    return false;
}
bool Syntax::MDM1()
{
    if (get<0>(token[i]) == "mdm")
    {
        i++;
        if (end())
        {
            if (MDM1())
            {
                return true;
            }
        }
    }
    else if (get<0>(token[i]) == "pm" || get<0>(token[i]) == "ro" || get<0>(token[i]) == "and" || get<0>(token[i]) == "or" || get<0>(token[i]) == ";" || get<0>(token[i]) == ")" || get<0>(token[i]) == "]" || get<0>(token[i]) == "," || get<0>(token[i]) == "}")
    {
        return true;
    }
    return false;
}
bool Syntax::end()
{
    if (get<0>(token[i]) == "ID" || get<0>(token[i]) == "int literal" || get<0>(token[i]) == "float literal" || get<0>(token[i]) == "char literal" || get<0>(token[i]) == "string literal" || get<0>(token[i]) == "bool literal" || get<0>(token[i]) == "(")
    {
        if (value())
        {
            return true;
        }
        else if (get<0>(token[i]) == "ID")
        {
            i++;
            if (exp_decl())
            {
                return true;
            }
        }
        else if (get<0>(token[i]) == "(")
        {
            i++;
            if (expression())
            {
                if (get<0>(token[i]) == ")")
                {
                    i++;
                    return true;
                }
            }
        }
    }
    return false;
}
bool Syntax::exp_decl()
{
    //( , null , [ , .
    if (get<0>(token[i]) == "(" || get<0>(token[i]) == "[" || get<0>(token[i]) == ".")
    {
        if (get<0>(token[i]) == "(")
        {
            i++;
            if (args())
            {
                if (get<0>(token[i]) == ")")
                {
                    i++;
                    if (decl_right())
                    {
                        return true;
                    }
                }
            }
        }
        else if (list_size())
        {
            if (decl_right())
            {
                return true;
            }
        }
        else if (decl_right())
        {
            return true;
        }
    }
    else if (get<0>(token[i]) == "mdm" || get<0>(token[i]) == "pm" || get<0>(token[i]) == "ro" || get<0>(token[i]) == "and" || get<0>(token[i]) == "or" || get<0>(token[i]) == ";" || get<0>(token[i]) == ")" || get<0>(token[i]) == "]" || get<0>(token[i]) == "," || get<0>(token[i]) == "}")
    {
        return true;
    }
    return false;
}

bool Syntax::decl_right()
{
    if (get<0>(token[i]) == ".")
    {
        i++;
        if (get<0>(token[i]) == "ID")
        {
            i++;
            if (decl_left())
            {
                return true;
            }
        }
    }
    else if (get<0>(token[i]) == "mdm" || get<0>(token[i]) == "pm" || get<0>(token[i]) == "ro" || get<0>(token[i]) == "and" || get<0>(token[i]) == "or" || get<0>(token[i]) == ";" || get<0>(token[i]) == ")" || get<0>(token[i]) == "]" || get<0>(token[i]) == "," || get<0>(token[i]) == "}")
    {
        return true;
    }
    return false;
}
bool Syntax::decl_left()
{
    if (get<0>(token[i]) == "(" || get<0>(token[i]) == "." || get<0>(token[i]) == "[")
    {
        if (get<0>(token[i]) == "(")
        {
            i++;
            if (args())
            {
                if (get<0>(token[i]) == ")")
                {
                    i++;
                    if (decl_right())
                    {
                        return true;
                    }
                }
            }
        }
        else if (list_size())
        {
            if (list_access())
            {
                return true;
            }
        }
        else if (decl_right())
        {
            return true;
        }
    }
    else if (get<0>(token[i]) == "mdm" || get<0>(token[i]) == "pm" || get<0>(token[i]) == "ro" || get<0>(token[i]) == "and" || get<0>(token[i]) == "or" || get<0>(token[i]) == ";" || get<0>(token[i]) == ")" || get<0>(token[i]) == "]" || get<0>(token[i]) == "," || get<0>(token[i]) == "}")
    {
        return true;
    }
    return false;
}
bool Syntax::value()
{
    if (get<0>(token[i]) == "int literal" || get<0>(token[i]) == "float literal" || get<0>(token[i]) == "char literal" || get<0>(token[i]) == "string literal" || get<0>(token[i]) == "bool literal")
    {
        i++;
        return true;
    }
    return false;
}

bool Syntax::list_access()
{
    if (get<0>(token[i]) == "." || get<0>(token[i]) == "=")
    {
        if (decl_right())
        {
            return true;
        }
        else if (get<0>(token[i]) == "=")
        {
            i++;
            if (expression())
            {
                return true;
            }
        }
    }
    else if (get<0>(token[i]) == "mdm" || get<0>(token[i]) == "pm" || get<0>(token[i]) == "ro" || get<0>(token[i]) == "and" || get<0>(token[i]) == "or" || get<0>(token[i]) == ";" || get<0>(token[i]) == ")" || get<0>(token[i]) == "]" || get<0>(token[i]) == "," || get<0>(token[i]) == "}")
    {
        return true;
    }
    return false;
}

bool Syntax::declare()
{
    if (get<0>(token[i]) == "DT")
    {
        i++;
        if (get<0>(token[i]) == "ID")
        {
            i++;
            if (init())
            {
                if (get<0>(token[i]) == ";")
                {
                    i++;
                    return true;
                }
            }
        }
    }
    return false;
}
bool Syntax::init()
{
    if (get<0>(token[i]) == "," || get<0>(token[i]) == "=")
    {
        if (get<0>(token[i]) == ",")
        {
            i++;
            if (get<0>(token[i]) == "ID")
            {
                i++;
                if (init())
                {
                    return true;
                }
            }
        }
        else if (get<0>(token[i]) == "=")
        {
            i++;
            if (expression())
            {
                if (init())
                {
                    return true;
                }
            }
        }
    }
    else if (get<0>(token[i]) == ";")
    {
        return true;
    }
    return false;
}

bool Syntax::conditional_st()
{
    if (get<0>(token[i]) == "if")
    {
        i++;
        if (get<0>(token[i]) == "(")
        {
            i++;
            if (expression())
            {
                if (get<0>(token[i]) == ")")
                {
                    i++;
                    if (body())
                    {
                        if (Else())
                        {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}
bool Syntax::Else()
{
    if (get<0>(token[i]) == "elif" || get<0>(token[i]) == "else")
    {
        if (get<0>(token[i]) == "elif")
        {
            i++;
            if (get<0>(token[i]) == "(")
            {
                i++;
                if (expression())
                {
                    if (get<0>(token[i]) == ")")
                    {
                        i++;
                        if (body())
                        {
                            if (Else())
                            {
                                return true;
                            }
                        }
                    }
                }
            }
        }
        else if (get<0>(token[i]) == "else")
        {
            i++;
            if (body())
            {
                return true;
            }
        }
    }
    else if (get<0>(token[i]) == "}")
    {
        return true;
    }
    return false;
}

bool Syntax::while_loop()
{
    if (get<0>(token[i]) == "while")
    {
        i++;
        if (get<0>(token[i]) == "(")
        {
            i++;
            if (expression())
            {
                if (get<0>(token[i]) == ")")
                {
                    i++;
                    if (body())
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool Syntax::for_loop()
{
    if (get<0>(token[i]) == "for")
    {
        i++;
        if (get<0>(token[i]) == "(")
        {
            i++;
            if (f1())
            {
                if (f2())
                {
                    if (get<0>(token[i]) == ";")
                    {
                        i++;
                        if (f3())
                        {
                            if (get<0>(token[i]) == ")")
                            {
                                i++;
                                if (body())
                                {
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}
bool Syntax::f1()
{
    if (get<0>(token[i]) == "DT" || get<0>(token[i]) == "ID")
    {
        if (declare())
        {
            return true;
        }
        else if (get<0>(token[i]) == "ID")
        {
            i++;
            if (declaration())
            {
                if (get<0>(token[i]) == ";")
                {
                    i++;
                    return true;
                }
            }
        }
    }
    else if (get<0>(token[i]) == ";" || get<0>(token[i]) == "int literal" || get<0>(token[i]) == "float literal" || get<0>(token[i]) == "char literal" || get<0>(token[i]) == "string literal" || get<0>(token[i]) == "bool literal" || get<0>(token[i]) == "ID")
    {
        return true;
    }
    return false;
}
bool Syntax::declaration()
{
    if (get<0>(token[i]) == "." || get<0>(token[i]) == "(" || get<0>(token[i]) == "=" || get<0>(token[i]) == "[" || get<0>(token[i]) == "ID")
    {
        if (object_decl())
        {
            return true;
        }
        else if (decl_left())
        {
            return true;
        }
        else if (get<0>(token[i]) == "=")
        {
            i++;
            if (expression())
            {
                return true;
            }
        }
    }
    else if (get<0>(token[i]) == ";")
    {
        return true;
    }
    return false;
}
bool Syntax::object_decl()
{
    if (get<0>(token[i]) == "ID")
    {
        i++;
        if (obj())
        {
            return true;
        }
    }
    return false;
}
bool Syntax::obj()
{
    if (get<0>(token[i]) == "(")
    {
        i++;
        if (parameter())
        {
            if (get<0>(token[i]) == ")")
            {
                i++;
                return true;
            }
        }
    }
    else if (get<0>(token[i]) == ";")
    {
        return true;
    }
    return false;
}
bool Syntax::parameter()
{
    if (get<0>(token[i]) == "DT" || get<0>(token[i]) == "ID")
    {
        if (type())
        {
            if (get<0>(token[i]) == "ID")
            {
                i++;
                if (para1())
                {
                    return true;
                }
            }
        }
    }
    else if (get<0>(token[i]) == ")")
    {
        return true;
    }
    return false;
}
bool Syntax::para1()
{
    if (get<0>(token[i]) == ",")
    {
        i++;
        if (parameter())
        {
            return true;
        }
    }
    else if (get<0>(token[i]) == ")")
    {
        return true;
    }
    return false;
}
bool Syntax::type()
{
    if (get<0>(token[i]) == "ID" || get<0>(token[i]) == "DT")
    {
        i++;
        return true;
    }
    return false;
}

bool Syntax::f2()
{
    cout<<"926"<<endl;
    if (get<0>(token[i]) == "int literal" || get<0>(token[i]) == "float literal" || get<0>(token[i]) == "char literal" || get<0>(token[i]) == "string literal" || get<0>(token[i]) == "bool literal" || get<0>(token[i]) == "ID" || get<0>(token[i]) == "(")
    {
        if (expression())
        {
            return true;
        }
    }
    else if (get<0>(token[i]) == ";")
    {
        return true;
    }
    return false;
}

bool Syntax::f3()
{
    if (get<0>(token[i]) == "ID")
    {
        i++;
        if (get<0>(token[i]) == "=")
        {
            i++;
            if (expression())
            {
                return true;
            }
        }
    }
    else if (get<0>(token[i]) == ")")
    {
        return true;
    }
    return false;
}

bool Syntax::function()
{
    if (get<0>(token[i]) == "def")
    {
        i++;
        if (func1())
        {
            return true;
        }
    }
    return false;
}
bool Syntax::func1()
{
    if (get<0>(token[i]) == "ID" || get<0>(token[i]) == "DT" || get<0>(token[i]) == "void")
    {
        if (get<0>(token[i]) == "ID")
        {
            i++;
            if (get<0>(token[i]) == "ID")
            {
                i++;
                if (get<0>(token[i]) == "(")
                {
                    i++;
                    if (parameter())
                    {
                        if (get<0>(token[i]) == ")")
                        {
                            i++;
                            if (body())
                            {
                                return true;
                            }
                        }
                    }
                }
            }
        }
        else if (get<0>(token[i]) == "DT")
        {
            i++;
            if (get<0>(token[i]) == "ID")
            {
                i++;
                if (get<0>(token[i]) == "(")
                {
                    i++;
                    if (parameter())
                    {
                        if (get<0>(token[i]) == ")")
                        {
                            i++;
                            if (body())
                            {
                                return true;
                            }
                        }
                    }
                }
            }
        }
        else if (get<0>(token[i]) == "void")
        {
            i++;
            if (get<0>(token[i]) == "ID")
            {
                i++;
                if (get<0>(token[i]) == "(")
                {
                    i++;
                    if (parameter())
                    {
                        if (get<0>(token[i]) == ")")
                        {
                            i++;
                            if (body())
                            {
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool Syntax::exception_handling()
{
    if (get<0>(token[i]) == "try")
    {
        i++;
        if (body())
        {
            if (get<0>(token[i]) == "catch")
            {
                i++;
                if (get<0>(token[i]) == "(")
                {
                    i++;
                    if (err())
                    {
                        if (get<0>(token[i]) == ")")
                        {
                            i++;
                            if (body())
                            {
                                if (get<0>(token[i]) == "finally")
                                {
                                    i++;
                                    if (body())
                                    {
                                        return true;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}
bool Syntax::err()
{
    return true;
}

bool Syntax::Return()
{
    if (get<0>(token[i]) == "return")
    {
        i++;
        if (Ret1())
        {
            return true;
        }
    }
    return false;
}
bool Syntax::Ret1()
{
    if (get<0>(token[i]) == "ID" || get<0>(token[i]) == "int literal" || get<0>(token[i]) == "float literal" || get<0>(token[i]) == "char literal" || get<0>(token[i]) == "string literal" || get<0>(token[i]) == "bool literal" || get<0>(token[i]) == "(")
    {
        if (expression())
        {
            return true;
        }
    }
    else if (get<0>(token[i]) == ";")
    {
        return true;
    }
    return false;
}

bool Syntax::list_decl()
{
    if (get<0>(token[i]) == "list")
    {
        i++;
        if (get<0>(token[i]) == "ID")
        {
            i++;
            if (list_size())
            {
                if (list_end())
                {
                    return true;
                }
            }
        }
    }
    return false;
}
bool Syntax::list_size()
{
    if (get<0>(token[i]) == "[")
    {
        i++;
        if (expression())
        {
            if (get<0>(token[i]) == "]")
            {
                i++;
                if (list_size1())
                {
                    return true;
                }
            }
        }
    }
    return false;
}
bool Syntax::list_size1()
{
    if (get<0>(token[i]) == "[")
    {
        if (list_size())
        {
            return true;
        }
    }
    else if (get<0>(token[i]) == "mdm" || get<0>(token[i]) == "pm" || get<0>(token[i]) == "ro" || get<0>(token[i]) == "and" || get<0>(token[i]) == "or" || get<0>(token[i]) == ";" || get<0>(token[i]) == ")" || get<0>(token[i]) == "]" || get<0>(token[i]) == "," || get<0>(token[i]) == "}" || get<0>(token[i]) == "=" || get<0>(token[i]) == ".")
    {
        return true;
    }
    return false;
}
bool Syntax::list_end()
{
    if (get<0>(token[i]) == ";" || get<0>(token[i]) == "=")
    {
        if (get<0>(token[i]) == ";")
        {
            i++;
            return true;
        }
        else if (get<0>(token[i]) == "=")
        {
            i++;
            if (a2())
            {
                if (get<0>(token[i]) == ";")
                {
                    i++;
                    return true;
                }
            }
        }
    }
    return false;
}
bool Syntax::a2()
{
    if (get<0>(token[i]) == "[")
    {
        i++;
        if (a3())
        {
            if (get<0>(token[i]) == "]")
            {
                i++;
                return true;
            }
        }
    }
    return false;
}
bool Syntax::a3()
{
    if (get<0>(token[i]) == "[" || get<0>(token[i]) == "ID" || get<0>(token[i]) == "int literal" || get<0>(token[i]) == "float literal" || get<0>(token[i]) == "char literal" || get<0>(token[i]) == "string literal" || get<0>(token[i]) == "bool literal" || get<0>(token[i]) == "(")
    {
        if (a2())
        {
            if (a4())
            {
                return true;
            }
        }
        else if (expression())
        {
            if (a4())
            {
                return true;
            }
        }
    }
    return false;
}
bool Syntax::a4()
{
    if (get<0>(token[i]) == ",")
    {
        i++;
        if (a3())
        {
            return true;
        }
    }
    else if (get<0>(token[i]) == "]")
    {
        return true;
    }
    return false;
}

bool Syntax::set_decl()
{
    if (get<0>(token[i]) == "set")
    {
        i++;
        if (type())
        {
            if (get<0>(token[i]) == "ID")
            {
                i++;
                if (get<0>(token[i]) == "[")
                {
                    i++;
                    if (expression())
                    {
                        if (get<0>(token[i]) == "]")
                        {
                            i++;
                            if (set_init())
                            {
                                if (get<0>(token[i]) == ";")
                                {
                                    i++;
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}
bool Syntax::set_init()
{
    if (get<0>(token[i]) == "=")
    {
        i++;
        if (get<0>(token[i]) == "{")
        {
            i++;
            if (expression())
            {
                if (set_next())
                {
                    if (get<0>(token[i]) == "}")
                    {
                        i++;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}
bool Syntax::set_next()
{
    if (get<0>(token[i]) == ",")
    {
        i++;
        if (expression())
        {
            if (set_next())
            {
                return true;
            }
        }
    }
    else if (get<0>(token[i]) == "}")
    {
        return true;
    }
    return false;
}

bool Syntax::flow_control()
{
    if (get<0>(token[i]) == "break" || get<0>(token[i]) == "continue")
    {
        i++;
        return true;
    }
    return false;
}

// class cfg's

bool Syntax::structure()
{
    if (get<0>(token[i]) == "class" || get<0>(token[i]) == "interface")
    {
        i++;
        return true;
    }
    return false;
}
bool Syntax::Class()
{
    if (get<0>(token[i]) == "class" || get<0>(token[i]) == "interface")
    {
        if (structure())
        {
            if (get<0>(token[i]) == "ID")
            {
                i++;
                if (inherit())
                {
                    if (access_modifier())
                    {
                        if (class_outer_body())
                        {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool Syntax::class_body()
{
    if (get<0>(token[i]) == "{")
    {
        i++;
        if (class_MST())
        {
            if (get<0>(token[i]) == "}")
            {
                i++;
                return true;
            }
        }
    }
    return false;
}
bool Syntax::class_MST()
{
    if (class_SST())
    {
        if (class_MST())
        {
            return true;
        }
    }
    else if (get<0>(token[i]) == "}")
    {
        return true;
    }
    return false;
}
bool Syntax::class_SST()
{
    if (get<0>(token[i]) == "DT" || get<0>(token[i]) == "if" || get<0>(token[i]) == "while" || get<0>(token[i]) == "for" || get<0>(token[i]) == "ID" || get<0>(token[i]) == "try" || get<0>(token[i]) == "return" || get<0>(token[i]) == "list" || get<0>(token[i]) == "set" || get<0>(token[i]) == "break" || get<0>(token[i]) == "continue" || get<0>(token[i]) == "this" || get<0>(token[i]) == "super")
    {
        if (class_declare())
        {
            return true;
        }
        else if (class_conditional_st())
        {
            return true;
        }
        else if (class_while())
        {
            return true;
        }
        else if (class_for_loop())
        {
            return true;
        }
        else if (get<0>(token[i]) == "ID")
        {
            i++;
            if (class_declaration())
            {
                if (get<0>(token[i]) == ";")
                {
                    i++;
                    return true;
                }
            }
        }
        else if (class_exception_handling())
        {
            return true;
        }
        else if (class_return())
        {
            if (get<0>(token[i]) == ";")
            {
                i++;
                return true;
            }
        }
        else if (class_list_decl())
        {
            return true;
        }
        else if (class_set_decl())
        {
            return true;
        }
        else if (flow_control())
        {
            if (get<0>(token[i]) == ";")
            {
                i++;
                return true;
            }
        }
        else if (super_this())
        {
            if (this_decl())
            {
                if (get<0>(token[i]) == ";")
                {
                    i++;
                    return true;
                }
            }
        }
    }
    return false;
}
bool Syntax::class_expression()
{
    if (get<0>(token[i]) == "ID" || get<0>(token[i]) == "int literal" || get<0>(token[i]) == "float literal" || get<0>(token[i]) == "char literal" || get<0>(token[i]) == "string literal" || get<0>(token[i]) == "bool literal" || get<0>(token[i]) == "(" || get<0>(token[i]) == "this" || get<0>(token[i]) == "super")
    {
        if (class_AND())
        {
            if (class_OR())
            {
                return true;
            }
        }
    }
    return false;
}
bool Syntax::class_AND()
{
    if (get<0>(token[i]) == "ID" || get<0>(token[i]) == "int literal" || get<0>(token[i]) == "float literal" || get<0>(token[i]) == "char literal" || get<0>(token[i]) == "string literal" || get<0>(token[i]) == "bool literal" || get<0>(token[i]) == "(" || get<0>(token[i]) == "this" || get<0>(token[i]) == "super")
    {
        if (class_RO())
        {
            if (class_AND1())
            {
                return true;
            }
        }
    }
    return false;
}
bool Syntax::class_OR()
{
    if (get<0>(token[i]) == "or")
    {
        i++;
        if (class_AND())
        {
            if (class_OR())
            {
                return true;
            }
        }
    }
    else if (get<0>(token[i]) == ";" || get<0>(token[i]) == ")" || get<0>(token[i]) == "]" || get<0>(token[i]) == "," || get<0>(token[i]) == "}")
    {
        return true;
    }
    return false;
}
bool Syntax::class_AND1()
{
    if (get<0>(token[i]) == "and")
    {
        i++;
        if (class_RO())
        {
            if (class_AND1())
            {
                return true;
            }
        }
    }
    else if (get<0>(token[i]) == "or" || get<0>(token[i]) == ";" || get<0>(token[i]) == ")" || get<0>(token[i]) == "]" || get<0>(token[i]) == "," || get<0>(token[i]) == "}")
    {
        return true;
    }
    return false;
}
bool Syntax::class_RO()
{
    if (get<0>(token[i]) == "ID" || get<0>(token[i]) == "int literal" || get<0>(token[i]) == "float literal" || get<0>(token[i]) == "char literal" || get<0>(token[i]) == "string literal" || get<0>(token[i]) == "bool literal" || get<0>(token[i]) == "(" || get<0>(token[i]) == "this" || get<0>(token[i]) == "super")
    {
        if (class_PM())
        {
            if (class_RO1())
            {
                return true;
            }
        }
    }
    return false;
}
bool Syntax::class_RO1()
{
    if (get<0>(token[i]) == "ro")
    {
        i++;
        if (class_PM())
        {
            if (class_RO1())
            {
                return true;
            }
        }
    }
    else if (get<0>(token[i]) == "and" || get<0>(token[i]) == "or" || get<0>(token[i]) == ";" || get<0>(token[i]) == ")" || get<0>(token[i]) == "]" || get<0>(token[i]) == "," || get<0>(token[i]) == "}")
    {
        return true;
    }
    return false;
}
bool Syntax::class_PM()
{
    if (get<0>(token[i]) == "ID" || get<0>(token[i]) == "int literal" || get<0>(token[i]) == "float literal" || get<0>(token[i]) == "char literal" || get<0>(token[i]) == "string literal" || get<0>(token[i]) == "bool literal" || get<0>(token[i]) == "(" || get<0>(token[i]) == "this" || get<0>(token[i]) == "super")
    {
        if (class_MDM())
        {
            if (class_PM1())
            {
                return true;
            }
        }
    }
    return false;
}
bool Syntax::class_PM1()
{
    if (get<0>(token[i]) == "pm")
    {
        i++;
        if (class_MDM())
        {
            if (class_PM1())
            {
                return true;
            }
        }
    }
    else if (get<0>(token[i]) == "ro" || get<0>(token[i]) == "and" || get<0>(token[i]) == "or" || get<0>(token[i]) == ";" || get<0>(token[i]) == ")" || get<0>(token[i]) == "]" || get<0>(token[i]) == "," || get<0>(token[i]) == "}")
    {
        return true;
    }
    return false;
}
bool Syntax::class_MDM()
{
    if (get<0>(token[i]) == "ID" || get<0>(token[i]) == "int literal" || get<0>(token[i]) == "float literal" || get<0>(token[i]) == "char literal" || get<0>(token[i]) == "string literal" || get<0>(token[i]) == "bool literal" || get<0>(token[i]) == "(" || get<0>(token[i]) == "this" || get<0>(token[i]) == "super")
    {
        if (class_end())
        {
            if (class_MDM1())
            {
                return true;
            }
        }
    }
    return false;
}
bool Syntax::class_MDM1()
{
    if (get<0>(token[i]) == "mdm")
    {
        i++;
        if (class_end())
        {
            if (class_MDM1())
            {
                return true;
            }
        }
    }
    else if (get<0>(token[i]) == "pm" || get<0>(token[i]) == "ro" || get<0>(token[i]) == "and" || get<0>(token[i]) == "or" || get<0>(token[i]) == ";" || get<0>(token[i]) == ")" || get<0>(token[i]) == "]" || get<0>(token[i]) == "," || get<0>(token[i]) == "}")
    {
        return true;
    }
    return false;
}
bool Syntax::class_end()
{
    if (get<0>(token[i]) == "ID" || get<0>(token[i]) == "int literal" || get<0>(token[i]) == "float literal" || get<0>(token[i]) == "char literal" || get<0>(token[i]) == "string literal" || get<0>(token[i]) == "bool literal" || get<0>(token[i]) == "(" || get<0>(token[i]) == "this" || get<0>(token[i]) == "super")
    {
        if (value())
        {
            return true;
        }
        else if (get<0>(token[i]) == "ID")
        {
            i++;
            if (class_exp_decl())
            {
                return true;
            }
        }
        else if (get<0>(token[i]) == "(")
        {
            i++;
            if (class_expression())
            {
                if (get<0>(token[i]) == ")")
                {
                    i++;
                    return true;
                }
            }
        }
        else if (super_this())
        {
            if (class_exp_decl())
            {
                return true;
            }
        }
    }
    return false;
}
bool Syntax::super_this()
{
    if (get<0>(token[i]) == "this" || get<0>(token[i]) == "super")
    {
        if (get<0>(token[i]) == "this")
        {
            i++;
            if (get<0>(token[i]) == ".")
            {
                i++;
                if (get<0>(token[i]) == "ID")
                {
                    i++;
                    return true;
                }
            }
        }
        if (get<0>(token[i]) == "super")
        {
            i++;
            if (get<0>(token[i]) == ".")
            {
                i++;
                if (get<0>(token[i]) == "ID")
                {
                    i++;
                    return true;
                }
            }
        }
    }
    return false;
}
bool Syntax::class_exp_decl()
{
    //( , null , [ , .
    if (get<0>(token[i]) == "(" || get<0>(token[i]) == "[" || get<0>(token[i]) == ".")
    {
        if (get<0>(token[i]) == "(")
        {
            i++;
            if (args())
            {
                if (get<0>(token[i]) == ")")
                {
                    i++;
                    if (class_decl_right())
                    {
                        return true;
                    }
                }
            }
        }
        else if (class_list_size())
        {
            if (class_decl_right())
            {
                return true;
            }
        }
        else if (class_decl_right())
        {
            return true;
        }
    }
    else if (get<0>(token[i]) == "mdm" || get<0>(token[i]) == "pm" || get<0>(token[i]) == "ro" || get<0>(token[i]) == "and" || get<0>(token[i]) == "or" || get<0>(token[i]) == ";" || get<0>(token[i]) == ")" || get<0>(token[i]) == "]" || get<0>(token[i]) == "," || get<0>(token[i]) == "}")
    {
        return true;
    }
    return false;
}
bool Syntax::class_decl_right()
{
    if (get<0>(token[i]) == ".")
    {
        i++;
        if (get<0>(token[i]) == "ID")
        {
            i++;
            if (class_decl_left())
            {
                return true;
            }
        }
    }
    else if (get<0>(token[i]) == "mdm" || get<0>(token[i]) == "pm" || get<0>(token[i]) == "ro" || get<0>(token[i]) == "and" || get<0>(token[i]) == "or" || get<0>(token[i]) == ";" || get<0>(token[i]) == ")" || get<0>(token[i]) == "]" || get<0>(token[i]) == "," || get<0>(token[i]) == "}")
    {
        return true;
    }
    return false;
}
bool Syntax::class_decl_left()
{
    if (get<0>(token[i]) == "(" || get<0>(token[i]) == "." || get<0>(token[i]) == "[")
    {
        if (get<0>(token[i]) == "(")
        {
            i++;
            if (class_args())
            {
                if (get<0>(token[i]) == ")")
                {
                    i++;
                    if (class_decl_right())
                    {
                        return true;
                    }
                }
            }
        }
        else if (class_list_size())
        {
            if (class_list_access())
            {
                return true;
            }
        }
        else if (class_decl_right())
        {
            return true;
        }
    }
    else if (get<0>(token[i]) == "mdm" || get<0>(token[i]) == "pm" || get<0>(token[i]) == "ro" || get<0>(token[i]) == "and" || get<0>(token[i]) == "or" || get<0>(token[i]) == ";" || get<0>(token[i]) == ")" || get<0>(token[i]) == "]" || get<0>(token[i]) == "," || get<0>(token[i]) == "}")
    {
        return true;
    }
    return false;
}
bool Syntax::class_args()
{
    if (get<0>(token[i]) == "ID" || get<0>(token[i]) == "int literal" || get<0>(token[i]) == "float literal" || get<0>(token[i]) == "char literal" || get<0>(token[i]) == "string literal" || get<0>(token[i]) == "bool literal" || get<0>(token[i]) == "(")
    {
        if (class_expression())
        {
            if (class_args_next())
            {
                return true;
            }
        }
    }
    else if (get<0>(token[i]) == ")")
    {
        return true;
    }
    return false;
}
bool Syntax::class_args_next()
{
    if (get<0>(token[i]) == ",")
    {
        i++;
        if (class_args())
        {
            return true;
        }
    }
    else if (get<0>(token[i]) == ")")
    {
        return true;
    }
    return false;
}
bool Syntax::class_list_size()
{
    if (get<0>(token[i]) == "[")
    {
        i++;
        if (class_expression())
        {
            if (get<0>(token[i]) == "]")
            {
                i++;
                if (class_list_size1())
                {
                    return true;
                }
            }
        }
    }
    return false;
}
bool Syntax::class_list_size1()
{
    if (get<0>(token[i]) == "[")
    {
        if (class_list_size())
        {
            return true;
        }
    }
    else if (get<0>(token[i]) == "mdm" || get<0>(token[i]) == "pm" || get<0>(token[i]) == "ro" || get<0>(token[i]) == "and" || get<0>(token[i]) == "or" || get<0>(token[i]) == ";" || get<0>(token[i]) == ")" || get<0>(token[i]) == "]" || get<0>(token[i]) == "," || get<0>(token[i]) == "}" || get<0>(token[i]) == "=" || get<0>(token[i]) == ".")
    {
        return true;
    }
    return false;
}
bool Syntax::class_list_access()
{
    if (get<0>(token[i]) == "." || get<0>(token[i]) == "=")
    {
        if (class_decl_right())
        {
            return true;
        }
        else if (get<0>(token[i]) == "=")
        {
            i++;
            if (class_expression())
            {
                return true;
            }
        }
        return false;
    }
    else if (get<0>(token[i]) == "mdm" || get<0>(token[i]) == "pm" || get<0>(token[i]) == "ro" || get<0>(token[i]) == "and" || get<0>(token[i]) == "or" || get<0>(token[i]) == ";" || get<0>(token[i]) == ")" || get<0>(token[i]) == "]" || get<0>(token[i]) == "," || get<0>(token[i]) == "}")
    {
        return true;
    }
    return false;
}
bool Syntax::inherit()
{
    if (get<0>(token[i]) == "from")
    {
        i++;
        if (get<0>(token[i]) == "ID")
        {
            i++;
            if (inherit())
            {
                return true;
            }
        }
    }
    else if (get<0>(token[i]) == "access-modifier" || get<0>(token[i]) == "{")
    {
        return true;
    }
    return false;
}
bool Syntax::access_modifier()
{
    if (get<0>(token[i]) == "access-modifier")
    {
        i++;
        if (get<0>(token[i]) == ":")
        {
            i++;
            return true;
        }
    }
    else if (get<0>(token[i]) == "def" || get<0>(token[i]) == "DT" || get<0>(token[i]) == "ID" || get<0>(token[i]) == "constructor" || get<0>(token[i]) == "{" || get<0>(token[i]) == "list" || get<0>(token[i]) == "set")
    {
        return true;
    }
    return false;
}
bool Syntax::class_outer_body()
{
    if (get<0>(token[i]) == "{")
    {
        i++;
        if (class_outer_MST())
        {
            if (get<0>(token[i]) == "}")
            {
                i++;
                return true;
            }
        }
    }
    return false;
}
bool Syntax::class_outer_MST()
{
    if (get<0>(token[i]) == "access-modifier" || get<0>(token[i]) == "def" || get<0>(token[i]) == "DT" || get<0>(token[i]) == "ID" || get<0>(token[i]) == "constructor" || get<0>(token[i]) == "list" || get<0>(token[i]) == "set")
    {
        if (access_modifier())
        {
            if (class_outer_SST())
            {
                if (class_outer_MST())
                {
                    return true;
                }
            }
        }
    }
    else if (get<0>(token[i]) == "}")
    {
        return true;
    }
    return false;
}
bool Syntax::class_outer_SST()
{
    if (get<0>(token[i]) == "def" || get<0>(token[i]) == "DT" || get<0>(token[i]) == "ID" || get<0>(token[i]) == "constructor" || get<0>(token[i]) == "list" || get<0>(token[i]) == "set")
    {
        if (class_function())
        {
            return true;
        }
        else if (class_declare())
        {
            return true;
        }
        else if (get<0>(token[i]) == "ID")
        {
            i++;
            if (object_decl())
            {
                if (get<0>(token[i]) == ";")
                {
                    i++;
                    return true;
                }
            }
        }
        else if (class_constructor())
        {
            return true;
        }
        else if (class_list_decl())
        {
            return true;
        }
        else if (class_set_decl())
        {
            return true;
        }
    }
    return false;
}
bool Syntax::class_declare()
{
    if (get<0>(token[i]) == "DT")
    {
        i++;
        if (get<0>(token[i]) == "ID")
        {
            i++;
            if (class_init())
            {
                if (get<0>(token[i]) == ";")
                {
                    i++;
                    return true;
                }
            }
        }
    }
    return false;
}
bool Syntax::class_init()
{
    if (get<0>(token[i]) == "," || get<0>(token[i]) == "=")
    {
        if (get<0>(token[i]) == ",")
        {
            i++;
            if (get<0>(token[i]) == "ID")
            {
                i++;
                if (class_init())
                {
                    return true;
                }
            }
        }
        else if (get<0>(token[i]) == "=")
        {
            i++;
            if (class_expression())
            {
                if (class_init())
                {
                    return true;
                }
            }
        }
    }
    else if (get<0>(token[i]) == ";")
    {
        return true;
    }
    return false;
}

bool Syntax::fn()
{
    if (get<0>(token[i]) == "static")
    {
        i++;
        return true;
    }
    else if (get<0>(token[i]) == "DT" || get<0>(token[i]) == "ID" || get<0>(token[i]) == "void")
    {
        return true;
    }
    return false;
}
bool Syntax::class_function()
{
    if (get<0>(token[i]) == "def")
    {
        i++;
        if (fn())
        {
            if (class_func1())
            {
                return true;
            }
        }
    }
    return false;
}
bool Syntax::class_func1()
{
    if (get<0>(token[i]) == "ID" || get<0>(token[i]) == "DT" || get<0>(token[i]) == "void")
    {
        if (get<0>(token[i]) == "ID")
        {
            i++;
            if (a())
            {
                if (get<0>(token[i]) == "(")
                {
                    i++;
                    if (parameter())
                    {
                        if (get<0>(token[i]) == ")")
                        {
                            i++;
                            if (class_body())
                            {
                                return true;
                            }
                        }
                    }
                }
            }
        }
        else if (get<0>(token[i]) == "DT")
        {
            i++;
            if (a())
            {
                if (get<0>(token[i]) == "(")
                {
                    i++;
                    if (parameter())
                    {
                        if (get<0>(token[i]) == ")")
                        {
                            i++;
                            if (class_body())
                            {
                                return true;
                            }
                        }
                    }
                }
            }
        }
        else if (get<0>(token[i]) == "void")
        {
            i++;
            if (a())
            {
                if (get<0>(token[i]) == "(")
                {
                    i++;
                    if (parameter())
                    {
                        if (get<0>(token[i]) == ")")
                        {
                            i++;
                            if (class_body())
                            {
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}
bool Syntax::a()
{
    if (get<0>(token[i]) == "ID" || get<0>(token[i]) == "operator")
    {
        if (get<0>(token[i]) == "ID")
        {
            i++;
            return true;
        }
        else if (get<0>(token[i]) == "operator")
        {
            i++;
            if (op())
            {
                return true;
            }
        }
    }
    return false;
}
bool Syntax::op()
{
    if (get<0>(token[i]) == "pm" || get<0>(token[i]) == "ro" || get<0>(token[i]) == "mdm" || get<0>(token[i]) == "and" || get<0>(token[i]) == "or")
    {
        i++;
        return true;
    }
    return false;
}

bool Syntax::class_constructor()
{
    if (get<0>(token[i]) == "constructor")
    {
        i++;
        if (get<0>(token[i]) == "ID")
        {
            i++;
            if (get<0>(token[i]) == "(")
            {
                i++;
                if (parameter())
                {
                    if (get<0>(token[i]) == ")")
                    {
                        i++;
                        if (class_body())
                        {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool Syntax::class_conditional_st()
{
    if (get<0>(token[i]) == "if")
    {
        i++;
        if (get<0>(token[i]) == "(")
        {
            i++;
            if (class_expression())
            {
                if (get<0>(token[i]) == ")")
                {
                    i++;
                    if (class_body())
                    {
                        if (class_else())
                        {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}
bool Syntax::class_else()
{
    if (get<0>(token[i]) == "elif" || get<0>(token[i]) == "else")
    {
        if (get<0>(token[i]) == "elif")
        {
            i++;
            if (get<0>(token[i]) == "(")
            {
                i++;
                if (class_expression())
                {
                    if (get<0>(token[i]) == ")")
                    {
                        i++;
                        if (class_body())
                        {
                            if (class_else())
                            {
                                return true;
                            }
                        }
                    }
                }
            }
        }
        else if (get<0>(token[i]) == "else")
        {
            i++;
            if (class_body())
            {
                return true;
            }
        }
    }
    else if (get<0>(token[i]) == "}")
    {
        return true;
    }
    return false;
}

bool Syntax::class_while()
{
    if (get<0>(token[i]) == "while")
    {
        i++;
        if (get<0>(token[i]) == "(")
        {
            i++;
            if (class_expression())
            {
                if (get<0>(token[i]) == ")")
                {
                    i++;
                    if (class_body())
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool Syntax::class_for_loop()
{
    if (get<0>(token[i]) == "for")
    {
        i++;
        if (get<0>(token[i]) == "(")
        {
            i++;
            if (class_f1())
            {
                if (class_f2())
                {
                    if (get<0>(token[i]) == ";")
                    {
                        i++;
                        if (class_f3())
                        {
                            if (get<0>(token[i]) == ")")
                            {
                                i++;
                                if (class_body())
                                {
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}
bool Syntax::class_f1()
{
    if (get<0>(token[i]) == "DT" || get<0>(token[i]) == "ID")
    {
        if (class_declare())
        {
            return true;
        }
        else if (get<0>(token[i]) == "ID")
        {
            i++;
            if (class_declaration())
            {
                if (get<0>(token[i]) == ";")
                {
                    i++;
                    return true;
                }
            }
        }
    }
    else if (get<0>(token[i]) == ";" || get<0>(token[i]) == "int literal" || get<0>(token[i]) == "float literal" || get<0>(token[i]) == "char literal" || get<0>(token[i]) == "string literal" || get<0>(token[i]) == "bool literal" || get<0>(token[i]) == "ID")
    {
        return true;
    }
    return false;
}
bool Syntax::class_declaration()
{
    if (get<0>(token[i]) == "." || get<0>(token[i]) == "(" || get<0>(token[i]) == "=" || get<0>(token[i]) == "[" || get<0>(token[i]) == "ID")
    {
        if (object_decl())
        {
            return true;
        }
        else if (class_decl_left())
        {
            return true;
        }
        else if (get<0>(token[i]) == "=")
        {
            i++;
            if (class_expression())
            {
                return true;
            }
        }
    }
    else if (get<0>(token[i]) == ";")
    {
        return true;
    }
    return false;
}
bool Syntax::this_decl()
{
    if (get<0>(token[i]) == "." || get<0>(token[i]) == "(" || get<0>(token[i]) == "=" || get<0>(token[i]) == "[")
    {
        if (class_decl_left())
        {
            return true;
        }
        else if (get<0>(token[i]) == "=")
        {
            i++;
            if (class_expression())
            {
                return true;
            }
        }
    }
    else if (get<0>(token[i]) == ";")
    {
        return true;
    }
    return false;
}

bool Syntax::class_f2()
{
    if (get<0>(token[i]) == "int literal" || get<0>(token[i]) == "float literal" || get<0>(token[i]) == "char literal" || get<0>(token[i]) == "string literal" || get<0>(token[i]) == "bool literal" || get<0>(token[i]) == "ID" || get<0>(token[i]) == "(")
    {
        if (class_expression())
        {
            return true;
        }
    }
    else if (get<0>(token[i]) == ";")
    {
        return true;
    }
    return false;
}
bool Syntax::class_f3()
{
    if (get<0>(token[i]) == "ID")
    {
        i++;
        if (get<0>(token[i]) == "=")
        {
            i++;
            if (class_expression())
            {
                return true;
            }
        }
    }
    else if (get<0>(token[i]) == ")")
    {
        return true;
    }
    return false;
}

bool Syntax::class_list_decl()
{
    if (get<0>(token[i]) == "list")
    {
        i++;
        if (get<0>(token[i]) == "ID")
        {
            i++;
            if (class_list_size())
            {
                if (class_list_end())
                {
                    return true;
                }
            }
        }
    }
    return false;
}
bool Syntax::class_list_end()
{
    if (get<0>(token[i]) == ";" || get<0>(token[i]) == "=")
    {
        if (get<0>(token[i]) == ";")
        {
            i++;
            return true;
        }
        else if (get<0>(token[i]) == "=")
        {
            i++;
            if (class_a2())
            {
                if (get<0>(token[i]) == ";")
                {
                    i++;
                    return true;
                }
            }
        }
    }
    return false;
}

bool Syntax::class_set_decl()
{
    if (get<0>(token[i]) == "set")
    {
        i++;
        if (type())
        {
            if (get<0>(token[i]) == "ID")
            {
                i++;
                if (get<0>(token[i]) == "[")
                {
                    i++;
                    if (class_expression())
                    {
                        if (get<0>(token[i]) == "]")
                        {
                            i++;
                            if (class_set_init())
                            {
                                if (get<0>(token[i]) == ";")
                                {
                                    i++;
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}
bool Syntax::class_set_init()
{
    if (get<0>(token[i]) == "=")
    {
        i++;
        if (get<0>(token[i]) == "{")
        {
            i++;
            if (class_expression())
            {
                if (class_set_next())
                {
                    if (get<0>(token[i]) == "}")
                    {
                        i++;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}
bool Syntax::class_set_next()
{
    if (get<0>(token[i]) == ",")
    {
        i++;
        if (class_expression())
        {
            if (class_set_next())
            {
                return true;
            }
        }
    }
    else if (get<0>(token[i]) == "}")
    {
        return true;
    }
    return false;
}

bool Syntax::class_a2()
{
    if (get<0>(token[i]) == "[")
    {
        i++;
        if (class_a3())
        {
            if (get<0>(token[i]) == "]")
            {
                i++;
                return true;
            }
        }
    }
    return false;
}
bool Syntax::class_a3()
{
    if (get<0>(token[i]) == "[" || get<0>(token[i]) == "ID" || get<0>(token[i]) == "int literal" || get<0>(token[i]) == "float literal" || get<0>(token[i]) == "char literal" || get<0>(token[i]) == "string literal" || get<0>(token[i]) == "bool literal" || get<0>(token[i]) == "(")
    {
        if (class_a2())
        {
            if (class_a4())
            {
                return true;
            }
        }
        else if (class_expression())
        {
            if (class_a4())
            {
                return true;
            }
        }
    }
    return false;
}
bool Syntax::class_a4()
{
    if (get<0>(token[i]) == ",")
    {
        i++;
        if (class_a3())
        {
            return true;
        }
    }
    else if (get<0>(token[i]) == "]")
    {
        return true;
    }
    return false;
}

bool Syntax::class_return()
{
    if (get<0>(token[i]) == "return")
    {
        i++;
        if (class_ret1())
        {
            return true;
        }
    }
    return false;
}
bool Syntax::class_ret1()
{
    if (get<0>(token[i]) == "ID" || get<0>(token[i]) == "int literal" || get<0>(token[i]) == "float literal" || get<0>(token[i]) == "char literal" || get<0>(token[i]) == "string literal" || get<0>(token[i]) == "bool literal" || get<0>(token[i]) == "(")
    {
        if (class_expression())
        {
            return true;
        }
    }
    else if (get<0>(token[i]) == ";")
    {
        return true;
    }
    return false;
}

bool Syntax::class_exception_handling()
{
    if (get<0>(token[i]) == "try")
    {
        i++;
        if (class_body())
        {
            if (get<0>(token[i]) == "catch")
            {
                i++;
                if (get<0>(token[i]) == "(")
                {
                    i++;
                    if (err())
                    {
                        if (get<0>(token[i]) == ")")
                        {
                            i++;
                            if (class_body())
                            {
                                if (get<0>(token[i]) == "finally")
                                {
                                    i++;
                                    if (class_body())
                                    {
                                        return true;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

void Syntax::createScope(){
    scope++;
    currentScope = scope;
    stack.push_back(scope);
}
void Syntax::destroyScope(){
    stack.pop_back();
    currentScope = stack.back();
}

string Syntax::lookUp_ST(string name){
    for (int i = 0; i < scopeTable.size(); i++)
    {
        if(name == scopeTable[i].name && currentScope == scopeTable[i].scope){
            return scopeTable[i].type;
        }
    }
    return "cannot find";
}
defTableInstance Syntax::lookUp_DT(string name){
    for (int i = 0; i < defTable.size(); i++)
    {
        if(name == defTable[i].name){
            CCN = name;
            return defTable[i];
        } 
    }
    defTableInstance temp;
    temp.name = "null";
    return temp;
}
memberTableInstance Syntax::lookUp_MT(string name,string class_name){
    CCN = class_name;
    CCR = lookUp_DT(CCN);
    if(CCR.name != "null"){
        for (int i = 0; i < CCR.memberTable.size(); i++)
        {
            if(CCR.memberTable[i].name == name){
                return CCR.memberTable[i];
            }
        }        
    }
}