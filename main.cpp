#include "header files\Lexical.h"
#include "header files\syntax.h"
using namespace std;

int main () {
    
    Lexical analyzer;
    Syntax analizer;

    analyzer.createToken();
    //analyzer.printTokens();
    analyzer.assignClassPart();
    analyzer.token.push_back(make_tuple("$", "$", 100));
    analizer.token = analyzer.token;
    analizer.stack.push_back(0);
    // analizer.print();
    analizer.checkSyntax();
    analyzer.writeTokens();
    return 0;
}
