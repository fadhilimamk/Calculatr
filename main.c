#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "controller/hitung.h"
#include "controller/boolean.h"

int main(){
  /*
    CFL
    E -> E+T E-T T
    T -> E*F E/F E*E E/E F
    F -> (E) N
    N -> I L
    I -> D ID MI Z
    M -> - -M
    L -> I.R
    R -> D RD
    D -> 0 1 2 3 4 5 6 7 8 9
    Z -> +D ZD


    CNF (26 lines)
1    E -> EV EX EK EP ES EU GH 0 1 2 3 4 5 6 7 8 9 ID MI WD ZD IA
2    T -> EK EP ES EU GH 0 1 2 3 4 5 6 7 8 9 ID MI WD ZD IA
3    F -> GH 0 1 2 3 4 5 6 7 8 9 ID MI WD ZD IA
4    N -> 0 1 2 3 4 5 6 7 8 9 ID MI WD ZD IA
5    I -> 0 1 2 3 4 5 6 7 8 9 ID MI WD ZD
6    M -> - CM
7    L -> IA
8    R -> 0 1 2 3 4 5 6 7 8 9 RD
9    D -> 0 1 2 3 4 5 6 7 8 9
10    A -> BR
11    B -> .
12    C -> -
13    G -> (
14    H -> EJ
15    J -> )
16    K -> OF
17    O -> *
18    P -> QF
19    Q -> /
20    S -> OE
21    Z -> WD ZD
22    U -> QE
23    V -> WT
24    W -> +
25    X -> CT

  */

  boolean *P;
  int i,j,k,n;
  char str[1000000];
  char * lang = str;

  printf("Masukkan string : ");
  scanf("%[^\n]", lang);
  n = strlen(lang);
  P = malloc((n+1)*(n+1)*26);
  int offset( int x, int y, int z ) { return ( z * (n+1) * (n+1) ) + ( y * (n+1) ) + x ; }

  for (i = 0; i <= n; i++)
    for (j = 0; j <=n; j++)
      for (k = 0; k <= 25; k++)
        P[offset(i,j,k)] = false;

  for (i = 1; i <= n; i++) {
    switch (lang[i-1]) {
      case '0'...'9' :
                      P[offset(1,i,8)] = true;
                      P[offset(1,i,9)] = true;
                      P[offset(1,i,1)] = true;
                      P[offset(1,i,2)] = true;
                      P[offset(1,i,3)] = true;
                      P[offset(1,i,4)] = true;
                      P[offset(1,i,5)] = true;
                      break;
      case '-'      : P[offset(1,i,12)] = P[offset(1,i,6)] = true; break;
      case '+'      : P[offset(1,i,24)] = true; break;
      case '*'      : P[offset(1,i,17)] = P[offset(1,i,21)] = true; break;
      case '/'      : P[offset(1,i,19)] = true; break;
      case '('      : P[offset(1,i,13)] = true; break;
      case ')'      : P[offset(1,i,15)] = true; break;
      case '.'      : P[offset(1,i,11)] = true; break;
      }
  }

  for (i = 2; i <= n; i++) {
    for (j = 1; j <= (n-i+1); j++) {
      for (k = 1; k <= (i-1); k++) {
          if(P[offset(k,j,24)] && P[offset(i-k,j+k,9)])  // Z -> WD
            P[offset(i,j,21)] = true;
          if(P[offset(k,j,21)] && P[offset(i-k,j+k,9)])  // Z -> ZD
            P[offset(i,j,21)] = true;
          if(P[offset(k,j,24)] && P[offset(i-k,j+k,9)])  // T -> WD
            P[offset(i,j,2)] = true;
          if(P[offset(k,j,21)] && P[offset(i-k,j+k,9)])  // T -> ZD
            P[offset(i,j,2)] = true;
          if(P[offset(k,j,24)] && P[offset(i-k,j+k,9)])  // F -> WD
            P[offset(i,j,3)] = true;
          if(P[offset(k,j,21)] && P[offset(i-k,j+k,9)])  // F -> ZD
            P[offset(i,j,3)] = true;
          if(P[offset(k,j,24)] && P[offset(i-k,j+k,9)])  // I -> WD
            P[offset(i,j,5)] = true;
          if(P[offset(k,j,21)] && P[offset(i-k,j+k,9)])  // I -> ZD
            P[offset(i,j,5)] = true;
          if(P[offset(k,j,1)] && P[offset(i-k,j+k,23)])  // E -> EV
            P[offset(i,j,1)] = true;
          if(P[offset(k,j,1)] && P[offset(i-k,j+k,25)])  // E -> EX
            P[offset(i,j,1)] = true;
          if(P[offset(k,j,1)] && P[offset(i-k,j+k,16)])  // E -> EK
            P[offset(i,j,1)] = true;
          if(P[offset(k,j,1)] && P[offset(i-k,j+k,18)])  // E -> EP
            P[offset(i,j,1)] = true;
          if(P[offset(k,j,1)] && P[offset(i-k,j+k,20)])  // E -> ES
            P[offset(i,j,1)] = true;
          if(P[offset(k,j,1)] && P[offset(i-k,j+k,22)])  // E -> EU
            P[offset(i,j,1)] = true;
          if(P[offset(k,j,13)] && P[offset(i-k,j+k,14)])  // E -> GH
            P[offset(i,j,1)] = true;
          if(P[offset(k,j,5)] && P[offset(i-k,j+k,9)])  // E -> ID
            P[offset(i,j,1)] = true;
          if(P[offset(k,j,6)] && P[offset(i-k,j+k,5)])  // E -> MI
            P[offset(i,j,1)] = true;
          if(P[offset(k,j,5)] && P[offset(i-k,j+k,10)])  // E -> IA
            P[offset(i,j,1)] = true;
          if(P[offset(k,j,24)] && P[offset(i-k,j+k,9)])  // E -> WD
            P[offset(i,j,1)] = true;
          if(P[offset(k,j,21)] && P[offset(i-k,j+k,9)])  // E -> ZD
            P[offset(i,j,1)] = true;
          if(P[offset(k,j,1)] && P[offset(i-k,j+k,16)])  // T -> EK
            P[offset(i,j,2)] = true;
          if(P[offset(k,j,1)] && P[offset(i-k,j+k,18)])  // T -> EP
            P[offset(i,j,2)] = true;
          if(P[offset(k,j,1)] && P[offset(i-k,j+k,20)])  // T -> ES
            P[offset(i,j,2)] = true;
          if(P[offset(k,j,1)] && P[offset(i-k,j+k,22)])  // T -> EU
            P[offset(i,j,2)] = true;
          if(P[offset(k,j,13)] && P[offset(i-k,j+k,14)])  // T -> GH
            P[offset(i,j,2)] = true;
          if(P[offset(k,j,5)] && P[offset(i-k,j+k,9)])  // T -> ID
            P[offset(i,j,2)] = true;
          if(P[offset(k,j,6)] && P[offset(i-k,j+k,5)])  // T -> MI
            P[offset(i,j,2)] = true;
          if(P[offset(k,j,5)] && P[offset(i-k,j+k,10)])  // T -> IA
            P[offset(i,j,2)] = true;
          if(P[offset(k,j,13)] && P[offset(i-k,j+k,14)])  // F -> GH
            P[offset(i,j,3)] = true;
          if(P[offset(k,j,5)] && P[offset(i-k,j+k,9)])  // F -> ID
            P[offset(i,j,3)] = true;
          if(P[offset(k,j,6)] && P[offset(i-k,j+k,5)])  // F -> MI
            P[offset(i,j,3)] = true;
          if(P[offset(k,j,5)] && P[offset(i-k,j+k,10)])  // F -> IA
            P[offset(i,j,3)] = true;
          if(P[offset(k,j,5)] && P[offset(i-k,j+k,9)])  // N -> ID
            P[offset(i,j,4)] = true;
          if(P[offset(k,j,6)] && P[offset(i-k,j+k,5)])  // N -> MI
            P[offset(i,j,4)] = true;
          if(P[offset(k,j,5)] && P[offset(i-k,j+k,10)])  // N -> IA
            P[offset(i,j,4)] = true;
          if(P[offset(k,j,24)] && P[offset(i-k,j+k,9)])  // N -> WD
            P[offset(i,j,4)] = true;
          if(P[offset(k,j,21)] && P[offset(i-k,j+k,9)])  // N -> ZD
            P[offset(i,j,4)] = true;
          if(P[offset(k,j,5)] && P[offset(i-k,j+k,9)])  // I -> ID
            P[offset(i,j,5)] = true;
          if(P[offset(k,j,6)] && P[offset(i-k,j+k,5)])  // I -> MI
            P[offset(i,j,5)] = true;
          if(P[offset(k,j,12)] && P[offset(i-k,j+k,6)])  // M -> CM
            P[offset(i,j,6)] = true;
          if(P[offset(k,j,5)] && P[offset(i-k,j+k,10)])  // L -> IA
            P[offset(i,j,7)] = true;
          if(P[offset(k,j,8)] && P[offset(i-k,j+k,9)])  // R -> RD
            P[offset(i,j,8)] = true;
          if(P[offset(k,j,11)] && P[offset(i-k,j+k,8)])  // A -> BR
            P[offset(i,j,10)] = true;
          if(P[offset(k,j,1)] && P[offset(i-k,j+k,15)])  // H -> EJ
            P[offset(i,j,14)] = true;
          if(P[offset(k,j,17)] && P[offset(i-k,j+k,3)])  // K -> OF
            P[offset(i,j,16)] = true;
          if(P[offset(k,j,19)] && P[offset(i-k,j+k,3)])  // P -> QF
            P[offset(i,j,18)] = true;
          if(P[offset(k,j,17)] && P[offset(i-k,j+k,1)])  // S -> OE
            P[offset(i,j,20)] = true;
          if(P[offset(k,j,19)] && P[offset(i-k,j+k,1)])  // U -> QE
            P[offset(i,j,22)] = true;
          if(P[offset(k,j,24)] && P[offset(i-k,j+k,2)])  // V -> WT
            P[offset(i,j,23)] = true;
          if(P[offset(k,j,12)] && P[offset(i-k,j+k,2)])  // X -> CT
            P[offset(i,j,25)] = true;
      }
    }
  }

  if(P[offset(n,1,1)]){
    evaluasi(lang);
  }else
    printf("SINTAK ERROR.\n");

  return 0;
}
