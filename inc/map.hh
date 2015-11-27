#ifndef _MAP_HH
# define _MAP_HH

#include <iostream>
#include <cstring>

class Map
{
private:
  int _x;
  int _y;
  int *_map;
public:
  Map(int x = 10, int y = 10);
  Map(const Map &);
  ~Map();
  void displayMap() const;
  int getSizeX() const;
  int getSizeY() const;
  int getMapValue(int x, int y) const;
  void setMapValue(int x, int y, int val);
  bool checkCase(int x, int y) const;
  int hasWon() const;
  bool isFull() const;
};

#endif
