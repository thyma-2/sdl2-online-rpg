#pragma once
#include <SDL2/SDL.h>
#include <stdlib.h>

struct img
{
    struct textures *t;
    struct skin *s;
    struct lettres_img *li;
    struct gui_sprite *g;
};

struct textures
{
    SDL_Surface *he1;
    SDL_Surface *he2;
    SDL_Surface *he3;
    SDL_Surface *he4;
    SDL_Surface *he5;
    SDL_Surface *bl1;
    SDL_Surface *bl2;
    SDL_Surface *bl3;
    SDL_Surface *ea1;
    SDL_Surface *ea2;
    SDL_Surface *ea3;
    SDL_Surface *gr1;
    SDL_Surface *gr2;
    SDL_Surface *ne1;
    SDL_Surface *ne2;
    SDL_Surface *ne3;
    SDL_Surface *sa1;
    SDL_Surface *sa2;
    SDL_Surface *sa3;
    SDL_Surface *te1;
    SDL_Surface *te2;
    SDL_Surface *te3;
    SDL_Surface *fond;
};

struct skin
{
    SDL_Surface *hoArDoMa1; // homme archer Dos Marcher 1
    SDL_Surface *hoArDoMa2;
    SDL_Surface *hoArDoMa3;
    SDL_Surface *hoArDoMa4;
    SDL_Surface *hoArDoMa5;
    SDL_Surface *hoArDdMa1;
    SDL_Surface *hoArDdMa2;
    SDL_Surface *hoArDdMa3;
    SDL_Surface *hoArDdMa4;
    SDL_Surface *hoArDdMa5;
    SDL_Surface *hoArDrMa1;
    SDL_Surface *hoArDrMa2;
    SDL_Surface *hoArDrMa3;
    SDL_Surface *hoArDrMa4;
    SDL_Surface *hoArDrMa5;
    SDL_Surface *hoArDfMa1;
    SDL_Surface *hoArDfMa2;
    SDL_Surface *hoArDfMa3;
    SDL_Surface *hoArDfMa4;
    SDL_Surface *hoArDfMa5;
    SDL_Surface *hoArFaMa1;
    SDL_Surface *hoArFaMa2;
    SDL_Surface *hoArFaMa3;
    SDL_Surface *hoArFaMa4;
    SDL_Surface *hoArFaMa5;
    SDL_Surface *hoArGfMa1;
    SDL_Surface *hoArGfMa2;
    SDL_Surface *hoArGfMa3;
    SDL_Surface *hoArGfMa4;
    SDL_Surface *hoArGfMa5;
    SDL_Surface *hoArGaMa1;
    SDL_Surface *hoArGaMa2;
    SDL_Surface *hoArGaMa3;
    SDL_Surface *hoArGaMa4;
    SDL_Surface *hoArGaMa5;
    SDL_Surface *hoArGdMa1;
    SDL_Surface *hoArGdMa2;
    SDL_Surface *hoArGdMa3;
    SDL_Surface *hoArGdMa4;
    SDL_Surface *hoArGdMa5;
    SDL_Surface *ship1haut;
    SDL_Surface *ship1gauchehaut;
    SDL_Surface *ship1gauche;
    SDL_Surface *ship1gauchebas;
    SDL_Surface *ship1bas;
    SDL_Surface *ship1droitebas;
    SDL_Surface *ship1droite;
    SDL_Surface *ship1droitehaut;
};

struct gui_sprite
{
    SDL_Surface *croix;
    SDL_Surface *croix_inverse;
    SDL_Surface *textInput;
    SDL_Surface *selTextInput;
    SDL_Surface *narrowTextInput;
    SDL_Surface *narrowSelTextInput;
};


struct lettres_img
{
    SDL_Surface *a;
    SDL_Surface *b;
    SDL_Surface *c;
    SDL_Surface *d;
    SDL_Surface *e;
    SDL_Surface *f;
    SDL_Surface *g;
    SDL_Surface *h;
    SDL_Surface *i;
    SDL_Surface *j;
    SDL_Surface *k;
    SDL_Surface *l;
    SDL_Surface *m;
    SDL_Surface *n;
    SDL_Surface *o;
    SDL_Surface *p;
    SDL_Surface *q;
    SDL_Surface *r;
    SDL_Surface *s;
    SDL_Surface *t;
    SDL_Surface *u;
    SDL_Surface *v;
    SDL_Surface *w;
    SDL_Surface *x;
    SDL_Surface *y;
    SDL_Surface *z;
    SDL_Surface *k0;
    SDL_Surface *k1;
    SDL_Surface *k2;
    SDL_Surface *k3;
    SDL_Surface *k4;
    SDL_Surface *k5;
    SDL_Surface *k6;
    SDL_Surface *k7;
    SDL_Surface *k8;
    SDL_Surface *k9;
    SDL_Surface *sup;
    SDL_Surface *tirret;
    SDL_Surface *tirret_bas;
    SDL_Surface *slash;
    SDL_Surface *point;
    SDL_Surface *A;
    SDL_Surface *B;
    SDL_Surface *C;
    SDL_Surface *D;
    SDL_Surface *E;
    SDL_Surface *F;
    SDL_Surface *G;
    SDL_Surface *H;
    SDL_Surface *I;
    SDL_Surface *J;
    SDL_Surface *K;
    SDL_Surface *L;
    SDL_Surface *M;
    SDL_Surface *N;
    SDL_Surface *O;
    SDL_Surface *P;
    SDL_Surface *Q;
    SDL_Surface *R;
    SDL_Surface *S;
    SDL_Surface *T;
    SDL_Surface *U;
    SDL_Surface *V;
    SDL_Surface *W;
    SDL_Surface *X;
    SDL_Surface *Y;
    SDL_Surface *Z;
};

struct img *init_img(SDL_Window *window);
struct textures *init_textures(SDL_Window *window);
struct skin *init_skin(SDL_Window *window);
struct lettres_img *init_lettre(SDL_Window *windows);
struct gui_sprite *init_gui(SDL_Window *window);

struct img *img;
