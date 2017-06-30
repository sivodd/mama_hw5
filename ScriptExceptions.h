#ifndef _SCRIPT_EXCEPTIONS_H_
#define _SCRIPT_EXCEPTIONS_H_

#include<string.h>
#include<exception>
#include<stdexcept>
using namespace std;

#define SYNTAX_UNBALANCED ScriptException("Error: Expression or statement is incorrect--possibly unbalanced (, {, or [.")
#define SYNTAX_INCOMPLETE ScriptException("Error: Expression or statement is incomplete or incorrect.")
#define SYNTAX_UNDEFINED(x) ScriptException(string("Undefined function or variable '") += string(x) += "'")

#define MISSING_VAR ScriptException("Missing input arguments for operator or function.")
#define BAD_VAR_NUM ScriptException("Too many/few input arguments for operator or function.")
#define BAD_INPUT ScriptException("Invalid input arguments for operator or function.")
#define MISSING_BLOCK_END  ScriptException("At least one END is missing.")
#define SUBSCRIPT_MISMATCH ScriptException("Subscripted assignment dimension mismatch.")
#define INDEX_OUT_OF_RANGE ScriptException("Index exceeds matrix dimensions.")
#define BAD_MAT_DIMS(x) ScriptException(string("Error using  ") += string(x) += ", Matrix dimensions must agree.")
#define BAD_MAT_PROD ScriptException("Error using  *, Inner matrix dimensions must agree.")
#define INVALID_VAR_NAME(x) ScriptException(string("Invalid variable name '") += string(x) += "'")

#define UNEXPECTED(x)  ScriptException(x)

class ScriptException : public exception{
private:
    //std::string* err_msg;
    char* err_msg;
public:
    ScriptException(const char* error);
    ScriptException(std::string str);
    const char* what () const throw();

    ~ScriptException();

};

ScriptException::ScriptException(const char *error)
{
    err_msg = new char [strlen(error)+1];
    strcpy(err_msg,error);
}

ScriptException::ScriptException(std::string str)
{
    err_msg = new char[str.size()+1];
    std::copy(str.begin(),str.end(),err_msg);
    err_msg[str.size()] = '\0';
}

ScriptException::~ScriptException()
{
    delete [] err_msg ;
}

const char* ScriptException::what() const throw()
{
    return err_msg;
}

#endif // _SCRIPT_EXCEPTIONS_H_
