#ifndef _MAP_HH
# define _MAP_HH

#include <iostream>
#include <cstring>
#include <cstdint>

typedef struct line_field
{
    uint64_t line : 48;
} line_field;

enum case_type
{
    EMPTY = 0, //-
    WHITE,     //O
    BLACK,     //X
    ERR        //E
};

class Map
{
private:
    line_field _map[19];
public:
    Map();
    case_type get_case(unsigned int x, unsigned int y) const;
    void set_case(unsigned int x, unsigned int y, case_type content);
    void print_map() const;
};

/*class Map
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
};*/

#endif
