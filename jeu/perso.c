#include "perso.h"

void free_linked(struct linked_list *list, char free_content)
{
    if (list != NULL)
    {
        free_linked(list->next, free_content);
        if (free_content == 1)
        {
            free(list->p);
            free_linked_char(list->p->e_list);
            free_linked_char(list->p->i_list);
        }
        free(list);
    }
}

struct linked_list *append_in_linked(struct linked_list *list,struct personnages *p)
{
    if (list == NULL)
    {
        list = malloc(sizeof(struct linked_list));
        list->p = p;
        list->next = NULL;
        return (list);
    }
    else
    {
        struct linked_list *parcour = list;
        while (parcour->next != NULL)
        {
            if (parcour->p == p)
                return list;
            parcour = parcour->next;
        }
        if (parcour->p != p)
        {
            struct linked_list *to_append = malloc(sizeof(struct linked_list));
            parcour->next = to_append;
            to_append->p = p;
            to_append->next = NULL;
        }
        return list;
    }
}

struct linked_list *append_perso(struct linked_list *list,  char **line)
{
    if (**line == '\0')
        return NULL;
    if (list == NULL)
    {
        list = malloc(sizeof(struct linked_list));
        struct personnages *n = malloc(sizeof(struct personnages));
        list->p = n;
        list->next = NULL;
        int a = parse_order(n, *line);
        init_stat(n);
        *line = *line + a;
        return (list);
    }
    else
    {
        struct linked_list *parcour = list;
        while (parcour->next != NULL)
            parcour = parcour->next;
        struct linked_list *to_append = malloc(sizeof(struct linked_list));
        struct personnages *n = malloc(sizeof(struct personnages));
        parcour->next = to_append;
        to_append->p = n;
        int a = parse_order(n, *line);
        *line = *line + a;
        init_stat(n);
        to_append->next = NULL;
        return list;
    }
}

struct linked_list *recv_map(int socket, struct linked_list *list)
{
    char *buffer = calloc(order_size, sizeof(char));
    recv(socket, buffer, 20, 0);

    size_t res  = 0;
    size_t nb_to_res  = atoi(buffer);
    free(buffer);
    char *pos_buf = buffer;
    buffer = calloc(sizeof(char), nb_to_res);
    while (res < nb_to_res)
    {
        size_t tmp = recv(socket, buffer, nb_to_res - res, 0);
        res += tmp;
        buffer = buffer + tmp;
    }
    buffer = pos_buf;
    if (list == NULL)
        list = append_perso(list,  &buffer);
    while ((append_perso(list,  &buffer) != NULL));
    buffer = pos_buf;
    free(buffer);
    return list;
}

void *find_perso(struct linked_list *list ,char *name)
{
    struct linked_list *parcour = list;
    while (parcour != NULL)
    {
        if (strcmp(parcour->p->nom_de_compte, name) == 0)
            return parcour->p;
        parcour = parcour->next;
    }
    return NULL;
}

void *find_perso_by_name(struct linked_list *list ,char *name)
{
    struct linked_list *parcour = list;
    while (parcour != NULL)
    {
        if (strcmp(parcour->p->nom, name) == 0)
            return parcour->p;
        parcour = parcour->next;
    }
    return NULL;
}

void disp_perso_list(struct linked_list *list, struct personnages *moi ,SDL_Window *ecran)
{
    struct linked_list *parcour = list;
    SDL_Rect position;
    SDL_Surface *affiche;
    buble_sort_perso(list);
    int i = 0;
    while (parcour != NULL)
    {
        i++;
        if (parcour->p == moi)
        {
            position.x = 600;
            position.y = 350;
            affiche = select_good_img(moi, (i % 5));
        }
        else
        {
            position.x = 600 + parcour->p->x - moi->x;
            position.y = 350 + parcour->p->y - moi->y;
            affiche = select_good_img(parcour->p, (i % 5));
        }
        parcour = parcour->next;
        SDL_SetColorKey(affiche, SDL_SCANCODE_Y, SDL_MapRGB(affiche->format,255,255,255));
        SDL_BlitSurface(affiche, NULL, SDL_GetWindowSurface(ecran), &position);
    }
}

void buble_sort_perso(struct linked_list *list)
{
    for (struct linked_list *par = list; par != NULL; par = par->next)
    {
        for (struct linked_list *par2 = par; par2->next != NULL; par2 = par2->next)
        {
            if (par2->p->y > par2->next->p->y)
            {
                struct personnages *tmp = par2->p;
                par2->p = par2->next->p;
                par2->next->p = tmp;
            }
        }
    }
}

struct linked_list *remove_perso(struct linked_list *list)
{
    struct linked_list *ret = list;
    struct linked_list *prev;
    if (list != NULL)
    {
        if (list->p->pv <= 0)
        {
            list = list->next;
            free_linked_char(list->p->e_list);
            free_linked_char(list->p->i_list);
            free(ret->p);
            free(ret);
            ret = list;
        }
        while (list->next != NULL)
        {
            prev = list;
            list = list->next;
            if (list->p->pv <= 0)
            {
                prev->next = list->next;
                free_linked_char(list->p->e_list);
                free_linked_char(list->p->i_list);
                free(list->p);
                free(list);
            }
        }
        if (list->p->pv <= 0)
        {
            prev->next = NULL;
            free_linked_char(list->p->e_list);
            free_linked_char(list->p->i_list);
            free(list->p);
            free(list);
        }
    }
    return ret;
}
