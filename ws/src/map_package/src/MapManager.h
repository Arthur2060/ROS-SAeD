
struct cell
{
    int x;
    int y;
    bool value;
};

class MapManager
{
private:
    cell map[10][10] = {};
    float CELL_DISTANCE;

public:
    MapManager(int distancia)
    {
        for (int x = 0; x <= sizeof(map); x++)
        {
            for (int y = 0; y <= sizeof(map[x]); y++)
            {
                struct cell cell;

                cell.x = x;
                cell.y = y;
                cell.value = false;

                this->map[x][y] = cell;
            }
        }

        this->CELL_DISTANCE = distancia;
    }

    bool addObstacle(int x, int y)
    {
        if (!map[x][y].value)
        {
            this->map[x][y].value = !map[x][y].value;
            return true;
        }
        return false;
    }

    float getDistanciaDeQuadro() {
        return this->CELL_DISTANCE;
    }
};