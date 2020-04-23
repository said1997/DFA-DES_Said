#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "../Header/Des.h"
#include "../Header/DES_permutation.h"
#include "../Header/ScheduleKey.h"
#include "../Header/F_function.h"
#include "../Header/Tables_Of_Permutation.h"

uint64_t get_K48(uint64_t K16)
{

	/*
	 *On remet les 48 bits de K16 à la bonne position pour K 
	 *On passe de 48 à 56 bits avec 8 bits faux,On applique l'inverse de PC2. 
	 *On sauvegarde la position des bits faux.
	 *On passe de 56 à 64 bits avec 8 autres bits de parité faux,en appliquant l'inverse de PC1
	 *changement de position pour de 8 bits perdus par PC2
	 */
	uint64_t K48 = Permutation(Permutation(K16, PC2_Inv, 48, 56), PC1_Inv, 56, 64);
	return K48;
}

uint64_t get_K56(uint64_t clair, uint64_t chiffre, uint64_t K16)
{
	/*
	 *Attaque par recherche exhaustive sur les 8 bits perdus manquants de K avec à l'aide de DES
	 *Recuperer les bits perdus par PC1_Inv(PC2_Inv) dans K48, avec leur position : pos[]
	 *Les 8 bits de parite n'interviennent pas dans le DES
	*/

	uint64_t K48 = get_K48(K16);
	long MASK = 0x00L;
	uint64_t K_test = K48;

	//Tables pour differents positions des bits a charcher
	long pos[] = {14, 15, 19, 20, 51, 54, 58, 60};

	//On va tester toutes les possibilités pour les valeurs des 8 bits perdus dans les positions sauvegardées, donc 256 possibiliés
	while (MASK < 256 && chiffre != DES(clair, K_test))
	{
		//Pour retrouver les bits a 0 qu'on a perdu
		long res = 0x0L;

		for (int i = 0; i < 8; i++)
			res = res | (((MASK >> i) & 1) << (64 - pos[i]));
		K_test = K48 | res;
		MASK = MASK + 1;
	}
	//si on arrive pas a trouver la cle K apre le test de 256 pissibilites
	if (MASK == 256)
		printf("\nimpossible de trouver K 56 bits apres le test des 256 possibilites\n");

	return K_test;
}

long bitsParite(long K56)
{
	long res = K56;
	long tmp, parite;

	for (int i = 0; i < 8; i++)
	{
		parite = 0;
		for (int j = 0; j < 8; j++)
		{
			if (j != 7)
			{
				tmp = 0x1L << (((7 - i) * 8) + (7 - j));
				tmp = K56 & tmp;
				parite = tmp ? parite ^ 1 : parite ^ 0;
			}
			else
			{
				tmp = !parite;
				res |= tmp << ((7 - i) * 8);
			}
		}
	}
	return res;
}

uint64_t get_K(uint64_t clair, uint64_t chiffre, uint64_t K16)
{
	//Retrouver les 56 bits de K a partir de K16 i.e les 8 bits manquant
	uint64_t K56 = get_K56(clair, chiffre, K16);
	//Calcul des 8 bits de parite restants
	uint64_t K64 = bitsParite(K56);

	return K64;
}
