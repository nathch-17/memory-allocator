#include <stdio.h>
#include <stdlib.h>
#include <my_malloc.h>

/*fonction print_heap qui parcourt tout les blocs et affiche
 * adresse du blocs
 * inUSe ou libre
 * length
 * pointeurs prev/next*/

void print_heap() {
    my_stats* info = get_global_info();
    area* courant = (area*)(info + 1);
    int total_blocks = info->amount_of_blocks;

    printf("\n");
    printf("╔══════════════════════════════════════╗\n");
    printf("║         ÉTAT DU TAS (HEAP)           ║\n");
    printf("║      Nombre de blocs : %-3d           ║\n", total_blocks);
    printf("╚══════════════════════════════════════╝\n");

    for (int b = 1; b <= total_blocks; b++) {
        printf("\n");
        printf("  ┌─────────────────────────────────┐\n");
        printf("  │         BLOC  %-3d               │\n", b);
        printf("  ├─────────────────────────────────┤\n");
        printf("  │  Adresse  : %-20p │\n", (void*)courant);
        printf("  │  État     : %-20s │\n", courant->inUse ? "🔴 Occupé" : "🟢 Libre");
        printf("  │  Taille   : %-20d │\n", courant->length);
        printf("  ├─────────────────────────────────┤\n");

        if (courant->prev != NULL)
            printf("  │  Préc.    : %-20p │\n", (void*)courant->prev);
        else
            printf("  │  Préc.    : %-20s │\n", "Aucun");

        if (courant->next != NULL)
            printf("  │  Suiv.    : %-20p │\n", (void*)courant->next);
        else
            printf("  │  Suiv.    : %-20s │\n", "Aucun");

        printf("  └─────────────────────────────────┘\n");

        if (courant->next != NULL)
            courant = courant->next;
    }

    printf("\n");
    printf("╔══════════════════════════════════════╗\n");
    printf("║           FIN DU TAS                 ║\n");
    printf("╚══════════════════════════════════════╝\n");
    printf("\n");
}

