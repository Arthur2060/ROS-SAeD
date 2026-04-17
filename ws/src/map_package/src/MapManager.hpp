#include <vector>
#include <iostream>

struct cell
{
    int x;
    int y;
    bool value;
};

class MapManager
{
private:
    std::vector<std::vector<cell>> map = {};
    float CELL_DISTANCE;

public:
    MapManager(int distancia, int mapWidth, int mapHeight)
    {
        for (int x = 0 ; x <= mapWidth ; x++) {
            for (int y = 0; y <= mapWidth; y++)
            {
                cell emptyCell;

                emptyCell.value = false;
                emptyCell.x = x;
                emptyCell.y = y;

                map[x].push_back(emptyCell);
            }
        }


        this->CELL_DISTANCE = distancia;
    }

    MapManager(int distancia, int mapScale)
    {
        for (int x = 0; x <= mapScale; x++)
        {
            for (int y = 0; y <= mapScale; y++)
            {
                cell emptyCell;

                emptyCell.value = false;
                emptyCell.x = x;
                emptyCell.y = y;

                map[x].push_back(emptyCell);
            }
        }

        this->CELL_DISTANCE = distancia;
    }

    bool addObstacle(float bruteX, float bruteY)
    {
        int x = bruteX / this->CELL_DISTANCE;
        int y = bruteY / this->CELL_DISTANCE;

        if (!map[x][y].value)
        {
            this->map[x][y].value = !map[x][y].value;
            return true;
        }
        return false;
    }

    float getCellDistance() {
        return this->CELL_DISTANCE;
    }
};