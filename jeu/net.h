#include "alloc.h"

#ifndef NET
#define NET

#include "sys/types.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "arpa/inet.h"
#include "perso.h"
#include "parseur.h"
#include <stdlib.h>
#include <string.h>

void recv_order(int socket, struct linked_list *list);
void generate_orders(struct linked_list *l, int socket);
int try_connect(char *ip, char *port);
#endif /*NET*/
