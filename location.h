#ifndef LOCATION_H
#define LOCATION_H
struct Location {
  int x, y;
  Location() : x(0), y(0) {}
  Location(int x, int y) : x(x), y(y) {}
};
#endif
