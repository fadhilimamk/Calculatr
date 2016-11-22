/* File : DStackt.h */
/* deklarasi DStack yang diimplementasi dengan tabel kontigu dan ukuran sama */
/* DTop adalah alamat elemen puncak */
/* Implementasi dalam bahasa C dengan alokasi statik */

#include "boolean.h"
#include "stacktdouble.h"


/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void DCreateEmpty (DStack *S){
	DTop(*S) = Nil;
}
/* I.S. sembarang; */
/* F.S. Membuat sebuah DStack S yang kosong berkapasitas MaxEl */
/* jadi indeksnya antara 1.. MaxEl+1 karena 0 tidak dipakai */
/* Ciri DStack kosong : DTop bernilai Nil */

/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean DIsEmpty (DStack S){
	return (DTop(S) == Nil);
}
/* Mengirim true jika DStack kosong: lihat definisi di atas */
boolean DIsFull (DStack S){
	return (DTop(S) == MaxEl);
}
/* Mengirim true jika tabel penampung nilai elemen DStack penuh */

/* ************ Menambahkan sebuah elemen ke DStack ************ */
void DPush (DStack * S, Dinfotype X){
	DTop(*S)++;
	DInfoTop(*S) = X;
}
/* Menambahkan X sebagai elemen DStack S. */
/* I.S. S mungkin kosong, tabel penampung elemen DStack TIDAK penuh */
/* F.S. X menjadi DTop yang baru,DTop bertambah 1 */

/* ************ Menghapus sebuah elemen DStack ************ */
void DPop (DStack * S, Dinfotype* X){
	*X = InfoTop(*S);
	DTop(*S)--;
}
/* Menghapus X dari DStack S. */
/* I.S. S  tidak mungkin kosong */
/* F.S. X adalah nilai elemen DTop yang lama, DTop berkurang 1 */
