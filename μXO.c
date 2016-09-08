#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print(long);
char finished(long);

/**
 * μXO is a *super* lightweight Tic Tac Toe client.
 *
 * The game board is stored in a 32-bit long which is laid out like this:
 * 00000000000000000000000000000000
 * |___O___||___X___|T|__unused___|
 *
 * In the O and X sections, a 1 indicates that an X or an O is in that space on
 * the board. T is just an indicator of turn. If it is set, it's O's turn, else
 * it's X's turn.
 *
 * @author Abe Fehr
 */
int main() {

  /* Create the long to store all of the game data */
  long board = 0;

  /* Randomly decide which symbol starts the game */
  srand(time(NULL));
  if (rand() & 1) { board |= 1 << 19; }

  /* Be curteous and welcome the player */
  printf("Welcome to μXO.\n");

  /* Loop until the board has been completely filled */
  while (!finished(board)) {
    print(board);
    printf("It's %c's turn. Where would you like your symbol? (0-9) ", ((board >> 19) & 1 ? 'O' : 'X'));
    int i;
    scanf("%d", &i);

    /* Marks the board at the given index with either an X or an O */
    board |= (1 << ((board >> 19 & 1) ? i : i + 9));

    /* Switch to ask the other player */
    board ^= (1 << 19);
  }

  print(board);
  /* Get whose turn it last was and say they won */
  printf("\n\n%c wins.", ((board ^ (1 << 19)) >> 19) & 1 ? 'O' : 'X');
  return 0;
}

/**
 * Prints the board out prettily
 *
 * @param board the board to print out
 */
void print(long board) {
  /* Print it beautifully for the user */
  for (int i = 0; i < 9; ++i) {
    /* Start by printing a line break if it's a new row */
    if (i % 3 == 0) { printf("\n"); }

    /* Checks if it's either O, X, or unset */
    if ((board >> i) & 1) { printf("O "); }
    else if ((board >> (i + 9)) & 1) { printf("X "); }
    else { printf("  "); }
  }
}

/**
 * Checks whether the game is completed or not by using a bunch of bit masks
 *
 * To check for wins in a row, the number 0x7 (0b111) is shifted to various
 * positions.
 * To check for wins in a column, the number 0x49 (0b1001001) is used
 * Lastly, the diagonals use 0x54 and 0x111 (0b1010100 and 0b100010001
 * respectively)
 *
 * @param board the game board with the placement information
 */
char finished(long board) {
  char result = 0;

  /* Checks if either X or O won in the columns or rows */
  for (int i = 0; i <= 3; ++i) {
    result |= ((board & 0x7 << (i * 3)) == 0x7 << (i * 3));
    result |= ((board & 0x7 << (i * 3 + 9)) == 0x7 << (i * 3 + 9));
    result |= ((board & 0x49 << i) == 0x49 << i);
    result |= ((board & 0x49 << (i + 9)) == 0x49 << (i + 9));
  }
  /* Checks if X or O won in a diagonal */
  result |= ((board & 0x54) == 0x54);
  result |= ((board & 0x54 << 9) == 0x54 << 9);
  result |= ((board & 0x111) == 0x111);
  result |= ((board & 0x111 << 9) == 0x111 << 9);

  return result;
}