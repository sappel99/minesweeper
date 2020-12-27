/** \file
 * \brief Header file for the functions, which are used for loading and saving player infos
 *
 */

#ifndef INC_130_MINESWEEPER_PLAYERINFO_H
#define INC_130_MINESWEEPER_PLAYERINFO_H

int askPlayerInfo(char eingabe[256]);
int loadPlayerInfo(char spielername[256],int *playedGames, int *gamesWon, int *gamesLost, int *openedCells);
int savePlayerInfo(char spielername[256],int playedGames, int gamesWon, int gamesLost, int openedCells);

#endif //INC_130_MINESWEEPER_PLAYERINFO_H
