#ifndef BOARD_H_
#define BOARD_H_
#include <multimap>

using namespace std;

int map[10][10]= {
  {1,1,2,3,3,2,4,4,1,1},
  {2,2,3,4,1,3,3,4,1,2},
  {1,2,2,4,3,3,4,1,2,1},
  {3,4,2,1,3,2,3,2,3,2},
  {1,1,3,3,1,4,2,4,1,1},
  {1,1,2,1,1,1,4,2,3,1},
  {2,2,3,4,1,3,3,4,1,2},
  {1,2,2,4,3,3,4,1,2,1},
  {3,4,2,1,1,2,3,2,3,2},
  {1,1,3,3,4,3,2,4,1,1},
};


class Board{
private:
  int score;
  int map[10][10];
  int board_score;
  void board_eval;
  void find_matches_V;
  void find_matches_H;
  void break_tiles;
  multimap <int, Board> branches;



public:
  Board(int map[10][10]);
  void print_board;
};


Board::Board(int map[10][10]) {
  this->map = map;
}

void Board::find_matches_H(int row) {
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
        start = x - counter +1;
        end = x + 1;
        //replace scoring tiles with 0
        for( int i = start; i < end; i++)
          { map[row][i] = 0; }
      }
      last = map[row][x];
      counter = 1;
    }
  }

  board_score+=score;

}
void Board::find_matches_V(int column) {
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
      if (counter > 2) {
        score += counter;
        start = y - counter +1;
        end = y + 1;
        //replace scoring tiles with 0
        for( int i = start; i < end; i++)
          { map[i][column] = 0; }

      } else {
      counter = 1;
      }
    }
    last = map[y][column];
  }

  board_score+=score;

}


void print_map() {
  int color_code = 0;
  string out_str;

    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 10; j++) {

        color_code = to_string( 40 + map[i][j]);
        cout <<"\033[1;" << color_code <<"m" << to_string(map[i][j]) <<  " \033[0m";
      }
    cout << endl;
    }
}
