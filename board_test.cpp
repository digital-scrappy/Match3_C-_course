#include <deque>
#include <iostream>
#include <map>
#include <string>

using namespace std;

int my_map[10][10] = {
    {1, 1, 2, 3, 3, 2, 4, 4, 1, 1}, {2, 2, 3, 4, 1, 3, 3, 4, 1, 2},
    {1, 2, 2, 4, 3, 3, 4, 1, 2, 1}, {3, 4, 2, 1, 3, 2, 3, 2, 3, 2},
    {1, 1, 3, 3, 1, 4, 2, 3, 1, 1}, {1, 1, 2, 1, 1, 1, 4, 4, 3, 1},
    {2, 2, 3, 4, 1, 3, 3, 4, 1, 2}, {1, 2, 2, 4, 3, 3, 4, 1, 2, 1},
    {3, 4, 2, 1, 1, 2, 3, 2, 3, 2}, {1, 1, 3, 3, 4, 3, 2, 4, 1, 1},
};

class Board {
private:
  int map[10][10];

  multimap<int, Board> branches;

public:
  void break_board();
  int find_matches_V(int column);
  int find_matches_H(int row);
  bool find_matches(int multiplier);
  int board_score = 0;
  Board(int init_map[10][10]);
  void eval_board();
  void print_board();
};

Board::Board(int init_map[10][10]) {
  for (int i = 0; i < 10; i++) {
    for (int x = 0; x < 10; x++) {
      this->map[i][x] = init_map[i][x];
    }
  }
}

void Board::break_board() {
  // have temp_row be a structure that gets pushed back all the time maybe with
  // some zeros at the end
  bool need_change = false;
  deque<int> temp_row;
  for (int x = 0; x < 10; x++) {
    for (int y = 0; y < 10; y++) {

      if (map[y][x] != 0) {
        temp_row.push_back(map[y][x]);
      } else {
        temp_row.push_front(0);
        need_change = true;
      }
    }
    if (need_change) {
      for (int i = 0; i < 10; i++) {
        map[i][x] = temp_row[i];
      }
    }
    need_change = false;
    temp_row.clear();
  }
}

int Board::find_matches_H(int row) {
  // horizontal search
  // finds the matches in a specific row
  // counts them and then turns them into zeros

  int counter = 1;
  int score = 0;
  int last = 11;
  int start;
  int end;

  for (int x = 0; x < 10; x++) {
    if (last == map[row][x]) {
      counter++;
    } else {
      if (counter > 2 && last != 0) {
        score += counter;
        start = x - counter;
        end = x;
        // replace scoring tiles with 0
        for (int i = start; i < end; i++) {
          map[row][i] = 0;
        }
      }
      last = map[row][x];
      counter = 1;
    }
  }

  return score;
}

int Board::find_matches_V(int column) {
  // vertical search
  // finds the matches in a specific column
  // counts them and then turns them into zeros
  int counter = 1;
  int score = 0;
  int last = 11;
  int start;
  int end;

  for (int y = 0; y < 10; y++) {
    if (last == map[y][column]) {
      counter++;
    } else {
      if (counter > 2 && last != 0) {
        score += counter;
        start = y - counter;
        end = y;
        // replace scoring tiles with 0
        for (int i = start; i < end; i++) {
          map[i][column] = 0;
        }
      }
      counter = 1;
      last = map[y][column];
    }
  }
  return score;
}

void Board::print_board() {
  string color_code;
  string out_str;

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {

      color_code = to_string(40 + map[i][j]);
      out_str = to_string(map[i][j]);
      cout << "\033[1;" << color_code << "m" << out_str << " \033[0m";
    }
    cout << endl;
  }
}

bool Board::find_matches(int multiplier) {
  int score = 0;
  for (int i = 0; i < 10; i++) {
    // here thess two functions could append to a container full of indices
    // which get set to zero in this function.
    // this could then also be used to pass it to the break function
    // and an optimized match finding function.

    score += find_matches_H(i);
    score += find_matches_V(i);
  }
  if (score > 0) {
    board_score += score * multiplier;
    return true;
  } else {
    return false;
  }
}

void Board::eval_board() {
  int multiplier = 1;
  while (find_matches(multiplier)) {
    break_board();
    multiplier++;
  }
}
int main() {

  Board one(my_map);
  one.eval_board();
  // one.print_board();
  // cout << one.board_score << endl;
  // for (int i = 0; i <10 ; i++) {
  //   one.find_matches_V(i);
  // }
  // one.print_board();
  // cout << one.board_score << endl;
  // one.break_board();
  // one.print_board();
  // cout << one.board_score << endl;
}
