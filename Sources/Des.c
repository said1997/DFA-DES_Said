#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "../Header/DES_permutation.h"
#include "../Header/ScheduleKey.h"
#include "../Header/F_function.h"
#include "../Header/Tables_Of_Permutation.h"

long DES(uint64_t clair, uint64_t K)
{

	uint64_t Ki[16] = {0}; //Avoir les 16 sous-cles
	ScheduleKey(Ki, K);

	uint64_t clairIP = Permutation(clair, IP, 64, 64); //On fait la Permutation initiale IP

	//Pour Separer le bloc clair en deux blocs de 32 bits
	uint32_t L = (clairIP & 0xFFFFFFFF00000000L) >> 32;
	uint64_t R = clairIP & 0x00000000FFFFFFFFL;

	uint32_t LiPlus1, RiPlus1;
	// Les 16 tours de Feistel
	for (int i = 0; i < 16; i++)
	{
		LiPlus1 = R;
		RiPlus1 = L ^ f(R, Ki[i]);
		L = LiPlus1;
		R = RiPlus1;
	}

	//Inversion du dernier tour de fiestel
	return Permutation((R << 32) | L, IP_Inv, 64, 64);
}
