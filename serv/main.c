#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include "perso.h"
#include "map_op.h"

int open_acount(char *test)
{
    if (test[0] == '\0' || test[0] == '\n')
        return 0;
    FILE *acount = fopen("acount.txt", "r");
    char *line = NULL;
    size_t len = 0;
    while (getline(&line, &len, acount) > 0)
    {
        if (strncmp(line, test, strlen(line) - 1) == 0)
        {
            fclose(acount);
            return 1;
        }
    }
    fclose(acount);
    return 0;
}

int append(int *list, int to_add, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (list[i] == to_add)
            return i;
        else if (list[i] < 0)
        {
            list[i] = to_add;
            return i;
        }
    }
    return -1;
}

void set_name(char *list, char *buffer)
{
    int i = 0;
    while (buffer[i] != ' ' && buffer[i] != 0)
    {
        list[i] = buffer[i];
        i++;
    }
    list[i] = 0;
}

int have_char(struct personnages *list, char *name)
{
    while (list)
    {
        if (strcmp(list->nom_de_compte, name) == 0)
            return 1;
        list = list->next;
    }
    return -1;
}

char *load_ground(size_t *size)
{
    FILE *f = fopen("gmap.txt", "rb");
    fseek(f, 0, SEEK_END);
    size_t fsize = ftell(f);
    fseek(f, 0, SEEK_SET);  /* same as rewind(f); */
    
    char *source = malloc(fsize + 1);
    fread(source, 1, fsize, f);
    fclose(f);
    *size = fsize;
    source[fsize] = 0;
    return source;
}

void send_background(int socket,char *map, size_t size_map)
{
    char *str_nb = calloc(sizeof(char), 9);
    sprintf(str_nb, "%ld", size_map);
    send(socket, str_nb, 8, MSG_NOSIGNAL);
    send(socket, map, size_map, MSG_NOSIGNAL);
    free(str_nb);
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf ("error 1 : serv need a port\n");
        return 1;
    }

    size_t len_of_ground;
    char *ground = load_ground(&len_of_ground);
    if (ground == NULL)
        fputs("connot open gmap.txt", stderr);

    struct personnages *list = init_map();
    int unlog_client[10];
    unsigned int unlog_client_afk_timing[10];
    int logged_client[10];
    unsigned int logged_client_afk_timing[10];
    char arr_name[10][50];
    int ingame_client[100];
    char ingame_arr_name[100][50];
    unsigned int ingame_client_afk_timing[100];

    for (int i = 0; i < 10; i++)
    {
        unlog_client[i] = -1;
        logged_client[i] = -1;
        unlog_client_afk_timing[i] = 0;
        logged_client_afk_timing[i] = 0;
    }

    for (int i = 0; i < 100; i++)
    {
        ingame_client[i] = -1;
        ingame_client_afk_timing[i] = 0;
    }

    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM,0);
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(atoi(argv[1]));
    server_address.sin_addr.s_addr = INADDR_ANY;
    fcntl(server_socket, F_SETFL, O_NONBLOCK);
    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
    listen(server_socket, 120);

    char *boolrep = malloc(1);
    int save = 0;
    //debout boucle, on suppose que la carte est initialisée.
    while (1 == 1)
    {
        for (int i = 0; i < 10; i++)
        {
            if (unlog_client[i] < 0)
            {
                unlog_client[i] = accept(server_socket, NULL, NULL);
                fcntl(unlog_client[i], F_SETFL, O_NONBLOCK);
            }
            if (unlog_client[i] > 0)
            {
                char *buffer = calloc(101, 1);
                recv(unlog_client[i], buffer,101, 0);
                if (buffer[0] != 0)
                {
                    unlog_client_afk_timing[i] = 0;
                    if (open_acount(buffer) == 1)
                    {
                        boolrep[0] = 'o';
                        send(unlog_client[i], boolrep, 1, MSG_NOSIGNAL);
                        int j = append(logged_client, unlog_client[i], 10);
                        set_name(arr_name[j], buffer);
                        unlog_client[i] = -1;
                    }
                    else
                    {
                        boolrep[0] = 'n';
                        send(unlog_client[i], boolrep, 1, MSG_NOSIGNAL);
                    }
                }
                else
                {
                    unlog_client_afk_timing[i] += 1;
                    if (unlog_client_afk_timing[i] > 5000000)
                    {
                        close(unlog_client[i]);
                        unlog_client[i] = -1;
                        unlog_client_afk_timing[i] = 0;
                    }
                }
                free(buffer);
            }
        }
        for (int i = 0; i < 10; i++)
        {
            if (logged_client[i] > 0)
            {
                char *buffer = calloc(1, 1);
                recv(logged_client[i], buffer, 1, 0);
                if (buffer[0] != 0)
                {
                    logged_client_afk_timing[i] = 0;
                    if (buffer[0] == 'p')
                    {
                        if (have_char(list, arr_name[i]) == 1)
                        {
                            boolrep[0] = 'o';
                            send(logged_client[i], boolrep, 1, MSG_NOSIGNAL);
                            send_map(logged_client[i], list);
                            int j = append(ingame_client, logged_client[i], 10);
                            set_name(ingame_arr_name[j], arr_name[j]);
                            logged_client[i] = -1;
                            logged_client_afk_timing[i] = 0;
                        }
                        else
                        {
                            boolrep[0] = 'n';
                            send(logged_client[i], boolrep, 1,MSG_NOSIGNAL);
                        }
                    }
                }
                else
                {
                    logged_client_afk_timing[i] += 1;
                    if (logged_client_afk_timing[i] > 5000000)
                    {
                        close(logged_client[i]);
                        logged_client[i] = -1;
                        logged_client_afk_timing[i] = 0;
                    }
                }
                free(buffer);
            }
        }
        int movedObj[400];
        for (int i = 0; i < 400; i++)
            movedObj[i] = -1;
        for (int i = 0; i < 100; i++)
        {
            if (ingame_client[i] > 0)
            {
                char *buffer = calloc(20, 1);
                if (recv(ingame_client[i], buffer, 20, 0) > 0)
                {
                    ingame_client_afk_timing[i] = 0;
                    if (strncmp(buffer, "ordre", 5) == 0)
                    {
                        int size = atoi(&buffer[5]);
			free(buffer);
			if (size > 0)
			{
			    buffer = calloc(1, size + 3);
    			    int res  = 0;
			    char *pos_buf = buffer;
			    while (res < size)
			    {
			        int tmp = recv(ingame_client[i], buffer, size - res, 0);
				if (tmp == -1)
				{
				    res = size + 1;
				    pos_buf[0] = 0;
				}
			        res += tmp;
		                buffer = buffer + tmp;
			    }
		            buffer = pos_buf;
			    while (*buffer != 0)
			    {
			        int id = get_id(buffer);
                                append(movedObj, id, 400);
                                struct personnages *yalist = get_ptr_from_id(id, list);
                                if (yalist == NULL)
				{
				    printf ("%s\n", buffer);
                                    append_perso(&buffer, list);
				}
                                else
                                    buffer += parse_order(yalist, buffer) + 1;
			    }
			    buffer = pos_buf;
			}
		    }
		    else if (strncmp(buffer, "get_ground", 10) == 0)
		        send_background(ingame_client[i], ground, len_of_ground);
                }
                else
                {
                    ingame_client_afk_timing[i] += 1;
                    if (ingame_client_afk_timing[i] > 5000000)
                    {
                        close(ingame_client[i]);
                        ingame_client[i] = -1;
                        ingame_client_afk_timing[i] = 0;
                    }
                }
                free(buffer);
            }
        }
        for (int i = 0; i < 100; i++)
            if (ingame_client[i] > 0)
                send_order(ingame_client[i], list, movedObj);
	list = remove_perso(list);
        save++;
        if (save > 1000000)
        {
            printf("\nSAVE\n");
            save = 0;
            save_map(list);
        }
    }
    return 0;
}
