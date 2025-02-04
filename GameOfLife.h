#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#include <vector>
#include <string>

class GameOfLife {
public:
    void loadBoard(const std::string& filename);
    void saveBoard(const std::string& filename) const;
    void computeNextGeneration(bool parallel, int threads);

private:
    int rows, cols;
    std::vector<std::vector<bool>> board;

    int countNeighbors(int x, int y) const;
};

#endif // GAMEOFLIFE_H
