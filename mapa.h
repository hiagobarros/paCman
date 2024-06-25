#ifndef _MAPA_H_
#define _MAPA_H_

#define EMPTY '.'
#define PACMAN '@'
#define PHANTOM 'F'
#define WALL '|'
#define VERTICAL_WALL '-'
#define PILL 'P'

struct mapa
{
    char** matriz;
    int linhas;
    int colunas;
};

typedef struct mapa MAPA;

struct posicao {
    int x;
    int y;
};

typedef struct posicao POSICAO;


void copyMap(MAPA* m, MAPA* copyM);
void movingOnMap(MAPA *m, int originX, int originY, int destinationX, int destinationY);
int canMove(MAPA* n, char character, int x , int y);
int isEmpty(MAPA* m, int nextX, int nextY);
int isValid(MAPA* m, char positionX, char positionY);
int findOnMap(MAPA* m,POSICAO* p, char c );
void desmallocMap(MAPA* m);
void map(MAPA* m);
void printMap(MAPA* m);
void mallocMap(MAPA* m);
int isWall(MAPA* m, int x, int y);
int isCharacter(MAPA* m, char character, int x, int y);

#endif