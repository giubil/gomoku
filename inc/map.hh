#ifndef _MAP_HH
# define _MAP_HH

#include <iostream>
#include <cstring>
// #include <cstdint>

enum case_type : uint8_t
{
    EMPTY = 0, //-
    WHITE,     //O
    BLACK,     //X
    ERR        //E
};

typedef struct case_field {
  std::uint32_t data_black : 31;
  std::uint32_t data_white : 31;
  case_type occupancy : 2;
} case_field;

class Map
{
private:
    case_field _map[19][19];
public:
    Map();
    case_type get_occ_case(unsigned int x, unsigned int y) const;
    void set_occ_case(unsigned int x, unsigned int y, case_type content);
    void print_occ_map() const;
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
