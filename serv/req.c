#include "req.h"

void send_background(int socket,char *map, size_t size_map)
{
	char *str_nb = calloc(sizeof(char), 9);
	sprintf(str_nb, "%ld", size_map);
	send(socket, str_nb, 8, MSG_NOSIGNAL);
	send(socket, map, size_map, MSG_NOSIGNAL);
	free(str_nb);
}


char handle_req(int socket, struct personnages *list, int *movedObj)
{
	char *buffer = calloc(20, 1);
	if (recv(socket, buffer, 20, 0) > 0)
	{
		if (strncmp(buffer, "ordre", 5) == 0)
		{
			int size = atoi(&buffer[5]);
			if (size > 0)
			{
				buffer = realloc(buffer, size + 3);
				int res  = 0;
				char *pos_buf = buffer;
				while (res < size)
				{
					int tmp = recv(socket, buffer, size - res, MSG_WAITALL);
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
					if (id == -1)
					{
						list = append_perso(&buffer, list);
						int id = find_smalest_valid_id(list, 0);
						struct personnages *yalist = get_ptr_from_id(-1, list);
						yalist->id = id;
						append(movedObj, id, 400);
					}
					else
					{
						append(movedObj, id, 400);
						struct personnages *yalist = get_ptr_from_id(id, list);
						if (yalist != NULL)
							buffer += parse_order(yalist, buffer) + 1;
					}
				}
				buffer = pos_buf;
			}
		}
		free(buffer);
		return 0;
	}
	else
	{
		free(buffer);
		return 1;
	}
}
