#include <iostream>
using namespace std;

#define N 4

class NQueensBranchBound {

private:
    int board[N][N];

    bool cols[N];
    bool leftDiag[2 * N];
    bool rightDiag[2 * N];

public:

    NQueensBranchBound() {

        for(int i = 0; i < N; i++) {

            cols[i] = false;

            for(int j = 0; j < N; j++)
                board[i][j] = 0;
        }

        for(int i = 0; i < 2 * N; i++) {
            leftDiag[i] = false;
            rightDiag[i] = false;
        }
    }

    bool solve(int row) {

        // All queens placed
        if(row == N)
            return true;

        for(int col = 0; col < N; col++) {

            // Check bounds
            if(!cols[col] &&
               !leftDiag[row - col + N - 1] &&
               !rightDiag[row + col]) {

                // Place queen
                board[row][col] = 1;

                cols[col] = true;
                leftDiag[row - col + N - 1] = true;
                rightDiag[row + col] = true;

                // Recur
                if(solve(row + 1))
                    return true;

                // Backtrack
                board[row][col] = 0;

                cols[col] = false;
                leftDiag[row - col + N - 1] = false;
                rightDiag[row + col] = false;
            }
        }

        return false;
    }

    void printBoard() {

        cout << "\nSolution:\n";

        for(int i = 0; i < N; i++) {

            for(int j = 0; j < N; j++) {

                if(board[i][j] == 1)
                    cout << "Q ";
                else
                    cout << ". ";
            }

            cout << endl;
        }
    }
};

class NQueensBacktracking {
private:
    int board[N][N];

public:
    NQueensBacktracking() {
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                board[i][j] = 0;
    }

    bool isSafe(int row, int col) {

        // Check column
        for(int i = 0; i < row; i++) {
            if(board[i][col] == 1)
                return false;
        }

        // Check left diagonal
        for(int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
            if(board[i][j] == 1)
                return false;
        }

        // Check right diagonal
        for(int i = row, j = col; i >= 0 && j < N; i--, j++) {
            if(board[i][j] == 1)
                return false;
        }

        return true;
    }

    bool solve(int row) {

        // All queens placed
        if(row == N)
            return true;

        // Try each column
        for(int col = 0; col < N; col++) {

            if(isSafe(row, col)) {

                // Place queen
                board[row][col] = 1;

                // Recur for next row
                if(solve(row + 1))
                    return true;

                // Backtrack
                board[row][col] = 0;
            }
        }

        return false;
    }

    void printBoard() {
        cout << "\nSolution:\n";

        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {

                if(board[i][j] == 1)
                    cout << "Q ";
                else
                    cout << ". ";
            }
            cout << endl;
        }
    }
};

int main() {

    NQueensBranchBound obj;

    if(obj.solve(0))
        obj.printBoard();
    else
        cout << "Solution does not exist";

    return 0;
}