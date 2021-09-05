cflags=-Wall -Werror -Wextra -g -std=c99 -pedantic
jfiles=jeu/net.c jeu/gui.c jeu/perso.c jeu/init_sprite.c jeu/select_sprite.c jeu/clavier.c jeu/alloc.c jeu/control.c jeu/parseur.c jeu/collision.c jeu/ordre.c jeu/ia.c jeu/map.c jeu/linked_char.c jeu/stat.c jeu/chiffrement.c jeu/inventaire.c jeu/diplo.c jeu/pathfinding.c jeu/init_sound.c jeu/btree.c
sfiles=serv/perso.c serv/map_op.c serv/req.c serv/utile.c serv/deschiffrement.c serv/net.c serv/diplo.c serv/inventaire.c serv/demographie.c serv/acount.c
efiles=editmap/init_img.c editmap/select_sprite.c


j:
	gcc ${cflags} jeu/main.c $(jfiles) -o empireExpense -lSDL2 -lm -lSDL2_mixer

s:
	gcc $(cflags) serv/main.c $(sfiles) -lpthread -o serveur

static:
	gcc ${cflags} jeu/main.c $(jfiles) -o empireExpense `sdl2-config --cflags --static-libs` `sdl2_mixer-config --cflags --static-libs` 

e:
	gcc $(cflags) editmap/main.c $(efiles) -o mapEditor -lSDL2 -lm

