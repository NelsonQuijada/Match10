#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_PLAYERS 2

void fillBoard(int matrix[][9]);
void showMatrix(int matrix[][9], int N);

struct player {
    char name[20];
    int turn;
    int points;
};

int main() {
    srand(time(NULL));

    int shownRows = 3;
    int board[9][9];
    fillBoard(board);

    struct player totalPlayers[NUM_PLAYERS];
    printf("Bienvenidos a Match 10!\n");

    for (int i = 0; i < NUM_PLAYERS; i++) {
        printf("Ingrese su nickname (maximo 20 caracteres) jugador %d: ",
               i + 1);
        scanf("%s", &totalPlayers[i].name);

        totalPlayers[i].turn = i;
        totalPlayers[i].points = 0;
    }

    int continues = 1;
    while (continues == 1) {

        int chosenRow[2];
        int chosenCol[2];

        for (int number = 0; number < NUM_PLAYERS; number++) {
            printf("%s, es su turno.\n", totalPlayers[number].name);

            for (int i = 0; i < 2; i++) {
                printf("Este es el tablero de juego!\n");
                showMatrix(board, shownRows);

                printf(
                    "Por favor, ingrese la fila del numero %d que quiere "
                    "seleccionar: ",
                    i + 1);
                scanf("%d", &chosenRow[number]);
                printf("La fila seleccionada es:\n");
                showMatrix(board, chosenRow[number]);

                printf("Seleccione una columna del numero %d en esta fila: ",
                       i + 1);
                scanf("%d", &chosenCol[number]);

                printf("Su seleccion numero %d es: %d\n", i + 1,
                       board[chosenRow[number]-1][chosenCol[number]-1]);
            }
        }
    }
    printf("Recordar que no es la version final, entonces los puntos no estan definidos y el loop es infinito.\n");
    printf("Ctr+C para terminar");
}

void fillBoard(int matrix[][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            matrix[i][j] = rand() % (9 - 1 + 1) + 1;
        }
    }
}

void showMatrix(int matrix[][9], int rows) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}