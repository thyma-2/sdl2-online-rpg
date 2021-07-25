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
#include "net.h"
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

int main(int argc, char **argv)
{
	clock_t time = clock();
	float t = (float)(time / CLOCKS_PER_SEC);
	float t2;
	if (argc != 2)
	{
		printf ("error 1 : serv need a port\n");
		return 1;
	}

	FILE *f = fopen("ground.txt", "rb");
	if (f == NULL)
	{
		fputs("connot open gmap.txt", stderr);
		exit(0);
	}

	fseek(f, 0, SEEK_END);
	size_t size_ground = ftell(f);
	fseek(f, 0, SEEK_SET);  /* same as rewind(f); */
	size_t sizeline = 0;
	while (fgetc(f) != '\n')
		sizeline++;
	size_ground -= sizeline;
	char *ground = malloc(size_ground);
	char *spawn = malloc(sizeline);
	fseek(f, 0, SEEK_SET);
	fread(spawn, sizeline, 1, f);
	fseek(f, sizeline + 1, SEEK_SET);
	fread(ground, size_ground, 1, f);
	fclose(f);
	ground[size_ground] = 0;
	spawn[sizeline] = 0;

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
						send_background(client->socket, ground, size_ground);
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
						tmp[0] = 0;
						int id = find_smalest_valid_id(list, 0);
						sprintf (tmp, "%d", id); 
						strcpy(line, tmp);
						strcat(line, " 10 ");
						strcat(line, client->name);
						strcat(line, " ");
						strcat(line, spawn);
						strcat(line, " -1 0 0 0 1000000 civil ");
						strcat(line, client->name);
						strcat(line, " none none none region1 n [] [] none 0 0 [] 0 0 ");
						append_perso(line, list);
						boolrep = 'o';
						send(client->socket, &boolrep, 1,MSG_NOSIGNAL);
						send_map(client->socket, list);
						ingame_client = append_linked(ingame_client, client->socket, client->name);
						send_background(client->socket, ground, size_ground);
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
			int afk = handle_req(client->socket, list);
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
		if (t2 - t > 15)
		{
			t = t2;
			char *order = calloc(100000, 1);
			int size = generate_order(list, order);
			for (struct linked_client *client = ingame_client; client != NULL; client=client->next)
				send(client->socket, order, size + 20, MSG_NOSIGNAL);
			list = remove_perso(list);
			free(order);
		}
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
