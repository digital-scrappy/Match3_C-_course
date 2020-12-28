#include <iostream>
#include <string>

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
int map_copy[10][10]= {
  {1,1,2,3,3,2,4,4,1,1},
  {2,2,3,4,1,3,3,4,1,2},
  {1,2,2,4,3,3,4,1,2,1},
  {3,4,2,1,1,2,3,2,3,2},
  {1,1,3,3,4,3,2,4,1,1},
  {1,1,2,3,3,2,4,2,3,1},
  {2,2,3,4,1,3,3,4,1,2},
  {1,2,2,4,3,3,4,1,2,1},
  {3,4,2,1,1,2,3,2,3,2},
  {1,1,3,3,4,3,2,4,1,1},
};

int future_map[10][10]= {
  {1,1,2,3,3,2,4,4,1,1},
  {2,2,3,4,1,3,3,4,1,2},
  {1,2,2,4,3,3,4,1,2,1},
  {3,4,2,1,1,2,3,2,3,2},
  {1,1,3,3,4,3,2,4,1,1},
  {1,1,2,3,3,2,4,4,1,1},
  {2,2,3,4,1,3,3,4,1,2},
  {1,2,2,4,3,3,4,1,2,1},
  {3,4,2,1,1,2,3,2,3,2},
  {1,1,3,3,4,3,2,4,1,1},
};

// void board_eval() {
//   score += find_matches();
//   break_stone();





// int find_matches_V(int column) {
//   // vertical search
//   // finds the matches in a specific column
//   int counter = 1;
//   int score = 0;
//   int last = 11;
//   for (int y = 0; y < 10; y++) {
//     if (last == map[y][column]) {
//       counter++;
//    } else {
//       if (counter > 2) {
//         score += counter;

//       } else {
//       counter = 1;
//       }
//     }
//     last = map[y][column];
//   }
//   return score;
// }


// int find_matches_H(int row) {
//   // horizontal search
//   // finds the matches in a specific row

//   int counter = 1;
//   int score = 0;
//   int last = 11;

//   for (int x = 0; x < 10; x++) {
//     if (last == map[row][x]) {
//       counter++;
//     } else {
//       if (counter > 2 && last != 0) {
//         score += counter;
//       }
//       last = map[row][x];
//       counter = 1;
//     }
//   }

//   return score;
// }

// int check_map() {
//   int score = 0;
//   for (int i =0; i < 10; i++) {
//     score += find_matches_H(i);
//     score += find_matches_V(1);
//   }
//   return score;
// }



void print_map() {
  int color_code = 0;
  string out_str;

    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 10; j++) {


        cout <<"\033[1;" << to_string( 40 + map[i][j]) <<"m" << to_string(map[i][j]) <<  " \033[0m";
      }
    cout << endl;
    }
}

void print_line(int index) {

  for (int j = 0; j < 10; j++) {


    cout <<"\033[1;" << to_string( 40 + map[index][j]) <<"m" << to_string(map[index][j]) <<  " \033[0m";
  }
  cout << endl;
}

// void find_legal_moves() {
//   int x1;
//   int x2;
//   int y1;
//   int y2;
//   int tile_1;
//   int tile_2;
//   int count = 0;

//   for (int x = 0; x < 10; x++) {
//     for (int y =0; y < 10; y++) {
//       // test horizontal move

//       if (x < 9) {

//         x1 = x;
//         x2 = x+1;
//         y1 = y;
//         y2 = y;

//         tile_1= map[y1][x1];
//         tile_2= map[y2][x2];
//         map[y1][x1]= tile_2;
//         map[y2][x2]= tile_1;
//         cout << check_map() << endl;
//         print_map();
//         count++;
//         map[y1][x1]= tile_1;
//         map[y2][x2]= tile_2;
//         }
//       // test vertical move

//       if (y < 9) {
//         x1 = x;
//         x2 = x;
//         y1 = y;
//         y2 = y+1;

//         tile_1= map[y1][x1];
//         tile_2= map[y2][x2];
//         map[y1][x1]= tile_2;
//         map[y2][x2]= tile_1;
//         cout << check_map() << endl;
//         print_map();
//         count++;
//         map[y1][x1]= tile_1;
//         map[y2][x2]= tile_2;
//         }
//       }
//     }
//   cout << count << endl;
// }


// get_affected_square(int changed[][]) {
//   // since there cannot be breaks more than two blocks away from the the furthest break
//   // in any direction it might make sense to only loop over that part of the matrix for calculating
//   // further breaks
// }

int main() {
  print_map();
}
