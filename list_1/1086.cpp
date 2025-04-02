#include <iostream>

using namespace std;

#define MAX_PLANKS 10010
#define INF 0x3f3f3f3f
#define min(a,b) ((a)<(b)?(a):(b))

int planksH[MAX_PLANKS], planksV[MAX_PLANKS];

int fillFloor(int planks[], int rows, int columns, int plankWidth) {
  int planksNeeded = 0, coveredWidth = 0, neededWidth = (columns * 100);
  while ((planks[rows] > 0) && (coveredWidth < neededWidth)) {
    coveredWidth += plankWidth;
    planksNeeded++;
    planks[rows]--;
  }

  int lowIt = 1, highIt = rows - 1;
  while(lowIt < highIt){
    while((planks[lowIt] > 0) && (planks[highIt] > 0) && (coveredWidth < neededWidth)) {
      coveredWidth += plankWidth;
      planks[lowIt]--;
      planksNeeded++;
      planks[highIt]--;
      planksNeeded++;
    }
    lowIt++;
    highIt--;
  }

  if(lowIt == highIt && coveredWidth < neededWidth) {
    while((planks[lowIt] > 1) && (coveredWidth < neededWidth)) {
      coveredWidth += plankWidth;
      planks[lowIt] -= 2;
      planksNeeded += 2;
    }
  }

  return coveredWidth == neededWidth ? planksNeeded : INF;
}

int main() {
  int N, M;
  while (cin >> M) {
    cin >> N;

    if(N == 0 && M == 0) return 0;

    int width;
    cin >> width;

    int planksAmount = 0;
    cin >> planksAmount;

    for(int i = 0; i < MAX_PLANKS; i++) planksH[i] = planksV[i] = 0;

    for(int i = 0; i < planksAmount; i++) {
      int plankLength = 0;
      cin >> plankLength;

      planksH[plankLength]++;
      planksV[plankLength]++;
    }
    
    if(((N*100) % width != 0) && ((M*100) % width != 0)) {
      cout << "impossivel" << endl;
      continue;
    }

    int planksNeededH = 0;
    planksNeededH = fillFloor(planksH, N, M, width);
    int planksNeededV = 0;
    planksNeededV = fillFloor(planksV, M, N, width);

    int minimumPlanksNeeded = min(planksNeededH, planksNeededV);
    if(minimumPlanksNeeded <= planksAmount) cout << minimumPlanksNeeded << endl;
    else cout << "impossivel" << endl;
  }
  return 0;
}