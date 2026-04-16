
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

public:
    MapManager()
    {
        for (int x = 0; x <= sizeof(map); x++)
        {
            for (int y = 0; y <= sizeof(map[x]); y++)
            {
                struct cell cell;

                cell.x = x;
                cell.y = y;
                cell.value = false;

                map[x][y] = cell;
            }
        }
    }

    bool addObstacle(int x, int y)
    {
        if (!map[x][y].value)
        {
            map[x][y].value = !map[x][y].value;
            return true;
        }
        return false;
    }
};