/** \file
 * \brief These functions are used for either checking events or checking inputs
 *
 */

#include <stdio.h>
#include <memory.h>
#include "checkingFunctions.h"
#include "prints.h"

/**
 * \brief OLD - This function is similar to isAlphaSwitch();
 * @param letter the given letter to check
 * @return 1 when part of upper alphabet, 0 if not part of alph.
 */
int partOfAlphabet(char letter){
    char *alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    if(strstr(alphabet, &letter) != NULL) {
        return 1;
    }
    return 0;
}
/**
 * \brief OLD - This function is similar to isDigitSwitch();
 * @param numberIn the given character/number
 * @return 1 if number, 0 if not number
 */
int isDigit(char numberIn){
    char *number = "0123456789";
    if(strstr(number, &numberIn) != NULL) {
        return 1;
    }
    return 0;
}
/**
 * \brief This function checks if all mines are marked.
 * @param list the existing matrix list
 * @param mines the amount of mines in the game
 * @return 1 if all mines marked are correct, 0 if not
 */
int checkAllMinesMarked(struct matrix list, int mines){
    int countMinesMarked = 0;
    int countWrongMinesMarked = 0;
    struct matrix *it = &list;
    while (it != NULL) {
        if (strcmp(it->hiddenSymbol, "M") == 0 && strcmp(it->publicSymbol, "?") == 0) { //marked mine
            countMinesMarked++;
        }
        if (strcmp(it->hiddenSymbol, "M") != 0 && strcmp(it->publicSymbol, "?") == 0) { //not a mine but marked
            countWrongMinesMarked++;
        }
        if(countMinesMarked==mines&&countWrongMinesMarked==0){ //if all mines marked and no wrong mines
            return 1;
        }
        it = it->next;
    }
    //printf("Wrong:%d, Correct:%d",countWrongMinesMarked,countMinesMarked);
    return 0;
}
/**
 * \brief This function checks if all number fields are opened
 * @param list the existing matrix list
 * @param rows the number of rows
 * @param cols the number of columns
 * @param mines the amount of mines in the game
 * @return 1 if all fields are opened, 0 if not
 */
int checkAllFieldsOpened(struct matrix list, int rows,int cols, int mines){
    int correctlyOpened = 0;
    struct matrix *it = &list;
    while (it != NULL) { //if playfield && opened or opened zero
        if(it->x>0&&it->y>0&&((strcmp(it->publicSymbol, it->hiddenSymbol) == 0)||(strcmp(it->publicSymbol, " ") == 0))){
            correctlyOpened++;
        }
        if(correctlyOpened==(rows*cols-rows-cols+1-mines)){ //if opened number fields == amount of number fields
            return 1;
        }
        it = it->next;
    }
    return 0;
}
/**
 * \brief This function checks if the given character is a number
 * @param digit the char digit given
 * @return 1 if charc digit is a number, 0 if not
 */
int isDigitSwitch(char digit){
    switch (digit) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9': return 1;
        default: return 0;
    }
}
/**
 * \brief This function checks if the given letter is part of the uppercase alphabet
 * @param alpha the given letter to check
 * @return 1 if charc alpha is a letter, 0 if not
 */
int isAlphaSwitch(char alpha){
    switch (alpha) {
        case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
        case 'G': case 'H': case 'I': case 'J': case 'K': case 'L':
        case 'M': case 'N': case 'O': case 'P': case 'Q': case 'R':
        case 'S': case 'T': case 'U': case 'V': case 'W': case 'X':
        case 'Y':
        case 'Z': return 1;
        default: return 0;
    }
}

/**
 * \brief This functions checks the arguments given, when main function was called
 * @param argc Number of arguments given
 * @param argv Value of arguments given
 * @param x the x coordinate
 * @param y the y coordinate
 * @param mines the amount of mines in the game
 * @return 1 if error anywhere, 0 if no error
 */
int checkMainParameters(int argc, char* argv[], int *x, int *y, int *mines){
    if (argc < 3) {
        printError("Missing argument\n");
        return 1;
    } else if(argc > 3) {
        printError("Too many arguments\n");
        return 1;
    }

    if(strlen(argv[1]) != 3 && strlen(argv[1]) != 5){
        printError("First arg not 3 or 5 characters\n");
        return 1;
    }

    if(strlen(argv[2]) != 1 && strlen(argv[2]) != 2){
        printError("Second arg not 1 or 2 characters\n");
        return 1;
    }

    if(strlen(argv[1]) == 3){
        if(isDigitSwitch(argv[1][0])!=1){
            printError("First arg, 1st charc not a digit\n");
            return 1;
        }

        if(argv[1][1] != 'x'){
            printError("First arg, 2nd charc not an x\n");
            return 1;
        }

        if(isDigitSwitch(argv[1][2])!=1){
            printError("First arg, 3rd charc not a digit\n");
            return 1;
        }

        *x = (unsigned char) (argv[1][0]-48);
        *y = (unsigned char) (argv[1][2]-48);

    }else if(strlen(argv[1]) == 5){
        if(isDigitSwitch(argv[1][0])!=1){
            printError("First arg, 1st charc not a digit\n");
            return 1;
        }

        if(isDigitSwitch(argv[1][1])!=1){
            printError("First arg, 2nd charc not a digit\n");
            return 1;
        }

        if(argv[1][2] != 'x'){
            printError("First arg, 3rd charc not an x\n");
            return 1;
        }

        if(isDigitSwitch(argv[1][3])!=1){
            printError("First arg, 4th charc not a digit\n");
            return 1;
        }

        if(isDigitSwitch(argv[1][4])!=1){
            printError("First arg, 5th charc not a digit\n");
            return 1;
        }

        *x = (unsigned char) ((argv[1][0]-48)*10+(argv[1][1]-48));
        *y = (unsigned char) ((argv[1][3]-48)*10+(argv[1][4]-48));

    }else{
        printf("\033[0;31mError in strlen(argv[1]), not 3 or 5 past check: %lu\033[0m",strlen(argv[1]));
        return 1;
    }

    if(strlen(argv[2]) == 1){
        if(isDigitSwitch(argv[2][0])!=1){
            printError("2nd arg, 1st charc not a digit\n");
            return 1;
        }

        *mines = (unsigned char) (argv[2][0]-48);

    }else if(strlen(argv[2]) == 2){
        if(isDigitSwitch(argv[2][0])!=1){
            printError("2nd arg, 1st charc not a digit\n");
            return 1;
        }
        if(isDigitSwitch(argv[2][1])!=1){
            printError("2nd arg, 2nd charc not a digit\n");
            return 1;
        }

        *mines = (unsigned char) ((argv[2][0]-48)*10+(argv[2][1]-48));

    }else{
        printf("\033[0;31mError in strlen(argv[2]), not 1 or 2 past check: %lu\033[0m",strlen(argv[2]));
        return 1;
    }

    if(*x < 3 || *y < 3){
        printf("\033[0;31mMatrix < 3x3 -> %dx%d\033[0m",*x,*y);
        return 1;
    }

    if(*x > 26 || *y > 26){
        printf("\033[0;31mMatrix > 26x26 -> %dx%d\033[0m",*x,*y);
        return 1;
    }

    if(*mines > ((*x * *y)/3)){
        printWarn("Minenanzahl sehr hoch! - This might cause incorrect program functionality\n");
    }

    if(*mines < ((*x * *y)/10)){
        printWarn("Minenanzahl sehr niedrig! - This might cause incorrect program functionality\n");
    }

    return 0;
}