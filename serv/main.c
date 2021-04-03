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

void cut(char *str, char cutter)
{
	int i = 0;
	while (str[i] != 0)
	{
		if (str[i] == cutter)
		{
			str[i] = 0;
			return;
		}
		i++;
	}
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
	struct linked_client *unlog_client = NULL;
	struct linked_client *logged_client = NULL;
	struct linked_client *ingame_client = NULL;
	struct linked_client *client;
	struct linked_client *next;

	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM,0);
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(atoi(argv[1]));
	server_address.sin_addr.s_addr = INADDR_ANY;
	fcntl(server_socket, F_SETFL, O_NONBLOCK);
	bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
	listen(server_socket, 120);

	char boolrep;
	char buffer[103];
	int save = 0;
	//debout boucle, on suppose que la carte est initialisée.
	while (1 == 1)
	{
		int new = accept(server_socket, NULL, NULL);
		if (new >= 0)
		{
			fcntl(new, F_SETFL, O_NONBLOCK);
			unlog_client = append_linked(unlog_client, new, NULL);
		}
		next = unlog_client;
		client = unlog_client;
		while (client != NULL)
        {
			next = next->next;
			if (recv(client->socket, &buffer,101, 0) > 0)
			{
				client->afk_timmer = 0;
				if (open_acount(buffer) == 1)
				{
					boolrep = 'o';
					send(client->socket, &boolrep, 1, MSG_NOSIGNAL);
					cut(buffer, ' ');
					logged_client = append_linked(logged_client, client->socket, buffer);
					unlog_client = remove_linked(unlog_client, client->socket);
				}
				else
				{
					boolrep = 'n';
					send(client->socket, &boolrep, 1, MSG_NOSIGNAL);
				}
			}
			else
			{
				client->afk_timmer += 1;
				if (client->afk_timmer > 5000000)
				{
					close(client->socket);
					unlog_client = remove_linked(unlog_client, client->socket);
				}
			}
			client = next;
		}
		next = logged_client;
		client = logged_client;
		while (client != NULL)
		{
			next = next->next;
			if (recv(client->socket, &buffer, 102, 0) > 0)
			{
				client->afk_timmer = 0;
				if (buffer[0] == 'p')
				{
					if (have_char(list, client->name) == 1)
					{
						boolrep = 'o';
						send(client->socket, &boolrep, 1, MSG_NOSIGNAL);
						send_map(client->socket, list);
						ingame_client = append_linked(ingame_client, client->socket, client->name);
						send_background(client->socket, ground, len_of_ground);
						logged_client = remove_linked(logged_client, client->socket);
					}
					else
					{
						boolrep = 'n';
						send(client->socket, &boolrep, 1,MSG_NOSIGNAL);
					}
				}
				if (buffer[0] == 'c')
				{
					if (have_char(list, client->name) == 1)
					{
						boolrep = 'n';
						send(client->socket, &boolrep, 1,MSG_NOSIGNAL);
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
						strcat(line, client->name);
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
						boolrep = 'o';
						send(client->socket, &boolrep, 1,MSG_NOSIGNAL);
						send_map(client->socket, list);
						ingame_client = append_linked(ingame_client, client->socket, client->name);
						send_background(client->socket, ground, len_of_ground);
						logged_client = remove_linked(logged_client, client->socket);
					}
				}
			}
			else
			{
				client->afk_timmer += 1;
				if (client->afk_timmer > 5000000)
				{
					close(client->socket);
					logged_client = remove_linked(logged_client, client->socket);
				}
			}
			client = next;
		}
		next = ingame_client;
		client = ingame_client;
		while (client != NULL)
		{
			next = next->next;
			int afk = handle_req(client->socket, list, movedObj);
			if (afk == 1)
				client->afk_timmer += 1;
			else
				client->afk_timmer = 0;
			if (client->afk_timmer > 50000000)
			{
				close(client->socket);
				ingame_client = remove_linked(ingame_client, client->socket);
			}
			client = next;
		}
		time = clock();
		t2 = (float)(time / (CLOCKS_PER_SEC / 1000));
		if (t2 - t > 20)
		{
			t = t2;
			char *order = calloc(100000, 1);
			int size = generate_order(list, movedObj, order);
			for (struct linked_client *client = ingame_client; client != NULL; client=client->next)
				send(client->socket, order, size + 20, MSG_NOSIGNAL);
			for (int i = 0; i < 400; i++)
				movedObj[i] = -1;
			free(order);
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
