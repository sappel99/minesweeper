/** \file
 * \brief Header file for the functions, which are used for revealing Fields.
 *
 */

#ifndef INC_130_MINESWEEPER_REVEALFIELDS_H
#define INC_130_MINESWEEPER_REVEALFIELDS_H

#include "minesweeper.h"

int revealAroundXY(struct matrix list,int xIn, int yIn);
int findMoreZeroes(struct matrix list,int rows);
int turnPublicZeroIntoSpace(struct matrix list);
int readAndReveal(struct matrix list,int rows);

#endif //INC_130_MINESWEEPER_REVEALFIELDS_H
