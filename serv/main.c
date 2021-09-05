#include "main.h"

struct personnages *list = NULL;
struct personnages *flag = NULL;

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
	char *ground = malloc(size_ground);
	fread(ground, size_ground, 1, f);
	fclose(f);
	ground[size_ground] = 0;

	list = init_map();
	flag = list;
	while (strcmp(flag->skin, "flag_zone") != 0)
		flag = flag->next;
	list = croissance_pop(list);
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
	char *order = calloc(10000, 1);
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
					if (have_char(client->name) == 1)
					{
						boolrep = 'o';
						send(client->socket, &boolrep, 1, MSG_NOSIGNAL);
						send_background(client->socket, ground, size_ground);
						send_map(client->socket);
						ingame_client = append_linked(ingame_client, client->socket, client->name);
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
					if (have_char(client->name) == 1)
					{
						boolrep = 'n';
						send(client->socket, &boolrep, 1,MSG_NOSIGNAL);
					}
					else
					{
						create_new_char(client->name);
						boolrep = 'o';
						send(client->socket, &boolrep, 1,MSG_NOSIGNAL);
						send_background(client->socket, ground, size_ground);
						send_map(client->socket);
						ingame_client = append_linked(ingame_client, client->socket, client->name);
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
			int afk = handle_req(client->socket);
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
		t2 = (float)(time / (CLOCKS_PER_SEC / 60));
		if (t2 - t >= 1)
		{
			t = t2;
			int size = generate_order(order);
			for (struct linked_client *client = ingame_client; client != NULL; client=client->next)
				send(client->socket, order, size + 20, MSG_NOSIGNAL);
			list = remove_perso();
		}
		save++;
		if (save > 10000000)
		{
			printf("\nSAVE\n");
			save = 0;
			save_map();
		}
	}
	return 0;
}
