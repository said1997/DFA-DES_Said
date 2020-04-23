#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "../Header/DES_permutation.h"
#include "../Header/Tables_Of_Permutation.h"
#include "../Header/bits_manip.h"

//Rotation à gauche des bits de chaque moitié de K56
long Rotation_Gauche(long K56)
{
	uint64_t C28, D28;
	uint64_t test;

	C28 = ShiftDroit(AND_Binary(K56, 0xFFFFFFF0000000), 28);
	D28 = AND_Binary(K56, 0xFFFFFFF);
	//On prend le bit le plus a droite
	test = ShiftDroit(C28, 27);
	//Décalage des bits à gauche
	C28 = ShiftGauche(C28, 1);
	//On elnleve le bit de poids fort
	C28 = AND_Binary(C28, 0xFFFFFFF);
	C28 = concat(C28, test);
	//Choix du bit le plus à droite
	test = ShiftDroit(D28, 27);
	//Décalage des bits à gauche
	D28 = ShiftGauche(D28, 1);
	//Suppression du bit de poids fort
	D28 = AND_Binary(D28, 0xFFFFFFF);
	//Mis à la position voulue
	D28 = concat(D28, test);

	C28 = ShiftGauche(C28, 28);

	return AND_Binary(concat(C28, D28), 0xFFFFFFFFFFFFFF);
}

void ScheduleKey(uint64_t Ki[], uint64_t K)
{
	// Nombre de permutations à effectuer
	int v[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

	// Division de K en deux entités de 28 bits (C et D sont les deux moitiés de T)
	long T = Permutation(K, PC1, 64, 56);

	for (int i = 0; i < 16; i++)
	{
		if (v[i] == 1)
			T = Rotation_Gauche(T);
		else
			T = Rotation_Gauche(Rotation_Gauche(T));

		Ki[i] = Permutation(T, PC2, 56, 48);
	}
}
