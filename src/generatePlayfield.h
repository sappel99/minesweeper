/** \file
 * \brief Header file for the functions, which are used for generating the playing field, before the game begins.
 *
 */

#ifndef INC_130_MINESWEEPER_GENERATEPLAYFIELD_H
#define INC_130_MINESWEEPER_GENERATEPLAYFIELD_H

#include "minesweeper.h"

int insertlist(int x, int y,int index, const char publicSymbol[2], const char hiddenSymbol[2], struct matrix *start);
int generateMatrix(int x, int y, int count,char alph,struct matrix *list, int rows, int cols);
int setMines(struct matrix list,int mines,int rows,int cols, int minesIndex[mines]);
int calculateMineValues(struct matrix list,int mines,int cols, const int minesIndex[mines]);
int revealFirst(struct matrix list,int rows, int cols);

#endif //INC_130_MINESWEEPER_GENERATEPLAYFIELD_H
