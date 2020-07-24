cflags=-Wall -Werror -Wextra -g -std=c99 -pedantic
jfiles=jeu/net.c jeu/gui.c jeu/perso.c jeu/init_sprite.c jeu/select_sprite.c jeu/clavier.c jeu/alloc.c jeu/control.c jeu/parseur.c jeu/collision.c jeu/ordre.c jeu/ia.c jeu/map.c jeu/linked_char.c jeu/stat.c
sfiles=serv/perso.c serv/map_op.c


j:
	gcc ${cflags} jeu/main.c $(jfiles) -o empireExpense -lSDL2 -lm

s:
	gcc $(cflags) serv/main.c $(sfiles) -o serveur

satan:
	gcc ${cflags} -fsanitize=address jeu/main.c $(jfiles) -o empireExpense -lSDL2 -lm
