#include "map_op.h"

void save_map(struct personnages *list)
{
    FILE *file = fopen("map.txt","r+");
    char a[360];
    char tmp[20];
    while (list != NULL)
    {
            a[0] = 0;
            sprintf(tmp, "%d", list->id);
            strcat(a, tmp);
            strcat(a , " ");
	    tmp[0] = 0;
	    sprintf(tmp, "%d", list->pv);
	    strcat(a, tmp);
	    strcat(a, " ");
            strcat(a, list->nom_de_compte);
            strcat(a , " ");
	    strcat(a, list->tout_le_reste);
	    strcat(a, "\n");
            fprintf(file, "%s", a);
            list = list->next;
    }
    fclose(file);
}
