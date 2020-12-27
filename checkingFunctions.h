/** \file
 * \brief Header file for the functions, which are used for either checking events or checking inputs
 *
 */

#ifndef INC_130_MINESWEEPER_CHECKINGFUNCTIONS_H
#define INC_130_MINESWEEPER_CHECKINGFUNCTIONS_H

#include "minesweeper.h"

int partOfAlphabet(char letter);
int isDigit(char numberIn);
int checkAllMinesMarked(struct matrix list, int mines);
int checkAllFieldsOpened(struct matrix list, int rows,int cols, int mines);
int isDigitSwitch(char digit);
int checkMainParameters(int argc, char* argv[], int *x, int *y, int *mines);
int isAlphaSwitch(char digit);

#endif //INC_130_MINESWEEPER_CHECKINGFUNCTIONS_H
