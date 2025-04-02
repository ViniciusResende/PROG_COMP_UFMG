#include <iostream>
#include <utility>
#include <vector>

#define EMPTY_CELL -1

using namespace std;

typedef pair<int, int> iPair;

int rows = -1, columns = -1;

bool isCoordinateValid(int y, int x) { return ((x >= 0 && x < columns) && (y >= 0 && y < rows));}

int eatablePieces(vector<vector<char>> &checkersBoard, vector<vector<bool>> &visitedBoard, int x, int y) {
  int maxVal = 0;
  if(isCoordinateValid(y - 2, x - 2)) { // bottom left
    if(checkersBoard[y - 1][x - 1] == 2) // opponent's piece in the middle
      if(checkersBoard[y - 2][x - 2] == 0) // other edge of diagonal is empty
        if(!visitedBoard[y - 1][x - 1]) { // coordinated not visited yet
          checkersBoard[y][x] = 0; checkersBoard[y - 2][x - 2] = 1; visitedBoard[y - 1][x - 1] = true; // make move
          maxVal = max(maxVal, eatablePieces(checkersBoard, visitedBoard, x - 2, y - 2) + 1);
          checkersBoard[y][x] = 1; checkersBoard[y - 2][x - 2] = 0; visitedBoard[y - 1][x - 1] = false; // clean up move
        }    
  }
  if(isCoordinateValid(y + 2, x - 2)) { // top left
    if(checkersBoard[y + 1][x - 1] == 2) 
      if(checkersBoard[y + 2][x - 2] == 0)
        if(!visitedBoard[y + 1][x - 1]){
          checkersBoard[y][x] = 0; checkersBoard[y + 2][x - 2] = 1;visitedBoard[y + 1][x - 1] = true;
          maxVal = max(maxVal, eatablePieces(checkersBoard, visitedBoard, x - 2, y + 2) + 1);        
          checkersBoard[y][x] = 1; checkersBoard[y + 2][x - 2] = 0; visitedBoard[y + 1][x - 1] = false;
        }
  }
  if(isCoordinateValid(y - 2, x + 2)) { // bottom right
    if(checkersBoard[y - 1][x + 1] == 2) 
      if(checkersBoard[y - 2][x + 2] == 0)
        if(!visitedBoard[y - 1][x + 1]) {
          checkersBoard[y][x] = 0; checkersBoard[y - 2][x + 2] = 1; visitedBoard[y - 1][x + 1] = true;
          maxVal = max(maxVal, eatablePieces(checkersBoard, visitedBoard, x + 2, y - 2) + 1);
          checkersBoard[y][x] = 1; checkersBoard[y - 2][x + 2] = 0; visitedBoard[y - 1][x + 1] = false;
        }
  }
  if(isCoordinateValid(y + 2, x + 2)) { // top right
    if(checkersBoard[y + 1][x + 1] == 2) {
      if(checkersBoard[y + 2][x + 2] == 0)
        if(!visitedBoard[y + 1][x + 1]) {
        checkersBoard[y][x] = 0; checkersBoard[y + 2][x + 2] = 1; visitedBoard[y + 1][x + 1] = true;
        maxVal = max(maxVal, eatablePieces(checkersBoard, visitedBoard, x + 2, y + 2) + 1);
        checkersBoard[y][x] = 1; checkersBoard[y + 2][x + 2] = 0; visitedBoard[y + 1][x + 1] = false;
        }
    }
  }

  return maxVal;
}

int main() {
  cin >> rows;
  cin >> columns;
  while (rows && columns) {
    vector<vector<bool>> visitedBoard(rows, vector<bool>(columns, false));
    vector<vector<char>> checkersBoard(rows, vector<char>(columns, EMPTY_CELL));
    vector<iPair> playerPieces;

    int totalBoardPlaces = ((rows * columns) + 1) / 2;
    int y = 0, x = 0, currPiece = EMPTY_CELL;
    for (int i = 0; i < totalBoardPlaces; i++) {
      cin >> currPiece;
      if (currPiece == 1) playerPieces.push_back(make_pair(y, x));
      
      checkersBoard[y][x] = currPiece;

      x++;
      if (x >= columns - 1) {
        x = checkersBoard[y][0] == -1 ? 0 : 1; // alternate if first column is black or white
        y++;
      } else x++;
    }

    int answer = 0;
    for (int i = playerPieces.size() - 1; i >= 0; i--) {
      y = playerPieces[i].first;
      x = playerPieces[i].second;

      answer = max(answer, eatablePieces(checkersBoard, visitedBoard, x, y));
    }

    cout << answer << endl;

    cin >> rows;
    cin >> columns;
  }

  return 0;
}