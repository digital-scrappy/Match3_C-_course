#ifndef SRC_BOT_H_
#define SRC_BOT_H_
#include "Move.h"

class Bot {
private:
  int ownMap[10][10];
  int mapCopy[10][10];
  int map_side;

  // vector<Move> possibleMoves;
public:
  Bot();
  int *getNextMove(int map[], int nextMove[]);
  bool isLegalMove(int x1, int y1, int x2, int y2);
  bool isLegalH(int x1, int y1, int x2, int y2);
  bool isLegalV(int x1, int y1, int x2, int y2);
  void fillMap(int map[]);
  void findPossibleMoves(int bestMove[]);
  int calculateScore(int x1, int y1, int x2, int y2);
  int findSets();
  void findBestMove(int bestMove[]);
  void printMap();
  void printMapCopy();
};

Bot::Bot() // initialise Bot class - constructor
{}

void Bot::fillMap(int map[]) {
  for (int i = 0; i < 100; i++) {
    ownMap[i / 10][i % 10] = map[i];
  }
}

void Bot::calc_Score() {}

int Bot::calc_V_score(int column) {
  // vertical search
  // finds the matches in a specific column
  int counter = 1;
  int score = 0;
  int last = 11;
  for (int y = 0; x < 10; x++) {
    if (last == map[y][idx]) {
      counter++;
    }
    else {
      if (counter > 2) {
        score += counter;
      }
      last = map[y][idx];
      counter = 1;
    }
  }
  return score;
}


int Bot::calc_H_score(int row) {
  // horizontal search
  // finds the matches in a specific row
  int counter = 1;
  int score = 0;
  int last = 11;
  for (int x = 0; y < 10; y++) {
    if (last == map[idx][x]) {
      counter++;
    }
    else {
      if (counter > 2 && last != 0) {
        score += counter;
      }
      last = map[idx][x];
      counter = 1;
    }
  }
  return score;
}
int Bot::update_map(x1, x2, y1, y2) {
  int map_copy [10][10];
}



void Bot::get_affected_square(int changed[][]) {
  // since there cannot be breaks more than two blocks away from the the furthest break
  // in any direction it might make sense to only loop over that part of the matrix for calculating
  // further breaks
}

void Bot::find_legal_moves() {

  for (int x = 0; x < 10; x++) {
    for (int y =0; y < 10, y++) {
      // test horizontal move
      if (x < 10) {

        x1 = x;
        x2 = x++;
        y1 = y;
        y2 = y;
        if (check_legal_H_move(x1, x2, y1, y2)) {
          // instantiate move in data struct
        }
      }
      // test vertical move
      if (y < 10) {
        x1 = x;
        x2 = x;
        y1 = y;
        y2 = y++;
        if (check_legal_V_move(x1, x2, y1, y2)) {
            // instantiate move in data struct
        }
      }
    }
  }
}
void Bot:: get_checking_indices(int x1, int x2, int y1, int y2) {
  // this function is used to get the subset of the matrix that needs to be checked for each move
  // it returns the starting indices for then checking a subset of the field in the following fashion
  // only the fields containing 1 or A or B are checked for matches
  // | 0 | 0 | 1 | 0 | 0 |
  // | 0 | 0 | 1 | 0 | 0 |
  // | 1 | 1 | A | 1 | 1 |
  // | 1 | 1 | B | 1 | 1 |
  // | 0 | 0 | 1 | 0 | 0 |
  // | 0 | 0 | 1 | 0 | 0 |
  int x_start;
  int x_end;
  int y_start;
  int y_end;


  if (x1 > 2) {
    x_start = x1 - 2;
  }
  else {
    x_start = 0;
  }
  if (x2 < 7) {
    x_end = x2 + 2;
  }
  else {
    x_end = 9;
  }
  if (y1 > 2) {
    y_start = y1 - 2;
  }
  if (y2 < 7) {
    y_end = y2 + 2;
  }
  else {
    y_end = 9;
  }

  return x_start, x_end, y_start, y_end;
}

void Bot::check_legal_V_move() {
  // configuration for checking whether a Vertical move is legal
  // this is an adaptation of the more general calc_V_score function
  // since it is only required to check a subset of the matrix for the first break iteration
  // | 0 | 0 | 1 | 0 | 0 |
  // | 0 | 0 | 1 | 0 | 0 |
  // | 1 | 1 | A | 1 | 1 | h1
  // | 1 | 1 | B | 1 | 1 | h2
  // | 0 | 0 | 1 | 0 | 0 |
  // | 0 | 0 | 1 | 0 | 0 |
  //           v1
  int last_h1 = 0;
  int counter_h1 = 1;
  int last_h2 = 0;
  int counter_h2 = 0;
  int score = 0;

  // horizontal checks
  for (int x = x_start, x < x_end, x++) {
    // h1
    if (last_h1 == map[y1][x]) {
      counter_h1++;
    }
    else {
      if (counter_h1 > 2 && last_h1 != 0) {
        score += counter_h1;
      }
      last_h1 = map[y1][x];
      counter_h1 = 1;
    }
    // h2
    if (last_h2 == map[y2][x]) {
      counter_h2++;
    }
    else {
      if (counter_h2 > 2 && last_h2 != 0) {
        score += counter_h2;
      }
      last_h2 = map[y2][x];
      counter_h2 = 1;
    }
  }

  // vertical check
  // reset needed variables
  last_h1 = 0;
  counter_h1 = 1;

  for (int y = y_start, y < y_end, y++) {
    // is the last visited stone the same as this one?

    if (last_h1 == map[y1][x]) {
      // yes then up counter by 1
      counter_h1++;
    }
    else {
      // no then check if counter >= 3
      if (counter_h1 > 2 && last_h1 != 0) {
        // if yes then add the score to the global score
        score += counter_h1;
      }
      // reset counter and last stone
      last_h1 = map[y1][x];
      counter_h1 = 1;
    }

        }
  }

}

void Bot::check_legal_H_move() {
 // configuration for checking whether a Horizontal move is legal
  // this is an adaptation of the more general calc_H_score function
  // since it is only required to check a subset of the matrix for the first break iteration
  // | 0 | 0 | 1 | 1 | 0 | 0 |
  // | 0 | 0 | 1 | 1 | 0 | 0 |
  // | 1 | 1 | A | B | 1 | 1 | h1
  // | 0 | 0 | 1 | 1 | 0 | 0 |
  // | 0 | 0 | 1 | 1 | 0 | 0 |
  //           v1  v2
  int last_v1 = 0;
  int counter_v1 = 1;
  int last_v2 = 0;
  int counter_v2 = 0;

  // vertical checks
  for (int y = y_start, y < y_end, x++) {
    // v1
    if (last_v1 == map[y][x1]) {
      counter_v1++;
    }
    else {
      if (counter_v1 > 2 && last_v1 != 0) {
        score += counter_h1;
      }
      last_v1 = map[y][x1];
      counter_v1 = 1;
    }
    // v2
    if (last_v2 == map[y][x2]) {
      counter_v2++;
    }
    else {
      if (counter_v2 > 2 && last_v2 != 0)2 {
        score += counter_v2;
      }
      last_v2 = map[y][x2];
      counter_v2 = 1;
    }
  }
  // vertical check
  counter_v1 = 1;
  last_v1 = 0;
  for (int x = x_start, x < x_end, x++) {
    if (last_v1 == map[y1][x]) {
      counter_v1++;
    }
    else {
      if (counter_v1 > 2 && last_v1 != 0) {
        score += counter_v1;
      }
      last_h1 = map[y1][x];
      counter_h1 = 1;
    }

  }
}

int Bot::find_matches(int idx, bool row_col) {
  // finds the matches in a specific row
  // if row_col is true it will run it over a row
  // otherwise it will be run over a column

  int counter = 0;
  int row_count = 0;
  int last = 11;

  if (row_col) {
    for (int x = 0; x < 10; x++) {
      if (last == map[x][idx]) {
        counter++;
          }
      else {
        if (counter > 2) {
          row_count += counter;
        }
        last = map[x][idx];
        }
    }
  }

  else {
    for (int y = 0; y < 10; y++) {
      current = map[idx][y];
      if (last == current) {
        counter++;
          }
      else {
        if (counter > 2) {
          row_count += counter;
        }
        last = current;
        }
    }
  }
  return row_count;
}


    void Bot::findPossibleMoves(int bestMove[]) {
      possibleMoves.clear();
      for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
          if (x != 9 && isLegalMove(x, y, x + 1, y)) {
            int score = calculateScore(x, y, x + 1, y);
            Move m(x, y, x + 1, y, score);
            possibleMoves.push_back(m);
          }
          if (y != 9 && isLegalMove(x, y, x, y + 1)) {
            int score = calculateScore(x, y, x, y + 1);
            Move m(x, y, x, y + 1, score);
            possibleMoves.push_back(m);
          }
        }
      }

      findBestMove(bestMove);
    }

    void Bot::findBestMove(int bestMove[]) {
      int max = 0;
      for (int i = 0; i < possibleMoves.size(); i++) {
        if (possibleMoves[i].getScore() > max) {
          possibleMoves[i].getCoordinates(bestMove);
          max = possibleMoves[i].getScore();
        }
      }
      cout << "best move is: " << bestMove[0] << bestMove[1] << bestMove[2]
           << bestMove[3] << " with a score of " << max << endl;
    }

    int Bot::calculateScore(int x1, int y1, int x2, int y2) {
      for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
          mapCopy[x][y] = ownMap[x][y];
        }
      }
      swap(mapCopy[x1][y1], mapCopy[x2][y2]);
      int score = findSets();
      return score;
    }

    int Bot::findSets() {
      int totalScore = 0;
      for (int x = 0; x < 10; x++) {
        int tempScore = 1;
        for (int y = 0; y < 10; y++) {
          if (y > 0 && mapCopy[x][y] == mapCopy[x][y - 1] &&
              mapCopy[x][y] != 0) {
            tempScore++;

          } else if (y > 0 && mapCopy[x][y] != mapCopy[x][y - 1] &&
                     tempScore > 2) {
            totalScore += tempScore;
            tempScore = 1;
          } else {
            tempScore = 1;
          }
        }
        if (tempScore > 2) {
          totalScore += tempScore;
        }
      }

      for (int y = 0; y < 10; y++) {
        int tempScore = 1;
        for (int x = 0; x < 10; x++) {
          if (x > 0 && mapCopy[x][y] == mapCopy[x - 1][y] &&
              mapCopy[x][y] != 0) {
            tempScore++;
          } else if (y > 0 && mapCopy[x][y] != mapCopy[x - 1][y] &&
                     tempScore > 2) {
            totalScore += tempScore;
            tempScore = 1;
          } else {
            tempScore = 1;
          }
        }
        if (tempScore > 2) {
          totalScore += tempScore;
        }
      }

      return totalScore;
    }

    bool Bot::isLegalMove(int x1, int y1, int x2, int y2) {
      if ((isLegalH(x1, y1, x2, y2) || isLegalV(x1, y1, x2, y2)) &&
          ownMap[x1][y1] != 0 && ownMap[x2][y2] != 0) {
        return true;
      }
      return false;
    }

    bool Bot::isLegalH(int x1, int y1, int x2, int y2) {
      if ((y2 >= y1 && y1 > 1 && ownMap[x2][y2] == ownMap[x1][y1 - 1] &&
           ownMap[x2][y2] == ownMap[x1][y1 - 2]) ||
          (y1 >= y2 && y2 > 1 && ownMap[x1][y1] == ownMap[x2][y2 - 1] &&
           ownMap[x1][y1] == ownMap[x2][y2 - 2]) ||
          (y2 >= y1 && y2 < 8 && ownMap[x1][y1] == ownMap[x2][y2 + 1] &&
           ownMap[x1][y1] == ownMap[x2][y2 + 2]) ||
          (y1 >= y2 && y1 < 8 && ownMap[x2][y2] == ownMap[x1][y1 + 1] &&
           ownMap[x2][y2] == ownMap[x1][y1 + 2]) ||
          (x1 != x2 && y1 > 0 && y1 < 9 &&
           ownMap[x2][y2] == ownMap[x1][y1 + 1] &&
           ownMap[x2][y2] == ownMap[x1][y1 - 1]) ||
          (x1 != x2 && y2 > 0 && y2 < 9 &&
           ownMap[x1][y1] == ownMap[x2][y2 + 1] &&
           ownMap[x1][y1] == ownMap[x2][y2 - 1])) {
        return true;
      } else {
        return false;
      }
    }

    bool Bot::isLegalV(int x1, int y1, int x2, int y2) {
      if ((x1 >= x2 && x1 > 1 && ownMap[x2][y2] == ownMap[x1 - 2][y1] &&
           ownMap[x2][y2] == ownMap[x1 - 1][y1]) ||
          (x2 >= x1 && x2 > 1 && ownMap[x1][y1] == ownMap[x2 - 2][y2] &&
           ownMap[x1][y1] == ownMap[x2 - 1][y2]) ||
          (x1 >= x2 && x1 < 8 && ownMap[x2][y2] == ownMap[x1 + 2][y1] &&
           ownMap[x2][y2] == ownMap[x1 + 1][y1]) ||
          (x2 >= x1 && x2 < 8 && ownMap[x1][y1] == ownMap[x2 + 2][y2] &&
           ownMap[x1][y1] == ownMap[x2 + 1][y2]) ||
          (y1 != y2 && x1 > 0 && x1 < 9 &&
           ownMap[x2][y2] == ownMap[x1 - 1][y1] &&
           ownMap[x2][y2] == ownMap[x1 + 1][y1]) ||
          (y1 != y2 && x2 > 0 && x2 < 9 &&
           ownMap[x1][y1] == ownMap[x2 - 1][y2] &&
           ownMap[x1][y1] == ownMap[x2 + 1][y2])) {
        return true;
      } else {
        return false;
      }
    }

    int *Bot::getNextMove(int map[],
                          int nextMove[]) // decide and return next move, given
                                          // the current state of the map.
    {
      int bestMove[4];
      fillMap(map);
      findPossibleMoves(bestMove);

      int tempx1 = bestMove[0];
      int tempy1 = bestMove[1];
      int tempx2 = bestMove[2];
      int tempy2 = bestMove[3];
      nextMove[0] = tempx1;
      nextMove[1] = tempy1;
      nextMove[2] = tempx2;
      nextMove[3] = tempy2;
      return nextMove;
    }
    void Bot::printMap() {

      for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
          if (j != 9) {
            cout << ownMap[i][j] << " ";
          } else {
            cout << ownMap[i][j];
          }
        }
        cout << endl;
      }
      cout << endl;
    }

    void Bot::printMapCopy() {

      for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
          if (j != 9) {
            cout << mapCopy[i][j] << " ";
          } else {
            cout << mapCopy[i][j];
          }
        }
        cout << endl;
      }
      cout << endl;
    }

#endif /* SRC_BOT_H_ */
