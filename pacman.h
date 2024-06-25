#ifndef _PACMAN_H_
#define _PACMAN_H_

#define RIGHT 'd'
#define LEFT 'a'
#define UP 'w'
#define DOWN 's'
#define BOMB 'b'

int phantomWhereTo( int* posicaoDestinoX, int* posicaoDestinoY, int positionX, int positionY);
void movePhantom();
void move(char direcao);
int acabou();
int isDirection(char direcao);
void explodePilula();
void explodePilula2(int newX, int newY, int someX, int someY, int qtd);

#endif