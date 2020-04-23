#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "../Header/bits_manip.h"
#include "../Header/Tables_Of_Permutation.h"

// Cette fonction permet de shifter à droite de b decalage
uint64_t ShiftDroit(uint64_t msg, int b)
{
	return (msg >> b);
}

//Cette fonction permet de shifter à gauche de b decalage
uint64_t ShiftGauche(uint64_t msg, int b)
{
	return (msg << b);
}

//Cette fonction permet d'appliquer un ET binaire entre a et b
uint64_t AND_Binary(uint64_t a, uint64_t b)
{
	return (a & b);
}

// Fonction qui permet de concatener
uint64_t concat(uint64_t a, uint64_t b)
{
	return (a | b);
}

//Fonction qui fait un OR exclusif
uint64_t OR_exclusif(uint64_t a, uint64_t b)
{
	return (a ^ b);
}

//Calculer la valeur de la colonne et la retourner
int calcul_col_SBOX(int bloc6bits)
{
	return ((bloc6bits & 0x1E) >> 1);
}

//Calculer la valeur de ligne et la retourner
int calcul_lignes_SBOX(int bloc6bits)
{
	return (2 * ((bloc6bits & 0x20) >> 5) + (bloc6bits & 0x1));
}