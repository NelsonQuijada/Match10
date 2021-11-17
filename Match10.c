#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_PLAYERS 1

void fillBoard(int matrix[][9]);
void showMatrix(int matrix[][9], int rows);
bool checkMatrix(int matrix[][9], int rows);
bool checkCorner(int matrix[][9], int i, int j, int rows);

struct player {
    char name[20];
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

bool checkMatrix(int matrix[][9], int rows) {
    bool availablepair;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < 9; j++) {
            if (i == 0 || i == rows-1) {
                if (j == 0 || j == 8) {
                    availablepair = checkCorner(matrix, i, j, rows);
                    if (availablepair == 1){
                        return availablepair;
                    }
                }
            }
        }
    }
    return availablepair;
}

bool checkCorner(int matrix[][9], int i, int j, int rows) {
    bool result;
    if (i == 0) {
        if (j == 0) {
            // Esquina superior izquierda
            if (matrix[i][j] + matrix[i + 1][j] == 10 ||
                matrix[i][j] + matrix[i + 1][j + 1] == 10 ||
                matrix[i][j] + matrix[i][j + 1] == 10) {
                return 1;
            } else {
                return 0;
            }
        } else if (j == 8) {
            // Esquina superior derecha
            if (matrix[i][j] + matrix[i + 1][j] == 10 ||
                matrix[i][j] + matrix[i + 1][j - 1] == 10 ||
                matrix[i][j] + matrix[i][j - 1] == 10) {
                return 1;
            } else {
                return 0;
            }
        }
    }

    else if (i == rows-1) {
        if (j == 0) {
            // Esquina Inferior Izquierda
            if (matrix[i][j] + matrix[i - 1][j] == 10 ||
                matrix[i][j] + matrix[i - 1][j + 1] == 10 ||
                matrix[i][j] + matrix[i][j + 1] == 10) {
                return 1;
            } else {
                return 0;
            }
        } else if (j == 8) {
            // Esquina Inferior Derecha
            if (matrix[i][j] + matrix[i - 1][j] == 10 ||
                matrix[i][j] + matrix[i - 1][j - 1] == 10 ||
                matrix[i][j] + matrix[i][j - 1] == 10) {
                return 1;
            }

            else {
                return 0;
            }
        }
    }
}
