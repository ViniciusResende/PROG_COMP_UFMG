#include <iostream>
#include <vector>

using namespace std;

#define MAX 100000

int numPlants, workDays, lifeDays;

bool isPlantDead(int day, int lastDayOfPlantCare) {
  return day - lastDayOfPlantCare > lifeDays;
}

void updatePlantsCare(vector<int> &lastDayOfPlantsCare, int left, int right, int day) {
  for (int i = left; i <= right; ++i) {
    if (!isPlantDead(day, lastDayOfPlantsCare[i])) {
      lastDayOfPlantsCare[i] = day;
    }
  }
}

int main() {
  while (cin >> numPlants >> workDays >> lifeDays) {
    vector<int> lastDayOfPlantsCare(numPlants, 0);

    for (int i = 1; i <= workDays; ++i) {
      int left, right;
      cin >> left >> right;
      left--;
      right--;

      updatePlantsCare(lastDayOfPlantsCare, left, right, i);
    }

    int numLivingPlants = 0;
    vector<int> livingPlants;
    for (int i = 0; i < numPlants; ++i) {
      if (!isPlantDead(workDays+1, lastDayOfPlantsCare[i])) {
        numLivingPlants++;
        livingPlants.push_back(i);
      }
    }

    cout << numLivingPlants;
    if(numLivingPlants > 0) cout << " ";
    for (int i = 0; i < numLivingPlants; ++i) {
      cout << livingPlants[i] + 1;
      if(i < numLivingPlants - 1) cout << " ";
    }
    cout << endl;
  }
  return 0;
}

