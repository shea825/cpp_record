//
// Created by shea on 1/21/22.
//

#include "grid.h"

/*
 * This cpp file used to moveTest grid class.
 * Returns true if the given square (r1, c1) represents a Knight on a
 * chess board that can move to square (r2, c2) successfully.
 * Knights move in a 2-by-1 pattern or an "L" shape.
 * The (r1, c1) must contain the string "knight" and (r2, c2) must
 * be an empty square, and both squares must be within bounds of the
 * board, otherwise false is returned.
 */

bool knightCanMove(const Grid<std::string>& grid, int r1, int c1, int r2, int c2) {
    unsigned int rl = abs(r1-r2), cl = abs(c1-c2);
    if (rl == 1 && cl == 2) {
        return true;
    } else if (rl == 2 && cl == 1) {
        return true;
    } else {
        return false;
    }
}

void moveTest(const Grid<std::string>& board, int r1, int c1, int r2, int c2, bool expected = false) {
    std::cout << "knight can move (" << r1 << ", " << c1 << "), (" << r2 << ", " << c2 << ")? ";
    bool result = knightCanMove(board, r1, c1, r2, c2);
    std::cout << (result ? "true" : "false");
    if (result == expected) {
        std::cout << "\t pass.";
    } else {
        std::cout << "\t FAIL!";
    }
    std::cout << std::endl;
}

int main() {
    Grid<std::string> board(8, 8);
    board[1][2] = "knight";
    board[0][4] = "king";
    board[3][1] = "rook";
    for (int r = 0; r < board.numRows(); r++) {
        for (int c = 0; c < board.numCols(); c++) {
            if (board[r][c].empty()) {
                std::cout << "?" << "\t\t";
            } else {
                std::cout << board[r][c] << "\t";
            }
        }
        std::cout << std::endl;
    }
    moveTest(board, 1, 2, 0, 0, true);
    moveTest(board, 1, 2, 0, 1);
    moveTest(board, 1, 2, 0, 4);
//    moveTest(board, 1, 2, 1, 4);
//    moveTest(board, 1, 2, 2, 4, true);
//    moveTest(board, 1, 2, 3, 4);
//    moveTest(board, 1, 2, 3, 3, true);
//    moveTest(board, 1, 2, 3, 1);
//    moveTest(board, 1, 2, 2, 0, true);
//    moveTest(board, 1, 2, -1, 1);
//    moveTest(board, 1, 2, 2, 8);
    return EXIT_SUCCESS;
}