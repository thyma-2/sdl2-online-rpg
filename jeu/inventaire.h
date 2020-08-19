#include "perso.h"
#include "linked_char.h"

struct linked_char *use(int n, struct personnages *p);
int count(char *name);
struct linked_char *append_in_inventory(char *name, struct linked_char *p, int n);
struct linked_char *remove_from_inventory(char *name, struct linked_char *p, int n);
