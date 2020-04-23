#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "../Header/DES_permutation.h"
#include "../Header/F_function.h"
#include "../Header/Tables_Of_Permutation.h"
#include "../Header/bits_manip.h"


 /* 
 *  long f(long R, long K_i) 
 *  Fonction qui permet de simuler la fonction f du DES
 *  param R :  partie R du msg
 *  param K_i : sous cle
 *  return un message sur 48 bits
 */
uint64_t f(uint64_t R, uint64_t K_i) 
{
	long Sbox_in;
	long Sbox_out=0x0;
	long expansion;
	long ligne,colonne;
	long bloc_6bits;// Decoupage 6 bits pour entréee des SBOX
	
	expansion = Permutation(R,E,32,48);// Expansion de R
	
	Sbox_in = OR_exclusif(expansion,K_i);
	
	for (int i=0;i<8;i++)
	{	
		//Recuperation des 6bits pour chaque S-Box
		bloc_6bits = ShiftDroit(Sbox_in,AND_Binary((48 - 6 - i*6),0x3F));
		
		//Calcul Ligne S-Box
		ligne = calcul_lignes_SBOX(bloc_6bits);
		//Calcul Colonne S-Box
		colonne = calcul_col_SBOX(bloc_6bits);
		//Concatener les sorties de chaque S-Box
		Sbox_out = concat(Sbox_out,ShiftGauche(Sbox[i][ligne][colonne],(32 - 4 - i*4)));
	}
	
	return Permutation(Sbox_out,P,32,32);
}
