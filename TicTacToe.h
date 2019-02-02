/* NIM/Nama  : 13517137/Vincent Budianto
 * Nama file : TicTacToe.h
 * Topik     : Tugas Besar I IF2220 - Teori Bahasa Formal dan Otomata (TBFO)
 * Tanggal   : 04 Oktober 2018
 * Deskripsi : Definisi aplikasi permainan "Tic Tac Toe" dengan menggunakan Finite Automata */

#ifndef Tic_Tac_Toe_H
#define Tic_Tac_Toe_H

/* ********** Definisi TYPE Boolean ********** */
#define boolean unsigned char
#define true 1
#define false 0

/* ********** Definisi TYPE State ********** */
typedef struct {
	char o[5];
	char st[10];
} state;

/* ********** Definisi TYPE Dstate ********** */
typedef struct {
	int Neff;
	state q[150];
} Dstate;

/* ********** Definisi TYPE Symbol ********** */
typedef struct {
	char simbol[2];
} symbol;

/* ********** Definisi TYPE Statea ********** */
typedef struct {
	char n[5];
	char cond[5];
} statea;

/* ********** Definisi TYPE Fstate ********** */
typedef struct {
	int Neff;
	statea fs[100];
} Fstate;

/* ********** Definisi TYPE HInput ********** */
typedef struct {
	char HI[5];
} HInput;

/* ********** Definisi TYPE Transisi ********** */
typedef struct {
	HInput Input[10];
} Transisi;

/* ********** Definisi TYPE TabFunction ********** */
typedef struct {
	int Neff;
	Transisi TT[149];
} TabTransisi;

/* ********** Definisi TYPE Matriks ********** */
typedef struct { 
	char E[3][3];
} Matriks;

#define Elmt(M, i, j)			(M).E[(i)][(j)]

//KAMUS UMUM
extern Dstate rec;
extern Dstate S;
extern Fstate Fs;
extern symbol a;
extern TabTransisi T;

#endif
