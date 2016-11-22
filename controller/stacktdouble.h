/* File : DDStackt.h */
/* deklarasi DStack yang diimplementasi dengan tabel kontigu dan ukuran sama */
/* TOP adalah alamat elemen puncak */
/* Implementasi dalam bahasa C dengan alokasi statik */
#ifndef STACKTDOUBLE_H
#define STACKTDOUBLE_H

#include "boolean.h"
#include "stackt.h"
// #define Nil 0
// #define DMaxEl 20
// //
// #define T 991 	//  +
// #define M 992		//  -
// #define K 993		//  *
// #define B 994		//  /
// #define L 995		//  (
// #define R 996		//  )
//

/* Nil adalah DStack dengan elemen kosong . */
/* Karena indeks dalam bhs C dimulai 0 maka tabel dg indeks 0 tidak dipakai */

typedef double Dinfotype;
typedef int Daddress;   /* indeks tabel */

/* Contoh deklarasi variabel bertype DStack dengan ciri TOP : */
/* Versi I : dengan menyimpan tabel dan alamat top secara eksplisit*/
typedef struct {
	Dinfotype T[MaxEl+1]; /* tabel penyimpan elemen */
	Daddress TOP;  /* alamat TOP: elemen puncak */
}DStack;
/* Definisi DStack S kosong : S.TOP = Nil */
/* Elemen yang dipakai menyimpan nilai DStack T[1]..T[MaxEl] */
/* Jika S adalah DStack maka akses elemen : */
   /* S.T[(S.TOP)] untuk mengakses elemen TOP */
   /* S.TOP adalah alamat elemen TOP */

/* Definisi akses dengan Selektor : Set dan Get */
#define DTop(S) (S).TOP
#define DInfoTop(S) (S).T[(S).TOP]

/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void DCreateEmpty (DStack *S);
/* I.S. sembarang; */
/* F.S. Membuat sebuah DStack S yang kosong berkapasitas MaxEl */
/* jadi indeksnya antara 1.. MaxEl+1 karena 0 tidak dipakai */
/* Ciri DStack kosong : TOP bernilai Nil */

/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean DIsEmpty (DStack S);
/* Mengirim true jika DStack kosong: lihat definisi di atas */
boolean DIsFull (DStack S);
/* Mengirim true jika tabel penampung nilai elemen DStack penuh */

/* ************ Menambahkan sebuah elemen ke DStack ************ */
void DPush (DStack * S, Dinfotype X);
/* Menambahkan X sebagai elemen DStack S. */
/* I.S. S mungkin kosong, tabel penampung elemen DStack TIDAK penuh */
/* F.S. X menjadi TOP yang baru,TOP bertambah 1 */

/* ************ Menghapus sebuah elemen DStack ************ */
void DPop (DStack * S, Dinfotype* X);
/* Menghapus X dari DStack S. */
/* I.S. S  tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */

#endif
