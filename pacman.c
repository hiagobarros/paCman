#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pacman.h"
#include "mapa.h"
#include <time.h>
#include "ui.h"

MAPA m;
POSICAO pacman;
POSICAO phantom;
int isPill = 0;


int phantomWhereTo(int* posicaoDestinoX, int* posicaoDestinoY, int positionX, int positionY){
    int moveOption[4][2]={
        {positionX, positionY+1},
        {positionX+1, positionY},
        {positionX, positionY-1},
        {positionX-1, positionY}
    };

    srand(time(0));

    for(int i = 0; i < 10; i++){
        int moveDirection = rand() % 4;

        if(canMove( &m, PHANTOM, moveOption[moveDirection][0], moveOption[moveDirection][1])){
           *posicaoDestinoX = moveOption[moveDirection][0];
            *posicaoDestinoY = moveOption[moveDirection][1];
            return 1;
        }
    }
    return 0;
}

void movePhantom(){
    MAPA copyM;
    copyMap(&m, &copyM);
    for (int i = 0; i < copyM.linhas; i++) {
        for (int j = 0; j < copyM.colunas; j++) {
            if(copyM.matriz[i][j] == PHANTOM){
               int  phantomx ;
               int  phantomy;
                

                int moveu = phantomWhereTo(&phantomx , &phantomy , i, j);
                if(moveu){
                    movingOnMap(&m, i, j, phantomx, phantomy );
                }
            }
        }
    }
    desmallocMap(&copyM);
}

int isDirection(char direcao){
    if(direcao == LEFT ||
        direcao == RIGHT ||
        direcao == UP ||
        direcao == DOWN)
        return 1;

    return 0;
}

int acabou(){
    POSICAO zero;
    int pacmanFinded = findOnMap(&m, &zero, PACMAN);
    return !pacmanFinded;
}

void move(char direcao){

    if(!isDirection(direcao))
        return;

    int nextX = pacman.x;
    int nextY = pacman.y;

    switch(direcao){
        case LEFT:
        nextY--;
            break;
        case RIGHT:
        nextY++;
            break;
        case UP:
        nextX--;
            break;
        case DOWN:
        nextX++;
            break;
    }
    if(!canMove( &m, PACMAN, nextX, nextY))
        return;
    if(isCharacter(&m, PILL, nextX, nextY))
        isPill = 1;

    movingOnMap( &m, pacman.x, pacman.y, nextX, nextY);
    pacman.x = nextX;
    pacman.y = nextY;
}

int** lista;
void sendBox(){

    int anguloX= 10;
    int anguloY = 10;
        lista = malloc(sizeof(int*) * anguloX);
    for (int i = 0; i < anguloX; i++)
    {
        lista[i] = malloc(sizeof(int) * anguloY);

    }
    
  

    lista[1][1] = 100;
    int n = lista[1][1];
    printf("%d",n);

    for (int i = 0; i < anguloX; i++)
    {
        free(lista[anguloX]);
    }
    free(lista);

}




void explodePilula(){
    if(!isPill) return
    explodePilula2(pacman.x,pacman.y,0,1,3);
    explodePilula2(pacman.x,pacman.y,0,-1,3);
    explodePilula2(pacman.x,pacman.y,1,0,3);
    explodePilula2(pacman.x,pacman.y,-1,0,3);
    isPill = 0;

}
void explodePilula2(int x, int y, int someX, int someY, int qtd){
    int newX= x + someX;
    int newY= y + someY;

    if(qtd <= 0) return;
    if(!isValid(&m, newX, newY)) return;
    if(isWall(&m, newX, newY)) return;

    m.matriz[newX][newY]=EMPTY;
    explodePilula2(newX, newY,someX ,someY ,qtd-1);
    
}

int main()
{
    sendBox();
    //printf("\033[H\033[J");
    /////////////////////////
    // #ifdef _WWIN32
    //     system("cls");
    // #else
    //     system("clear");
    // #endif
    map(&m);
    findOnMap(&m,&pacman,PACMAN);

    do{
        system("clear");
        printf("\nTem Pilula: %s\n",(isPill ? "SIM" : "NÃO"));
        printMap(&m);
        char comando;
        scanf(" %c",&comando);
        move(comando);
        if(comando == BOMB && isPill) explodePilula();
        movePhantom();

    }while(!acabou());

    desmallocMap(&m);
    return 0;
}


