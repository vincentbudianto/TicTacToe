/* NIM/Nama  : 13517137/Vincent Budianto
 * Nama file : TicTacToe.c
 * Topik     : Tugas Besar I IF2220 - Teori Bahasa Formal dan Otomata (TBFO)
 * Tanggal   : 04 Oktober 2018
 * Deskripsi : Source code aplikasi permainan "Tic Tac Toe" dengan menggunakan Finite Automata */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TicTacToe.h"

//KAMUS UMUM
Dstate rec;
Dstate S;
Fstate Fs;
symbol a;
TabTransisi T;

void ConvertSM (Matriks *M, Dstate R, int c);
/* Mengubah isi matriks sesuai state saat itu */
void TulisMatrix (Matriks M);
/* I.S. M terdefinisi */
/* F.S. Nilai M(i,j) ditulis ke layar per baris per kolom menggunakan model papan TicTacToe */
/* Proses: Menulis nilai setiap elemen M ke layar dengan traversal per baris dan per kolom */
/* Contoh:
 - | - | - 		 O | X | O 		 X | O | X 
-----------		-----------		-----------
 - | - | - 		 X | X | O 		 X | O | O 
-----------		-----------		-----------
 - | - | - 		 X | O | X 		 O | X | O 
*/
boolean IsFull (Matriks M);
/* Mengirimkan true jika matriks penuh */
boolean IsCPUWin (Matriks M);
/* Mengirimkan true jika CPU yang menang */
boolean IsPlayerWin (Matriks M);
/* Mengirimkan true jika Player yang menang */

//PROGRAM UTAMA
int main()
{
	//KAMUS
	boolean		cek, found;
	char		x, output[255];
	int 		count, i, j, k, l, y;
	Matriks		M;
	
	//ALGORITMA
	//Tampilan Judul
	printf("|---------------------------------------------|\n");
	printf("|---------------- Tic Tac Toe ----------------|\n");
	printf("|---------------------------------------------|\n");
	printf("\n");
	printf("\n");
	printf("\n");
	count = 0;
	
	//Input Siapa Mulai Duluan
	printf("------ Apakah Anda ingin mulai duluan? --------\n");
	printf("----- ketik 'y' jika ya || 'n' jika tidak -----\n");
	printf(">> "); scanf("%c", &x);
	while ((x != 'y') && (x != 'n'))
	{
		printf("------ Input salah silahkan coba kembali ------\n");
		printf(">> "); scanf("%c", &x);
	}
	
	if (x == 'y')
	{
		goto LoadPlayer;
	}
	else if (x == 'n')
	{
		goto LoadCPU;
	}
	
LoadPlayer:
{
	FILE *F = fopen("StatePlayer.txt", "r");
	if (F == NULL)
	{
		printf("--- File 'StatePlayer.txt' tidak ditemukan ---\n");
		return 0;
	}
	else
	{
		while (fgets(output, sizeof(output), F) != NULL)
		{
			const char data1[20] = "DAFTAR STATE\n";
			const char data2[20] = "DAFTAR SIMBOL\n";
			const char data3[20] = "STATE AWAL\n";
			const char data4[20] = "STATE AKHIR\n";
			const char data5[20] = "TRANSITION FUNCTION\n";
			
			//DAFTAR STATE
			if (strcmp(output, data1) == 0)
			{
				S.Neff = 0;
				while (strcmp(fgets(output, sizeof(output), F), "\n") != 0)
				{
					const char* string = strtok(output, "\t\n");
					string = strtok(NULL, "\t\n");
					strcpy(S.q[S.Neff].o, output);
					strcpy(S.q[S.Neff].st, string);
					/*printf ("%s : %s\n", S.q[S.Neff].o, S.q[S.Neff].st);*/
					S.Neff += 1;
				}
				/*printf("\n");*/
			}
			
			//DAFTAR SIMBOL
			if (strcmp(output, data2) == 0)
			{
				while (strcmp(fgets(output, sizeof(output), F), "\n") != 0)
				{
					strcpy(a.simbol, output);
					/*printf("CPU : %c\n", a.simbol[1]);
					printf("Player : %c\n", a.simbol[0]);*/
				}
				/*printf("\n");*/
			}
			
			//STATE AWAL
			if (strcmp(output, data3) == 0)
			{
				rec.Neff = 0;
				while (strcmp(fgets(output, sizeof(output), F), "\n") != 0)
				{
					strtok(output, "\t\n");
					const char* isi = strtok(NULL, "\t\n");
					strcpy(rec.q[rec.Neff].o, output);
					strcpy (rec.q[rec.Neff].st, isi);
					/*printf("State Awal (%s) : %s\n", rec.q[rec.Neff].o, rec.q[rec.Neff].st);*/
					rec.Neff += 1;
				}
				/*printf("\n");*/
			}
			
			//STATE AKHIR
			if (strcmp(output, data4) == 0)
			{
				Fs.Neff = 0;
				while (strcmp(fgets(output, sizeof(output), F), "\n") != 0)
				{
					strtok (output, "q\t\n");
					const char* condition = strtok (NULL, "q\t\n");
					strcpy(Fs.fs[Fs.Neff].n, output);
					strcpy(Fs.fs[Fs.Neff].cond, condition);
					/*printf("%s :	%s\n", Fs.fs[Fs.Neff].n, Fs.fs[Fs.Neff].cond);*/
					Fs.Neff += 1;
				}
				/*printf("\n");*/
			}
			
			//TRANSITION FUNCTION
			if (strcmp(output, data5) == 0)
			{
				T.Neff = 0;
				do
				{
					fgets(output, sizeof(output), F);
					strtok (output, "\t\n");
					const char* input1 = strtok (NULL, "\t\n");
					const char* input2 = strtok (NULL, "\t\n");
					const char* input3 = strtok (NULL, "\t\n");
					const char* input4 = strtok (NULL, "\t\n");
					const char* input5 = strtok (NULL, "\t\n");
					const char* input6 = strtok (NULL, "\t\n");
					const char* input7 = strtok (NULL, "\t\n");
					const char* input8 = strtok (NULL, "\t\n");
					const char* input9 = strtok (NULL, "\t\n");
					strcpy(T.TT[T.Neff].Input[0].HI, output);
					strcpy(T.TT[T.Neff].Input[1].HI, input1);
					strcpy(T.TT[T.Neff].Input[2].HI, input2);
					strcpy(T.TT[T.Neff].Input[3].HI, input3);
					strcpy(T.TT[T.Neff].Input[4].HI, input4);
					strcpy(T.TT[T.Neff].Input[5].HI, input5);
					strcpy(T.TT[T.Neff].Input[6].HI, input6);
					strcpy(T.TT[T.Neff].Input[7].HI, input7);
					strcpy(T.TT[T.Neff].Input[8].HI, input8);
					strcpy(T.TT[T.Neff].Input[9].HI, input9);
					/*printf("%s :", T.TT[T.Neff].Input[0].HI);
					for (i = 1; i <= 9; i++)
					{
						printf("	Input[%d](%s)", i, T.TT[T.Neff].Input[i].HI);
					}
					printf("\n");*/
					T.Neff += 1;
				}
				while (T.Neff < S.Neff);
				/*printf("\n");*/
			}
		}
		fclose(F);
	}
	printf("|                                             |\n");
	printf("|------------   Karakter CPU : %c  ------------|\n", a.simbol[1]);
	printf("|------------ Karakter Player : %c ------------|\n", a.simbol[0]);
	printf("|                                             |\n");
	ConvertSM(&M, rec, count);
	TulisMatrix(M);
	printf("Masukan posisi : \n");
	printf(">> "); scanf("%d", &y);
	while (y != 5)
	{
		printf("---Posisi Invalid---\n");
		printf("Masukan posisi : \n");
		printf(">> "); scanf("%d", &y);
	}
	i = 0;
	j = 0;
	found = false;
	while ((i < T.Neff) && (!found))
	{
		if (strcmp(T.TT[i].Input[0].HI, rec.q[count].o) == 0)
		{
			count += 1;
			strcpy(rec.q[count].o, T.TT[i].Input[y].HI);
			while ((j < S.Neff) && (!found))
			{
				if (strcmp(S.q[j].o, rec.q[count].o) == 0)
				{
					found = true;
					strcpy(rec.q[count].st, S.q[j].st);
				}
				else
				{			
					j++;
				}
			}
		}
		else
		{
			i++;
		}
	}
	ConvertSM(&M, rec, count);
	TulisMatrix(M);
	goto Play;
}

LoadCPU:
{
	FILE *F = fopen("StateCPU.txt", "r");
	if (F == NULL)
	{
		printf("--- File 'StateCPU.txt' tidak ditemukan ---\n");
		return 0;
	}
	else
	{
		while (fgets(output, sizeof(output), F) != NULL)
		{
			const char data1[20] = "DAFTAR STATE\n";
			const char data2[20] = "DAFTAR SIMBOL\n";
			const char data3[20] = "STATE AWAL\n";
			const char data4[20] = "STATE AKHIR\n";
			const char data5[20] = "TRANSITION FUNCTION\n";
			
			//DAFTAR STATE
			if (strcmp(output, data1) == 0)
			{
				S.Neff = 0;
				while (strcmp(fgets(output, sizeof(output), F), "\n") != 0)
				{
					const char* string = strtok(output, "\t\n");
					string = strtok(NULL, "\t\n");
					strcpy(S.q[S.Neff].o, output);
					strcpy(S.q[S.Neff].st, string);
					/*printf ("%s : %s\n", S.q[S.Neff].o, S.q[S.Neff].st);*/
					S.Neff += 1;
				}
				/*printf("\n");*/
			}
			
			//DAFTAR SIMBOL
			if (strcmp(output, data2) == 0)
			{
				while (strcmp(fgets(output, sizeof(output), F), "\n") != 0)
				{
					strcpy(a.simbol, output);
					/*printf("CPU : %c\n", a.simbol[1]);
					printf("Player : %c\n", a.simbol[0]);*/
				}
				/*printf("\n");*/
			}
			
			//STATE AWAL
			if (strcmp(output, data3) == 0)
			{
				rec.Neff = 0;
				while (strcmp(fgets(output, sizeof(output), F), "\n") != 0)
				{
					strtok(output, "\t\n");
					const char* isi = strtok(NULL, "\t\n");
					strcpy(rec.q[rec.Neff].o, output);
					strcpy (rec.q[rec.Neff].st, isi);
					/*printf("State Awal (%s) : %s\n", rec.q[rec.Neff].o, rec.q[rec.Neff].st);*/
					rec.Neff += 1;
				}
				/*printf("\n");*/
			}
			
			//STATE AKHIR
			if (strcmp(output, data4) == 0)
			{
				Fs.Neff = 0;
				while (strcmp(fgets(output, sizeof(output), F), "\n") != 0)
				{
					strtok (output, "q\t\n");
					const char* condition = strtok (NULL, "q\t\n");
					strcpy(Fs.fs[Fs.Neff].n, output);
					strcpy(Fs.fs[Fs.Neff].cond, condition);
					/*printf("%s :	%s\n", Fs.fs[Fs.Neff].n, Fs.fs[Fs.Neff].cond);*/
					Fs.Neff += 1;
				}
				/*printf("\n");*/
			}
			
			//TRANSITION FUNCTION
			if (strcmp(output, data5) == 0)
			{
				T.Neff = 0;
				do
				{
					fgets(output, sizeof(output), F);
					strtok (output, "\t\n");
					const char* input1 = strtok (NULL, "\t\n");
					const char* input2 = strtok (NULL, "\t\n");
					const char* input3 = strtok (NULL, "\t\n");
					const char* input4 = strtok (NULL, "\t\n");
					const char* input5 = strtok (NULL, "\t\n");
					const char* input6 = strtok (NULL, "\t\n");
					const char* input7 = strtok (NULL, "\t\n");
					const char* input8 = strtok (NULL, "\t\n");
					const char* input9 = strtok (NULL, "\t\n");
					strcpy(T.TT[T.Neff].Input[0].HI, output);
					strcpy(T.TT[T.Neff].Input[1].HI, input1);
					strcpy(T.TT[T.Neff].Input[2].HI, input2);
					strcpy(T.TT[T.Neff].Input[3].HI, input3);
					strcpy(T.TT[T.Neff].Input[4].HI, input4);
					strcpy(T.TT[T.Neff].Input[5].HI, input5);
					strcpy(T.TT[T.Neff].Input[6].HI, input6);
					strcpy(T.TT[T.Neff].Input[7].HI, input7);
					strcpy(T.TT[T.Neff].Input[8].HI, input8);
					strcpy(T.TT[T.Neff].Input[9].HI, input9);
					/*printf("%s :", T.TT[T.Neff].Input[0].HI);
					for (i = 1; i <= 9; i++)
					{
						printf("	Input[%d](%s)", i, T.TT[T.Neff].Input[i].HI);
					}
					printf("\n");*/
					T.Neff += 1;
				}
				while (T.Neff < S.Neff);
				/*printf("\n");*/
			}
		}
		fclose(F);
	}
	printf("|                                             |\n");
	printf("|------------   Karakter CPU : %c  ------------|\n", a.simbol[0]);
	printf("|------------ Karakter Player : %c ------------|\n", a.simbol[1]);
	printf("|                                             |\n");
	ConvertSM(&M, rec, count);
	TulisMatrix(M);
	goto Play;
}

Play:
{
	printf("Masukan posisi : \n");
	printf(">> "); scanf("%d", &y);
	i = 0;
	j = 0;
	k = 0;
	cek = false;
	found = false;
	
	printf("|                                             |\n");
	printf("|--------------- Giliran ke-%d ----------------|\n", count);
	printf("|                                             |\n");
	while ((i < T.Neff) && (!found))
	{
		if (strcmp(T.TT[i].Input[0].HI, rec.q[count].o) == 0)
		{
			count += 1;
			strcpy(rec.q[count].o, T.TT[i].Input[y].HI);
			while ((j < S.Neff) && (!found))
			{
				if (strcmp(S.q[j].o, rec.q[count].o) == 0)
				{
					found = true;
					strcpy(rec.q[count].st, S.q[j].st);
				}
				else
				{			
					j++;
				}
			}
		}
		else
		{
			i++;
		}
	}
	ConvertSM(&M, rec, count);
	TulisMatrix(M);
	printf("|---------------------------------------------|\n");
	
	while ((k < Fs.Neff) && (!cek))
	{
		if (strcmp(Fs.fs[k].n, rec.q[count].o) == 0)
		{
			cek = true;
		}
		else
		{
			k++;
		}
	}
	
	if (!cek)
	{
		goto Play;
	}
	else
	{
		printf("CPU %s\n", Fs.fs[k].cond);
		goto ShowRecord;
	}
}

ShowRecord:
{
	printf("|---------------------------------------------|\n");
	printf("|------------- RECORD  PERMAINAN -------------|\n");
	printf("|---------------------------------------------|\n");
	for (l = 1; l <= count; l++)
	{
		printf("input%d ----> %s\n", l, rec.q[l].o);
	}
	printf("|---------------------------------------------|\n");
}

	return 0;
}


//Realisasi Fungsi + Prosedur
void ConvertSM (Matriks *M, Dstate R, int c)
{
	//KAMUS LOKAL
	
	//ALGORITMA FUNCTION/PROCEDURE
	Elmt(*M, 0, 0) = R.q[c].st[0];
	Elmt(*M, 0, 1) = R.q[c].st[1];
	Elmt(*M, 0, 2) = R.q[c].st[2];
	Elmt(*M, 1, 0) = R.q[c].st[3];
	Elmt(*M, 1, 1) = R.q[c].st[4];
	Elmt(*M, 1, 2) = R.q[c].st[5];
	Elmt(*M, 2, 0) = R.q[c].st[6];
	Elmt(*M, 2, 1) = R.q[c].st[7];
	Elmt(*M, 2, 2) = R.q[c].st[8];
}

void TulisMatrix (Matriks M)
{
 	//KAMUS LOKAL
	int i, j;

 	//ALGORITMA
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			printf(" %c", Elmt(M, i, j));
			if (j != 2)
			{
				printf(" |");
			}
		}
		printf("\n");
		if (i != 2)
		{
			printf("---|---|---\n");
		}
	}
}

boolean IsFull (Matriks M)
{
 	//KAMUS LOKAL
	boolean 	cek;
	int			i, j;

 	//ALGORITMA
 	cek = true;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (Elmt(M, i, j) == '-')
			{
				cek = false;
			}
		}
	}
	return (cek);
}

boolean IsCPUWin (Matriks M)
{
	//KAMUS LOKAL
	boolean cek;
	int i, j;
	
	//ALGORITMA
	cek = false;
	for(i = 0; i < 3; i++)
	{
		if ((Elmt(M, i, 0) == 'O') && (Elmt(M, i, 0) == Elmt(M, i, 1)) && (Elmt(M, i, 1) == Elmt(M, i, 2)))
		{
			cek = true;
		}
	}
	for (j = 0; j < 3; j++)
	{
		if ((Elmt(M, 0, j) == 'O') && (Elmt(M, 0, j) == Elmt(M, 1, j)) && (Elmt(M, 1, j) == Elmt(M, 2, j)))
		{
			cek = true;
		}
	}
	if ((Elmt(M, 1, 1) == 'O') && (((Elmt(M, 0, 0) == Elmt(M, 1, 1)) && (Elmt(M, 1, 1) == Elmt(M, 2, 2))) || ((Elmt(M, 0, 2) == Elmt(M, 1, 1)) && (Elmt(M, 1, 1) == Elmt(M, 2, 0)))))
	{
		cek = true;
	}
	return (cek);
}

boolean IsPlayerWin (Matriks M)
{
	//KAMUS LOKAL
	boolean		cek;
	int			i, j;
	
	//ALGORITMA
	cek = false;
	for (i = 0; i < 3; i++)
	{
		if ((Elmt(M, i, 0) == 'X') && (Elmt(M, i, 0) == Elmt(M, i, 1)) && (Elmt(M, i, 1) == Elmt(M, i, 2)))
		{
			cek = true;
		}
	}
	for (j = 0; j < 3; j++)
	{
		if ((Elmt(M, 0, j) == 'X') && (Elmt(M, 0, j) == Elmt(M, 1, j)) && (Elmt(M, 1, j) == Elmt(M, 2, j)))
		{
			cek = true;
		}
	}
	if ((Elmt(M, 1, 1) == 'X') && (((Elmt(M, 0, 0) == Elmt(M, 1, 1)) && (Elmt(M, 1, 1) == Elmt(M, 2, 2))) || ((Elmt(M, 0, 2) == Elmt(M, 1, 1)) && (Elmt(M, 1, 1) == Elmt(M, 2, 0)))))
	{
		cek = true;
	}
	return (cek);
}
