#include "map.hh"

Map::Map()
{
    memset(&_map, 0, sizeof(_map));
}

case_type Map::get_occ_case(unsigned int x, unsigned int y) const
{
  if (x >= 19 || y >= 19)
    return (case_type::ERR);
  return (_map[x][y].occupancy);
}

void Map::set_occ_case(unsigned int x, unsigned int y, case_type content)
{
  if (x >= 19 || y >= 19)
    return;
  _map[x][y].occupancy = content;
}

void Map::print_occ_map() const
{
    for (int y = 0; y < 19; ++y)
    {
        for (int x = 0; x < 19; ++x)
        {
            switch (get_occ_case(x, y))
            {
                case EMPTY:
                    std::cout << "-";
                    break;
                case WHITE:
                    std::cout << "O";
                    break;
                case BLACK:
                    std::cout << "X";
                    break;
                case ERR:
                    std::cout << "E";
                    break;
            }
        }
        std::cout << std::endl;
    }
}

/*
Map::Map(int x, int y) : _x(x), _y(y)
{
  _map = new int[_x * _y];
  memset(_map, _x * _y * sizeof(int), 0);
}

Map::Map(const Map &s) : _x(s._x), _y(s._y)
{
  _map = new int[_x * _y];
  for (int x = 0; x < _y; ++x)
    for (int y = 0; y < _y; ++y)
      __map[y * _x + x] = s.__map[y * _x + x];
}

Map::~Map()
{
  delete _map;
}

void Map::displayMap() const
{
  for (int y = 0; y < _y; ++y)
  {
    for (int x = 0; x < _x; ++x)
    {
      switch (__map[y * _x + x]) {
        case 0:
          std::cout << "-";
          break;
        case 1:
          std::cout << "X";
          break;
        case 2:
          std::cout << "O";
          break;
      }
    }
    std::cout << std::endl;
  }
}

int Map::getSizeX() const
{
  return (_x);
}

int Map::getSizeY() const
{
  return (_y);
}

int Map::getMapValue(int x, int y) const
{
  if (x < 0 || x >= _x || y < 0 || y >= _y)
    return (-1);
  return (__map[y * _x + x]);
}

void Map::setMapValue(int x, int y, int val)
{
  if (x < 0 || x >= _x || y < 0 || y >= _y)
    return ;
  __map[y * _x + x] = val;
}

bool Map::checkCase(int x, int y) const
{
  if (x < 0 || x >= _x || y < 0 || y >= _y)
    return (false);
  if (__map[y * _x + x] != 0)
    return (false);
  return (true);
}

int Map::hasWon() const
{
  int tab[][2] = {{0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};
  int testX, testY, val;
  for (int x = 0; x < _x; ++x)
    for (int y = 0; y < _y; ++y)
      for (int j = 0; j < 8; ++j)
      {
        if (__map[y * _x + x] != 0)
        {
          val = __map[y * _x + x];
          for (int k = 0; k < 3; ++k)
          {
            testX = x + (tab[j][0] * k);
            testY = y + (tab[j][1] * k);
            if (testX < 0 || testX >= _x || testY < 0 || testY >= _y
                || __map[testY * _x + testX] != val)
                val = -1;
          }
          if (val != -1)
            return (val);
        }
      }
  return (0);
}

bool Map::isFull() const
{
  for (int x = 0; x < _x; ++x)
    for (int y = 0; y < _y; ++y)
      if (__map[y * _x + x] == 0)
        return (false);
  return (true);
} */
