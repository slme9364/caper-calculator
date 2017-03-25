#ifndef SEMANTIC_ACTION_HPP
#define SEMANTIC_ACTION_HPP

#include<cstdio>
#include<cmath>

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

#endif

