import sys


SCOPE_TABLE = []
DEFINITION_TABLE = []
MEMBER_TABLES = {}
CURRENT_SCOPE = 0
SCOPE = 0
STACK = [CURRENT_SCOPE]
CR_STACK = ["-1"]
AM_STACK = []
CR = None
CCR = None
AM = None
TM = None


def enterClass(Name):
    global CR_STACK, CR, AM, AM_STACK

    if AM_STACK:
        AM_STACK.insert(0, AM)
    else:
        AM_STACK.insert(0, "-2")


    AM = "public"
    CR_STACK.insert(0, Name)
    CR = Name
    # print(f"Entered in class {Name}")


def leaveClass():
    global CR_STACK, CR, AM, AM_STACK

    # print(f"Leaving Class {CR}")

    CR_STACK.pop(0)
    CR = CR_STACK[0]

    AM = AM_STACK[0]
    AM_STACK.pop(0)

    # print(f"Now in Class {CR}")
    # print()


def getCurrentScope():
    global CURRENT_SCOPE
    return CURRENT_SCOPE


def getCR():
    global CR
    return CR

def getCCR():
    global CCR
    return CCR

def getAM():
    global AM
    return AM

def getTM():
    global TM
    return TM

def setTM(tm):
    global TM
    TM = tm

def setAM(am):
    global AM
    AM = am

def setCR(cr):
    global CR
    CR = cr

def setCCR(ccr):
    global CCR
    CCR = ccr



def isNotPremitive(Type):
    if Type in ["int", "float", "bool", "char", "str", "Int_Const", "Float_Const", "Bool_Const", "Char_Const", "Str_Const"]:
        return False

    return True




def createScope():
    """
    The function creates a new scope and updates the global variables STACK, SCOPE, and CURRENT_SCOPE.
    """
    global STACK, SCOPE, CURRENT_SCOPE

    SCOPE += 1
    CURRENT_SCOPE = SCOPE

    STACK.insert(0, SCOPE)



def destroyScope():
    """
    The function `destroyScope` removes the current scope from the stack and updates the current scope
    to the next scope in the stack.
    """
    global STACK, SCOPE, CURRENT_SCOPE

    STACK.pop(0)
    CURRENT_SCOPE = STACK[0]





def allScopeValue(Scope):
    """
    The function `allScopeValue` returns a list of items from the `SCOPE_TABLE` where the third element
    matches the given `Scope` parameter.
    
    :param Scope: The parameter "Scope" is a value that represents a specific scope in a program
    :return: a list of items from the SCOPE_TABLE where the third element of each item is equal to the
    input parameter "Scope".
    """
    global SCOPE_TABLE

    return [item for item in SCOPE_TABLE if item[2] == Scope]

def insertST(Name, Type, Scope):
    """
    The function `insertST` inserts a new entry into the `SCOPE_TABLE` if the name is not already
    defined in the given scope.
    
    :param Name: The Name parameter represents the name of the variable or symbol being inserted into
    the scope table
    :param Type: The "Type" parameter represents the data type of the variable or symbol being inserted
    into the scope table
    :param Scope: The "Scope" parameter represents the scope in which the variable or symbol is defined.
    It could be a function, a class, or any other block of code that defines a scope
    :return: a boolean value. It returns True if the insertion of the variable into the scope table is
    successful, and False otherwise.
    """

    global SCOPE_TABLE

    scope_rows = allScopeValue(Scope)
    flag = any(row[0] == Name for row in scope_rows)
    
    if flag:
        e =  f"RedeclarationError: '{Name}' is already defined."
        sys.exit(e)
        return False

    if '->' not in Type:

        T = (Type.split("[]"))[0]
        flag = isNotPremitive(T)
        if flag:
            row = lookupDT(Name=T)
            if row:
                if row[2] != "None":
                    e =  f"Error: can't declare object(s) of Abstract class '{T}'."
                    sys.exit(e)

            else:
                e =  f"UndeclearedError: Name '{T}' is not defined."
                sys.exit(e)

        




    SCOPE_TABLE.append((Name, Type, Scope))
    return True



def insertDT(Name, Type, Parent="None", TypeModifier="None"):
    """
    The function `insertDT` inserts a new entry into the definition table and creates an empty member
    table for the given name, type, parent, and type modifier.
    
    :param Name: The name of the variable or data type being inserted into the definition table
    :param Type: The "Type" parameter represents the data type of the variable or object being defined
    :param Parent: The "Parent" parameter is used to specify the parent of the current definition. It is
    an optional parameter and its default value is set to "None", defaults to None (optional)
    :param TypeModifier: The TypeModifier parameter is an optional parameter that specifies any
    additional information or modifications to the data type. It is set to "None" by default, meaning
    that if no TypeModifier is provided, it will be assumed to have no modifications, defaults to None
    (optional)
    :return: a boolean value. It returns True if the insertion is successful and False otherwise.
    """

    global DEFINITION_TABLE, MEMBER_TABLES

    if lookupDT(Name):
        e =  f"RedeclarationError: '{Name}' is already defined."
        sys.exit(e)
        return False

    DEFINITION_TABLE.append([Name, Type, Parent, TypeModifier])
    MEMBER_TABLES[Name] = []

    return True

    

def insertMT(Name, Type, Reference, AccessModifier="public", TypeModifier="None"):
    """
    The function `insertMT` inserts a new member into a member table with the specified name, type,
    reference, access modifier, and type modifier.
    
    :param Name: The name of the member being inserted
    :param Type: The "Type" parameter represents the data type of the member being inserted into the
    member table
    :param Reference: The "Reference" parameter refers to the location or context in which the member is
    being defined. It could be the name of a class, module, or any other entity that contains the member
    :param AccessModifier: The AccessModifier parameter is used to specify the access level of the
    member being inserted. It has a default value of "public", which means the member can be accessed
    from anywhere. Other possible values for AccessModifier could be "private" (the member can only be
    accessed within the same class), ", defaults to public (optional)
    :param TypeModifier: The TypeModifier parameter is an optional parameter that specifies any
    additional modifiers or attributes associated with the data type of the member being inserted. It
    can be used to provide more specific information about the type, such as whether it is nullable,
    constant, or any other relevant modifier, defaults to None (optional)
    :return: a boolean value. It returns True if the insertion of the member table is successful, and
    False otherwise.
    """

    global MEMBER_TABLES
    

    t, a, tm = lookupMT(Name, Reference)
    if t:
        e =  f"RedeclarationError: '{Name}' is already defined in {Reference}."
        sys.exit(e)
        return False

    MEMBER_TABLES[Reference].append((Name, Type, AccessModifier, TypeModifier))
    return True







def lookupST(Name):
    """
    The function `lookupST` searches for a variable name in the stack of scopes and returns its
    corresponding type if found, otherwise it returns False.
    
    :param Name: The Name parameter is the name of the variable or symbol that you want to look up in
    the symbol table
    :return: the type of the variable with the given name if it is found in any of the scopes in the
    STACK. If the variable is not found, it returns False.
    """
    global STACK

    for Scope in STACK:
        data = allScopeValue(Scope)
        matching_rows = [row for row in data if row[0] == Name]

        if matching_rows:
            return matching_rows[0][1]   # Return Type

    return False



def lookupDT(Name):
    """
    The function `lookupDT` searches for a name in the `DEFINITION_TABLE` and returns a tuple of values
    if found, otherwise it returns False.
    
    :param Name: The Name parameter is the name of the item you want to look up in the DEFINITION_TABLE
    :return: a tuple containing the values from the second, third, and fourth columns of the row in the
    DEFINITION_TABLE where the Name matches the value in the first column. If no match is found, it
    returns False.
    """
    global DEFINITION_TABLE

    for row in DEFINITION_TABLE:
        if (Name==row[0]):
            r = (row[1], row[2], row[3])
            return r

    return False



def lookupMT(Name, Reference):
    """
    The function `lookupMT` takes a name and a reference as input and returns a tuple of values from a
    member table if the name is found in the table, otherwise it returns False.
    
    :param Name: The Name parameter is the name of the member you want to look up in the member table
    :param Reference: The "Reference" parameter is used to specify which member table to look up in. It
    is a key that is used to retrieve the member table from the global variable "MEMBER_TABLES"
    :return: a tuple containing the values of row[1], row[2], and row[3] if a match is found in the
    MemberTable. If no match is found, it returns False.
    """
    global MEMBER_TABLES

    MemberTable = MEMBER_TABLES.get(Reference, False)

    if MemberTable:
        for row in MemberTable:
            if (row[0]==Name):
                t = (row[1], row[2], row[3])
                return t

        return False, False, False


    return False, False, False



def conversion(ParameterList):
    param = ParameterList.split(",")
    p = ""
    for j, i in enumerate(param):

        if i=="Int_Const":
            p += "int"

        elif i=="Float_Const":
            p += "float"

        elif i=="Str_Const":
            p += "str"

        elif i=="Char_Const":
            p += "char"

        elif i=="Bool_Const":
            p += "bool"

        else:
            p += i

        if j != len(param)-1:
            p += ","

    return p
            


def lookupFuncST(Name, ParameterList):
    """
    The function `lookupFuncST` searches for a function name in the stack of scopes and returns its type
    if found.
    
    :param Name: The Name parameter is the name of the function you want to look up
    :param ParameterList: The `ParameterList` is a string that represents the list of parameters for a
    function. It is used to match the function name and its parameter list with the given `Name` and
    `ParameterList` arguments in the `lookupFuncST` function
    :return: the type of the function if it matches the given name and parameter list. If there is no
    match, it returns False.
    """

    ParameterList = conversion(ParameterList)

    global STACK

    for Scope in STACK:

        data = allScopeValue(Scope)
        matching_rows = [row for row in data if row[0] == Name]

        if matching_rows:
            matching_row = matching_rows[0]

            if '->' in matching_row[1]:

                PList, Type = matching_row[1].split("->")
                
                if PList==ParameterList:
                    return Type

                else:
                    e = f"TypeError: ArgumentList does not match ParameterList for function '{Name}({PList})'"
                    sys.exit(e)



            e = f"Error: {Name} is not a function."
            sys.exit(e)

    e = f"NameError: Function '{Name}' is not declared."
    sys.exit(e)

    return False


def changeTM(Name):
    global DEFINITION_TABLE

    for y in range(len(DEFINITION_TABLE)):
        if (Name==DEFINITION_TABLE[y][0]):
            DEFINITION_TABLE[y][3] = "abstract"
            return True

    return False



def lookupFuncMT(Name, ParameterList, Reference):
    """
    The function `lookupFuncMT` searches for a matching row in a member table based on the given name
    and reference, and returns the type if found.
    
    :param Name: The Name parameter is the name of the function you want to look up in the MemberTable
    :param ParameterList: The ParameterList parameter is a string that represents a list of parameters.
    It is used to specify the types and names of the parameters that a function takes
    :param Reference: The "Reference" parameter is used to specify the reference to the member table. It
    is used to look up the member table in the global variable "MEMBER_TABLES"
    :return: The code is returning the value of the variable "Type".
    """
    global MEMBER_TABLES

    ParameterList = conversion(ParameterList)

    MemberTable = MEMBER_TABLES.get(Reference, False)

    if MemberTable:
        
        matching_rows = [row for row in MemberTable if row[0] == Name]

        if matching_rows:
            matching_row = matching_rows[0]

            if '->' in matching_row[1]:

                PList, Type = matching_row[1].split("->")
                
                if PList==ParameterList:
                    r = (Type, matching_row[2], matching_row[3])
                    return r


    return False, False, False
    






dt_INT = ["int", "Int_Const"]
dt_FLT = ["float", "Float_Const"]
dt_STR = ["str", "Str_Const" ]
dt_BOOl = ["bool", "Bool_Const"]
dt_CHAR = ["char", "Char_Const"]
                
def compatibiltyCheck(LeftOp, RightOp, Operator):
    """
    The function `compatibilityCheck` checks the compatibility of two operands and an operator and
    returns the corresponding data type if they are compatible, otherwise it returns False.
    
    :param LeftOp: The LeftOp parameter represents the left operand of the operation being checked for
    compatibility
    :param RightOp: The RightOp parameter represents the right operand in a binary operation. It can be
    any data type, such as integer, float, string, character, or boolean
    :param Operator: The "Operator" parameter represents the operator being used in the compatibility
    check. It can be one of the following operators: '+', '-', '*', '/', '%', '^', '>', '<', '<=', '>=',
    '!=', '=='
    :return: the compatibility check result, which can be one of the following:
    - 'Int_Const': if both operands are integers and the operator is compatible with integers
    - 'Bool_Const': if both operands are integers and the operator is compatible with booleans
    - 'Float_Const': if both operands are floats and the operator is compatible with floats
    - 'Str_Const':
    """
    
    
    if (LeftOp in dt_INT ) and (RightOp in dt_INT) and Operator in ['+','-','*','/','%', '^']:
        return 'Int_Const'
    

    elif (LeftOp in dt_INT) and (RightOp in dt_INT) and Operator in ['>','<','<=','>=','!=','==']:
        return 'Bool_Const'
    

    elif (LeftOp in dt_FLT) and (RightOp in dt_FLT) and Operator in ['+','-','*','/','%','^']:
        return 'Float_Const'
    

    elif (LeftOp in dt_FLT) and (RightOp in dt_FLT) and Operator in ['>','<','<=','>=','!=','==']:
        return 'Bool_Const'


    elif (LeftOp in dt_FLT) and (RightOp in dt_INT) and Operator in ['+','-','*','/','%','^']:
        return 'Float_Const'


    elif (LeftOp in dt_FLT) and (RightOp in dt_INT) and Operator in ['>','<','<=','>=','!=','==']:
        return 'Bool_Const'


    elif (LeftOp in dt_INT) and (RightOp in dt_FLT) and Operator in ['+','-','*','/','%','^']:
        return 'Float_Const'


    elif (LeftOp in dt_INT) and (RightOp in dt_FLT) and Operator in ['>','<','<=','>=','!=','==']:
        return 'Bool_Const'
    

    elif (LeftOp in dt_STR) and (RightOp in dt_STR) and Operator == "+":
        return 'Str_Const'


    elif (LeftOp in dt_FLT) and (RightOp in dt_BOOl) and Operator in ['+','-','*','/','%','^']:
        return 'Float_Const'


    elif (LeftOp in dt_FLT) and (RightOp in dt_BOOl) and Operator in ['>','<','<=','>=','!=','==']:
        return 'Bool_Const'


    elif (LeftOp in dt_INT) and (RightOp in dt_BOOl) and Operator in ['+','-','*','/','%','^']:
        return 'Float_Const'


    elif (LeftOp in dt_INT) and (RightOp in dt_BOOl) and Operator in ['>','<','<=','>=','!=','==']:
        return 'Bool_Const'
    

    elif (LeftOp in dt_BOOl) and (RightOp in dt_BOOl) and Operator in ['+','-','*','/','%','^']:
        return 'Int_Const'


    elif (LeftOp in dt_BOOl) and (RightOp in dt_BOOl) and Operator in ['>','<','<=','>=','!=','==']:
        return 'Bool_Const'


    elif (LeftOp in dt_BOOl) and (RightOp in dt_BOOl) and Operator in ['or', 'and']:
        return 'Bool_Const'


    elif (LeftOp in dt_BOOl) and (RightOp in dt_INT) and Operator in ['or', 'and']:
        return 'Bool_Const'


    elif (LeftOp in dt_INT) and (RightOp in dt_BOOl) and Operator in ['or', 'and']:
        return 'Bool_Const'


    elif (LeftOp in dt_FLT) and (RightOp in dt_BOOl) and Operator in ['or', 'and']:
        return 'Bool_Const'


    elif (LeftOp in dt_BOOl) and (RightOp in dt_FLT) and Operator in ['or', 'and']:
        return 'Bool_Const'


    elif (LeftOp in dt_INT) and (RightOp in dt_FLT) and Operator in ['or', 'and']:
        return 'Bool_Const'


    elif (LeftOp in dt_FLT) and (RightOp in dt_INT) and Operator in ['or', 'and']:
        return 'Bool_Const'


    elif (LeftOp in dt_BOOl) and (RightOp in dt_STR) and Operator in ['or', 'and']:
        return 'Bool_Const'


    elif (LeftOp in dt_STR) and (RightOp in dt_FLT) and Operator in ['or', 'and']:
        return 'Bool_Const'


    elif (LeftOp in dt_CHAR) and (RightOp in dt_FLT) and Operator in ['or', 'and']:
        return 'Bool_Const'


    elif (LeftOp in dt_BOOl) and (RightOp in dt_CHAR) and Operator in ['or', 'and']:
        return 'Bool_Const'


    elif (LeftOp in dt_FLT) and (RightOp in dt_INT) and Operator == "=":
        return 'float'

    
    elif (LeftOp in dt_FLT) and (RightOp in dt_INT) and Operator in ['+=','-=','*=','/=','%=', '^=']:
        return 'float'


    elif (LeftOp in dt_INT) and (RightOp in dt_FLT) and Operator == "=":
        return 'int'
    
    
    elif (LeftOp in dt_INT) and (RightOp in dt_FLT) and Operator in ['+=','-=','*=','/=','%=', '^=']:
        return 'int'


    elif (LeftOp in dt_INT) and (RightOp in dt_INT) and Operator == "=":
        return 'int'
    
    
    elif (LeftOp in dt_INT) and (RightOp in dt_INT) and Operator in ['+=','-=','*=','/=','%=', '^=']:
        return 'int'


    elif (LeftOp in dt_FLT) and (RightOp in dt_FLT) and Operator == "=":
        return 'float'
    
    
    elif (LeftOp in dt_FLT) and (RightOp in dt_FLT) and Operator in ['+=','-=','*=','/=','%=', '^=']:
        return 'float'
    

    elif (LeftOp in dt_STR) and (RightOp in dt_STR) and Operator == "=":
        return 'str'
    
    
    elif (LeftOp in dt_STR) and (RightOp in dt_STR) and Operator == "+=":
        return 'str'
    

    elif (LeftOp in dt_STR) and (RightOp in dt_CHAR) and Operator == "=":
        return 'str'
    
    
    elif (LeftOp in dt_STR) and (RightOp in dt_CHAR) and Operator == "+=":
        return 'str'
    

    elif (LeftOp in dt_CHAR) and (RightOp in dt_CHAR) and Operator == "=":
        return 'char'
    
    
    elif (LeftOp in dt_CHAR) and (RightOp in dt_CHAR) and Operator == "=":
        return 'char'
    

    elif (LeftOp in dt_INT) and (RightOp in dt_BOOl) and Operator == "=":
        return 'int'
    
    
    elif (LeftOp in dt_INT) and (RightOp in dt_BOOl) and Operator in ['+=','-=','*=','/=','%=', '^=']:
        return 'int'
    

    elif (LeftOp in dt_BOOl) and (RightOp in dt_BOOl) and Operator == "=":
        return 'bool'
    
    
    elif (LeftOp in dt_BOOl) and (RightOp in dt_BOOl) and Operator in ['+=','-=','*=','/=','%=', '^=']:
        return 'bool'
    

    elif (LeftOp in dt_BOOl) and (RightOp in dt_INT) and Operator == "=":
        return 'bool'


    elif (LeftOp in dt_BOOl) and (RightOp in dt_INT) and Operator in ['+=','-=','*=','/=','%=', '^=']:
        return 'bool'
    

    elif (LeftOp in dt_BOOl) and (RightOp in dt_FLT) and Operator == "=":
        return 'bool'


    elif (LeftOp in dt_BOOl) and (RightOp in dt_FLT) and Operator in ['+=','-=','*=','/=','%=', '^=']:
        return 'bool'
    

    elif (LeftOp in dt_BOOl) and (RightOp in dt_CHAR) and Operator == "=":
        return 'bool'
    

    elif (LeftOp in dt_BOOl) and (RightOp in dt_STR) and Operator == "=":
        return 'bool'
    

    elif (LeftOp in dt_FLT) and (RightOp in dt_BOOl) and Operator == "=":
        return 'float'
    
    
    elif (LeftOp in dt_FLT) and (RightOp in dt_BOOl) and Operator in ['+=','-=','*=','/=','%=', '^=']:
        return 'float'

    
    elif (LeftOp in dt_FLT) and (RightOp == "None") and Operator == "=":
        return 'float'
    
    
    elif (LeftOp in dt_INT) and (RightOp == "None") and Operator == "=":
        return 'int'
    
    
    elif (LeftOp in dt_STR) and (RightOp == "None") and Operator == "=":
        return 'str'
    
    
    elif (LeftOp in dt_BOOl) and (RightOp == "None") and Operator == "=":
        return 'bool'
    
    
    elif (LeftOp in dt_CHAR) and (RightOp == "None") and Operator == "=":
        return 'char'



    else:
        e = f"TypeError: unsupported operand type(s) for {Operator}: '{LeftOp}' and '{RightOp}'"
        sys.exit(e)



def CompatibilityTest(Optype, Operator):
    """
    The function CompatibilityTest checks the compatibility of a given operator and operand type and
    returns the corresponding constant type if compatible, otherwise returns False.
    
    :param Optype: The Optype parameter represents the type of the operand in the expression. It can be
    either 'INT' or 'FLT', indicating an integer or float type respectively
    :param Operator: The `Operator` parameter is a string that represents the operator being used in the
    compatibility test
    :return: either 'Int_Const', 'Float_Const', 'Bool_Const', or False.
    """
    if Operator in ['++','--']:
        if Optype in dt_INT:
            return 'int'

        elif Optype in dt_FLT:
            return 'float'    

    elif Operator=='!':
        return 'Bool_Const'


    e = f"TypeError: unsupported operand type(s) for {Operator}: '{Optype}'"
    sys.exit(e)



def typeCompatibilty(type1, type2):
    if type1 in ["float", "bool", "int", "float_Const", "bool_Const", "int_Const"] and type2 in ["float", "bool", "int", "float_Const", "bool_Const", "int_Const"]:
        return True
    else: False
 








# def lookupST(Name):
#     for j in range(len(Stack)):
#         check_scope = Stack[j]
#         print(check_scope,"CHECK SCOPE")
#         for i in range(len(ScopeTable)):
#             if ScopeTable[i].Name == Name :
#                 if "->" in ScopeTable[i].Type:
#                     continue
#                 if ScopeTable[i].Scope == check_scope:
#                     return ScopeTable[i].Type
#     return True
            

# def lookupDT(Name, Type):
#     for i in range(len(DefTable)):
#         if (DefTable[i].Name == Name):
#             if (DefTable[i].Type==Type):
#                 return DefTable[i]
#     if (len(DefTable)==0):
#         pass
#     else:
#         print("Can't Find The Structure")


# def lookUpMemTable(Name,Class_Name):
#     global CCN,CCR
#     CCN =Class_Name
#     CCR = lookUpDefTable(CCN)
#     if (CCR) :
#         for j in range(len(CCR.MemTable)):
#             if (CCR.MemTable[j].Name == Name):
#                 return False
            

#         return True
            
        
# def lookUpFuncST(Name,Plist):
#     size=len(Plist)
#     for j in range(len(Stack)):
#         check_scope = Stack[j]
#         for i in range(len(ScopeTable)):
#             if (ScopeTable[i].Name == Name):
#                 if ScopeTable[i].Type[:size] == Plist[:size]:
#                     if ScopeTable[i].Scope == check_scope:
#                         print(check_scope)
#                         return ScopeTable[i].Type[size+2:]
    
#     return True


# def lookUpFuncMT(Name, Plist, Class_Name):
#     global CCN,CCR
#     CCN = Class_Name
#     CCR = lookUpDefTable(CCN)
#     if (CCR) :
#         for j in range(len(CCR.MemTable)):
#             if (CCR.MemTable[j].Name == Name):
#                 if(CCR.MemTable[j].Type == Plist):
#                     return False
            

#         return True
    
    
                
# def compatibiltyCheck(LeftOp,RightOp,Operator):
#     print ("Inside Compatibility Check")
    
#     if (LeftOp == 'integ' or LeftOp=='int_const') and (RightOp == 'integ' or RightOp == 'int_const') and Operator in ['+','-','*','/','%','>','<','<=','>=','!=','=','==']:
#         return 'integ'
    
#     elif (LeftOp == 'fpoint' or LeftOp== 'fpoint_const') and (RightOp == 'fpoint' or RightOp == 'fpoint_const') and Operator in ['+','-','*','/','%','>','<','<=','>=','!=','=','==']:
#         return 'fpoint'

#     elif (LeftOp=='fpoint' or LeftOp=='fpoint_const') and (RightOp == 'integ' or RightOp =='integ_const') and Operator in ['+','-','*','/','%','>','<','<=','>=','!=','==']:
        
#         return 'fpoint'

#     elif (LeftOp=='integ' or LeftOp=='integ_const') and (RightOp == 'fpoint' or RightOp =='fpoint_const') and Operator in ['+','-','*','/','%','>','<','<=','>=','!=','==']:
        
#         return 'fpoint'
    
#     elif (LeftOp=='integ' or LeftOp=='integ_const') and (RightOp == 'fpoint' or RightOp =='fpoint_const') and Operator == "=":
        
#         return 'integ'
    
#     elif (LeftOp=='fpoint' or LeftOp=='fpoint_const') and (RightOp == 'integ' or RightOp =='integ_const') and Operator =='=':
        
#         return 'fpoint'
    
#     elif (LeftOp=='str' or LeftOp in dt_STR) and (RightOp == 'str' or RightOp  in dt_STR) and Operator in ['+','=']:
#         return 'str'

#     else:
#         return False


    
# def CompatibilityTest(Optype, Operator):
#     if Operator in ['!','++','--']:
#         if Optype == 'integ':
#             return 'integ'
#         elif Optype == 'fpoint':
#             return 'fpoint'    
#     else:
#         return False
        

        
    


# def insertScopeTable(Name,Type,Scope):
#     if "->" in Type:

#         if (lookUpFuncST(Name,Type)==True):
#             obj = ScopeTableInstance(Name,Type,Scope)
#             ScopeTable.append(obj)
#             print(f"Function {Name} is added")
#         else:
#             print("Function Redeclaration Error")
#             sys.exit()
#     else:
#         for i in range(len(ScopeTable)):
#             if ScopeTable[i].Name == Name: 
#                 if ScopeTable[i].Scope ==Scope:
#                     print("Redeclaration Error !")
#                     sys.exit()
                
#         obj=ScopeTableInstance(Name,Type,Scope)
#         ScopeTable.append(obj)
#         print(f"Variable {Name} is added")
            
            



# def insertDefTable(Name,Type,Acc_Mod,Parent,Type_Mod):
#     global CCN,CCR
#     if(lookUpDefTable(Name,Type)):
#         print("Error !  Redefinition of "+Name+".")
        
#     else:
#         CCN = Name
#         obj=DefTableInstance(Name,Type,Acc_Mod,Parent,Type_Mod)
#         CCR = obj.MemTable
#         DefTable.append(obj)
#         print(f"{CCN} is added as {Type}")



# def insertMemTable(Name,Type,Acc_Mod,Type_Mod,Const,Class_Name):
#     global CCR ,CCN
#     if "->" in Type:
#         a = lookUpFuncMT(Name,Type,Class_Name)

#         if(a==False):
#             print("Error: Redefinition of member function '"+str(Name)+"'")
#             return


#         if(a==True):
#             obj=MemTableInstance(Name,Type,Acc_Mod,Type_Mod,Const,Class_Name)
#             CCR.MemTable.append(obj)
#             print(f"{Name} function is added in {Class_Name} as member")

#     else:
#         a = lookUpMemTable(Name,Class_Name)

#         if(a==False):
#             print("Error: Redefinition of member variable '"+str(Name)+"'")
#             return


#         if(a==True):
#             obj=MemTableInstance(Name,Type,Acc_Mod,Type_Mod,Const,Class_Name)
#             CCR.MemTable.append(obj)
#             print(f"{Name} is added in {Class_Name} as member")


# def createScope():
#     global Stack
#     global scope
#     global currentScope
#     scope += 1
#     currentScope = scope
#     Stack.insert(0, scope)



# def destroyScope():
#     global currentScope
#     global Stack
#     Stack.pop(0)
#     currentScope = Stack[0]