/** \file
 * \brief These functions are used for printing matrixes, warnings, errors or informations
 *
 */

#include <stdio.h>
#include <memory.h>
#include "prints.h"
/**
 * \brief This function prints the design idea behind the matrix
 * @param list the existing matrix list
 * @return 0 if successful
 */
int printStructure(struct matrix list){
    struct matrix *it = &list;
    while (it != NULL) {
        printf("%d: [%d,%d,%c,%c]\n",it->index, it->x, it->y,it->publicSymbol[0],it->hiddenSymbol[0]);
        it = it->next;
    }
    return 0;
}
/**
 * \brief Prints a yellow colored text to warn
 * @param text the given text
 * @return 0 if successful
 */
int printWarn(char *text){
    printf("\033[0;33m%s\033[0m\n",text);
    return 0;
}
/**
 * \brief Prints a red colored text to show an error
 * @param text the given text
 * @return 0 if successful
 */
int printError(char *text){
    printf("\033[0;31m%s\033[0m\n",text);
    return 0;
}
/**
 * \brief Prints a green colored text to show info
 * @param text the given text
 * @return 0 if successful
 */
int printInfo(char *text){
    printf("\033[0;32m%s\033[0m\n",text);
    return 0;
}
/**
 * \brief Prints the public matrix
 * @param list the existing matrix list
 * @return 0 if successful
 */
int printPublic(struct matrix list){
    struct matrix *it2 = &list;
    while (it2 != NULL) {
        if(it2->y==0&&it2->x!=0){printf("\n");}
        if(it2->y==0){
            printf("%02d ",it2->x);
        }else{
            printf("%c ",it2->publicSymbol[0]);
        }
        it2 = it2->next;
    }
    printf("\n");
    return 0;
}

/**
 * \brief Prints the hidden/secret matrix
 * @param list the existing matrix list
 * @return 0 if successful
 */
int printHidden(struct matrix list){
    struct matrix *it3 = &list;
    while (it3 != NULL) {
        if(it3->y==0&&it3->x!=0){printf("\n");}
        if(it3->y==0){
            printf("%02d ",it3->x);
        }else{
            printf("%c ",it3->hiddenSymbol[0]);
        }
        it3 = it3->next;
    }
    printf("\n");
    return 0;
}
/**
 * \brief Prints amount of mines and amount of mines marked
 * @param list the existing matrix list
 * @param mines the amount of mines in the game
 * @return 0 if successful
 */
int printMineInfo(struct matrix list,int mines){
    int minesMarked = 0;
    struct matrix *it = &list;
    while (it != NULL) {
        if(strcmp(it->publicSymbol, "?") == 0){
            minesMarked++;
        }
        it = it->next;
    }

    printf("\033[0;32mAll Mines: %d, Mines Marked: %d\033[0m\n",mines,minesMarked);
    return 0;
}