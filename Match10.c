/**
 * @file Match10.c
 * @author Nelson Javier Quijada Mendoza/Maria Auxiliadora Martinez Avila (00385021@uca.edu.sv/00090121@uca.edu.sv)
 * 
 * @brief Juego Match10
 * @version 0.1
 * @date 2021-11-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <math.h>     //Importamos math
#include <stdbool.h>  //Imprtamos dependencias booleanas
#include <stdio.h>    //Libreria de input output basica
#include <stdlib.h>   //Libreria standard
#include <time.h>     //Tiempo, para usar rand()

#define NUM_PLAYERS 1  // Numero de jugadores

void fillBoard(int matrix[][9]);  // Para llenar la matriz con numeros
                                  // aleatorios
void showMatrix(int matrix[][9], int matrixB[][9],
                int rows);  // Imprimir la matriz hasta n filas
bool checkMatrix(int matrix[][9], int rows);  // Chequear posibles parejas
bool checkCorner(int matrix[][9], int i, int j, int rows);  // Chequear esquinas
bool checkTopBotSide(int matrix[][9], int i, int j,
                     int rows);  // Chequear fila superior y fila inferior
bool checkLeftRightSide(int matrix[][9], int i, int j,
                        int rows);  // Chequear fila primera e ultima
bool checkNormal(int matrix[][9], int i, int j,
                 int rows);  // Chequear elementos que no pertenecen a los demas
bool checkPairs(int matrix[][9], int chosenRow[2], int chosenCol[2],
                int shownRows,
                int *points);  // Chequear parejas dadas para ver si son validas
void eliminatePair(
    int matrix[][9], int chosenRow[2],
    int chosenCol[2]);  // Eliminar una pareja una vez sea validad
bool lastNonZero(int matrix[][9], int row, int column);
bool isEmpty(int matrix[][9]);
int emptyRow(int matrix[][9], int emptyRows);

struct player {
    char name[20];
    int points;
};  // Struct de un jugador, donde tiene su nickname y sus respectivos puntos

int main() {
    srand(time(NULL));  // Inicializamos aleatoreidad

    int shownRows = 3;  // El juego comienza con 3 filas
    int board[10][9];   // Defininimos la matriz de juego
    fillBoard(board);   // Llenamos la matriz de numeros aleatorios a traves de
                        // fillboard
    int copyboard[10][9];
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 9; j++) {
            copyboard[i][j] = board[i][j];
        }
    }

    struct player totalPlayers[NUM_PLAYERS];  // Por si hay mas de un jugador
    printf("Bienvenidos a Match 10!\n");

    for (int i = 0; i < NUM_PLAYERS; i++) {
        // Los jugadores Ingresan su nickname
        printf("Ingrese su nickname (maximo 20 caracteres) jugador %d: ",
               i + 1);
        scanf("%s", &totalPlayers[i].name);

        totalPlayers[i].points = 0;  // Inicializamos los puntos
    }

    int continues = 1;  // Variable para continuar el loop
    bool keepBoard;     // Variable para ver si se mantiene el tablero, o se
                        // agregan filas
    bool isValid;       // Variable para saber si una pareja es valida
    bool stopcheck = 0;
    int emptyRows = 0;

    while (continues == 1) {
        int addedPoints = 0;
        // El loop continua mientras continues sea 1.
        int chosenRow[2];  // Creamos un array para las elecciones del numero 1
                           // y 2 del jugador en las filas
        int chosenCol[2];  // Creamos un array para las elecciones del numero 1
                           // y 2 del jugador en las columnas

        if (stopcheck == 1) {
            keepBoard = 1;
        } else {
            keepBoard = checkMatrix(board,
                                    shownRows);  // Chequea si aun hay parejas
                                                 // disponibles en la matriz
        }

        if (keepBoard == 1) {
            // El tablero no se cambia y el juego inicia
            for (int number = 0; number < NUM_PLAYERS; number++) {
                printf("%s, es su turno.\n", totalPlayers[number].name);

                for (int i = 0; i < 2; i++) {
                    showMatrix(board, copyboard, shownRows);
                    // Se selecciona la fila del primer/sengundo numero
                    printf(
                        "Por favor, ingrese la fila del numero %d que quiere "
                        "seleccionar: ",
                        i + 1);
                    scanf("%d", &chosenRow[i]);

                    if (chosenRow[i] > shownRows ||
                        chosenRow[i] <
                            0) {  // Condicion que hace que el for vuelva a
                                  // comenzar si el numero es invalido
                        printf(
                            "Recuerda que solo puedes elegir hasta la fila %d "
                            "y que el numero debe ser positivo\n",
                            shownRows);
                        i = -1;
                        continue;
                    }

                    printf("La fila seleccionada es:\n");
                    showMatrix(board, copyboard, chosenRow[i]);

                    // Se selecciona la columna del primer/segundo numero
                    printf(
                        "Seleccione una columna del numero %d en esta fila: ",
                        i + 1);
                    scanf("%d", &chosenCol[i]);

                    if (chosenCol[i] > 9 ||
                        chosenCol[i] <
                            0) {  // Condicion que hace que el for vuelva a
                                  // comenzar si el numero es invalido
                        printf(
                            "Recuerda que solo puedes elegir hasta la columna "
                            "9 y que el numero debe ser positivo\n");
                        i = -1;
                        continue;
                    }

                    system("clear");  // Limpaimos la consola por estetica
                    printf("Su seleccion numero %d es: %d\n", i + 1,
                           board[chosenRow[i] - 1][chosenCol[i] - 1]);
                }
            }
            system("clear");  // Limpiamos la consola por estetica

            if (board[chosenRow[0] - 1][chosenCol[0] - 1] == 0 ||
                board[chosenRow[1] - 1][chosenCol[1] - 1] == 0) {
                printf("No puedes seleccionar una casilla vacia!\n");  // El
                                                                       // usuario
                                                                       // intento
                                                                       // utilizar
                                                                       // casillas
                                                                       // vacias
            } else {
                isValid = checkPairs(board, chosenRow, chosenCol, shownRows,
                                     &addedPoints);  // Chequeamos que la pareja
                                                     // seleccionada sea valida

                if (isValid == 1) {
                    // En caso de haber encontrado una pareja, se "eliminan"
                    // esas casillas
                    printf("Felicidades! Usted ha encontrado una pareja\n");
                    eliminatePair(board, chosenRow, chosenCol);

                } else {
                    // Caso contrario, no pasa nada
                    printf("Sigue Intentadolo!\n");
                }

                int empty =
                    emptyRow(board, emptyRows);  // Usamos el numero de filas
                                                 // (empty) que solo tienen ceros
                if (empty >=
                    1) {  // Esto con la finalidad de otorgar puntos por las
                          // filas que se vaciaron. emptyRow son las filas ya
                          // vacias, para no dar puntos dos veces
                    printf("Felicidades! Has limpiado %d fila entera!\n",
                           empty);
                    printf("Te entregaremos %d puntos!\n", empty * 10);
                    emptyRows = emptyRows + empty;  // Acutalizamos emptyRows
                    addedPoints += (10 * empty);    // Agregamos los puntos
                }

                keepBoard = checkMatrix(
                    board, shownRows);  // Volvemos a chequear si hay parejas

                if (keepBoard == 1) {
                    printf("Aun hay parejas! Sigue buscandolas...\n");
                } else {
                    if (shownRows < 9) {
                        printf(
                            "Rayos! Parece que no hay parejas disponibles.\n");
                        printf("Agregaremos una fila para ti!\n");
                        shownRows += 1;  // Incrementamos las filas validas
                    } else {
                        if (isEmpty(board)) {
                        }  // Si el tablero esta vacio, no hacemos nada, mas
                           // adelante nos encargamos de este caso
                        else {
                            int cloneRow =
                                0;  // Indice de la fila que clonaremos

                            if (shownRows == 9) {
                                shownRows += 1;  // Habilitamos la fila 10,
                                                 // destinada para clonacion.
                            }
                            showMatrix(board, copyboard, shownRows);
                            printf(
                                "Vaya! Parece ser que ya no hay mas filas en "
                                "el tablero.\n");
                            printf(
                                "Puedes clonar una fila y agregarla a la fila "
                                "10!\n");
                            printf(
                                "Si deseas clonar una fila, escribe su indice, "
                                "de lo contrario escribe 0: ");

                            scanf("%d",
                                  &cloneRow);  // Pedimos que fila se clonara
                            if (cloneRow == 0) {
                                // No clonamos nada
                            } else {
                                for (int j = 0; j < 9; j++) {
                                    board[9][j] =
                                        board[cloneRow - 1][j];  // clonamos
                                }
                            }
                        }
                    }
                }
            }
        } else {
            // Caso extremo en que el tablero aparezca sin parejas iniciales
            if (shownRows == 9 || shownRows == 10) {
                printf("Encuentra las parejas que faltan!\n");
                stopcheck = 1;

            } else {
                printf(
                    "Tienen las peores de las suertes! No hay parejas en el "
                    "tablero predeterminado :(\n");
                printf("Agregaremos una fila para ti!\n");
                shownRows += 1;  // Incrementamos las filas validas
            }
        }
        printf(
            "\033[32m"
            "Has recibido %d punto(s)."
            "\033[0m\n",
            addedPoints);//Imprimimos los puntos ganados en verde
        totalPlayers[0].points += addedPoints; //actualizamos los puntos del jugador

        if (isEmpty(board)) { //Cuando board esta vacio, hemos terminado
            printf(
                "Felicidades! Has encontrado todas las parejas del juego.\n");
            printf("Recibiras 150 puntos!");
            totalPlayers[0].points += 150;
            printf("%s fue un placer jugar contigo!\n", totalPlayers[0].name);
            printf("Tu puntaje fue de %d puntos", totalPlayers[0].points);

            continues = 0; //Paramos el while
        }
    }
}

void fillBoard(int matrix[][9]) {
    /**
     * A esta funcion se le pasa una matriz, que por naturaleza ya lleva
     * punteros asociados y se llena de numeros aleatorios, modificando asi
     * la matriz incial. No retorna ningun valor ya que no es necesario.
     */
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            matrix[i][j] =
                rand() % (9 - 1 + 1) + 1;  // Numeros aleatorios entre 1 y 9
        }
    }
    for (int j = 0; j < 9; j++) {
        matrix[9][j] = 0;
    }
}

void showMatrix(int matrix[][9], int matrixB[][9], int rows) {
    /**
     * Esta funcion recibe dos matrices y un entero.
     * Lo que la funcion hace es imprimir la matriz hasta cierto valor "rows".
     * Si un valor es cero, no se imprime, se imprime el numero de la matriz original pero en rojo.
     */
    for (int i = 0; i < rows; i++) {
        printf(
            "\033[36m"
            "-------------------------------------------------------\n"
            "\033[0m");//Imprimos borde superior

        for (int j = 0; j < 9; j++) {
            if (matrix[i][j] == 0) {
                printf(
                    "\033[31m"
                    "|  %d  "
                    "\033[0m",
                    matrixB[i][j]); //Imprimimos numeros en rojo para valores ya seleccionados
            } else {
                if (j == 8) {
                    printf(
                        "\033[36m"
                        "|  %d  |"
                        "\033[0m",
                        matrix[i][j]); //Imprimimos numero en la derecha
                } else {
                    printf(
                        "\033[36m"
                        "|  %d  "
                        "\033[0m",
                        matrix[i][j]); //Los demas elementos
                }
            }
        }
        printf("\n");
        if (i == rows - 1) {
            printf(
                "\033[36m"
                "-------------------------------------------------------\n" //Imprimimos parte de abajo
                "\033[0m");
        }
    }
}

bool checkMatrix(int matrix[][9], int rows) {
    /**
     * Esta funcion recibe una matriz y un numero entero y regresa un booleano.
     * Regresa 1, en caso de que exista una pareja valida y regresa 0 en caso
     * contrario. Esta funcion se ayuda de otras funciones complementarias para
     * mayor legibilidad.
     */
    bool availablepair;  // availablepair es el booleano que retornamos
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < 9; j++) {
            if (i == 0 ||
                i ==
                    rows -
                        1) {  // Con este if chequeamos la primera e ultima fila

                if (j == 0 ||
                    j == 8) {  // Con este if chequeamos si es una esquina

                    availablepair =
                        checkCorner(matrix, i, j, rows);  // Lllamos CheckCorner

                    if (availablepair == 1) {  // Si es igual a 1, hemos
                                               // encontrado una pareja valida
                        return availablepair;
                    }  // NOTA: Este if no tiene else ya que no es necesario y
                       // entorpeceria el codigo

                } else {
                    availablepair = checkTopBotSide(
                        matrix, i, j, rows);  // Si no es una esquina, entonces
                                              // es la fila de arriba o abajo

                    if (availablepair == 1) {
                        return availablepair;
                    }
                }

            } else if (j == 0 ||
                       j == 8) {  // Caso de la primera y ultima columna

                availablepair = checkLeftRightSide(
                    matrix, i, j, rows);  // Chequeamos las columnas

                if (availablepair == 1) {
                    return availablepair;
                }

            } else {
                availablepair = checkNormal(
                    matrix, i, j, rows);  // Chequeamos valores no extremos

                if (availablepair == 1) {
                    return availablepair;
                }
            }
        }
    }
    return availablepair;  // Si ningun return anterior se accede, este se
                           // retornara y valdra cero
}

bool checkCorner(int matrix[][9], int i, int j, int rows) {
    /**
     * Recibe una matriz y 3 enteros. Los primeros dos son la posicion i,j que
     * queremos chequear y el tercero es hasta donde hay que chequear. Retorna 1
     * en caso de que haya una pareja con una esquina y retorna 0 caso
     * contrario. Basicamente chequeamos las 4 esquinas.
     */

    bool result;  // Para retornar

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
    /**
     * Recibe una matriz y 3 enteros. Los primeros dos son la posicion i,j que
     * queremos chequear y el tercero es hasta donde hay que chequear. Retorna 1
     * en caso de que haya una pareja con la primera o ultima (hasta rows) filas
     * y retorna 0 caso contrario. Basicamente chequeamos la fila 1 y rows, SIN
     * volver a chequear las esquinas.
     */

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
        // Lado de Abajo (Sin esquinas)
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
    /**
     * Recibe una matriz y 3 enteros. Los primeros dos son la posicion i,j que
     * queremos chequear y el tercero es hasta donde hay que chequear. Retorna 1
     * en caso de que haya una pareja con una de las columnas 1 o 9 y retorna 0
     * caso contrario. Basicamente chequeamos la primera y ultima columna
     */

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
    /**
     * Recibe una matriz y 3 enteros. Los primeros dos son la posicion i,j que
     * queremos chequear y el tercero es hasta donde hay que chequear. Retorna 1
     * en caso de que haya una pareja con cualquiera de los elementos de valores
     * no extremos (desde (1,1) hasta (8,8)) y retorna 0 caso contrario.
     * Basicamente chequeamos todos los valores que son el centro de un cuadrado
     * 3*3.
     */

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
bool checkPairs(int matrix[][9], int chosenRow[2], int chosenCol[2],
                int shownRows, int *addedPoints) {
    /**
     * Reibe 3 parametros, una matriz y dos arrays. Los arrays son las
     * posiciones de los valores elegidos. Retorna 1 en caso de que las parejas
     * dadas sean adyacentes (separadas por cero tambien) y sumen 10. Retorna 0
     * en el caso contrario.
     */
    if (matrix[chosenRow[0] - 1][chosenCol[0] - 1] +
                matrix[chosenRow[1] - 1][chosenCol[1] - 1] ==
            10 ||
        matrix[chosenRow[0] - 1][chosenCol[0] - 1] ==
            matrix[chosenRow[1] - 1][chosenCol[1] - 1]) {
        // El primer if chequea que sumen 10
        if (pow(pow((chosenRow[0] - chosenRow[1]), 2) +
                    pow((chosenCol[0] - chosenCol[1]), 2),
                0.5) == 1 ||
            pow(pow((chosenRow[0] - chosenRow[1]), 2) +
                    pow((chosenCol[0] - chosenCol[1]), 2),
                0.5) == pow(2, 0.5)) {
            /**Este if chequea que sean adyacentes (sin el cero), a traves de un
           procedimiento muy eficiente e ingenioso que requiere explicacion. Lo
           que hemos hecho, es tomar cada casilla de la matriz y representarla
           como un punto en el plano cartesiano. Cada celda o punto, tiene sus
           coordenadas (x,y)=(i,j) que usaremos. Calculamos la distancia entre
           dos celdas con la formula: ???((x2-x1)^2-(y2-y1)^2). Si la distancia es
           uno, entonces es adyacente ya sea arriba, abajo, derecha o izquierda.
           Ahora, si la distancia nos da ???2, entonces es diagonal y tambien
           adyacente, sea a cualquier direccion.
           **/
            *addedPoints = 1;
            return 1;
        } else if ((pow(pow((chosenRow[0] - chosenRow[1]), 2) +
                            pow((chosenCol[0] - chosenCol[1]), 2),
                        0.5)) /
                       pow(2, 0.5) ==
                   (int)((pow(pow((chosenRow[0] - chosenRow[1]), 2) +
                                  pow((chosenCol[0] - chosenCol[1]), 2),
                              0.5)) /
                         pow(2, 0.5))) {
            /**
             * Este else if tambien ha de explicarse a profundidad, ya que una
             * solucion compleja requiere una buena explicacion para que se
             * entienda bien. En este else if, estamos analizando las
             * diagonales. Sabemos que para numeros adyacentes en la diagonal la
             * distancia es igual a ???2. Ahora, Si tenemos adyacencia con (un
             * cero de por medio), entonces la distancia no es igual a ???2, es
             * igual a k???2 donde k es un entero. Por ende d=k???2. Si despejamos:
             * d/???2 = k. Entonces solo basta probar que d/???2 es un entero. Por
             * eso la expresion de la derecha es el entero de la expresion
             * izquierda. Este proceso nos asegura que solo estamos admitiendo
             * numeros en la misma diagonal en cualquier direccion.
             */
            int k = (int)((pow(pow((chosenRow[0] - chosenRow[1]), 2) +
                                   pow((chosenCol[0] - chosenCol[1]), 2),
                               0.5)) /
                          pow(2, 0.5)) +
                    1;  // Obtenemos k, luego le sumamos 1. Ya que si el entero
                        // es k, la cantidad de celdas son k+1

            int x1, y1, x2, y2, r1, r2;  // Definimos variables de utilidad
            int sum = 0;
            bool mainDiagonal;  // Para chequear si los dos puntos estan en la
                                // diagonal principal

            /* Ahora, usaremos un proceso importante para determinar si el resto
             * de numeros entre ambas elecciones son cero. Para esto, usaremos
             * una submatriz cuadrada de nuestra matriz original. No usamos la
             * matriz original, ya que los indices no cumplen las propiedades de
             * la diagonal principal de una matriz. Es por ello que es necesario
             * trasladarla. Tambien, en caso de que los dos elementos se
             * encuentren en la diagonal secundaria es necesario hacerlo. Ahora,
             * simplemente tenemos que encontrar los elementos en la diagonal
             * (condicion x=y para la principal y condicion x+y=k-1 para la
             * secundaria). Al haber encontrado estos elementos, basta con
             * sumarlos. Si la suma es igual a 10, significa que todos los
             * elementos de por medio son cero, caso contrario, no lo son. 
             * 10-(x1,y1)-(x2,y2) es claramente cero.
             */

            if (chosenRow[0] - 1 <
                chosenRow[1] -
                    1) {  // Encontramos cual de las dos elecciones va primero
                x1 = chosenRow[0] -
                     1;  // x1 seria el punto "mas alto" de las dos elecciones
                y1 = chosenCol[0] - 1;  // y1 corresponde a x1
                x2 = chosenRow[1] - 1;
                y2 = chosenCol[1] - 1;

                // si y1 es menor que y2 y x1 tambien es menor que x2, significa
                // entonces que trataremos con la diagonal principal.
                if (y1 < y2) {
                    mainDiagonal = 1;
                } else {
                    mainDiagonal = 0;
                }
            } else {  // Simplemente es el caso contrario
                x2 = chosenRow[0] - 1;
                y2 = chosenCol[0] - 1;
                x1 = chosenRow[1] - 1;
                y1 = chosenCol[1] - 1;

                if (y2 < y1) {
                    mainDiagonal = 0;
                } else {
                    mainDiagonal = 1;
                }
            }
            // Ahora solo queremos encontrar cual esta mas arriba o abajo de los
            // y, asi como hicimos con x.
            if (y1 < y2) {
                r1 = y1;
                r2 = y2;
            } else {
                r1 = y2;
                r2 = y1;
            }
            // Inicializamos una matriz con memoria dinamica, ya que le pasamos
            // un parametro no constante.
            int **placeholderMatrix = malloc(sizeof(int *) * k);
            for (int i = 0; i < k; i++) {
                placeholderMatrix[i] = malloc(sizeof(int) * k);
            }

            // Llenamos nuestra sub matriz, recordemos que la matriz es
            // cuadrada, de orden k
            // y que en dos de sus esquinas opuestas se encuentran nuestros
            // puntos (ya sea principal o secundario)
            for (int i = x1; i <= x2; i++) {
                for (int j = r1; j <= r2; j++) {
                    placeholderMatrix[i - x1][j - r1] =
                        matrix[i][j];  // Pasamos de un indice x,y a uno 0,0 ...
                                       // 1,1 y asi
                }
            }

            if (mainDiagonal == 1) {  // Si esta en la diagonal principal, nos
                                      // interesan los elementos i==j
                for (int i = 0; i < k; i++) {
                    for (int j = 0; j < k; j++) {
                        if (i == j) {
                            sum += placeholderMatrix[i][j];  // Sacamos la suma
                                                             // de la diagonal
                        }
                    }
                }
            } else {  // Si esta en la diagonal secundaria, nos interesan los
                      // elementos que cumplen i+j=k-1
                for (int i = 0; i < k; i++) {
                    for (int j = 0; j < k; j++) {
                        if ((i + j) == k - 1) {
                            sum += placeholderMatrix[i][j];  // Sacamos la suma
                        }
                    }
                }
            }
            if (sum - matrix[x1][y1] - matrix[x2][y2] == 0) {
                *addedPoints = 4;
                return 1;  // Si la suma es mayor que 10, entonces hay numeros
                           // distintos a 0
            } else {
                return 0;  // Si la suma es menor o igual que 10, esta todo
                           // bien.
            }
        } else if ((pow(pow((chosenRow[0] - chosenRow[1]), 2) +
                            pow((chosenCol[0] - chosenCol[1]), 2),
                        0.5)) ==
                   (int)(pow(pow((chosenRow[0] - chosenRow[1]), 2) +
                                 pow((chosenCol[0] - chosenCol[1]), 2),
                             0.5))) {
            /**
             * Este else if se encarga de los casos separados en cero en
             * vertical y horizontal. La logica es similar a la anterior y aun
             * mas sencilla. Siempre buscamos una suma de todos los elementos
             * igual a 10 entre x1 y x2 o y1 y y2. La distancia entre n+1 celdas
             * horizontales o verticales seria de n. Entonces, d = n. Solo hace
             * falta probar que d es un Entero. Al tomar 10-(x1,y1)-(x2,y2) obtendremos cero.
             */
            int sum = 0;
            int x1, x2, y1, y2;

            if (chosenRow[0] == chosenRow[1]) {  // Si estan en la misma fila
                if (chosenCol[0] <
                    chosenCol[1]) {  // Si x1 es menor que x2 entonces x1 esta
                                     // mas a la izquierda
                    x1 = chosenCol[0] - 1;
                    x2 = chosenCol[1] - 1;
                } else {  // caso contrario, x2 esta mas a la izquierda.
                    x2 = chosenCol[0] - 1;
                    x1 = chosenCol[1] - 1;
                }
                for (int j = x1; j <= x2; j++) {
                    sum += matrix[chosenRow[0] - 1]
                                 [j];  // Sacamos la suma para este caso
                }
                if (sum - matrix[chosenRow[0] - 1][x1] -
                        matrix[chosenRow[0] - 1][x2] ==
                    0) {
                    *addedPoints = 4; //Le damos sus respectivos puntos por el proceso
                    return 1;
                } else {
                    return 0;
                }
            } else if (chosenCol[0] == chosenCol[1]) {
                //Obtenemos el y que este "mas a la izquierda" para comenzar y terminar la iteracion del array.
                if (chosenRow[0] < chosenRow[1]) {
                    y1 = chosenRow[0] - 1;
                    y2 = chosenRow[1] - 1;
                } else {
                    y2 = chosenRow[0] - 1;
                    y1 = chosenRow[1] - 1;
                }
                //Sumamos los elementos del array
                for (int i = y1; i <= y2; i++) {
                    sum += matrix[i][chosenCol[0] - 1];
                }
                //Chequeamos que todos los elementos sean cero
                if (sum - matrix[y1][chosenCol[0] - 1] -
                        matrix[y2][chosenCol[0] - 1] ==
                    0) {
                    *addedPoints = 4; //damos los puntos
                    return 1;
                } else {
                    return 0;
                }
            }
        } else if (lastNonZero(matrix, chosenRow[0] - 1, chosenCol[0] - 1) ||
                   lastNonZero(matrix, chosenRow[1] - 1, chosenCol[1] - 1)) {
                       /** Para el caso de la ultima y primera columna, llamamos a la funcion
                        * lasNonZero, que nos dice si el elemento en cuestion es el ultimo elemento
                        * distinto de cero, que es justo lo que queremos para el elemento de arriba
                        */
            int x1;
            int x2;

            if (chosenRow[0] < chosenRow[1]) {
                x1 = chosenRow[0] - 1;
                x2 = chosenRow[1] - 1;
            } else {
                x2 = chosenRow[0] - 1;
                x1 = chosenRow[1] - 1;
            } //Obtenemos el elemento que este mas a la izquierda de los dos, ese seria el elemento de abajo
            int counter = 0;
            if (lastNonZero(matrix, chosenRow[0] - 1, chosenCol[0] - 1)) {
                if (x1 == chosenRow[0] - 1) { //Caso para saber cual x estamos usando
                    for (int i = x1 + 1; i == x2; i++) {
                        for (int j = 0; j < 9; j++) {
                            counter++;
                            if (matrix[i][j] != 0) { //Chequeamos hasta el ultimo elemento distinto de cero
                                if (i == x2 && j == chosenCol[1] - 1) {
                                    if (counter == 1) {
                                        *addedPoints = 2; //Si no hay ningun cero, solo son 2 puntos
                                    } else {
                                        *addedPoints = 4; //4 puntos si hay varios ceros
                                    }
                                    return 1;
                                } else {
                                    return 0;
                                }
                            }
                        }
                    }
                } else {
                    return 0;
                }

            } else {  //Este es el caso contrario, es la misma logica pero con chosenRow[1]
                if (x1 == chosenRow[1] - 1) {
                    for (int i = x1 + 1; i == x2; i++) {
                        for (int j = 0; j < 9; j++) {
                            counter++;
                            if (matrix[i][j] != 0) {
                                if (i == x2 && j == chosenCol[0] - 1) {
                                    if (counter == 1) {
                                        *addedPoints = 2;
                                    } else {
                                        *addedPoints = 4;
                                    }
                                    return 1;
                                } else {
                                    return 0;
                                }
                            }
                        }
                    }
                } else {
                    return 0;
                }
            }
        }
    }
    return 0;
}
void eliminatePair(int matrix[][9], int chosenRow[2], int chosenCol[2]) {
    // Recibe una matriz y  2 arrays que indican las posiciones de los numeros y
    // simplemente los "elimina", volviendolos 0.

    matrix[chosenRow[0] - 1][chosenCol[0] - 1] = 0;
    matrix[chosenRow[1] - 1][chosenCol[1] - 1] = 0;
}

bool lastNonZero(int matrix[][9], int row, int column) {
    /**
     * Funcion para determinar si el elemento en la posicion row,column es
     * el ultimo de esa fila que es distinto de cero. Retorna 1 si es cierto.
     */
    int last = 0; //El ultimo numero en el array distinto de cero
    for (int j = 0; j < 9; j++) {
        if (matrix[row][j] != 0) {
            last = j;
        }
    }
    if (column == last) {
        return 1;
    } else {
        return 0;
    }
}

bool isEmpty(int matrix[][9]) {
    /**
     * Funcion para chequear si una matriz esta vacia.
     * Retorna 1 en el caso afirmativo
     * 
     */
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (matrix[i][j] != 0) {
                return 0;
            }
        }
    }
    return 1;
}

int emptyRow(int matrix[][9], int emptyRows) {
    /**
     * Funcion usada para determinar si una NUEVA fila se ha convertido en cero
     * solo chequeamos las nuevas filas para no dar doble punto. Toma una matriz
     * y el argumento emptyRows, que es el numero de filas que ya estaban vacias
     * en un momento pasado y por la cual ya se dieron puntos.
     */
    int totalEmpty = 0; //El total de filas vacias
    int counter = 0; //Cuenta los ceros
    int result = 0;

    for (int i = 0; i < 9; i++) {
        counter = 0; //reseteamos el numero de ceros para cada fila
        for (int j = 0; j < 9; j++) {
            if (matrix[i][j] == 0) {
                counter++; //anadimos al haber un 0.
            }

            if (counter == 9) {
                totalEmpty++; //Si hay 9 ceros en una fila, implica que si o si es una fila vacia
            }
        }
    }
    if (totalEmpty > emptyRows) {
        result = totalEmpty - emptyRows; //retornamos el numero de filas vacias NUEVAS
        return result;
    } else {
        return 0;
    }
}