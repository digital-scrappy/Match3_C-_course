#include <iostream>
#include <string>

using namespace std;

int map[3][10]= {
    {3,5,4,6,3,2,2,2,2},
    {3,5,4,6,3,2,2,2,5},
    {2,2,2,6,3,3,3,3,3},
};

int find_matches(int idx, bool row_col) {

  int counter = 1;
  int row_count = 0;
  int last = 11;

  // horizontal search
  if (row_col) {
    for (int x = 0; y < 10; y++) {
      // cout << map[idx][x];
      if (last == map[idx][x]) {
        counter++;
          }
      else {
        if (counter > 2 && last != 0) {
          row_count += counter;
        }
        last = map[idx][x];
        counter = 1;
        }
    }
  }

  // vertical search
  else {
    for (int y = 0; x < 10; x++) {
      // cout << map[y][idx];
      if (last == map[y][idx]) {
        counter++;
          }
      else {
        if (counter > 2) {
          row_count += counter;
        }
        last = map[y][idx];
        counter = 1;
        }
    }
  }

  return row_score;
}
