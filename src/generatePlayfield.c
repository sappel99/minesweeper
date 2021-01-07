/** \file
 * \brief These functions are used for generating the playing field, before the game begins.
 *
 */

#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include "generatePlayfield.h"
#include "checkingFunctions.h"

/**
 * \brief This funtion adds a new element to the matrix list
 * @param x the x coordinate
 * @param y the y coordinate
 * @param index the index of the element in the list
 * @param publicSymbol the visible symbol to the player: Nothing or numbers
 * @param hiddenSymbol the hidden symbol to the player: Mines,..
 * @param start the existing matrix list
 * @return 0 when successful, -1 when out of memory
 */
int insertlist(int x, int y,int index, const char publicSymbol[2], const char hiddenSymbol[2], struct matrix *start) {
    struct matrix *item = malloc(sizeof(struct matrix));
    if (item == NULL) {
        fprintf(stderr, "Out of memory");
        return -1;
    }
    item->x = x;
    item->y = y;
    item->index = index;
    item->publicSymbol[0] = publicSymbol[0];
    item->hiddenSymbol[0] = hiddenSymbol[0];
    if (start->next == NULL) { // first/only element
        start->next = item;
        item->next = NULL;
    }
    else { // append new item
        while (start->next != NULL) {
            start = start->next;
        }
        start->next = item;
    }
    return 0;
}

/**
 * \brief This function calculates the correct coordinates and symbols for each element
 *
 * Every element in the first row gets an alphabetical character.
 * Every element in the first column becomes a "|".
 * Every other elements becomes public "-" and hidden "0".
 *
 * @param x the x coordinate
 * @param y the y coordinate
 * @param index the index of the element in the list
 * @param alph the beginning character "A" for the first row
 * @param list the existing matrix list
 * @param rows the number of rows
 * @param cols the number of columns
 * @return 0 when successful, 1 when unsuccessful
 */
int generateMatrix(int x, int y, int index,char alph,struct matrix *list, int rows, int cols){

    for(int i = 0;i<(rows*cols-1);i++){
        if(index%cols==0){y=0;x++;}
        if(x==0){
            if (insertlist(x,y,index, &alph,&alph,list) != 0) {
                return 1;
            }
            alph++;
        }else{
            if(y==0){
                if (insertlist(x,y,index, "|","|",list) != 0) {
                    return 1;
                }
            }else{
                if (insertlist(x,y,index, "-","0",list) != 0) {
                    return 1;
                }
            }
        }
        y++;
        index++;
    }
    return 0;
}
/**
 * \brief This function sets the mines randomly in the playing field
 * @param list the existing matrix list
 * @param mines the amount of mines in the game
 * @param rows the number of rows
 * @param cols the number of columns
 * @param minesIndex saves the place of mines to caluclate the surrounding mine values later
 * @return 0 when successful
 */
int setMines(struct matrix list,int mines,int rows,int cols, int minesIndex[mines]){
    int anzGesetzteMinen = 0;
    while(anzGesetzteMinen < mines){
        struct matrix *it = &list;
        int random = randomNumber(0,(rows*cols));
        while (it != NULL) {
            if(it->index==random){
                if(strcmp(it->publicSymbol,"|")!=0&&strcmp(it->hiddenSymbol,"M")!=0&&isAlphaSwitch(it->publicSymbol[0])==0){
                    strcpy(it->hiddenSymbol, "M");
                    minesIndex[anzGesetzteMinen] = it->index;
                    anzGesetzteMinen++;
                }
            }
            it = it->next;
        }
    }
    return 0;
}

/**
 * \brief This function calculates the hidden value for each field surrounding a mine
 * @param list the existing matrix list
 * @param mines the amount of mines in the game
 * @param cols the number of columns
 * @param minesIndex the places of mines on the playing field
 * @return 0 when successful
 */
int calculateMineValues(struct matrix list,int mines,int cols, const int minesIndex[mines]){
    for(int i = 0; i < mines; i++){
        struct matrix *it = &list;
        while (it != NULL) {
            if(it->index==minesIndex[i]-1&&strcmp(it->publicSymbol,"|")!=0&&strcmp(it->hiddenSymbol,"M")!=0&&isAlphaSwitch(it->publicSymbol[0])==0){
                it->hiddenSymbol[0]++;
            }
            if(it->index==minesIndex[i]+1&&strcmp(it->publicSymbol,"|")!=0&&strcmp(it->hiddenSymbol,"M")!=0&&isAlphaSwitch(it->publicSymbol[0])==0){
                it->hiddenSymbol[0]++;
            }
            if(it->index==minesIndex[i]-cols&&strcmp(it->publicSymbol,"|")!=0&&strcmp(it->hiddenSymbol,"M")!=0&&isAlphaSwitch(it->publicSymbol[0])==0){
                it->hiddenSymbol[0]++;
            }
            if(it->index==minesIndex[i]-cols-1&&strcmp(it->publicSymbol,"|")!=0&&strcmp(it->hiddenSymbol,"M")!=0&&isAlphaSwitch(it->publicSymbol[0])==0){
                it->hiddenSymbol[0]++;
            }
            if(it->index==minesIndex[i]-cols+1&&strcmp(it->publicSymbol,"|")!=0&&strcmp(it->hiddenSymbol,"M")!=0&&isAlphaSwitch(it->publicSymbol[0])==0){
                it->hiddenSymbol[0]++;
            }
            if(it->index==minesIndex[i]+cols&&strcmp(it->publicSymbol,"|")!=0&&strcmp(it->hiddenSymbol,"M")!=0&&isAlphaSwitch(it->publicSymbol[0])==0){
                it->hiddenSymbol[0]++;
            }
            if(it->index==minesIndex[i]+cols-1&&strcmp(it->publicSymbol,"|")!=0&&strcmp(it->hiddenSymbol,"M")!=0&&isAlphaSwitch(it->publicSymbol[0])==0){
                it->hiddenSymbol[0]++;
            }
            if(it->index==minesIndex[i]+cols+1&&strcmp(it->publicSymbol,"|")!=0&&strcmp(it->hiddenSymbol,"M")!=0&&isAlphaSwitch(it->publicSymbol[0])==0){
                it->hiddenSymbol[0]++;
            }
            it = it->next;
        }
    }
    return 0;
}

/**
 * \brief This function randomly reveals the first number to begin with
 * @param list the existing matrix list
 * @param rows the number of rows
 * @param cols the number of columns
 * @return 0 when successful
 */
int revealFirst(struct matrix list,int rows, int cols){
    int gesetzt = 0;
    while(gesetzt == 0) {
        struct matrix *it = &list;
        int random = rand() % (rows * cols);
        while (it != NULL) {
            if (it->index == random) {
                if (strcmp(it->publicSymbol, "|") != 0 && strcmp(it->hiddenSymbol, "M") != 0 &&
                    isAlphaSwitch(it->publicSymbol[0]) == 0 && strcmp(it->hiddenSymbol, "0") != 0) {
                    strcpy(it->publicSymbol, it->hiddenSymbol);
                    gesetzt++;
                }
            }
            it = it->next;
        }
    }
    return 0;
}