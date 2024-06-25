#include <assert.h>
#include <stdio.h>
#include <string.h>

//#include "Front-End.h"
#include "File.h"

const char* nameFile = "Code.txt";

/*#define LEXICAL_ASSERT(condition) lexical_assert(condition, tree, buf);


Tokens* lexical_analysis(char* buf);
Token* get_token(char** buf);

void skip_spaces(char** buf);

bool get_operator(Token* token, char** buf);
bool get_variable(Token* token, char** buf);
bool get_number(Token* token, char** buf);

void* elem_ctor(void* elem);
void  elem_dtor(void* elem);
void  write_elem(FILE* fp, void* elem);
*/
int main()
{   
    File* code = file_ctor(nameFile);
    printf("%d\n", code->sizeFile);
    for(int i = 0; i < code->sizeFile; i++)
        printf("%d ", code->buf[i]);
    file_dtor(code);  
/*    Tokens* lexis = lexical_analysis(buf);

    for(int i = 0; i < lexis->sizeTokens; i++)
    {
        if(lexis->tokens[i]->type == OPERATOR)
            printf("op %d\n", lexis->tokens[i]->elem.op);
        
        if(lexis->tokens[i]->type == VARIABLE)
            printf("var %s\n", lexis->tokens[i]->elem.var);
        
        if(lexis->tokens[i]->type == NUMBER)
            printf("num %g\n", lexis->tokens[i]->elem.num);
    }
*/    
    return 0;
}

/*void* elem_ctor(void* elem)
{
    assert(elem != nullptr);

    if()
}
void lexical_assert(bool cond, char** buf)
{
    if(!cond)

}
Tokens* lexical_analysis(char* buf)
{
    assert(buf != nullptr);

    Tokens* lexis = (Tokens*)calloc(1, sizeof(Tokens));
    if(lexis == nullptr)
        return nullptr;

    lexis->tokens = (Token**)calloc(strlen(buf), sizeof(Token*));
    if(lexis->tokens == nullptr)
        return nullptr;

    skip_spaces(&buf);
    for(int i = 0; *buf != '\0'; i++)
    {
        lexis->tokens[i] = get_token(&buf);
        lexis->sizeTokens++;
        skip_spaces(&buf);
    }

    return lexis;
}

void skip_spaces(char** buf)
{
    assert(buf != nullptr);

    while(**buf == ' ' || **buf == '\n' || **buf == '\r')
        (*buf)++;
}

Token* get_token(char** buf)
{
    assert(buf != nullptr);

    Token* token = (Token*)calloc(1, sizeof(Token));
    if(token == nullptr)
        return nullptr;

    if(get_operator(token, buf))
        return token;
    else if(get_variable(token, buf))
        return token;
    else if(get_number(token, buf))
        return token;
    else
        assert(!"Unknown type");

    return  token;
}

bool get_operator(Token* token, char** buf)
{
    assert(token != nullptr);
    assert(buf   != nullptr);

    switch(**buf)
    {
        #define DEF_OP(name, icon)              \
            case icon:                          \
                token->elem.op = name;          \
                break;              
        
        #include "Operators.h"
        
        #undef DEF_OP  

        default: return false;    
    }

    token->type = OPERATOR;
    (*buf)++;
    return true;
}

bool get_variable(Token* token, char** buf)
{
    assert(token != nullptr);
    assert(buf   != nullptr);

    if(!('a' <= **buf && **buf <= 'z' || 'A' <= **buf && **buf <= 'Z'))
        return false;

    const int MAX_SIZE_ID = 20;
    char id[MAX_SIZE_ID] = {};
    int p = 0;

    while('a' <= **buf && **buf <= 'z' || 'A' <= **buf && **buf <= 'Z' || **buf == '_'
                        || **buf == '_' || **buf == '$' || '0' <= **buf && **buf <= '9')
    {
        id[p] = **buf;
        (*buf)++;
        p++;
    }

    token->type = VARIABLE;
    token->elem.var = strdup(id);
    return true;
}

bool get_number(Token* token, char** buf)
{
    assert(token != nullptr);
    assert(buf   != nullptr);

    double value = 0;
    char* oldBuf = *buf;

    while('0' <= **buf && **buf <= '9')
    {
        value = value * 10 + (**buf - '0');
        (*buf)++;
    }
    if(**buf == '.')
    {
        (*buf)++;
        double order = 10;
        while('0' <= **buf && **buf <= '9')
        {
            value  = value  + (**buf - '0') / order;
            order *= 10;
            (*buf)++;
        }
    }
    LEXICAL_ASSERT(oldBuf < *buf)

    token->type = NUMBER;
    token->elem.num = value;

    return true;
}*/
