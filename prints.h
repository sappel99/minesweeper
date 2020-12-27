/** \file
 * \brief Header file for the functions, which are used for printing.
 *
 */

#ifndef INC_130_MINESWEEPER_PRINTS_H
#define INC_130_MINESWEEPER_PRINTS_H

#include "minesweeper.h"

int printStructure(struct matrix list);
int printWarn(char *text);
int printError(char *text);
int printInfo(char *text);
int printPublic(struct matrix list);
int printHidden(struct matrix list);
int printMineInfo(struct matrix list,int mines);

#endif //INC_130_MINESWEEPER_PRINTS_H
