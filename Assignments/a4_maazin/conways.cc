#include <iostream>
#include <string>

struct GameBoard {
    std::string cells;
    int cols;
};

char fetchCell(GameBoard& b, int r, int c) {
    if (r < 0 || c < 0 || c >= b.cols) return '.';
    
    int pos = r * b.cols + c;
    if (pos >= (int)b.cells.length()) {
        return '.';
    }
    return b.cells[pos];
}

int calculateAlive(GameBoard& b, int r, int c) {
    int aliveCount = 0;
    
    for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {
            if (dr == 0 && dc == 0) continue;
            
            if (fetchCell(b, r + dr, c + dc) == 'O') {
                aliveCount++;
            }
        }
    }
    
    return aliveCount;
}

void stepBoard(GameBoard& b) {
    GameBoard nextGen = b;
    int totalCells = (int)b.cells.length();
    
    for (int k = 0; k < totalCells; k++) {
        int row = k / b.cols;
        int col = k % b.cols;
        int neighbors = calculateAlive(b, row, col);
        
        if (b.cells[k] == 'O') {
            if (neighbors < 2 || neighbors > 3) {
                nextGen.cells[k] = '.';
            }
        } else {
            if (neighbors == 3) {
                nextGen.cells[k] = 'O';
            }
        }
    }
    
    b = nextGen;
}

void displayBoard(GameBoard& b) {
    for (int col = 0; col < b.cols; col++) {
        std::cout << "|";
    }
    std::cout << "\n";
        
    int totalCells = (int)b.cells.length();
    for (int k = 0; k < totalCells; k++) {
        std::cout << b.cells[k];
        if ((k + 1) % b.cols == 0) {
            std::cout << "\n";
        }
    }
    
    for (int col = 0; col < b.cols; col++) {
        std::cout << "|";
    }
    std::cout << "\n";
}
    
int main() {
    GameBoard board;
    std::string initialRow;
    
    if (!(std::cin >> initialRow)) return 0;
    
    board.cells = initialRow;
    board.cols = initialRow.length();
    
    std::string nextRow;
    while (std::cin >> nextRow) {
        if (nextRow == "x") break;
        board.cells += nextRow;
    }
    
    char command;
    while (std::cin >> command) {
        if (command == 'p') {
            displayBoard(board);
        } else if (command == 's') {
            stepBoard(board);
        } else {
            std::cerr << "Invalid command: " << command << "\n";
            std::cerr << "Test is invalid input.\n";
        }
    }
    
    return 0;
}