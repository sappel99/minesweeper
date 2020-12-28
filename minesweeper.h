/** \file
 * \brief Main header file of the game minesweeper
 */

#ifndef INC_130_MINESWEEPER_MINESWEEPER_H
#define INC_130_MINESWEEPER_MINESWEEPER_H

#define NULL ( (void *) 0)

/** \struct
 * \brief This is the matrix for every element on the playing field.
 *
 * Each element consists of an x and y coordinate, an index in the list,
 * a public and a secret symbol and a pointer to the next element in the list.
 *
 */
struct matrix {
    int x; /**< the x coordinate */
    int y; /**< the y coordinate */
    int index; /**< the index of the element in the list */
    char publicSymbol[2]; /**< the visible symbol to the player: Nothing or numbers */
    char hiddenSymbol[2]; /**< the hidden symbol to the player: Mines,..*/
    struct matrix *next; /**< pointer to the next element */
};

void free_list(struct matrix *start);
int randomNumber(int x, int y);

#endif //INC_130_MINESWEEPER_MINESWEEPER_H
