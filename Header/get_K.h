#ifndef get_K_H
#define get_K_H

// Retourne la cle de 64 bits K du DES en prenant le param le clai le chiffre et k16

uint64_t get_K(uint64_t, uint64_t, uint64_t);
uint64_t get_K56(uint64_t, uint64_t, uint64_t);
uint64_t get_K48(uint64_t);

#endif
