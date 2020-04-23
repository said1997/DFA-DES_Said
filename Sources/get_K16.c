#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "../Header/DES_permutation.h"
#include "../Header/ScheduleKey.h"
#include "../Header/F_function.h"
#include "../Header/Tables_Of_Permutation.h"


//Cette fonction traite les resultat de la recherche exhaustive pour trouver le bon K16
uint64_t Calcul_true_K16(int Solution[8][6][64] , int Nbr_Solutions[8][6], int num_Sbox, uint64_t K16){

		int f;
	    int numSolf0 = 0;
		long candidat = (long) Solution[num_Sbox][0][numSolf0];
		
		for (f = 1; f < 6; f++)
		{
			int numSolf;
			for (numSolf = 0; numSolf < Nbr_Solutions[num_Sbox][f]; numSolf++)
				if (candidat == Solution[num_Sbox][f][numSolf])
					break;
			
			if (numSolf == Nbr_Solutions[num_Sbox][f]){
				if (numSolf0+1 >= Nbr_Solutions[num_Sbox][0]){
					printf("\nProblème Sbox %d faute %d pour trouver K16\n",num_Sbox,f);
					break;
				}
				f = 1;
				++numSolf0;
				candidat = (long) Solution[num_Sbox][0][numSolf0];
			}
		}
		printf("\nSolution S%d est : %lx \t \t |\t ",num_Sbox+1,candidat);
		K16 = K16 << 6;
		K16 = K16 | candidat;
		printf("K16 evolution : %lx\n",K16);

		return K16;
		
}
	
	

// Afficher la solution trouvée à la sortie de chaque S-box
void affiche_Solutin_SBox(int Nbr_Solutions[8][6], int Solution[8][6][64], int num_Sbox, long *chiffreFaux, int faux[8][6]){

		int f;
		int k;
	
	printf("\033[1m\033[34m\nResultat de recherche S-Box n°%d : \n\n\033[0m", num_Sbox+1);
		for (f = 0; f < 6; f++) 
		{
			for(k=0; k<32; k++){
				if(chiffreFaux[faux[num_Sbox][f]]==chiffreFaux[k])
					printf("Le chiffré faux n°%d : %d solutions\t",k+1, Nbr_Solutions[num_Sbox][f]);

			}
			for (int i = 0; i < Nbr_Solutions[num_Sbox][f]; i++) 
				printf("%x ", Solution[num_Sbox][f][i]);
			printf("\n"); 
		}

}

//Recherche exhaustive pour trouver la cle K16 sur 56 bits
uint64_t get_K16(uint64_t chiffreJuste, long chiffreFaux[]) 
{	
	int num_Sbox;
	int k16i;
	int f;
	int r, c, rf, cf;

	uint64_t K16,dechiffJuste,dechiffFaux;
	uint32_t L16, R15, L_f_16, R_f_15,verif;
	uint64_t E_R15, ER_f_15;
	uint32_t  tmp, tmpf;
	int num_chiffre_faux;
	
	
	//2^6 solutions possibles  des 6 fautes pour les 8 Sbox
	int Solution[8][6][64] = {{{0}}};
	//Nombre de solutions possibles pour 6 chiffres faux sur les 8 Sbox 
	int Nbr_Solutions[8][6] = {{0}};
	
	
	/*
		*On va attasue chaque S-box par 6 chiffrés faut donc il faut un total de 32 chiffres
		*Chaque attaque change qu'un seul bit de R15 
	*/	
	int faux[8][6] = {
		{0, 31, 30, 29, 28, 27},
		{28, 27, 26, 25, 24, 23},
		{24, 23, 22, 21, 20, 19},
		{20, 19, 18, 17, 16, 15},
		{16, 15, 14, 13, 12, 11},
		{12, 11, 10, 9, 8, 7},
		{8, 7, 6, 5, 4, 3},
		{4, 3, 2, 1, 0, 31}
	};
	
	//Calcule de L16 et R16 a partir d'un chiffre juste
	dechiffJuste = Permutation(chiffreJuste, IP, 64, 64); 
	L16 = (dechiffJuste >> 32) & 0xFFFFFFFFL; 
	// R16 = R15
	R15 = dechiffJuste & 0xFFFFFFFFL;	
	
	/*Recharche de la cle K16 par une recharche exhaustive a l'aide les 8 equation 
	 *chaque attaque va nous permettre de connaitre 8 bits de K16 l'aide de la func Calcul_true_K16
	*/
	for (num_Sbox = 0; num_Sbox < 8 ; num_Sbox++) 
	{	
		
		for (f = 0; f < 6 ; f++) 
		{
			//Attaque d'une S-Box par 6 chiffres faux

			dechiffFaux = Permutation(chiffreFaux[faux[num_Sbox][f]], IP, 64, 64);
			L_f_16 = (dechiffFaux >> 32) & 0xFFFFFFFFL; 
			R_f_15 = dechiffFaux & 0xFFFFFFFFL;
	
			// calcule des éléments de l'équation
			verif = Permutation(L16 ^ L_f_16, P_Inv, 32, 32);
			E_R15 = Permutation(R15, E, 32, 48); 
			ER_f_15 = Permutation(R_f_15, E, 32, 48);
			
			//recherche exhaustive de K16 sur 6 bits
			for (k16i = 0 ; k16i < 64 ; k16i++) 
			{
				//Valeurs de 6 bits qu'on va rentrer dans la Sbox numéro s puis vérifier avec les 4 bits corréspondants de verif
				tmp = ((E_R15 & get_6bits[num_Sbox]) >> ((7 - num_Sbox) * 6)) ^ k16i;
				tmpf = ((ER_f_15 & get_6bits[num_Sbox]) >> ((7 - num_Sbox) * 6)) ^ k16i;
				
				//Trouver numero de la ligne et de colonne de la S-Box
				r = 2 * ((tmp & 0x20) >> 5) + (tmp & 0x1);
				c = (tmp & 0x1E) >> 1;
				
				rf = 2 * ((tmpf & 0x20) >> 5) + (tmpf & 0x1);
				cf = (tmpf & 0x1E) >> 1;
				
				//On va Verfifier la k16i en on comparant les 4 bits de verifvcation avec les 4 bits du XOR de S-Box
				int PP = (verif & get_4bits[num_Sbox]) >> ((7 - num_Sbox) * 4);
				int SS = Sbox[num_Sbox][r][c] ^ Sbox[num_Sbox][rf][cf];
				
				if ( PP ==	SS ) 
				{	
					Solution[num_Sbox][f][Nbr_Solutions[num_Sbox][f]] = k16i;
					++Nbr_Solutions[num_Sbox][f];
				}
			}
		}
		
		//Affichage des solutions pour chaque faute de chaque Sbox
		affiche_Solutin_SBox(Nbr_Solutions,Solution,num_Sbox,chiffreFaux,faux);
		//Pour trouver la bonne cle K16
		K16=Calcul_true_K16(Solution, Nbr_Solutions,num_Sbox,K16);
	}
		return K16;

		
}