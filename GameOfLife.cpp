#include "GameOfLife.h"
#include <fstream>
#include <stdexcept>
#include <omp.h>

// Load the board from a file
void GameOfLife::loadBoard(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Error: Unable to open file: " + filename);
    }

    file >> cols;
    char delimiter;
    file >> delimiter >> rows;

    if (delimiter != ',' || rows <= 0 || cols <= 0) {
        throw std::runtime_error("Error: Invalid dimensions in file: " + filename);
    }

    board.resize(rows, std::vector<bool>(cols, false));
    std::string line;
    std::getline(file, line); // Skip to the next line

    for (int i = 0; i < rows; ++i) {
        std::getline(file, line);
        for (int j = 0; j < cols; ++j) {
            board[i][j] = (line[j] == 'x');
        }
    }
}

// Save the board to a file
void GameOfLife::saveBoard(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file) {
        throw std::runtime_error("Error: Unable to save file: " + filename);
    }

    file << cols << "," << rows << "\n";
    for (const auto& row : board) {
        for (bool cell : row) {
            file << (cell ? 'x' : '.');
        }
        file << "\n";
    }
}

// Count neighbors of a cell
int GameOfLife::countNeighbors(int x, int y) const {
    int liveNeighbors = 0;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;
            int nx = (x + dx + rows) % rows;
            int ny = (y + dy + cols) % cols;
            liveNeighbors += board[nx][ny];
        }
    }
    return liveNeighbors;
}

// Compute the next generation
void GameOfLife::computeNextGeneration(bool parallel, int threads) {
    std::vector<std::vector<bool>> next(rows, std::vector<bool>(cols, false));

    if (parallel) {
        #pragma omp parallel for num_threads(threads) collapse(2)
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                int neighbors = countNeighbors(i, j);
                next[i][j] = (board[i][j] && (neighbors == 2 || neighbors == 3)) || (!board[i][j] && neighbors == 3);
            }
        }
    } else {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                int neighbors = countNeighbors(i, j);
                next[i][j] = (board[i][j] && (neighbors == 2 || neighbors == 3)) || (!board[i][j] && neighbors == 3);
            }
        }
    }

    board = std::move(next);
}
