#ifndef SCANNER_HPP
#define SCANNER_HPP

#include<iostream>
#include<cstdio>
#include<cctype>
#include<cmath>
#include"SemanticAction.hpp"

class unexpected_char : public std::exception {};

template <typename It>
class Scanner {
  public:
    using char_type = int;

  public:
    Scanner(It b, It e) : b_(b), e_(e), c_(b), unget_(EOF) {}

    calc::Token get(int& v ){
      int c;
      do{
        c = getc();
      }while(isspace(c));

      // operator
      switch(c){
        case '+': return calc::token_Add;
        case '-': return calc::token_Sub;
        case '*': return calc::token_Mul;
        case '/': return calc::token_Div;
        case '.': return calc::token_Point;
        case 's': return calc::token_Sin;
        case 'c': return calc::token_Cos;
        case 't': return calc::token_Tan;
        case 'r': return calc::token_Sqrt;
        case '(': return calc::token_Begin;
        case ')': return calc::token_End;
        case EOF: return calc::token_eof;
      }

      // number
      if(isdigit(c)){
        int n = 0;
        while(c != EOF && isdigit(c)) {
          n *= 10;
          n += c - '0';
          c = getc();
        }
        ungetc(c);
        v = n;
        return calc::token_Number;
      }


      std::cerr << char(c) << std::endl;
      throw unexpected_char();
    }

  private:
    char_type getc(){
      int c;
      if(unget_ != EOF){
        c = unget_;
        unget_ = EOF;
      } else if(c_ == e_){
        c = EOF;
      } else{
        c = *c_++;
      }
      return c;
    }

    void ungetc(char_type c){
      if(c != EOF) {
        unget_ = c;
      }
    }

  private:
    It b_, e_, c_;
    char_type unget_;

};

#endif

