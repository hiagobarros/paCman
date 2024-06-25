#include <stdio.h>
//#include <string.h>
#include <stdlib.h>
//#include "pacman.h"
#include "ui.h"
#include "mapa.h"
//#include <time.h>

char desenhofantasma[4][7] = {
    {" .-.  " },
    {"| OO| " },
    {"|   | " },
    {"'^^^' " }
};

char desenhoparede[4][7] = {
    {"......" },
    {"......" },
    {"......" },
    {"......" }
};

char desenhoheroi[4][7] = {
    {" .--. "  },
    {"/ _.-'"  },
    {"\\  '-." },
    {" '--' "  }
};

char desenhopilula[4][7] = {
    {"      "},
    {" .-.  "},
    {" '-'  "},
    {"      "}
};

char desenhovazio[4][7] = {
    {"      "},
    {"      "},
    {"      "},
    {"      "}
};

void imprimeparte(char desenho[4][7], int parte) {
    printf("%s", desenho[parte]);
}

void printMap(MAPA* m) {
    for(int i = 0; i < m->linhas; i++) {

        for(int parte = 0; parte < 4; parte++) {
            for(int j = 0; j < m->colunas; j++) {

                switch(m->matriz[i][j]) {
                    case PHANTOM:
                        imprimeparte(desenhofantasma, parte);
                        break;
                    case PACMAN:
                        imprimeparte(desenhoheroi, parte);
                        break;
                    case PILL:
                        imprimeparte(desenhopilula, parte);
                        break;
                    case VERTICAL_WALL:
                    case WALL:
                        imprimeparte(desenhoparede, parte);
                        break;
                    case EMPTY:
                        imprimeparte(desenhovazio, parte);
                        break;
                }

            }
            printf("\n");
        }

    }
}
