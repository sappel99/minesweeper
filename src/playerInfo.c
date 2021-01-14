/** \file
 * \brief These functions are used for loading and saving player infos
 *
 */

#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include "playerInfo.h"
#include "checkingFunctions.h"
#include "prints.h"

/**
 * \brief This function asks for the player name
 * @param eingabe the player name
 * @return 0 if successful
 */
int askPlayerInfo(char eingabe[256]){
    printf("\033[0;34mSpielername:\033[0m\n");
    scanf("%s", eingabe);
    return 0;
}
/**
 * \brief This functions loads the statistics from a local file
 * @param spielername the player name
 * @param playedGames the amount of games played
 * @param gamesWon the amount of games won
 * @param gamesLost the amount of games lost
 * @param openedCells the amount of opened cells
 * @return 0 if successful, 1 if Error
 */
int loadPlayerInfo(char spielername[256],int *playedGames, int *gamesWon, int *gamesLost, int *openedCells){
    FILE *fptr;
    char buff[255];
    fptr = fopen(spielername,"r");
    if(fptr == NULL)
    {
        printInfo("Player not found!\n");
        return 0;
    }
    fscanf(fptr, "%s", buff);
    printf("Statistics for: %s\n", buff );

    fgets(buff, 255, (FILE*)fptr);
    // Ignore random 2nd row printf("2: %s\n", buff );

    fgets(buff, 255, (FILE*)fptr);
    printf("%s", buff );
    if(isDigitSwitch(buff[(strlen(buff)-3)])){
        *playedGames = (unsigned char) (buff[(strlen(buff)-3)]-48)*10+buff[(strlen(buff)-2)]-48;
    }else if(isDigitSwitch(buff[(strlen(buff)-2)])){
        *playedGames = (unsigned char) buff[(strlen(buff)-2)]-48;
    }else{
        printError("Error with playedGamesNumber in File");
        return 1;
    }

    fgets(buff, 255, (FILE*)fptr);
    printf("%s", buff );
    if(isDigitSwitch(buff[(strlen(buff)-3)])){
        *gamesWon = (unsigned char) (buff[(strlen(buff)-3)]-48)*10+buff[(strlen(buff)-2)]-48;
    }else if(isDigitSwitch(buff[(strlen(buff)-2)])){
        *gamesWon = (unsigned char) buff[(strlen(buff)-2)]-48;
    }else{
        printError("Error with gamesWonNumber in File");
        return 1;
    }

    fgets(buff, 255, (FILE*)fptr);
    printf("%s", buff );
    if(isDigitSwitch(buff[(strlen(buff)-3)])){
        *gamesLost = (unsigned char) (buff[(strlen(buff)-3)]-48)*10+buff[(strlen(buff)-2)]-48;
    }else if(isDigitSwitch(buff[(strlen(buff)-2)])){
        *gamesLost = (unsigned char) buff[(strlen(buff)-2)]-48;
    }else{
        printError("Error with gamesLostNumber in File");
        return 1;
    }

    fgets(buff, 255, (FILE*)fptr);
    printf("%s", buff );
    if(isDigitSwitch(buff[(strlen(buff)-4)])) {
        *openedCells = (unsigned char) (buff[(strlen(buff) - 4)] - 48) * 100 + (buff[(strlen(buff) - 3)] - 48) * 10 + buff[(strlen(buff) - 2)] - 48;
    }else if(isDigitSwitch(buff[(strlen(buff)-3)])){
        *openedCells = (unsigned char) (buff[(strlen(buff)-3)]-48)*10+buff[(strlen(buff)-2)]-48;
    }else if(isDigitSwitch(buff[(strlen(buff)-2)])){
        *openedCells = (unsigned char) buff[(strlen(buff)-2)]-48;
    }else{
        printError("Error with openedCellsNumber in File");
        return 1;
    }

    fclose(fptr);
    printf("\n");

    return 0;
}
/**
 * \brief This function saves the statistics into a local file
 * @param spielername the player name
 * @param playedGames the amount of games played
 * @param gamesWon the amount of games won
 * @param gamesLost the amount of games lost
 * @param openedCells the amount of cells opened
 * @return 0 if successful, 1 if error
 */
int savePlayerInfo(char spielername[256],int playedGames, int gamesWon, int gamesLost, int openedCells){
    FILE *fptr;
    fptr = fopen(spielername,"w");
    if(fptr == NULL)
    {
        printf("Error in file saving!");
        return 1;
    }
    fprintf(fptr,"%s\n",spielername);
    fprintf(fptr,"playedGames: %d\n",playedGames);
    fprintf(fptr,"gamesWon: %d\n",gamesWon);
    fprintf(fptr,"gamesLost: %d\n",gamesLost);
    fprintf(fptr,"openedCells: %d\n",openedCells);

    fclose(fptr);

    return 0;
}
/**
 * \brief This function saves the game matrix into a local file
 * @param spielername the player name
 * @param list the game matrix
 * @return 0 if successful, 1 if error
 */
int saveGame(char spielername[256], struct matrix list){
    FILE *fptr;
    char savedGameName[266] = "savedGame_";
    strcat(savedGameName,spielername);
    fptr = fopen(savedGameName,"w");
    if(fptr == NULL)
    {
        printf("Error in Game file saving!");
        return 1;
    }

    fprintf(fptr,"Game save by: %s\n",spielername);

    struct matrix *it = &list;
    while (it != NULL) {
        fprintf(fptr,"%d: [%d,%d,%c,%c]\n",it->index, it->x, it->y,it->publicSymbol[0],it->hiddenSymbol[0]);
        it = it->next;
    }

    fclose(fptr);

    return 0;
}

/**
 * \brief This functions loads the game from a file
 * @param spielername the player name
 * @return 0 if successful, 1 if Error
 */
int loadPlayerGame(char spielername[256]){
    FILE *fptr;
    char savedGameName[266] = "savedGame_";
    strcat(savedGameName,spielername);
    fptr = fopen(savedGameName,"r");
    if(fptr == NULL)
    {
        printInfo("No local game found\n");
        return 1;
    }else{
        printInfo("Local game found\n");
    }

    fclose(fptr);
    printf("\n");

    return 0;
}