#ifndef BOARD_H_
#define BOARD_H_

#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <iterator>

using namespace std;

class Board {
private:
  uint8_t map[10][10];
  uint8_t map_copy[10][10];
  void regenerate_map();
  void break_board();
  int find_matches_V(int column);
  int find_matches_H(int row);
  int check_legal();
  bool switch_stones(int * move);
  void get_checking_indices(int * checking_indices, int * move);
  bool find_matches();
  int multiplier = 1;


public:
  Board(uint8_t init_map[10][10],int  move[4], int score);
  void drop_low_scores();
  int move[4];
  void find_legal_moves(bool drop_low_scoring);
  void eval_board();
  int legal_moves = 0;
  int board_score = 0;
  void print_board();
  multimap<int, Board, greater <int>> branches;
};

Board::Board(uint8_t init_map[10][10], int  move[4], int score) {
  this->board_score = score;
  if (score > 0)
    { this-> multiplier = 2; }
  // init the map
  for (int i = 0; i < 10; i++) {
    for (int x = 0; x < 10; x++) {
      this->map[i][x] = init_map[i][x];
      this->map_copy[i][x] = init_map[i][x];
    }
  }
  for (int i = 0; i < 4; i++) {

    this->move[i] = move[i];
  }
}

void Board::regenerate_map() {
  // init the map
  for (int i = 0; i < 10; i++) {
    for (int x = 0; x < 10; x++) {
      map[i][x] = map_copy[i][x];
    }
  }
}

void Board::break_board() {
  // removes the stones in a board that are 0 and lets the other stones fall down
  // have temp_row be a structure that gets pushed back all the time maybe with
  // some zeros at the end
  bool need_change = false;
  deque <int> temp_row;
  for (int x = 0; x < 10; x++) {
    for (int y = 0; y < 10; y++) {

      if (map[y][x] != 0) {
        temp_row.push_back(map[y][x]);
      } else {
        temp_row.push_front(0);
        need_change= true; }
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
      if (counter > 2 && last !=0) {
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


bool Board::find_matches() {
  int score = 0;
  for (int i = 0; i < 10; i++) {
    // here the two functions could append to a container full of indices
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


void Board::eval_board() {
  break_board();
  while (find_matches()) {
    break_board();
    multiplier++;
  }
}

int Board::check_legal() {
  int score = 0;
  for (int i = 0; i < 10; i++) {
    // here the two functions could append to a container full of indices
    // which get set to zero in this function.
    // this could then also be used to pass it to the break function
    // and an optimized match finding function.

    score += find_matches_H(i);
    score += find_matches_V(i);
  }
  return score;
}

void Board::get_checking_indices(int * checking_indices, int * move) {
  // this function is used to get the subset of the matrix that needs to be checked for each move
  // it returns the starting indices for then checking a subset of the field in the following fashion
  // only the fields containing 1 or A or B are checked for matches
  // | 0 | 0 | 1 | 0 | 0 |
  // | 0 | 0 | 1 | 0 | 0 |
  // | 1 | 1 | A | 1 | 1 |
  // | 1 | 1 | B | 1 | 1 |
  // | 0 | 0 | 1 | 0 | 0 |
  // | 0 | 0 | 1 | 0 | 0 |

  if (move[0] > 2)
    { checking_indices[0] = move[0] - 2; }

  if (move[1] < 7)
    { checking_indices[1] = move[1] + 2; }

  if (move[2] > 2)
    { checking_indices[2] = move[2] - 2; }

  if (move[3] < 7)
    { checking_indices[3] = move[3] + 2; }
}

bool Board::switch_stones(int * move) {
  int temp1;
  int temp2;
  temp1 = map[move[2]][move[0]];
  temp2 = map[move[3]][move[1]];
  if (temp1 == 0 || temp2 == 0)
    { return false; }
  else {
  map[move[2]][move[0]] = temp2;
  map[move[3]][move[1]] = temp1;
  return true;
  }
}

void Board::drop_low_scores() {

  std::multimap<int, Board>::iterator firstit = branches.begin();
  advance(firstit, branches.size()/2);
  std::multimap<int, Board>::iterator lastit = branches.end();
  branches.erase(firstit,lastit);
}
void Board::find_legal_moves(bool drop_low_scoring) {
  int score;
  int move[4];

  for (int x = 0; x < 10; x++) {
    for (int y =0; y < 10; y++) {

      // test horizontal move

      if (x < 9) {

        move[0] = x;
        move[1] = x + 1;
        move[2] = y;
        move[3] = y;

        // switch stones according to move
        if (switch_stones(move))
          { score = check_legal(); }
        else
          { score = 0; }


        if (score > 0) {
          // instantiate move in data struct
          Board two(map,move,score);
          two.eval_board();

          if (two.board_score > 3 && drop_low_scoring)
            { branches.insert({two.board_score, two}); }
          else if (drop_low_scoring == false)
            { branches.insert({two.board_score, two}); }
          regenerate_map();

        } else {
        // switch stones back according to move
          switch_stones(move);
        }

      }

      // test vertical move

      if (y < 9) {
        move[0] = x;
        move[1] = x;
        move[2] = y;
        move[3] = y + 1;

        // switch stones according to move
        if (switch_stones(move))
          { score = check_legal(); }
        else
          { score = 0; }


        if (score > 0) {
          // instantiate move in data struct
          Board three(map,move,score);
          three.eval_board();
          if (three.board_score > 3 && drop_low_scoring)
            { branches.insert({three.board_score, three}); }
          else if (drop_low_scoring == false)
            { branches.insert({three.board_score, three}); }

          regenerate_map();

        } else {
        // switch stones back according to move
          switch_stones(move);
        }
      }
    }
  }
}
