#include <algorithm>
#include <cmath>
#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

struct Point {
  int x;
  int y;
};


double getEuclideanDistance(Point p1, Point p2) {
  double xDiff = pow(p1.x - p2.x, 2.0);
  double yDiff = pow(p1.y - p2.y, 2.0);
  return sqrt(xDiff + yDiff);
}

int main() {
  int pointsAmount;
  while (cin >> pointsAmount && pointsAmount != 0) {
    int x, y;
    vector<Point> points;
    for (int i = 0; i < pointsAmount; i++) {
      cin >> x >> y;
      points.push_back({x, y});
    }

    double distances[pointsAmount + 1][pointsAmount + 1];
    memset(distances, 0, (pointsAmount + 1) * (pointsAmount + 1) * sizeof(double));
    double dist;
    int count = 0;
    for (int i = 0; i < pointsAmount; i++) {
      for (int j = 0; j < pointsAmount; j++) {
        if (distances[i][j] == 0) {
          dist = getEuclideanDistance(points[i], points[j]);
          distances[i][j] = dist;
          distances[j][i] = dist;
        }
      }

      sort(distances[i], distances[i] + pointsAmount);
      int equallyDistant = 1;
      dist = distances[i][0];
      for (int j = 1; j < pointsAmount; j++) {
        if (distances[i][j] != dist) {
          count += equallyDistant * (equallyDistant - 1) / 2; // combination of points
          dist = distances[i][j];
          equallyDistant = 0;
        }
        equallyDistant++;
      }
      
      // In case the last point in the for loop has same distance
      if (equallyDistant > 1) {
        count += equallyDistant * (equallyDistant - 1) / 2;
      }
    }

    cout << count << endl;
  }

  return 0;
}