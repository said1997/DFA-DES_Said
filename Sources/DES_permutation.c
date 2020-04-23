#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*

 * long Permutation(long msg, int table[] ,int tailleBits_in, int tailleOfBits_out) 
 * c'est Fonction qui permet d'appliquer une Permutation avec le nombre d'éléments de table[] équivalent à tailleOfBits_out
 * param msg : message a permuter selon la table[]
 * param table[] : table d'entiers d'une Permutation
 * param tailleOfBits_in : le nombre de bits à l'entree de la permutation
 * param tailleOfBits_out :le nombre de bits à la sortie de la permutation
 * return res le resultat final de la permutation correspondante

 */

long Permutation(uint64_t msg, int table[] ,int tailleOfBits_in, int tailleOfBits_out) {
		
	long resultat = 0x0L;
	long bit_position = 0x1L;
	long tmp;
	

	for (int i = 0; i < tailleOfBits_out; i++) 
	{

		tmp = bit_position << (tailleOfBits_in - table[i]);
		
		//On charge le bit de msg à cette position table[i]
		tmp = msg & tmp;
		
		//si le bit vaut 1 on le laisse a la position actuelle 
		if (tmp != 0){
			//On met le bit a 1 dans sa position
			tmp = 0x1L;
			tmp = tmp << (tailleOfBits_out - i - 1);
		} 
		
		//melange le nouveau bit avec resultat
		resultat = resultat | tmp;
	}
	return resultat;
}
