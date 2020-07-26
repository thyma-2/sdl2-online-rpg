#include "gui.h"

void *cast(void *p)
{
    return p;
}






void blit_mdp(SDL_Rect position, char *text, SDL_Window *ecran, int limite, int couleur)
{
    int pox = position.x;
    int i = 0;
    SDL_Surface *lettre_afficher = select_lettre('x');
    while (text[i] != 0)
    {
        if (i % limite == 0 && i != 0)
        {
            position.y += 20;
            position.x = pox;
        }
        if (text[i] == '\n')
        {
            position.y += 20;
            position.x = pox;
            i++;
        }
        else if (text[i] == ' ')
        {
            position.x += 14;
            i++;
        }
        else
        {
            if (lettre_afficher != NULL)
            {
                SDL_SetColorKey(lettre_afficher, SDL_SCANCODE_Y, SDL_MapRGB(lettre_afficher->format,couleur,couleur,couleur));
                SDL_BlitSurface(lettre_afficher, NULL, SDL_GetWindowSurface(ecran), &position);
                position.x += lettre_afficher->w;
            }
            i++;
        }
    }
}





void blit_text(SDL_Rect position, char *text, SDL_Window *ecran, int limite, int couleur)
{
    int pox = position.x;
    int i = 0;
    while (text[i] != 0)
    {
        if (i % limite == 0 && i != 0)
        {
            position.y += 20;
            position.x = pox;
        }
        if (text[i] == '\n')
        {
            position.y += 20;
            position.x = pox;
            i++;
        }
        else if (text[i] == ' ')
        {
            position.x += 14;
            i++;
        }
        else
        {
            SDL_Surface *lettre_afficher = select_lettre(text[i]);
            if (lettre_afficher != NULL)
            {
                SDL_SetColorKey(lettre_afficher, SDL_SCANCODE_Y, SDL_MapRGB(lettre_afficher->format,couleur,couleur,couleur));
                SDL_BlitSurface(lettre_afficher, NULL, SDL_GetWindowSurface(ecran), &position);
                position.x += lettre_afficher->w;
            }
            i++;
	}
    }
}

void gui_event(struct personnages *perso, SDL_Window *ecran, struct linked_list *list)
{
    SDL_Rect position;
    position.x = 50;
    position.y = 50;
    char txt[150];
    txt[0] = 0;
    if (strcmp(perso->echange_player, "none") != 0)
    {
	struct personnages *p = find_perso_by_name(list, perso->echange_player);
	{
	    if (p != NULL)
	    {
		strcat(txt, perso->echange_player);
		strcat(txt, " vous propose un echange -> ");
		struct linked_char *obj1 = get_char_n(perso->item2, perso->i_list); //le tiens
		struct linked_char *obj2 = get_char_n(perso->item1, p->i_list);
		if (obj1 != NULL)
		    strcat(txt, obj1->nom);
		else
		    strcat(txt, "rien");
		strcat(txt, " contre : ");
		if (obj2 != NULL)
                    strcat(txt, obj2->nom);
                else
                    strcat(txt, "rien");
		strcat(txt, "\nappuyez sur y pour accepter et n pour refuser");
		if (lettres->n == 1)
		{
		    perso->echange_player[0] = 0;
		    strcat(perso->echange_player, "none");
		    lettres->n = 0;
		}
		if (lettres->y == 1)
		{
		    lettres->y = 0;
		    perso->echange_player[0] = 0;
                    strcat(perso->echange_player, "none");
		    if (obj1 != NULL && obj2 != NULL)
		    {
    		        char tmp[50];
		        tmp[0] = 0;
		        strcat(tmp, obj1->nom);
		        obj1->nom[0] = 0;
		        strcat(obj1->nom, obj2->nom);
		        obj2->nom[0] = 0;
		        strcat(obj2->nom, tmp);
			perso->a_bouger = 1;
			p->a_bouger = 1;
		    }
		    else if (obj1 == NULL && obj2 != NULL)
		    {
			perso->i_list = append_linked_char(obj2->nom, perso->i_list);
		  	p->i_list = remove_enemi(obj2->nom, p->i_list);
			perso->a_bouger = 1;
                        p->a_bouger = 1;
		    }
		    else if (obj2 == NULL && obj1 != NULL)
		    {
			p->i_list = append_linked_char(obj1->nom, p->i_list);
                        perso->i_list = remove_enemi(obj1->nom, perso->i_list);
			perso->a_bouger = 1;
                        p->a_bouger = 1;
		    }
		}
	    }
	}
    }
    blit_text(position, txt, ecran, 150, 255);
}

void display_selected(struct linked_list *selected, SDL_Window *ecran, struct personnages *moi)
{
    char txt[50];
    char tmp[20];
    SDL_Rect position;
    txt[0] = 0;
    strcat(txt, "pV->");
    position.x = 0;
    position.y = 550;
    tmp[0] = 0;
    sprintf(tmp, "%d", moi->pv);
    strcat(txt, tmp);
    strcat(txt, "/");
    tmp[0] = 0;
    sprintf(tmp, "%d", moi->max_pv);
    strcat(txt, tmp);
    blit_text(position, txt, ecran, 20, 255);
    txt[0] = 0;
    strcat(txt, "vitesse->");
    position.x = 0;
    position.y = 570;
    tmp[0] = 0;
    sprintf(tmp, "%d", moi->vitesse_dep);
    strcat(txt, tmp);
    strcat(txt, "\n         ");
    tmp[0] = 0;
    sprintf(tmp, "%d", moi->vitesse_dom);
    strcat(txt, tmp);
    blit_text(position, txt, ecran, 20, 255);
    int pv = 0;
    int vitesse_dom = 0;
    int i = 0;
    int vitesse_dep = 99999;
    position.y = 550;
    for (struct linked_list *parcour = selected; parcour != NULL; parcour = parcour->next)
    {
        position.x = 700;
	txt[0] = 0;
	strcat(txt, parcour->p->nom);
	if (strcmp(parcour->p->nom_superieur, moi->nom) == 0)
	{
	    i++;
	    pv += parcour->p->pv;
	    vitesse_dom += parcour->p->vitesse_dom;
	    if (parcour->p->vitesse_dep < vitesse_dep)
	        vitesse_dep = parcour->p->vitesse_dep;
            blit_text(position,txt,ecran, 20, 100);
	}
	else
	    blit_text(position,txt,ecran, 20, 255);
	position.y += 20;
    }
    if (i > 0)
    {
        position.x = 900;
        position.y = 550;
        txt[0] = 0;
        strcat(txt, "pv->");
        tmp[0] = 0;
        sprintf(tmp, "%d", pv / i);
	strcat(txt, tmp);
        blit_text(position, txt, ecran, 20, 255);
        position.x = 900;
        position.y = 570;
        txt[0] = 0;
        strcat(txt, "vitesse->");
	tmp[0] = 0;
        sprintf(tmp, "%d", vitesse_dep);
	strcat(txt, tmp);
	tmp[0] = 0;
	strcat(txt, "\n         ");
        sprintf(tmp, "%d", vitesse_dom / i);
	strcat(txt, tmp);
        blit_text(position, txt, ecran, 20, 255); 
    }
}

void menu(SDL_Window *ecran, struct menu *m, struct personnages *perso, struct linked_list *list)
{
    char txt[] = "Menu inventaire -> Taper i.\nMenu diplomatique -> Taper d.\nMenu action -> taper a";
    char txt1[] = "Ajouter un enemi";
    char txt2[] = "Retirer un enemi";
    char txt3[] = "Ajouter les enemis du suzerain";
    char txt4[] = "Changer de suzerain";
    char txt5[] = "Prendre possession";
    char txt6[] = "Main Gauche";
    char txt7[] = "Main Droite";
    char txt8[] = "Vetements";
    char txt9[] = "Stockage";
    char *e_list = malloc(200);
    SDL_Surface *inputBox = SDL_LoadBMP("img/gui/textInput.bmp");
    SDL_Surface *narrowInputBox = SDL_LoadBMP("img/gui/narrowTextInput.bmp");
    SDL_Surface *selInputBox = SDL_LoadBMP("img/gui/selTextInput.bmp");
    SDL_Surface *narrowSelInputBox = SDL_LoadBMP("img/gui/narrowSelTextInput.bmp");
    SDL_Rect position1;
    SDL_Rect position2;
    SDL_Rect position3;
    SDL_Rect position4;
    SDL_Rect position5;
    SDL_Rect position6;
    SDL_Rect position7;
    SDL_Rect position8;
    SDL_Rect position9;
    SDL_Rect position10;
    SDL_Rect position11;
    SDL_Rect position12;
    SDL_Rect position13;
    SDL_Rect position14;
    position1.x = 50;
    position2.x = 50;
    position3.x = 50;
    position4.x = 50;
    position4.x = 50;
    position5.x = 700;
    position6.x = 50;
    position7.x = 50;
    position8.x = 50;
    position9.x = 50;
    position10.x = 50;
    position11.x = 50;
    position12.x = 50;
    position13.x = 200;
    position14.x = 250;
    position1.y = 70;
    position2.y = 100;
    position3.y = 170;
    position4.y = 200;
    position5.y = 70;
    position6.y = 300;
    position7.y = 370;
    position8.y = 400;
    position9.y = 100;
    position10.y = 120;
    position11.y = 140;
    position12.y = 160;
    position13.y = 100;
    position14.y = 0;
    if (lettres->esc == 1)
    {
	lettres->esc = 0;
	if (m->echange_on != 0)
	    m->echange_on = 0;
	else if (m->inventaire_on != 0)
	    m->inventaire_on = 0;
	else if (m->diplo_on != 0)
	    m->diplo_on = 0;
	else if (m->action_on != 0)
	    m->action_on = 0;
	else
	    m->on = 0;
    }
    if (m->inventaire_on == 0 && m->diplo_on == 0 && m->action_on == 0 && m->echange_on == 0)
    {
	blit_text(position1, txt, ecran, 200, 255);
	if (lettres->i == 1)
	{
	    lettres->i = 0;
	    m->inventaire_on = 1;
        }
        if (lettres->d == 1)
        {
            lettres->d = 0;
	    m->diplo_on = 1;
	}
	if (lettres->a == 1)
	{
	    lettres->a = 0;
	    m->action_on = 1;
	}
    }
    if (m->echange_on == 1)
    {
	struct linked_char *t = perso->i_list;
        for (int i = 0; i < 10; i++)
        {
            if (m->sel_echange1 == position14.y / 20)
                SDL_BlitSurface(narrowSelInputBox, NULL, SDL_GetWindowSurface(ecran), &position14);
            else
                SDL_BlitSurface(narrowInputBox, NULL, SDL_GetWindowSurface(ecran), &position14);
            if (t != NULL)
            {
                blit_text(position14, t->nom, ecran, 20, 255);
                t = t->next;
            }
            position14.y += 20;
        }
	position14.y += 20;
	t = m->echange->i_list;
        for (int i = 0; i < 10; i++)
        {
            if (m->sel_echange2 == (position14.y - 220) / 20)
                SDL_BlitSurface(narrowSelInputBox, NULL, SDL_GetWindowSurface(ecran), &position14);
            else
                SDL_BlitSurface(narrowInputBox, NULL, SDL_GetWindowSurface(ecran), &position14);
            if (t != NULL)
            {
                blit_text(position14, t->nom, ecran, 20, 255);
                t = t->next;
            }
            position14.y += 20;
        }
	if (lettres->enter == 1)
	{
	    lettres->enter = 0;
	    m->echange->echange_player[0] = 0;
	    m->echange->a_bouger = 1;
	    strcat(m->echange->echange_player, perso->nom);
	    m->echange->item1 = m->sel_echange1 + 1;
	    m->echange->item2 = m->sel_echange2 + 1;
	}
        if (lettres->s == 1)
        {
            lettres->s = 0;
	    if (m->tab_echange == 1)
	    {
                if (m->sel_echange1 == 9)
                    m->sel_echange1 = 0;
                else
                    m->sel_echange1 += 1;
	    }
	    else
	    {
		if (m->sel_echange2 == 9)
                    m->sel_echange2 = 0;
		else
		    m->sel_echange2 += 1;
	    }
        }
        if (lettres->z == 1)
        {
	    lettres->z = 0;
	    if (m->tab_echange == 1)
	    {
                if (m->sel_echange1 == 0)
                    m->sel_echange1 = 9;
                else
                    m->sel_echange1 -= 1;
	    }
	    else
	    {
		if (m->sel_echange2 == 0)
                    m->sel_echange2 = 9;
                else
                    m->sel_echange2 -= 1;
	    }

        }
	if (lettres->tab == 1)
	{
	    lettres->tab = 0;
	    if (m->tab_echange == 0)
		m->tab_echange = 1;
	    else
		m->tab_echange = 0;
	}
    }
    else if (m->action_on == 1)
    {
	int c = 0;
	if (perso->sur_plancher != NULL)
	{
	    if (m->sel_action == 0)
		SDL_BlitSurface(selInputBox, NULL, SDL_GetWindowSurface(ecran),
                    &position2);
	    else
		SDL_BlitSurface(inputBox, NULL, SDL_GetWindowSurface(ecran),
                    &position2);
     	    blit_text(position2, txt5, ecran, 20, 255);
   	    if (lettres->enter == 1 && m->sel_action == 0)
	    {
	        lettres->enter = 0;
		perso->sur_plancher->nom_superieur[0] = 0;
		strcat(perso->sur_plancher->nom_superieur, perso->nom);
	    }
	}
	for (struct linked_list *l = list; l != NULL; l = l->next)
	{
	    if (l->p != perso)
	    {
		int x1, x2, x3, x4, y1, y2, y3, y4;
		coo_corner(l->p, &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4);
		x2 = (x1 + x2 + x3 + x4) / 4;
		y2 = (y1 + y2 + y3 + y4) / 4;
	        if (sqrt((x2 - perso->x)*(x2 - perso->x) + (y2 - perso->y)*(y2 - perso->y)) < 99 + sqrt(((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1))/2))
		{
		    c += 1;
		    position2.y += 50;
		    if (m->sel_action == (position2.y - 100) / 50)
		    {
  		        SDL_BlitSurface(selInputBox, NULL, SDL_GetWindowSurface(ecran),
 	                    &position2);
			m->echange = l->p;
			
		    }
		    else
			SDL_BlitSurface(inputBox, NULL, SDL_GetWindowSurface(ecran),
                            &position2);
		    blit_text(position2, l->p->nom, ecran, 20, 255);
		}
	    }
	}
	if (lettres->enter == 1 && m->sel_action > 0)
        {
            lettres->enter = 0;
	    m->echange_on = 1;
        }
	if (lettres->s == 1)
        {
            lettres->s = 0;
            m->sel_action += 1;
        }
        if (lettres->z == 1)
        {
            lettres->z = 0;
	    if (m->sel_action > 0)
	        m->sel_action -= 1;
        }
	if (m->sel_action > c)
	    m->sel_action = c;
    }
    else if (m->inventaire_on == 1)
    {
	blit_text(position9, txt6, ecran, 20, 255);
	blit_text(position10, txt7, ecran, 20, 255);
	blit_text(position11, txt8, ecran, 20, 255);
	blit_text(position12, txt9, ecran, 20, 255);
	struct linked_char *t = perso->i_list;
	for (int i = 0; i < 10; i++)
	{
	    if (m->sel_inventaire == (position13.y - 100) / 20)
	        SDL_BlitSurface(narrowSelInputBox, NULL, SDL_GetWindowSurface(ecran), &position13);
	    else
 	        SDL_BlitSurface(narrowInputBox, NULL, SDL_GetWindowSurface(ecran), &position13);
	    if (t != NULL)
	    {
	        blit_text(position13, t->nom, ecran, 20, 255);
		t = t->next;
	    }
	    position13.y += 20;
	}
	if (lettres->s == 1)
        {
            lettres->s = 0;
            if (m->sel_inventaire == 9)
                m->sel_inventaire = 0;
            else
                m->sel_inventaire += 1;
	}
	if (lettres->z == 1)
	{
	    lettres->z = 0;
	    if (m->sel_inventaire == 0)
		m->sel_inventaire = 9;
	    else
		m->sel_inventaire -= 1;
	}
	if (lettres->k1 == 1)
	{
	    exchange_char(0, m->sel_inventaire, perso->i_list);
	    lettres->k1 = 0;
	}
	else if (lettres->k2 == 1)
	{
	    exchange_char(1, m->sel_inventaire, perso->i_list);
	    lettres->k2 = 0;
	}
	else if (lettres->k3 == 1)
	{
	    exchange_char(2, m->sel_inventaire, perso->i_list);
	    lettres->k3 = 0;
	}
    }
    else if (m->diplo_on == 1)
    {
	blit_text(position1, txt1, ecran, 20, 255);
	blit_text(position3, txt2, ecran, 20, 255);
	blit_text(position7, txt4, ecran, 20, 255);
	if (m->sel_diplo == 0)
	{
	    text_input(m->add_enemi, 50);
            SDL_BlitSurface(selInputBox, NULL, SDL_GetWindowSurface(ecran),
                &position2);
	    SDL_BlitSurface(inputBox, NULL, SDL_GetWindowSurface(ecran),
                &position4);
	    SDL_BlitSurface(inputBox, NULL, SDL_GetWindowSurface(ecran),
                &position6);
	    SDL_BlitSurface(inputBox, NULL, SDL_GetWindowSurface(ecran),
                &position8);
	    if (lettres->enter == 1)
	    {
		lettres->enter = 0;
		if (exist_in_linked_char(perso->e_list, m->add_enemi) == 0)
  		    perso->e_list = append_linked_char(m->add_enemi, perso->e_list);
	    }
	}
	else if (m->sel_diplo == 1)
	{
	    text_input(m->rem_enemi, 50);
	    SDL_BlitSurface(selInputBox, NULL, SDL_GetWindowSurface(ecran),
                &position4);
            SDL_BlitSurface(inputBox, NULL, SDL_GetWindowSurface(ecran),
                &position2);
	    SDL_BlitSurface(inputBox, NULL, SDL_GetWindowSurface(ecran),
                &position6);
	    SDL_BlitSurface(inputBox, NULL, SDL_GetWindowSurface(ecran),
                &position8);
	    if (lettres->enter == 1)
	    {
		lettres->enter = 0;
		perso->e_list = remove_enemi(m->rem_enemi, perso->e_list);
	    }
	}
	else if (m->sel_diplo == 2)
	{
	    SDL_BlitSurface(selInputBox, NULL, SDL_GetWindowSurface(ecran),
                &position6);
            SDL_BlitSurface(inputBox, NULL, SDL_GetWindowSurface(ecran),
                &position2);
            SDL_BlitSurface(inputBox, NULL, SDL_GetWindowSurface(ecran),
                &position4);
	    SDL_BlitSurface(inputBox, NULL, SDL_GetWindowSurface(ecran),
                &position8);
	    if (lettres->enter == 1)
	    {
		lettres->enter = 0;
		append_enemi_list(list, perso);
	    }
	}
	else
	{
	    text_input(perso->nom_superieur, 50);
	    SDL_BlitSurface(inputBox, NULL, SDL_GetWindowSurface(ecran),
                &position6);
            SDL_BlitSurface(inputBox, NULL, SDL_GetWindowSurface(ecran),
                &position2);
            SDL_BlitSurface(inputBox, NULL, SDL_GetWindowSurface(ecran),
                &position4);
            SDL_BlitSurface(selInputBox, NULL, SDL_GetWindowSurface(ecran),
                &position8);		
	}
	blit_text(position2, m->add_enemi, ecran, 20, 255);
        blit_text(position4, m->rem_enemi, ecran, 20, 255);
	blit_text(position6, txt3, ecran, 40, 255);
	blit_text(position8, perso->nom_superieur, ecran, 20, 255);
	if (lettres->tab == 1)
	{
	    lettres->tab = 0;
	    if (m->sel_diplo == 3)
		m->sel_diplo = 0;
	    else
		m->sel_diplo += 1;
	}
	e_list[0] = 0;
	struct linked_char *parcour = perso->e_list;
	while (parcour != NULL)
	{
	    strcat(e_list, parcour->nom);
	    strcat(e_list, "\n");
	    parcour = parcour->next;
	}
	blit_text(position5, e_list, ecran, 9999, 255);
    }
}
