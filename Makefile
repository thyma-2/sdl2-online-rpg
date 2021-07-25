cflags=-Wall -Werror -Wextra -g -std=c99 -pedantic
jfiles=jeu/net.c jeu/gui.c jeu/perso.c jeu/init_sprite.c jeu/select_sprite.c jeu/clavier.c jeu/alloc.c jeu/control.c jeu/parseur.c jeu/collision.c jeu/ordre.c jeu/ia.c jeu/map.c jeu/linked_char.c jeu/stat.c jeu/chiffrement.c jeu/inventaire.c jeu/diplo.c jeu/pathfinding.c jeu/init_sound.c jeu/btree.c
sfiles=serv/perso.c serv/map_op.c serv/req.c serv/utile.c serv/deschiffrement.c serv/net.c serv/diplo.c serv/inventaire.c
efiles=editmap/init_img.c editmap/select_sprite.c


j:
	gcc ${cflags} jeu/main.c $(jfiles) -o empireExpense -Bstatic -lSDL2 -lSDL2_mixer -Bdynamic -Wl,--no-undefined -lm -ldl -lasound -lm -ldl -lpthread -lpulse-simple -lpulse -lsndio -lX11 -lXext -lXcursor -lXinerama -lXi -lXrandr -lXss -lXxf86vm -lwayland-egl -lwayland-client -lwayland-cursor -lxkbcommon -lpthread -lrt

s:
	gcc $(cflags) serv/main.c $(sfiles) -lpthread -o serveur

satan:
	gcc ${cflags} -fsanitize=address jeu/main.c $(jfiles) -o empireExpense -lSDL2 -lm

e:
	gcc $(cflags) editmap/main.c $(efiles) -o mapEditor -Bstatic -lSDL2 -lSDL2_mixer -Bdynamic -Wl,--no-undefined -lm -ldl -lasound -lm -ldl -lpthread -lpulse-simple -lpulse -lsndio -lX11 -lXext -lXcursor -lXinerama -lXi -lXrandr -lXss -lXxf86vm -lwayland-egl -lwayland-client -lwayland-cursor -lxkbcommon -lpthread -lrt

