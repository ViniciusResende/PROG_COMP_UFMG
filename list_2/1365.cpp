#include <iostream>
#include <algorithm>

#define INF 0x3f3f3f3f
#define USED_SEAT 'X'
#define DIMENSION_THRESHOLD 301

using namespace std;

int subConfig[DIMENSION_THRESHOLD][DIMENSION_THRESHOLD][DIMENSION_THRESHOLD];
char roomConfig[DIMENSION_THRESHOLD][DIMENSION_THRESHOLD];

int main() {
  while(1) {
    int R, C, K;
    cin >> R >> C >> K;
    if(R == 0 && C == 0 && K == 0) break;

    for(int i = 0; i < R; i++) cin >> roomConfig[i];

    // initialize possible sub configs depending on the number of used seats
    for (int row = R - 1; row >= 0; row--) {
      for (int seat = C - 1; seat >= 0; seat--) {
        for (int usedSeats = 1; usedSeats <= C - seat; usedSeats++) {
          int isAvailable = roomConfig[row][seat] == USED_SEAT ? 0 : 1;
          if (usedSeats > 1)
            subConfig[row][seat][usedSeats] = subConfig[row][seat + 1][usedSeats - 1] + isAvailable;
          else subConfig[row][seat][usedSeats] = isAvailable;
        }
      }
    }

    int rectHeight, neededArea = INF;
    for(int currSeat = 0; currSeat < C; currSeat++) {
      for(int size = 1; size <= C - currSeat; size++) {
        int availableSeats = 0;
        int rectBegin = 0;
        for(int row = 0; row < R; row++) {
          availableSeats += subConfig[row][currSeat][size];
          while(availableSeats >= K) {
            availableSeats -= subConfig[rectBegin][currSeat][size];

            rectHeight = row - rectBegin + 1;
            int currArea = size * rectHeight;
            neededArea = min(currArea, neededArea);
            
            rectBegin++;
          }
        }
      }
    }

    cout << neededArea << endl;
  }
}