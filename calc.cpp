#include <iostream>
#include <cstdio>
#include <cctype>
#include <cmath>
#include "calc.hpp"

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

      // 記号類
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

      // 数字
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

struct SemanticAction {

  void syntax_error(){}
  void stack_overflow(){}
  void downcast(double& x, double y) { x = y; }
  void upcast(double& x, double y) { x = y; }

  double Identity(double n) { return n; }
  double MakeAdd(double x, double y){
    return x + y;
  }
  double MakeSub(double x, double y){
    return x - y;
  }
  double MakeMul(double x, double y){
    return x * y;
  }
  double MakeDiv(double x, double y){
    return x / y;
  }
  double MakeDouble(double x, double y){//自分で小数を入力した際に起こす
    int nod = log10(y) + 1;//log10(y)+1でyの桁数を求める
    for(int i = 0; i < nod; i++)  y /= 10;//yを小数点以下の値にする
    return x + y;
  }
  double MakeSin(double x){
    return sin(x);
  }
  double MakeCos(double x){
    return cos(x);
  }
  double MakeTan(double x){
    return tan(x);
  }
  double MakeSqrt(double x){
    return sqrt(x);
  }
};

int main( int, char** ){
  using is_iterator = std::istreambuf_iterator<char>;
  is_iterator b(std::cin);
  is_iterator e;
  Scanner<is_iterator> s(b, e);

  SemanticAction sa;

  calc::Parser<double, SemanticAction> parser(sa);

  calc::Token token;
  while(true){
    int v;
    token = s.get(v);
    if(parser.post(token, v)) break;
  }

  double v;
  if(parser.accept(v)){
    std::cout << v << std::endl;
  }

  return 0;
}
