L’attaque par fautes contre le DES permet d’obtenir la clé de chiffrement d’un message chiffré.

Ici on suppose que l’attaquant dispose d’une implémentation de DES, d’un message clair, d’un
message chiffré ainsi qu’un ensemble de 32 de messages chiffrés faux obtenus grâce à un single bit flip sur R 15 du
15ème tour de fiestel , cela veut dire que l’attaquant doit changer un seul bit parmi les 32 bits de R 15.

-Pour compiler l'application taper dans le términal make.

-Pour l'ancer l'attaque taper dans le términal make run.

-Pour supprimer tout les dépendance taper make clean.
