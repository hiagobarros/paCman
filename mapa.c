#include "mapa.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void copyMap(MAPA* m, MAPA* copyM){
    copyM->colunas = m->colunas;
    (*copyM).linhas = m->linhas;

    mallocMap(copyM);
    for(int i = 0; i < m->linhas; i++)
        strcpy(copyM->matriz[i], m->matriz[i]);
    

}

void movingOnMap(MAPA *m, int originX, int originY, int destinationX, int destinationY){
    char character =  m->matriz[originX][originY];
    m->matriz[originX][originY] = EMPTY;
    m->matriz[destinationX][destinationY] = character;

}

int isWall(MAPA* m, int x, int y){
    return m->matriz[x][y] == WALL || m->matriz[x][y] == VERTICAL_WALL;
}

int isCharacter(MAPA* m, char character, int x, int y){
    return m->matriz[x][y] == character;
}

int canMove(MAPA* m, char character, int x , int y){

    return isValid(m, x, y) && !isWall(m, x, y) && !isCharacter(m, character, x, y);

}

int isEmpty(MAPA* m, int nextX, int nextY){
    if(m->matriz[nextX][nextY]==EMPTY)
        return 1;

    return 0;
}

int isValid(MAPA* m, char positionX, char positionY){
    if(positionY >= m->colunas || 
        positionX >= (*m).linhas)
        return 0;

    return 1;
}

int findOnMap(MAPA* m, POSICAO* p, char c){
    for (int i = 0; i < m->linhas; i++) {
        for (int j = 0; j < (*m).colunas; j++) {
            if(m->matriz[i][j] == c){
                p->x=i;
                (*p).y=j;
                return 1;
            }
        }
    }
    return 0;
}

void desmallocMap(MAPA* m){
        for (int i = 0; i < m->linhas; i++)
        {
            free(m->matriz[i]);
        }
        free((*m).matriz);
}

void mallocMap(MAPA* m){
    m->matriz = malloc(sizeof(char*) * m->linhas);
        for (int i = 0; i < m->linhas; i++)
        {
            m->matriz[i] = malloc(sizeof(char) * (m->colunas +1));
        }
}

void map(MAPA* m)
{
    FILE *f;
    f = fopen("mapa.txt", "r");
        if(!f){
            printf("Erro na leitura do mapa.");
            exit(1);
        }
        fscanf(f,"%d %d", &(m->linhas), &(m->colunas));

        mallocMap(m);
        //scaning such FILE string by string
        for (int i = 0; i < m->linhas; i++)
        {
            fscanf(f,"%s",m->matriz[i]);
        }  
    fclose(f);
}

