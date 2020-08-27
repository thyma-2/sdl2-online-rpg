#include "stat.h"

void actualise_stat(struct personnages *p)
{
    if (strcmp(p->skin, "archer") == 0 || strcmp(p->skin, "civil") == 0)
    {
        int max_pv = 10;
        int vitesse_dom = 100;
        int vitesse_dep = 5;
        int porte_dom = 10;
        int dom = 1;
        int poid = 65; 	
        p->skin[0] = 0;
        strcat(p->skin, "civil");
        if (p->i_list != NULL)
        {
            if (strcmp(p->i_list->nom, "arc") == 0)
            {
       	        porte_dom = 200;
	        dom = 5;
	        if (p->i_list->next != NULL && p->i_list->next->next != NULL)
	        {
    	            if (strcmp(p->i_list->next->next->nom, "Protections_de_cuir") == 0)
                    {
	                p->skin[0] = 0;
	                strcat(p->skin, "archer");
	                max_pv += 1;
	                poid += 15;
		    }
	        }
	    }
        }
        p->max_pv = max_pv;
        p->vitesse_dom = vitesse_dom;
        p->vitesse_dep = vitesse_dep;
        p->porte_dom = porte_dom;
        p->dom = dom;
        p->poid = poid;
	p->eau = '0';
	p->plancher = 'n';
    }
    else if (strcmp(p->skin, "ship1") == 0)
    {
	p->max_pv = 800;
	p->vitesse_dom = 0;
        p->vitesse_dep = 0;
        p->porte_dom = 0;
        p->dom = 0;
        p->poid = 9999;
	p->eau = '1';
	p->plancher = 'y';
    }
    else if (strcmp(p->skin, "arbre1") == 0)
    {
        p->max_pv = 200;
        p->dom = 0;
        p->poid = 999;
        p->eau = '0';
        p->plancher = 'n';
    }
}

void init_stat(struct personnages *p)
{
    actualise_stat(p);
    p->sur_plancher = NULL;
    p->speak_timer = 0;
}
