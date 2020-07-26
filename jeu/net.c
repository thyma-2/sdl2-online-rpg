#include "net.h"

int try_connect(char *ip, char *port) // Connecter
{
    int network_socket;
    network_socket = socket(AF_INET, SOCK_STREAM, 0);
    //specify an address for the socket
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(atoi(port));
    server_address.sin_addr.s_addr = inet_addr(ip);
    if (connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address)) == 0)
        return network_socket;
    return -1;
}

void recv_order(int socket, struct linked_list *list)
{
    char *buffer = calloc(20, sizeof(char));
    recv(socket, buffer, 20, 0);
    if (buffer[0] == '0')
    {
	free(buffer);
	return;
    }
    size_t res  = 0;
    size_t nb_to_res  = atoi(buffer);
    free(buffer);
    buffer = calloc(sizeof(char), nb_to_res + 3);
    char *pos_buf = buffer;
    while (res < nb_to_res)
    {
        size_t tmp = recv(socket, buffer, nb_to_res - res, 0);
        res += tmp;
        buffer = buffer + tmp;
    }
    buffer = pos_buf;
    while (*buffer != 0)
    {
        struct personnages *yalist = get_ptr_from_id(buffer, list);
        if (yalist != NULL)
        {
            free_linked_char(yalist->e_list);
            free_linked_char(yalist->i_list);
            buffer += parse_order(yalist, buffer) + 1;
            actualise_stat(yalist);
        }
        else
            list = append_perso(list, &buffer);
    }
    free(pos_buf);
}


void generate_orders(struct linked_list *l, int socket)
{
    char *order = malloc(10000);
    order[0] = 0;
    char tmp[20];
    for (struct linked_list *list = l; list != NULL; list = list->next)
    {
	if (list->p->a_bouger == 1)
	{
	    if (order[0] != 0)
		strcat(order, "\n");
            sprintf (tmp, "%d", list->p->id);
            strcat(order, tmp);
            strcat(order , " ");
	    tmp[0] = 0;
	    sprintf (tmp, "%d", list->p->pv);
	    strcat (order, tmp);
	    strcat(order , " ");
	    strcat(order, list->p->nom_de_compte);
	    strcat(order , " ");
	    tmp[0] = 0;
	    sprintf(tmp, "%f", list->p->x);
	    strcat(order, tmp);
	    strcat(order , " ");
	    tmp[0] = 0;
	    sprintf(tmp, "%f", list->p->y);
	    strcat(order, tmp);
	    strcat(order , " ");
	    tmp[0] = 0;
	    sprintf(tmp, "%f", list->p->ordrex);
	    strcat(order, tmp);
	    strcat(order , " ");
	    tmp[0] = 0;
	    sprintf(tmp, "%f", list->p->ordrey);
	    strcat(order, tmp);
	    strcat(order , " ");
	    tmp[0] = 0;
   	    sprintf (tmp, "%d", list->p->angle);
	    strcat (order, tmp);
	    strcat(order , " ");
	    tmp[0] = 0;
	    sprintf (tmp, "%d", list->p->timer_dom);
	    strcat (order, tmp);
	    strcat(order , " ");
	    strcat(order, list->p->skin);
	    strcat(order, " ");
	    strcat(order, list->p->nom);
	    strcat(order , " ");
	    strcat(order, list->p->nom_superieur);
	    strcat(order , " ");
	    strcat(order, list->p->titre);
	    strcat(order , " ");
	    strcat(order, list->p->region);
	    if (list->p->est_chef == 'y')
	        strcat(order, " y [");
	    else
		strcat(order, " n [");
	    for (struct linked_char *p = list->p->e_list; p != NULL; p = p->next)
	    {
	        strcat(order, p->nom);
	        if (p->next != NULL)
	    	    strcat(order, " ");
	    }
	    strcat(order, "] [");
	    for (struct linked_char *p = list->p->i_list; p != NULL; p = p->next)
	    {
	        strcat(order, p->nom);
	        if (p->next != NULL)
	            strcat(order, " ");
	    }
	    strcat(order, "] ");
	    strcat(order, list->p->echange_player);
	    strcat(order, " ");
	    tmp[0] = 0;
	    sprintf (tmp, "%d", list->p->item1);
	    strcat (order, tmp);
	    strcat(order , " ");
	    tmp[0] = 0;
	    sprintf (tmp, "%d", list->p->item2);
	    strcat (order, tmp);
	}
    }
    int s = strlen(order);
    if (s > 0)
    {
	tmp[0] = 0;
        strcat(tmp, "ordre");
        sprintf (tmp + 5, "%d", s);
	send(socket, tmp, 20, MSG_NOSIGNAL);
        send(socket, order, s, MSG_NOSIGNAL);
    }
    free(order);
}
