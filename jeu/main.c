#include "main.h"

struct lettres *lettres;
struct img *img;

int main(void)
{
    lettres = calloc(sizeof(struct lettres), 1);
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *ecran = SDL_CreateWindow("Empire Expense",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            1200,700,
            SDL_WINDOW_OPENGL);
    img = init_img(ecran);
    int socket = menu_connection(ecran);
    if (socket == -1)
    {
        free_malloc();
        SDL_Quit();
        return 1;
    }
    char *name = log_menu(socket, ecran);
    if (name == NULL)
    {
        free_malloc();
        SDL_Quit();
        return 1;
    }
    if (start_menu(socket, ecran) < 0)
    {
        free_malloc();
        SDL_Quit();
        return -1;
    }
    struct linked_list *list = recv_map(socket, NULL);
    boucle_jeu(socket, ecran, list, name);
    free_malloc();
    SDL_Quit();
}

void free_malloc()
{
    free(img);
    free(lettres);
}

void boucle_jeu(int socket, SDL_Window *ecran, struct linked_list *list, char *name)
{
    struct personnages *moi = find_perso_by_name(list, name);
    int max_x = 0;
    int max_y = 0;
    char *ground = rec_ground(socket, &max_x, &max_y);
    struct linked_list *selected = NULL;
    //peux être faire une sous fonction pour init tout ca
    struct menu *menu_s = malloc(sizeof(struct menu));
    struct speak *speak_s = malloc(sizeof(struct speak));
    struct formation *f= malloc(sizeof(struct formation));
    f->ecart_x = 25;
    f->ecart_y = 25;
    f->n_par_lignes = 10;
    speak_s->on = 0;
    speak_s->speak[0] = 0;
    menu_s->on = 0;
    menu_s->diplo_on = 0;
    menu_s->inventaire_on = 0;
    menu_s->action_on = 0;
    menu_s->echange_on = 0;
    menu_s->add_enemi[0] = 0;
    menu_s->rem_enemi[0] = 0;
    menu_s->sel_diplo = 0;
    menu_s->sel_inventaire = 0;
    //
    while (lettres->exit != 1)
    {
        display_ground(moi, ground ,ecran);
        gestion_touche();
        disp_perso_list(list, moi, ecran);
        display_selected(selected, ecran, moi, f);
        if (menu_s->on == 0 && speak_s->on == 0)
        {
            deplacement(moi, ground, max_x);
            selected = select(list, moi, selected);
            commande(selected, moi, f);
            if (lettres->m == 1)
            {
                lettres->m = 0;
                menu_s->on = 1;
            }
	    if (lettres->t == 1)
            {
                lettres->t = 0;
                speak_s->on = 1;
            }
            if (lettres->Mouse_Mclick == 1)
            {
                free_linked(selected, 0);
                selected = NULL;
            }
        }
        else if (menu_s->on == 1)
            menu(ecran, menu_s, moi, list);
	else
	    talk(ecran, speak_s, moi);
	ia(list);
	collision(list, ground, max_x, max_y);
	gui_event(moi, ecran, list);
        generate_orders(list, socket);
        recv_order(socket, list);
	selected = clean_selected(selected);
        list = death(list);
        SDL_UpdateWindowSurface(ecran);
    }
    free(menu_s);
    free(ground);
}

void set_pos(SDL_Rect *pos, int x, int y)
{
    pos->x = x;
    pos->y = y;
}

int start_menu(int socket, SDL_Window* ecran)
{
    char err1[] = "Vous avez deja un personnage.";
    char err2[] = "Veuillez cree un personnage";
    char txt1[] = "Jouer";
    char txt2[] = "Creer un personnage";
    char txt3[] = "Nom du personnage";
    char txt4[] = "Zone";
    char zone[50] = "";
    char nom[50] = "";
    SDL_Rect position0; //position background
    set_pos(&position0, 0, 0);
    SDL_Rect position1;
    SDL_Rect position2;
    SDL_Rect position3;
    SDL_Rect position4;
    SDL_Rect position5;
    set_pos(&position3, 100, 300);
    set_pos(&position1, 100, 100);
    set_pos(&position2, 100, 200);
    set_pos(&position4, 100, 70);
    set_pos(&position5, 100, 170);
    char play = 0;
    char sel = 1;
    int tryed = -127;
    char *c = malloc(101);
    char create = 0;
    while (play ==  0)
    {
        gestion_touche();
        SDL_BlitSurface(img->t->fond, NULL, SDL_GetWindowSurface(ecran),
            &position0);
        if (lettres->exit == 1)
        {
            return -1;
        }
        if (create == 0)
        {
            if (tryed > -126)
            {
                blit_text(position3, err2, ecran, 99, 255);
                tryed --;
            }
            if (sel == 1)
            {
                SDL_BlitSurface(img->g->selTextInput, NULL, SDL_GetWindowSurface(ecran),
                        &position1);
                SDL_BlitSurface(img->g->textInput, NULL, SDL_GetWindowSurface(ecran), 
                        &position2);
                if (lettres->tab == 1)
                {
                    sel = 2;
                    lettres->tab = 0;
                }
                if (lettres->enter == 1)
                {
                    c[0] = 'p';
                    send(socket, c, 1, 0);
                    while (c[0] == 'p')
                        recv(socket, c, 1, 0);
                    if (c[0] == 'o')
                        return 1;
                    else
                        tryed = 127;
                    lettres->enter = 0;
                }
            }
            else
            {
                SDL_BlitSurface(img->g->selTextInput, NULL, SDL_GetWindowSurface(ecran),
                        &position2);
                SDL_BlitSurface(img->g->textInput, NULL, SDL_GetWindowSurface(ecran),
                        &position1);
                if (lettres->tab == 1)
                {
                    sel = 1;
                    lettres->tab = 0;
                }
                if (lettres->enter == 1)
                {
                    create = 1;
                    lettres->enter = 0;
                }
            }
            blit_text(position2,txt2,ecran, 20, 255);
            blit_text(position1,txt1,ecran, 20, 255);
        }
	else
	{
	    if (tryed > -126)
            {
                blit_text(position3, err1, ecran, 99, 255);
                tryed --;
            }
            if (sel == 1)
            {
                SDL_BlitSurface(img->g->selTextInput, NULL, SDL_GetWindowSurface(ecran),
                        &position1);
                SDL_BlitSurface(img->g->textInput, NULL, SDL_GetWindowSurface(ecran),
                        &position2);
		if (lettres->tab == 1)
		{
		    lettres->tab = 0;
		    sel = 2;
		}
		text_input(nom, 50);
	    }
	    else
	    {
		SDL_BlitSurface(img->g->textInput, NULL, SDL_GetWindowSurface(ecran),
                        &position1);
                SDL_BlitSurface(img->g->selTextInput, NULL, SDL_GetWindowSurface(ecran),
                        &position2);
		if (lettres->tab == 1)
		{
		    lettres->tab = 0;
		    sel = 1;
		}
		text_input(zone, 50);
	    }
	    if (lettres->enter == 1)	
	    {
		c[0] = 'c';
		c[1] = 0;
		strcat(c, nom);
		strcat(c, " ");
		strcat(c, zone);
		send(socket, c, strlen(c), 0);
		while (c[0] == 'c')
                    recv(socket, c, 1, 0);
		if (c[0] == 'o')
                    return 1;
		else
		    tryed = 127;
		lettres->enter = 0;
	    }
	    if (lettres->esc == 1)
	    {
		lettres->esc = 0;
		create = 0;
	    }
	    blit_text(position4,txt3,ecran, 20, 255);
	    blit_text(position5,txt4,ecran, 20, 255);
	    blit_text(position1,nom,ecran, 20, 255);
            blit_text(position2,zone,ecran, 20, 255);
	}
        SDL_UpdateWindowSurface(ecran);
    }
    free(c);
    return 1;
}

char *log_menu(int socket, SDL_Window *ecran)
{
    char err1[] = "Mauvais identifiant .il est pas gentil.";
    char txt1[] = "Nom";
    char txt2[] = "Mot de passe";
    char *nom = ecalloc(50, 1);
    char mdp[50] = "";
    SDL_Rect position0; //position background
    set_pos(&position0, 0, 0);
    SDL_Rect position1;
    SDL_Rect position2;
    SDL_Rect position3;
    SDL_Rect position4;
    SDL_Rect position5;
    set_pos(&position1, 100, 100);
    set_pos(&position2, 100, 200);
    set_pos(&position3, 100, 70);
    set_pos(&position4, 100, 170);
    set_pos(&position5, 100, 300);
    char *boolean_rep = emalloc(1);
    boolean_rep[0] = 'p';
    char sel = 1;
    char tryed = -127;
    while (boolean_rep[0] != 'o')
    {
        SDL_BlitSurface(img->t->fond, NULL, SDL_GetWindowSurface(ecran),
            &position0);
        if (lettres->exit == 1)
        {
            return NULL;
        }
        if (tryed > -126)
        {
            blit_text(position5, err1, ecran, 20, 255);
            tryed --;
        }
        blit_text(position3, txt1, ecran, 40, 255);
        blit_text(position4, txt2, ecran, 40, 255);
        if (sel == 1)
        {
            SDL_BlitSurface(img->g->selTextInput, NULL, SDL_GetWindowSurface(ecran),
                    &position1);
            SDL_BlitSurface(img->g->textInput, NULL, SDL_GetWindowSurface(ecran),
                    &position2);
            text_input(nom, 50);
            if (lettres->tab == 1)
            {
                sel = 2;
                lettres->tab = 0;
            }
        }
        else
        {
            SDL_BlitSurface(img->g->selTextInput, NULL, SDL_GetWindowSurface(ecran), 
                    &position2);
            SDL_BlitSurface(img->g->textInput, NULL, SDL_GetWindowSurface(ecran), 
                    &position1);
            text_input(mdp, 50);
            if (lettres-> tab == 1)
            {
                sel = 1;
                lettres->tab = 0;
            }
        }
        if (lettres->enter == 1)
        {
            tryed = 127;
            char *to_send = ecalloc(101,1);
            chifrage(mdp,nom);
            strcat(to_send, nom);
            strcat(to_send, " ");
            strcat(to_send, mdp);
            send(socket, to_send, 101, 0);
            while (boolean_rep[0] == 'p')
                recv(socket, boolean_rep, 1, 0);
            if (boolean_rep[0] == 'n')
                boolean_rep[0] = 'p';
            lettres->enter = 0;
        }
        blit_text(position1, nom, ecran, 20, 255);
        blit_mdp(position2, mdp, ecran, 20, 255);
        SDL_UpdateWindowSurface(ecran);
    }
    free(boolean_rep);
    return nom;
}


int menu_connection(SDL_Window *ecran)
{
    char err1[] = "La connection a echouer";
    char txt1[] = "Adresse IP";
    char txt2[] = "Port";
    char ip[50] = "";
    char port[50] = "";
    SDL_Rect position0; //position background
    set_pos(&position0, 0, 0);
    SDL_Rect position1;
    SDL_Rect position2;
    SDL_Rect position3;
    SDL_Rect position4;
    SDL_Rect position5;
    set_pos(&position1, 100, 100);
    set_pos(&position2, 100, 200);
    set_pos(&position3, 100, 70);
    set_pos(&position4, 100, 170);
    set_pos(&position5, 100, 300);
    int socket = -1;
    char sel = 1;
    char tryed = -127;
    while (socket < 0)
    {
        SDL_BlitSurface(img->t->fond, NULL, SDL_GetWindowSurface(ecran),
            &position0);
        if (lettres->exit == 1)
            return -1;
        if (tryed > -126)
        {
            blit_text(position5, err1, ecran, 40, 255);
            tryed --;
        }
        blit_text(position3, txt1, ecran, 40, 255);
        blit_text(position4, txt2, ecran, 40, 255);
        if (sel == 1)
        {
            SDL_BlitSurface(img->g->selTextInput, NULL, SDL_GetWindowSurface(ecran),
                    &position1);
            SDL_BlitSurface(img->g->textInput, NULL, SDL_GetWindowSurface(ecran), 
                    &position2);
            text_input(ip, 39);
            if (lettres->tab == 1)
            {
                sel = 2;
                lettres->tab = 0;
            }
        }
        else
        {
            SDL_BlitSurface(img->g->selTextInput, NULL, SDL_GetWindowSurface(ecran), 
                    &position2);
            SDL_BlitSurface(img->g->textInput, NULL, SDL_GetWindowSurface(ecran), 
                    &position1);
            text_input(port, 6);
            if (lettres-> tab == 1)
            {
                sel = 1;
                lettres->tab = 0;
            }
        }
        if (lettres->enter == 1 && *ip != '\0' && *port != '\0')
        {
            tryed = 127;
            socket = try_connect(ip, port);
            lettres->enter = 0;
        }
        blit_text(position1, ip, ecran, 20, 255);
        blit_text(position2, port, ecran, 7, 255);
        SDL_UpdateWindowSurface(ecran);
    }
    return socket;
}
