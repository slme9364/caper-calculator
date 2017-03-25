#include <iostream>
#include <cstdio>
#include <cctype>
#include <cmath>
#include "calc.hpp"
#include "Scanner.hpp"
#include "SemanticAction.hpp"

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
