#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define NUM_PLAYERS 1

void fillBoard(int matrix[][9]);
void showMatrix(int matrix[][9], int rows);
bool checkMatrix(int matrix[][9], int rows);
bool checkCorner(int matrix[][9], int i, int j, int rows);
bool checkTopBotSide(int matrix[][9], int i, int j, int rows);
bool checkLeftRightSide(int matrix[][9], int i, int j, int rows);
bool checkNormal(int matrix[][9], int i, int j, int rows);
bool checkPairs(int matrix[][9], int chosenRow[2],int chosenCol[2]);
void eliminatePair(int matrix[][9], int chosenRow[2],int chosenCol[2]);

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
    bool keepBoard;
    bool isValid;

    while (continues == 1) {
        int chosenRow[2];
        int chosenCol[2];

        keepBoard = checkMatrix(board, shownRows);
        if (keepBoard == 1) {
            for (int number = 0; number < NUM_PLAYERS; number++) {
                printf("%s, es su turno.\n", totalPlayers[number].name);

                for (int i = 0; i < 2; i++) {
                    printf("Este es el tablero de juego!\n");
                    showMatrix(board, shownRows);

                    printf(
                        "Por favor, ingrese la fila del numero %d que quiere "
                        "seleccionar: ",
                        i + 1);
                    scanf("%d", &chosenRow[i]);
                    printf("La fila seleccionada es:\n");
                    showMatrix(board, chosenRow[i]);

                    printf(
                        "Seleccione una columna del numero %d en esta fila: ",
                        i + 1);
                    scanf("%d", &chosenCol[i]);

                    printf("Su seleccion numero %d es: %d\n", i + 1,
                           board[chosenRow[i] - 1][chosenCol[i] - 1]);
                }
            }
            isValid = checkPairs(board, chosenRow, chosenCol);
            
            if (isValid == 1){
                printf("Felicidades! Usted ha encontrado una pareja\n");
                eliminatePair(board, chosenRow, chosenCol);
            } else{
                printf("Sigue Intentadolo!\n");
            }

            keepBoard = checkMatrix(board, shownRows);

            if (keepBoard == 1) {
                printf("Aun hay parejas! Sigue buscandolas...\n");
            } else {
                printf("Rayos! Parece que no hay parejas disponibles.");
                printf("Agregaremos una fila para ti!\n");
                shownRows += 1;
            }
        } else {
            printf(
                "Tienen las peores de las suertes! No hay parejas en el "
                "tablero predeterminado :(\n");
            printf("Agregaremos una fila para ti!\n");
            shownRows += 1;
        }
    }
    printf(
        "Recordar que no es la version final, entonces los puntos no estan "
        "definidos y el loop es infinito.\n");
    printf("Ctr+C para terminar");
    /**
    showMatrix(board, shownRows);
    bool a;
    a = checkMatrix(board, shownRows);
    printf("%d", a);**/
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
            if ( matrix[i][j] == 0){
                prinf(" ");
            } else printf("%d\t", matrix[i][j]);
        }
        printf("\n");   
    }
}

bool checkMatrix(int matrix[][9], int rows) {
    bool availablepair;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < 9; j++) {
            if (i == 0 || i == rows - 1) {
                if (j == 0 || j == 8) {
                    availablepair = checkCorner(matrix, i, j, rows);
                    if (availablepair == 1) {
                        return availablepair;
                    }
                } else {
                    availablepair = checkTopBotSide(matrix, i, j, rows);
                    if (availablepair == 1) {
                        return availablepair;
                    }
                }
            } else if (j == 0 || j == 8) {
                availablepair = checkLeftRightSide(matrix, i, j, rows);
                if (availablepair == 1) {
                    return availablepair;
                }
            } else {
                availablepair = checkNormal(matrix, i, j, rows);
                if (availablepair == 1) {
                    return availablepair;
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

    else if (i == rows - 1) {
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

bool checkTopBotSide(int matrix[][9], int i, int j, int rows) {
    if (i == 0) {
        // Lado de Arriba (Sin esquinas)
        if (matrix[i][j] + matrix[i][j - 1] == 10 ||
            matrix[i][j] + matrix[i][j + 1] == 10 ||
            matrix[i][j] + matrix[i + 1][j - 1] == 10 ||
            matrix[i][j] + matrix[i + 1][j] == 10 ||
            matrix[i][j] + matrix[i + 1][j + 1] == 10) {
            return 1;
        } else {
            return 0;
        }
    } else if (i == rows - 1) {
        if (matrix[i][j] + matrix[i][j - 1] == 10 ||
            matrix[i][j] + matrix[i][j + 1] == 10 ||
            matrix[i][j] + matrix[i - 1][j - 1] == 10 ||
            matrix[i][j] + matrix[i - 1][j] == 10 ||
            matrix[i][j] + matrix[i - 1][j + 1] == 10) {
            return 1;
        } else {
            return 0;
        }
    }
}

bool checkLeftRightSide(int matrix[][9], int i, int j, int rows) {
    if (j == 0) {
        // Columna izquierda
        if (matrix[i][j] + matrix[i][j + 1] == 10 ||
            matrix[i][j] + matrix[i - 1][j] == 10 ||
            matrix[i][j] + matrix[i + 1][j] == 10 ||
            matrix[i][j] + matrix[i + 1][j + 1] == 10 ||
            matrix[i][j] + matrix[i - 1][j + 1] == 10) {
            printf("%d\t", matrix[i][j] + matrix[i][j + 1]);
            return 1;
        } else {
            return 0;
        }

    } else if (j == 8) {
        // Columna derecha
        if (matrix[i][j] + matrix[i][j - 1] == 10 ||
            matrix[i][j] + matrix[i - 1][j] == 10 ||
            matrix[i][j] + matrix[i + 1][j] == 10 ||
            matrix[i][j] + matrix[i + 1][j - 1] == 10 ||
            matrix[i][j] + matrix[i - 1][j - 1] == 10) {
            return 1;
        } else {
            return 0;
        }
    }
}

bool checkNormal(int matrix[][9], int i, int j, int rows) {
    if (matrix[i][j] + matrix[i][j - 1] == 10 ||
        matrix[i][j] + matrix[i - 1][j] == 10 ||
        matrix[i][j] + matrix[i + 1][j] == 10 ||
        matrix[i][j] + matrix[i + 1][j - 1] == 10 ||
        matrix[i][j] + matrix[i - 1][j - 1] == 10 ||
        matrix[i][j] + matrix[i + 1][j + 1] == 10) {
        return 1;
    } else {
        return 0;
    }
}
bool checkPairs(int matrix[][9], int chosenRow[2],int chosenCol[2]){
    }   
void eliminatePair(int matrix[][9], int chosenRow[2],int chosenCol[2]){

}
