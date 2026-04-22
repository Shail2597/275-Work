#include <iostream>
#include <string>

struct Grid {
    std::string data;
    int width;
};

char getCell(Grid& g, int r, int c) {
    if (r < 0 || c < 0 || c >= g.width) return '.';
    
    int pos = r * g.width + c;
    if (pos >= (int)g.data.length()) {
        return '.';
    }
    return g.data[pos];
}

int countNeighbors(Grid& g, int r, int c) {
    int count = 0;
    
    for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {
            if (dr == 0 && dc == 0) continue;
            
            if (getCell(g, r + dr, c + dc) == 'O') {
                count++;
            }
        }
    }
    
    return count;
}

void nextGeneration(Grid& g) {
    Grid next = g;
    int size = (int)g.data.length();
    
    for (int k = 0; k < size; k++) {
        int row = k / g.width;
        int col = k % g.width;
        int neighbors = countNeighbors(g, row, col);
        
        if (g.data[k] == 'O') {
            if (neighbors < 2 || neighbors > 3) {
                next.data[k] = '.';
            }
        } else {
            if (neighbors == 3) {
                next.data[k] = 'O';
            }
        }
    }
    
    g = next;
}

void printGrid(Grid& g) {
    for (int col = 0; col < g.width; col++) {
        std::cout << "|";
    }
    std::cout << "\n";
        
    int size = (int)g.data.length();
    for (int k = 0; k < size; k++) {
        std::cout << g.data[k];
        if ((k + 1) % g.width == 0) {
            std::cout << "\n";
        }
    }
    
    for (int col = 0; col < g.width; col++) {
        std::cout << "|";
    }
    std::cout << "\n";
}
    
int main() {
    Grid board;
    std::string initialRow;
    
    if (!(std::cin >> initialRow)) return 0;
    
    board.data = initialRow;
    board.width = initialRow.length();
    
    std::string nextRow;
    while (std::cin >> nextRow) {
        if (nextRow == "x") break;
        board.data += nextRow;
    }
    
    char command;
    while (std::cin >> command) {
        if (command == 'p') {
            printGrid(board);
        } else if (command == 's') {
            nextGeneration(board);
        } else {
            std::cerr << "Invalid command: " << command << "\n";
            std::cerr << "Test is invalid input.\n";
        }
    }
    
    return 0;
}