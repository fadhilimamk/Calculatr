#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hitung.h"
#include "stackt.h"
#include "stacktdouble.h"
#include "boolean.h"

// Mengecek operator precedence
/*
  Akan bernilai true jika prioritas lebih besar
*/
boolean OperatorPrec(char a, char b){
  if ((( a == '-' || a == '+') && ( b == '*' || b == '/')) || (( a == '+') && ( b == '-')) || (( a == '+') && ( b == '+')) || (( a == '-') && ( b == '-')) ||  (( a == '-') && ( b == '+')) || (( a == '*') && ( b == '/')) || (( a == '/') && ( b == '*')) || (( a == '*') && ( b == '*')) || (( a == '/') && ( b == '/')))
    return true;
  else
    return false;
}

boolean IsOperator(char a){
  if ( a == '+' || a == '-' || a == '*' || a == '/')
    return true;
  else
    return false;
}

boolean IsOperand(char a){
  if ( a == '0' || a == '1' || a == '2' || a == '3' || a == '4' || a == '5' || a == '6' || a == '7' || a == '8' || a == '9')
    return true;
  else
    return false;
}

boolean IsLeft(char a){
  if ( a == '(')
    return true;
  else
    return false;
}

boolean IsRight(char a){
  if ( a == ')')
    return true;
  else
    return false;
}


//mengecek apakah ada '-' bersebelahan
boolean IsMinus(char *str){
  size_t i = 1;
  boolean cek = true;
  if (strlen(str) > 1){
    while ( i < strlen(str) && cek){
      if (*(str+i-1) == '-' && *(str+i) == '-')
        cek = false;
      if (*(str+i-1) == '+' && *(str+i) == '+')
        cek = false;
      if (*(str+i-1) == '-' && *(str+i) == '+')
        cek = false;
      if (*(str+i-1) == '+' && *(str+i) == '-')
        cek = false;
      if (*(str+i-1) == '(' && *(str+i) == '-')
        cek = false;
      i++;
    }
  }
  return cek;
}

void konversikali(char *str, char *temp){
  int i = 0;
  int j = 0;
  if (strlen(str) > 1){
    while ( i < strlen(str)){
      if (( *(str+i-1) == '*' ||  *(str+i-1) == '/') && *(str+i) == '+' )
        i++;
      if (( *(str+i-1) == '*' ||  *(str+i-1) == '/') && *(str+i) == '-' ){
        temp[j] = '(';
        j++;
        temp[j] = '-';
        j++;

        i++;
        while (IsOperand(*(str+i)) || *(str+i) == '.'){
          temp[j] = str[i];
          j++;
          i++;
        }
        temp[j] = ')';
        j++;
      }

      temp[j] = str[i];
      i++;
      j++;

    }
  } else {
    temp[j] = str[i];
    i++;
    j++;
  }
}

void konversi(char *str, char *temp){
  int i = 0;
  int j = 0;
  if (*(str) == '+' || *(str) == '-'){
    temp[j] = '0';
    j++;
  }
  if (strlen(str) > 1){
    while ( i < strlen(str)){
      //mengubah ekspresi (-A) menjadi (0-A) atau (+A) menjadi (0+A)
      if ( i > 0 ){
        if (*(str+i-1) == '(' && ( *(str+i) == '-' || *(str+i) == '+')){
          temp[j] = '0';
          j++;
        }
      }

      //mengubah ekspresi 2(A) menjadi 2*(A)
      if (*(str+i) == '(' && IsOperand(*(str+i-1))){
        temp[j] = '*';
        j++;
      }

      if ( *(str+i) == '+' && *(str+i+1) == '-' ){
        i+=2;
        temp[j] = '-';
        j++;
      } else if ( *(str+i) == '-' && *(str+i+1) == '+' ){
        i+=2;
        temp[j] = '-';
        j++;
      } else {
        //mengilangkan tanda '-' atau '+' yang bersebelahan
        while ((*(str+i) == '-' && *(str+i+1) == '-') || (*(str+i) == '+' && *(str+i+1) == '+')){
          i+=2;
          temp[j] = '+';
          j++;
        }
      }


      temp[j] = str[i];
      i++;
      j++;
    }
  } else {
    temp[j] = str[i];
    i++;
    j++;
  }
}

/*
//Mengambil ekspresi diantara 2 kurung ()
//I.S test[0] = '('
//F.S str berisi nilai yang ada dalam dua kurung
//misal jika test = "(1+2-3+4)" maka str = "1+2-3+4"
*/
void AmbilKurung(char *test , char *str){
  Stack T;
  CreateEmpty(&T);
  int k = 0;
  size_t i = 0;
  int iter = 0;
  Push(&T,test[i]);
  i++;
  // str[0] = '\0';
  char a = '#';
  while (!(IsEmpty(T))){
    if ((test[i] == '('))
      Push(&T,a);
    if ((test[i] == ')'))
      Pop(&T,&a);
    if (!(IsEmpty(T))){
      str[iter] = test[i];
      i++;
      iter++;
    }
  }
  str[iter] = '\0';
}


//Mengubah ekspresi infix menjadi postfix serta menambahkan spasi antar simbol
//I.S. test berisi karakter infix, temp kosong
//F.S. temp berisi ekspresi postfix dari test
void Postfix(char *test, char *temp){
  size_t i = 0;
  size_t j = 0;

  // temp[0] = '\0';

  Stack S;
  CreateEmpty(&S);

  while (i < strlen(test)){
    char a = test[i];
    if (IsOperand(a) || a == '.'){
      temp[j] = test[i];
      j++;
      if (!(IsOperand(test[i+1]) || (test[i+1] == '.'))){
        temp[j] = ' ';
        j++;
      }
    } else if (IsOperator(a)){
      if (!(IsEmpty(S))){
        char b = InfoTop(S);
        while (OperatorPrec(a,b) && !(IsEmpty(S))){
          temp[j] = InfoTop(S);
          j++;
          temp[j] = ' ';
          j++;
          char x;
          Pop(&S,&x);
          if (!(IsEmpty(S)))
            b = InfoTop(S);
        }
        Push(&S,a);
      } else {
        Push(&S,a);
      }
    } else if (IsLeft(a)){
      char *str = (char*) malloc(100);
      char *kurung = (char*) malloc(100);
      char *postkurung = (char*) malloc(100);
      // str[0] = '\0';
      str = (test+i);
      AmbilKurung(str,kurung);
      Postfix(kurung,postkurung);
      strcat(temp,postkurung);
      i += strlen(kurung) + 1;
      j = strlen(temp);
      // free(str);
      // free(kurung);
      // free(postkurung);
    }
    i++;
  }

  j = strlen(temp);
  while (!(IsEmpty(S))){
    temp[j] = InfoTop(S);
    j++;
    temp[j] = ' ';
    j++;
    char x;
    Pop(&S,&x);
  }
}


double nilai(double a, double b, char c){
  if ( c == '+' )
    return a + b;
  else if (c == '-')
    return a - b;
  else if (c == '*')
    return a*b;
  else  //c = /
    return a/b;
}

double hitung (char *str){

  int i = 0;
  double a,hasil;

  char *e;

  DStack S;
  DCreateEmpty(&S);

  while (strlen(str) > 0){

    if (IsOperator(*str)){
      if (*str == '-' && (DTop(S) - 1) == 0){
        double x;
        DPop(&S,&x);
        x*=-1;
        DPush(&S,x);
        str++;
        while (*str == ' '){
          str = str+1;
        }
      } else {
        double x,y;
        DPop(&S,&x);
        DPop(&S,&y);
        // printf("x : %lf\n",x);
        // printf("y : %lf\n",y);
				if (*str == '/' && x == 0){
					printf("Pembagian dengan 0 tidak bisa\n");
					// abort();
				}
        hasil = nilai(y,x,*str);
        DPush(&S,hasil);
        str++;
        while (*str == ' '){
          str = str+1;
        }
      }

    } else if (IsOperand(*str)){
      a = strtod(str,&e);
      DPush(&S,a);
      while (*e == ' '){
        e = e+1;
      }
      str = e;
    }
  }

  return DInfoTop(S);

}


double evaluasi(char * lang){
  char *str = malloc(strlen(lang)*2);

  str = lang;


  //mengkonversi susunan dan mengganti useless operator
  //Proses : menghapus tanda '-' bersebelahan, atau '+' bersebelahan serta mengubah ekspresi (-A) menjadi (0-A)
  //misal input ----9 maka dikonversi menjadi 9
  //misal input (-9) maka dikonversi menjadi (0-9)



  while (!(IsMinus(str))){
    char *temp = (char *) malloc(strlen(lang)*2);
    konversi(str,temp);
    str = temp;
  }

  char *temp = (char *) malloc(strlen(lang)*2);
  konversikali(str,temp);
  char *temp1 = (char *) malloc(strlen(lang)*2);
  konversi(temp,temp1);

  //mengubah ekspresi menjadi postfix
  char *postfix = (char*) malloc(strlen(lang)*2);
  Postfix(temp1,postfix);

  //menampilkan hasil perhitungan ekspresi
  printf("%g\n", hitung(postfix));

  return 0;
}
