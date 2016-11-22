#ifndef _HITUNG_h
#define _HITUNG_h

#include "boolean.h"

boolean OperatorPrec(char a, char b);
boolean IsOperator(char a);
boolean IsOperand(char a);
boolean IsLeft(char a);
boolean IsRight(char a);
boolean IsMinus(char *str);
void konversikali(char *str, char *temp);
void konversi(char *str, char *temp);
void AmbilKurung(char *test , char *str);
void Postfix(char *test, char *temp);
double nilai(double a, double b, char c);
double hitung (char *str);
double evaluasi(char * lang);

#endif
