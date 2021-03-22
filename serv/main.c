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
#include <sys/epoll.h>
#include "req.h"
#include "utile.h"
#include "time.h"

#include "deschiffrement.h"
int open_acount(char *test)
{
    if (test[0] == '\0' || test[0] == '\n')
        return 0;
    FILE *acount = fopen("acount.txt", "r");
    char *line = NULL;
    size_t len = 0;
    char *s = test;
    int count  = 0;
    while (*s != ' ')
    {
        count++;
        s = s + 1;
    }
    s = s + 1;
    char *tmp = calloc(count + 1, sizeof(char));
    strncat(tmp, test,count);
    deschifrage(s, tmp);
    free(tmp);
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

int main(int argc, char **argv)
{
    int movedObj[400] = {-1};
    clock_t time = clock();
    float t = (float)(time / CLOCKS_PER_SEC);
    float t2;
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
                char *buffer = calloc(102, 1);
                if (recv(logged_client[i], buffer, 102, 0) > 0)
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
			    send_background(logged_client[i], ground, len_of_ground);
                            logged_client[i] = -1;
                            logged_client_afk_timing[i] = 0;
                        }
                        else
                        {
                            boolrep[0] = 'n';
                            send(logged_client[i], boolrep, 1,MSG_NOSIGNAL);
                        }
                    }
		    if (buffer[0] == 'c')
		    {
			if (have_char(list, arr_name[i]) == 1)
			{
			    boolrep[0] = 'n';
  			    send(logged_client[i], boolrep, 1,MSG_NOSIGNAL);
			}
			else
			{
			    char *line = malloc(1000);
			    char tmp[20];
			    line[0] = 0;
			    tmp[0] = 0;
			    int id = find_smalest_valid_id(list, 0);
			    sprintf (tmp, "%d", id); 
			    strcat(line, tmp);
			    strcat(line, " 10 ");
			    strcat(line, arr_name[i]);
			    strcat(line, " 10 10 -1 0 0 0 civil ");
			    int k = 1;
			    int j = strlen(line);
			    while (buffer[k] != ' ')
			    {
				line[j] = buffer[k];
				k++;
				j++;
			    }
			    line[j] = 0;
		            strcat(line, " none none ");
			    j += 12;
			    k++;
			    while (buffer[k] != 0)
			    {
				line[j] = buffer[k];
				k++;
				j++;
			    }
			    line[j] = 0;
			    strcat (line, " n [] []none 0 0 []");
			    append_perso(&line, list);
			    append(movedObj, id, 400);
			    boolrep[0] = 'o';
                            send(logged_client[i], boolrep, 1,MSG_NOSIGNAL);
			    send_map(logged_client[i], list);
                            j = append(ingame_client, logged_client[i], 10);
                            set_name(ingame_arr_name[j], arr_name[j]);
                            send_background(logged_client[i], ground, len_of_ground);
                            logged_client[i] = -1;
                            logged_client_afk_timing[i] = 0;
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
        for (int i = 0; i < 100; i++)
        {
            if (ingame_client[i] > 0)
            {
		int afk = handle_req(ingame_client[i], list, movedObj);
	        if (afk == 1)
		    ingame_client_afk_timing[i] += 1;
		else
		    ingame_client_afk_timing[i] = 0;
                if (ingame_client_afk_timing[i] > 50000000)
                {
                    close(ingame_client[i]);
                    ingame_client[i] = -1;
                    ingame_client_afk_timing[i] = 0;
                }
            }
        }
	time = clock();
    	t2 = (float)(time / (CLOCKS_PER_SEC / 1000));
	if (t2 - t > 20)
	{
	    t = t2;
            for (int i = 0; i < 100; i++)
                if (ingame_client[i] > 0)
                    send_order(ingame_client[i], list, movedObj);
 	    for (int i = 0; i < 400; i++)
                movedObj[i] = -1;
	}
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
