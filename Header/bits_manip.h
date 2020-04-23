#ifndef bits_manip_H
#define bits_manip_H


//Fichier contenant les différentes fonctions communes aux autres fichiers


uint64_t ShiftDroit(uint64_t a, int b);

uint64_t ShiftGauche(uint64_t a, int b);
 
uint64_t concat(uint64_t a,uint64_t b);

uint64_t OR_exclusif(uint64_t a,uint64_t b);

uint64_t AND_Binary(uint64_t a,uint64_t b);

int calcul_col_SBOX(int bloc6bits);

int calcul_lignes_SBOX(int bloc6bits);


#endif
