#pragma once
#include "token.hpp"
#include <cctype>// just to check weather a charecter is a alphabet or int or bool etc..
#include <string>
#include <utility>
#include <vector>

class Lexer{
public:
    explicit Lexer(std::string src):source(std::move(src)){}// generally when the class has a single data in it the c++ allows someone to simply pass that data type variable as a class to stop hat we use explicit here
    std::vector<Token> scanTokens();

private:
    std::string source;
    size_t start=0;
    size_t current=0;
    int line=1;

    bool isAtEnd()const{return current>=source.size();}
    char advance(){return source[current++];}
    bool match(char expected);
    char peek()const{return isAtEnd()?'\0':source[current];}
    char peekNext()const{return current+1>=source.size()?'\0':source[current+1];}

    void addToken(std::vector<Token>&tokens,TokenType type,Literal lit={});
    void skipWhitespace();
    void number(std::vector<Token>&tokens);
    void identifier(std::vector<Token>&tokens);

    static bool isAlpha(char c){return std::isalpha((unsigned char)c)||c=='_';}
    static bool isAlphaNumeric(char c){return isAlpha(c)||std::isdigit((unsigned char)c);}
};
