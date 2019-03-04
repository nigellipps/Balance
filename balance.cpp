// Nigel Lipps
// Hanging in the Balance

#include <iostream>
#include <fstream>
#include <istream>
#include <cstring>
#include <iomanip>
#include <stack>
using namespace std;

void printFile(istream &dictfile){
    char c;
    int n = 1;
    cout << right  << setw(3) << n << "  ";
    n++;
    while(dictfile.peek() != EOF){
        dictfile.get(c);
        //add it to queue of strings. Each string is a new line
        cout << c;
        if(c == '\n'){
            cout << right << setw(3) << n << "  ";
            n++;
        }
    }
    cout << endl;
    dictfile.clear();
    dictfile.seekg(0, ios::beg);
}

//handle block comments
bool opensBlockComment(istream &dictfile, string &c, int &i, int &n){
    //check the rest of the line
    while (i<c.length()){
        if(c[i]=='*' && c[i+1]=='/'){
            cout << "pair matching /* and */" << endl;
            return true;
        }
        i++;
    }
    int temp = n;
    //check the other lines
    while (dictfile.peek()!= EOF){
        n++;
        getline(dictfile, c);
        for(int i=0; i < c.length(); i++){
            if(c[i]=='*' && c[i+1]=='/'){
                cout << "pair matching /* and */" << endl;
                return true;
            }
        }
    }
    cout << "unbalanced /* on line " << temp << endl;
    return false;
}

//handle single quotes
bool opensSingleQuote(istream &dictfile, string &c, int &i, int &n){
    //check the rest of the line
    while (i<c.length()){
        i++;
        if(c[i]=='\''){
            cout << "pair matching \' and \'" << endl;
            return true;
        }
    }
    cout << "unbalanced ' on line " << n << endl;
    return false;
}

//handle double quotes
bool opensDoubleQuote(istream &dictfile, string &c, int &i, int &n){
    //check the rest of the line
    while (i<c.length()){
        i++;
        if(c[i]=='\"'){
            cout << "pair matching \" and \"" << endl;
            return true;
        }
    }
        cout << "unbalanced \" on line " << n << endl;
    return false;
}

bool balanceFile(istream &dictfile){
    string c;
    int n = 0;
    stack<char> s;
    stack<int> l;
    //go through each line
    while (dictfile.peek()!= EOF){
        n++;
        getline(dictfile, c);
        //check for brackets through the line
        for(int i=0; i < c.length(); i++){
            if(c[i]=='('|| c[i]=='{' || c[i]=='['){
                s.push(c[i]);
                l.push(n);
            }
            else if(c[i] == '/' && c[i+1] == '*'){
                if(opensBlockComment(dictfile, c, i, n)==false)
                    return false;
            }
            else if(c[i] == '\''){
                if(opensSingleQuote(dictfile, c, i, n)==false)
                    return false;
            }
            else if(c[i] == '"'){
                if(opensDoubleQuote(dictfile, c, i, n)==false)
                    return false;
            }
            else if(c[i] == '/' && c[i+1] == '/'){
                while(i<c.length())
                    i++;
            }
            else if(s.empty()){
                if(c[i]=='}'){
                    cout << "unmatched } symbol at line " << n << endl;
                    return false;
                }
                if(c[i]==')'){
                    cout << "unmatched ) symbol at line " << n << endl;
                    return false;
                }
                if(c[i]==']'){
                    cout << "unmatched ] symbol at line " << n << endl;
                    return false;
                }
            }
            else if(c[i]==')' && s.top()=='('){
                s.pop();
                l.pop();
                cout << "pair matching ( and )" << endl;
            }
            else if(c[i]==')' && s.top()!='('){
                cout << "unmatched ) symbol at line " << n << endl;
                return false;
            }
            else if(c[i]=='}' && s.top()=='{'){
                s.pop();
                l.pop();
                cout << "pair matching { and }" << endl;
            }
            else if(c[i]=='}' && s.top()!='{'){
                cout << "unmatched } symbol at line " << n << endl;
                return false;
            }
            else if(c[i]==']' && s.top()=='['){
                s.pop();
                l.pop();
                cout << "pair matching [ and ]." << endl;
            }
            else if(c[i]==']' && s.top()!='['){
                cout << "unmatched ] symbol at line " << n << endl;
                return false;
            }
            
        }
    }
    //check for unmatched open brackets in the stack
    while(!s.empty()){
        if(s.top() == '{'){
            s.pop();
            cout << "unmatched { symbol at line " << l.top() << endl;
            l.pop();
            return false;
        }
        else if(s.top() == '['){
            s.pop();
            cout << "unmatched [ symbol at line " << l.top() << endl;
            l.pop();
            return false;
        }
        else if(s.top() == '('){
            s.pop();
            cout << "unmatched ( symbol at line " << l.top() << endl;
            l.pop();
            return false;
        }
        else{
            s.pop();
            cout << "There was an error with this file." << endl;
        }
    }
    return true;
}

//int main() {
//    ifstream dictfile; // file containing the list of words
//    string file;
//    cout << "Enter the file name: ";
//    cin >> file;
//    cout << endl;
//    dictfile.open(file);
//    if (!dictfile) {
//        cout << "File not found!" << endl;
//        return (1);
//    }
//    printFile(dictfile);
//    if(balanceFile(dictfile)){
//        cout << "Balance is OK." << endl;
//    }
//    return 0;
//}
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cassert>
#include <algorithm>
#include <csignal>
#include <regex>
#include <type_traits>
#include <set>
using namespace std;
class streambuf_switcher
{
public:
    streambuf_switcher(ios& dest, ios& src)
    : dest_stream(dest),
    saved_streambuf(dest.rdbuf(src.rdbuf()))
    {}
    ~streambuf_switcher()
    {
        dest_stream.rdbuf(saved_streambuf);
    }
private:
    ios& dest_stream;
    streambuf* saved_streambuf;
};
void testone(int n)
{
    ostringstream strCout;
    streambuf_switcher sso(cout, strCout);
    
    switch (n)
    {
        default: {
            cout << "Bad argument" << endl;
        } break; case 1: {
            istringstream iss("{}");
            assert(balanceFile(iss));
            string str = strCout.str();
            regex e(R"(pair *matching *\{ *and *\})");
            assert(regex_search(str, e));
        } break; case 2: {
            istringstream iss("[]");
            assert(balanceFile(iss));
            string str = strCout.str();
            regex e(R"(pair *matching *[ *and *])");
            assert(regex_search(str, e));
        } break; case 3: {
            istringstream iss("()");
            assert(balanceFile(iss));
            string str = strCout.str();
            regex e("pair *matching *\\( *and *\\)");
            assert(regex_search(str, e));
        } break; case 4: {
            istringstream iss("/* */");
            assert(balanceFile(iss));
            string str = strCout.str();
            regex e(R"(pair *matching */\* *and *\*/)");
            assert(regex_search(str, e));
        } break; case 5: {
            istringstream iss("\" \"");
            assert(balanceFile(iss));
            string str = strCout.str();
            regex e(R"(pair *matching *\" *and *\")");
            assert(regex_search(str, e));
        } break; case 6: {
            istringstream iss("' '");
            assert(balanceFile(iss));
            string str = strCout.str();
            regex e(R"(pair *matching *' *and *')");
            assert(regex_search(str, e));
        } break; case 7: {
            istringstream iss("{\n}");
            assert(balanceFile(iss));
            string str = strCout.str();
            regex e(R"(pair *matching *\{ *and *\})");
            assert(regex_search(str, e));
        } break; case 8: {
            istringstream iss("{(\n)}");
            assert(balanceFile(iss));
            string str = strCout.str();
            regex e("pair *matching *\\( *and *\\).*\\npair *matching *\\{ *and *\\}");
            assert(regex_search(str, e));
        } break; case 9: {
            istringstream iss("() {}");
            assert(balanceFile(iss));
            string str = strCout.str();
            regex e("pair *matching *\\( *and *\\).*\\npair *matching *\\{ *and *\\}");
            assert(regex_search(str, e));
        } break; case 10: {
            istringstream iss("\" ][ \"");
            assert(balanceFile(iss));
            string str = strCout.str();
            regex e(R"(pair *matching *\" *and *\")");
            assert(regex_search(str, e));
        } break; case 11: {
            istringstream iss("/* \n ][ */ { * }");
            assert(balanceFile(iss));
            string str = strCout.str();
            regex e(R"(pair *matching */\* *and *\*/.*\npair *matching *\{ *and *\})");
            assert(regex_search(str, e));
        } break; case 12: {
            istringstream iss("/* \n ][ */");
            assert(balanceFile(iss));
            string str = strCout.str();
            regex e(R"(pair *matching */\* *and *\*/)");
            assert(regex_search(str, e));
        } break; case 13: {
            istringstream iss("\n{\n(\n//']\n)}");
            assert(balanceFile(iss));
            string str = strCout.str();
            regex e("pair *matching *\\( *and *\\).*\\npair *matching *\\{ *and *\\}");
            assert(regex_search(str, e));
        } break; case 14: {
            istringstream iss("\n{\n(\n//*]\n)}");
            assert(balanceFile(iss));
            string str = strCout.str();
            regex e("pair *matching *\\( *and *\\).*\\npair *matching *\\{ *and *\\}");
            assert(regex_search(str, e));
        } break; case 15: {
            istringstream iss("\n{\n(]\n)}");
            assert(!balanceFile(iss));
            string str = strCout.str();
            regex e("(unmatched|unbalanced).*(\\(|\\]).*3");
            assert(regex_search(str, e));
        } break; case 16: {
            istringstream iss("\n{(\n)");
            assert(!balanceFile(iss));
            string str = strCout.str();
            regex e("(unmatched|unbalanced).*\\{.*2");
            assert(regex_search(str, e));
        } break; case 17: {
            istringstream iss("\n\n{(\n')}");
            assert(!balanceFile(iss));
            string str = strCout.str();
            regex e("(unmatched|unbalanced).*'.*4");
            assert(regex_search(str, e));
        } break; case 18: {
            istringstream iss("{");
            assert(!balanceFile(iss));
            string str = strCout.str();
            regex e("(unmatched|unbalanced)");
            assert(regex_search(str, e));
        } break; case 19: {
            istringstream iss("}");
            assert(!balanceFile(iss));
            string str = strCout.str();
            regex e("(unmatched|unbalanced)");
            assert(regex_search(str, e));
        } break; case 20: {
            istringstream iss("{ /* }");
            assert(!balanceFile(iss));
            string str = strCout.str();
            regex e("(unmatched|unbalanced)");
            assert(regex_search(str, e));
        } break; case 21: {
            istringstream iss("'*");
            assert(!balanceFile(iss));
            string str = strCout.str();
            regex e("(unmatched|unbalanced)");
            assert(regex_search(str, e));
        } break; case 22: {
            istringstream iss("()[]{ * }}");
            assert(!balanceFile(iss));
            string str = strCout.str();
            regex e("(unmatched|unbalanced)");
            assert(regex_search(str, e));
        } break; case 23: {
            istringstream iss("()([{}]) /* */");
            assert(balanceFile(iss));
        } break; case 24: {
            istringstream iss("/* ]][()) ' */");
            assert(balanceFile(iss));
        } break; case 25: {
            istringstream iss(" ][ ");
            assert(!balanceFile(iss));
            string str = strCout.str();
            regex e("(unmatched|unbalanced)");
            assert(regex_search(str, e));
        } break;
    }
}
int main()
{
    cout << "Enter test number: ";
    int n;
    cin >> n;
    testone(n);
    cout << "Passed" << endl;
}
