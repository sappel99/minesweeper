/** \file
 * \brief This is the main C file of the game minesweeper
 *
 * Run this program with 2 arguments given, first a square matrix eg 5x5 or 15x5
 * and second a one to two digit number of mines.
 *
 * e.g. \c .minesweeper.c 10x10 20
 */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "minesweeper.h"
#include "prints.h"
#include "generatePlayfield.h"
#include "revealFields.h"
#include "checkingFunctions.h"
#include "playerInfo.h"

/**
 * \brief Frees all elements in the struct matrix list
 * @param start The matrix list to be freed
 */
void free_list(struct matrix *start) {
    struct matrix *it = start->next;
    while (it != NULL) {
        struct matrix *item = it;
        it = it->next;
        free(item);
    }
}
/**
 * \brief Returns a random number between x and y
 * @param x Smallest possible number
 * @param y Biggest possible number
 * @return Returns the random number generated
 */
int randomNumber(int x, int y){
    //srand (time (NULL));
    return (rand() % ((y + 1) - x)) + x;
}



/**
 * \brief Main function for minesweeper, calling all functions needed
 * @param argc Number of arguments given
 * @param argv Value of arguments given
 * @return 0 when \c EXIT.SUCCESS
 */
int main(int argc, char* argv[]) {
    int playfieldRows = 0, playfieldCols = 0, mines = 0;
    if (checkMainParameters(argc, argv, &playfieldRows, &playfieldCols, &mines)) {
        exit(1);
    }
    int rows = playfieldRows + 1, cols = playfieldCols + 1;
    int minesIndex[mines];
    for (int i = 0; i < mines; i++) {
        minesIndex[i] = 0;
    }

    struct matrix list = {0, 0, 0, "|", " ", NULL};
    if(generateMatrix(0, 1, 1, 'A', &list, rows, cols)){
        exit(1);
    }
    setMines(list, mines, rows, cols, minesIndex);
    calculateMineValues(list, mines, cols, minesIndex);
    revealFirst(list, rows, cols);

    char spielername[256];
    int playedGames =0,gamesWon=0,gamesLost=0,openedCells=0;
    askPlayerInfo(spielername);
    if(loadPlayerInfo(spielername,&playedGames,&gamesWon,&gamesLost,&openedCells)==1){
        exit(1);
    }

    printPublic(list);

    int playGame = 1;
    while (playGame) {
        switch (readAndReveal(list, rows)) {
            case 1: { //Mine found
                printf("\033[0;31mGame lost - Mine found\033[0m\n");
                openedCells++;playedGames++;gamesLost++;savePlayerInfo(spielername,playedGames,gamesWon,gamesLost,openedCells);
                printPublic(list);
                printf("\n");
                printHidden(list);
                playGame = 0;
                break;
            }
            case 2: { //Player exit
                printInfo("Game exit initiated..\n");
                printInfo("Playing data discarded\n");
                playGame = 0;
                break;
            }
            case 3: { //Player save
                printInfo("Game exit initiated..\n");
                printInfo("Playing data saved\n");
                savePlayerInfo(spielername,playedGames,gamesWon,gamesLost,openedCells);
                saveGame(spielername,list);
                playGame = 0;
                break;
            }
            case 4: { //Player help
                printZeroInfo(list,rows,cols);
                break;
            }
            default: { //Player opened cell
                openedCells++;
                printPublic(list);
                printMineInfo(list, mines);
            }
        }
        if (checkAllMinesMarked(list, mines) == 1) {
            printInfo("Game won - All mines marked\n");
            openedCells++;playedGames++;gamesWon++;savePlayerInfo(spielername,playedGames,gamesWon,gamesLost,openedCells);
            printPublic(list);
            printf("\n");
            printHidden(list);
            break;
        }
        if (checkAllFieldsOpened(list, rows, cols, mines) == 1) {
            printInfo("Game won - All Fields opened\n");
            openedCells++;playedGames++;gamesWon++;savePlayerInfo(spielername,playedGames,gamesWon,gamesLost,openedCells);
            printPublic(list);
            printf("\n");
            printHidden(list);
            break;
        }
    }

    printf("Game finished\n");
    free_list(&list);

    return EXIT_SUCCESS;
}


