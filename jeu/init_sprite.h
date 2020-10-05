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
    SDL_Surface *hoFaDoRien;
    SDL_Surface *hoFaDoMa1;
    SDL_Surface *hoFaDoMa2;
    SDL_Surface *hoFaDoMa3;
    SDL_Surface *hoFaDoMa4;
    SDL_Surface *hoFaDoMa5;
    SDL_Surface *hoFaDoDrRien;
    SDL_Surface *hoFaDoDrMa1;
    SDL_Surface *hoFaDoDrMa2;
    SDL_Surface *hoFaDoDrMa3;
    SDL_Surface *hoFaDoDrMa4;
    SDL_Surface *hoFaDoDrMa5;
    SDL_Surface *hoFaDrDoRien;
    SDL_Surface *hoFaDrDoMa1;
    SDL_Surface *hoFaDrDoMa2;
    SDL_Surface *hoFaDrDoMa3;
    SDL_Surface *hoFaDrDoMa4;
    SDL_Surface *hoFaDrDoMa5;
    SDL_Surface *hoFaDrRien;
    SDL_Surface *hoFaDrMa1;
    SDL_Surface *hoFaDrMa2;
    SDL_Surface *hoFaDrMa3;
    SDL_Surface *hoFaDrMa4;
    SDL_Surface *hoFaDrMa5;
    SDL_Surface *hoFaDrFaRien;
    SDL_Surface *hoFaDrFaMa1;
    SDL_Surface *hoFaDrFaMa2;
    SDL_Surface *hoFaDrFaMa3;
    SDL_Surface *hoFaDrFaMa4;
    SDL_Surface *hoFaDrFaMa5;
    SDL_Surface *hoFaFaDrRien;
    SDL_Surface *hoFaFaDrMa1;
    SDL_Surface *hoFaFaDrMa2;
    SDL_Surface *hoFaFaDrMa3;
    SDL_Surface *hoFaFaDrMa4;
    SDL_Surface *hoFaFaDrMa5;
    SDL_Surface *hoFaFaRien;
    SDL_Surface *hoFaFaMa1;
    SDL_Surface *hoFaFaMa2;
    SDL_Surface *hoFaFaMa3;
    SDL_Surface *hoFaFaMa4;
    SDL_Surface *hoFaFaMa5;
    SDL_Surface *hoFaFaGaRien;
    SDL_Surface *hoFaFaGaMa1;
    SDL_Surface *hoFaFaGaMa2;
    SDL_Surface *hoFaFaGaMa3;
    SDL_Surface *hoFaFaGaMa4;
    SDL_Surface *hoFaFaGaMa5;
    SDL_Surface *hoFaGaFaRien;
    SDL_Surface *hoFaGaFaMa1;
    SDL_Surface *hoFaGaFaMa2;
    SDL_Surface *hoFaGaFaMa3;
    SDL_Surface *hoFaGaFaMa4;
    SDL_Surface *hoFaGaFaMa5;
    SDL_Surface *hoFaGaRien;
    SDL_Surface *hoFaGaMa1;
    SDL_Surface *hoFaGaMa2;
    SDL_Surface *hoFaGaMa3;
    SDL_Surface *hoFaGaMa4;
    SDL_Surface *hoFaGaMa5;
    SDL_Surface *hoFaGaDoRien;
    SDL_Surface *hoFaGaDoMa1;
    SDL_Surface *hoFaGaDoMa2;
    SDL_Surface *hoFaGaDoMa3;
    SDL_Surface *hoFaGaDoMa4;
    SDL_Surface *hoFaGaDoMa5;
    SDL_Surface *hoFaDoGaRien;
    SDL_Surface *hoFaDoGaMa1;
    SDL_Surface *hoFaDoGaMa2;
    SDL_Surface *hoFaDoGaMa3;
    SDL_Surface *hoFaDoGaMa4;
    SDL_Surface *hoFaDoGaMa5;

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
    SDL_Surface *fruit;
    SDL_Surface *legume;
    SDL_Surface *arbre1;
};

struct gui_sprite
{
    SDL_Surface *croix;
    SDL_Surface *croix_inverse;
    SDL_Surface *textInput;
    SDL_Surface *selTextInput;
    SDL_Surface *narrowTextInput;
    SDL_Surface *narrowSelTextInput;
    SDL_Surface *demarcation;
    SDL_Surface *plus;
    SDL_Surface *moins;
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
    SDL_Surface *espace;
};

struct img *init_img(SDL_Window *window);
struct textures *init_textures(SDL_Window *window);
struct skin *init_skin(SDL_Window *window);
struct lettres_img *init_lettre(SDL_Window *windows);
struct gui_sprite *init_gui(SDL_Window *window);

struct img *img;
