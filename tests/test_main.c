#include <stdio.h>
#include <unistd.h>   // pour sbrk
#include <stdint.h>

int main(void) {
    void *before = sbrk(0);       // adresse actuelle de la fin du tas
    printf("Avant sbrk(0): %p\n", before);

    intptr_t increment = 4096;       // demander 4096 octets
    void *ret = sbrk(increment);     // retourne l'ancienne fin du tas
    if (ret == (void *) -1) {
        perror("sbrk failed");
        return 1;
    }

    printf("sbrk(%ld) a retourne : %p\n", (long)increment, ret);
    printf("Nouvelle fin du tas (sbrk(0)) : %p\n", sbrk(0));

    /* Visualisation : ret vaut l'adresse avant l'extension ;
       la nouvelle fin est ret + increment */
    printf("Verification: ret + increment = %p\n", (void *)((char *)ret + increment));
    return 0;
}
