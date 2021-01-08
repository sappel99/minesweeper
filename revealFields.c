/** \file
 * \brief These functions are used for revealing fields
 *
 */

#include <stdio.h>
#include <memory.h>
#include "revealFields.h"
#include "checkingFunctions.h"
/**
 * \brief This function reveals all Fields around a given coordinate
 * @param list the existing matrix list
 * @param xIn the x coordinate
 * @param yIn the y coordinate
 * @return count number of new fields opened
 */
int revealAroundXY(struct matrix list,int xIn, int yIn){
    int anzNeue0 = 0; // this counts the number of new zeroes found around XY
    struct matrix *it = &list;
    while (it != NULL) {
        if(it->x==xIn&&it->y==yIn-1){
            strcpy(it->publicSymbol, it->hiddenSymbol);anzNeue0++;
        }
        if(it->x==xIn&&it->y==yIn+1){
            strcpy(it->publicSymbol, it->hiddenSymbol);anzNeue0++;
        }
        if(it->x==xIn-1&&it->y==yIn){
            strcpy(it->publicSymbol, it->hiddenSymbol);anzNeue0++;
        }
        if(it->x==xIn-1&&it->y==yIn-1){
            strcpy(it->publicSymbol, it->hiddenSymbol);anzNeue0++;
        }
        if(it->x==xIn-1&&it->y==yIn+1){
            strcpy(it->publicSymbol, it->hiddenSymbol);anzNeue0++;
        }
        if(it->x==xIn+1&&it->y==yIn){
            strcpy(it->publicSymbol, it->hiddenSymbol);anzNeue0++;
        }
        if(it->x==xIn+1&&it->y==yIn-1){
            strcpy(it->publicSymbol, it->hiddenSymbol);anzNeue0++;
        }
        if(it->x==xIn+1&&it->y==yIn+1){
            strcpy(it->publicSymbol, it->hiddenSymbol);anzNeue0++;
        }
        it = it->next;
    }
    //printf("Anz Neue 0: %d\n",anzNeue0);
    return anzNeue0;
}
/**
 * \brief This function trys to find more zeroes if a new field has been opened, which was a zero.
 *
 * In case of big groups of zeroes this function opens them all.
 *
 * @param list the existing matrix list
 * @param rows the number of rows
 * @return 0 if successful
 */
int findMoreZeroes(struct matrix list,int rows){
    for(int i = 0;i<rows;i++) {
        struct matrix *it = &list;
        while (it != NULL) {
            if (strcmp(it->hiddenSymbol, "0") == 0 && strcmp(it->publicSymbol, "0") == 0) {
                if (revealAroundXY(list, it->x, it->y) == 0) {
                }
            }
            it = it->next;
        }
    }
    return 0;
}
/**
 * \brief This function turns a public zero into a better readable blank space
 * @param list the existing matrix list
 * @return 0 if successful
 */
int turnPublicZeroIntoSpace(struct matrix list){
    struct matrix *it = &list;
    while (it != NULL) {
        if (strcmp(it->hiddenSymbol, "0") == 0 && strcmp(it->publicSymbol, "0") == 0) { //if public zero
            strcpy(it->publicSymbol, " ");
        }
        it = it->next;
    }
    return 0;
}
/**
 * \brief This function reads a coordinate from the user and either opens it or marks (?) it.
 * @param list the existing matrix list
 * @param rows the number of rows
 * @return 0 if successful
 */
int readAndReveal(struct matrix list,int rows){
    int falscheEingabe = 1; //boolean for checking if Eingabe is useful
    int xIn = 0, yIn = 0;
    int eingabe0Fragezeichen = 0; //boolean for checking if first char of Eingabe is "?"
    while(falscheEingabe) {
        char eingabe[256];
        printf("\033[0;34mEingabe:\033[0m\n");
        scanf("%s", eingabe);
        if (strncmp(eingabe, "?", 1) == 0) { //if Eingabe ?
            eingabe0Fragezeichen=1;
            if (strlen(eingabe) == 3&&isAlphaSwitch(eingabe[1])&&isDigitSwitch(eingabe[2])) {
                yIn = (unsigned char) eingabe[1] - 64;
                xIn = (unsigned char) eingabe[2] - 48;
                printf("X: %d, Y: %d\n", xIn, yIn);
                falscheEingabe=0;
            } else {
                if (strlen(eingabe) == 4&&isAlphaSwitch(eingabe[1])&&isDigitSwitch(eingabe[2])&&isDigitSwitch(eingabe[3])) {
                    yIn = (unsigned char) eingabe[1] - 64;
                    xIn = (unsigned char) (eingabe[2] - 48) * 10 + (eingabe[3] - 48);
                    printf("X: %d, Y: %d\n", xIn, yIn);
                    falscheEingabe=0;
                }
            }
        } else { //Kein "?"
            if (strlen(eingabe) == 2&&isAlphaSwitch(eingabe[0])&&isDigitSwitch(eingabe[1])) {
                yIn = (unsigned char) eingabe[0] - 64;
                xIn = (unsigned char) eingabe[1] - 48;
                printf("X: %d, Y: %d\n", xIn, yIn);
                falscheEingabe=0;
            } else {
                if (strlen(eingabe) == 3&&isAlphaSwitch(eingabe[0])&&isDigitSwitch(eingabe[1])&&isDigitSwitch(eingabe[2])) {
                    yIn = (unsigned char) eingabe[0] - 64;
                    xIn = (unsigned char) (eingabe[1] - 48) * 10 + (eingabe[2] - 48);
                    printf("X: %d, Y: %d\n", xIn, yIn);
                    falscheEingabe=0;
                }
            }
        }
        if (strncmp(eingabe, "exit", 4) == 0||strncmp(eingabe, "e", 1) == 0) {
            return 2;
        }
        if (strncmp(eingabe, "save", 4) == 0||strncmp(eingabe, "s", 1) == 0) {
            return 3;
        }
        if (strncmp(eingabe, "help", 4) == 0||strncmp(eingabe, "h\0", 2) == 0) {
            return 4;
        }
    }

    struct matrix *it = &list;
    while (it != NULL) { //do something with the entered field, if its not first row/col && not opened
        if (it->x == xIn && it->y == yIn && it->y > 0 && it->x > 0 && strcmp(it->publicSymbol, it->hiddenSymbol) != 0) {
            if (eingabe0Fragezeichen){
                strcpy(it->publicSymbol, "?");
            }else{
                strcpy(it->publicSymbol, it->hiddenSymbol);
                if(strcmp(it->publicSymbol, "M") == 0){
                    return 1;
                }
                if(strcmp(it->publicSymbol, "0") == 0){
                    //reveal other Zeroes
                    if(revealAroundXY(list,xIn,yIn)!=0){
                        findMoreZeroes(list,rows);
                    }
                    turnPublicZeroIntoSpace(list);
                }
            }
        }
        it = it->next;
    }
    return 0;
}