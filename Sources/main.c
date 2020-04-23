#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "../Header/get_K16.h"
#include "../Header/ScheduleKey.h"
#include "../Header/F_function.h"
#include "../Header/Mon_message.h"
#include "../Header/get_K.h"
#include "../Header/Des.h"

int main()
{
	//Recherche de la clé K16 avec les chiffrés faux donnés
	uint64_t K16 = get_K16(messageChiffreJuste, messagesChiffreFaux);
	printf("\n<----------------------------------------------------------------------------->\n\n");

	printf("Recherche de la Cle du chiffrement K :\n");
	printf("\033[1m\033[33m\n \tCle K16 trouvée avec succes : %lx. \n\033[0m", K16);

	//Recherche de la clé K sur 48 bits
	uint64_t K48 = get_K48(K16);
	printf("\033[1m\033[33m\n \tLa clé K sur 48 bits trouvée avec succes K48 : %lx. \n\033[0m", K48);

	//Recherche de la clé K de 64 bit
	uint64_t K = get_K(messageClair, messageChiffreJuste, K16);
	printf("\033[1m\033[33m\n \tClé K trouvée avec succes : %lx. \n\033[0m", K);

	printf("\n<----------------------------------------------------------------------------->\n\n");

	//Tester la clé K trouvée
	uint64_t testKey = DES(messageClair, K);
	printf("\tLe Message Chiffré donné est : %lx.\n", messageChiffreJuste);
	printf("\n \tLe Chiffré trouvé avec la clé K est : %lx.\n", testKey);

	if (messageChiffreJuste == testKey)
		printf("\033[1m\033[32m\n \tSucces test. \n\033[0m");
	else
		printf("\033[1m\033[33m\n \tFailed test. \n\033[0m");

	printf("\n<----------------------------------------------------------------------------->\n\n");

	return 0;
}
