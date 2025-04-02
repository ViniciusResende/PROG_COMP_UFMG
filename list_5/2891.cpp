#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// Função para calcular a área usando a fórmula de Shoelace
double shoelaceArea(const vector<pair<int, int>>& points) {
  int n = points.size();
  double area = 0;
  for (int i = 0; i < n; i++) {
    int j = (i + 1) % n;
    area += points[i].first * points[j].second;
    area -= points[j].first * points[i].second;
  }

  return fabs(area) / 2.0;
}

// Função para ordenar os pontos em ordem anti-horária
vector<pair<int, int>> sortPointsCounterClockwise(vector<pair<int, int>> points) {
  int n = points.size();
  pair<int, int> centroid = {0, 0};
  for (int i = 0; i < n; i++) {
    centroid.first += points[i].first;
    centroid.second += points[i].second;
  }
  centroid.first /= n;
  centroid.second /= n;

  sort(points.begin(), points.end(), [centroid](pair<int, int> a, pair<int, int> b) {
    double angleA = atan2(a.second - centroid.second, a.first - centroid.first);
    double angleB = atan2(b.second - centroid.second, b.first - centroid.first);
    return angleA < angleB;
  });

  return points;
}

// Função para verificar se um quadrilátero é convexo
bool isConvexQuadrilateral(const vector<pair<int, int>>& points) {
  int n = points.size();
  bool ret = true;
  for (int i = 0; i < n; i++) {
    int j = (i + 1) % n;
    int k = (i + 2) % n;
    int crossProduct = (points[j].first - points[i].first) * (points[k].second - points[j].second) -
                       (points[j].second - points[i].second) * (points[k].first - points[j].first);
                       
    if (crossProduct < 0) {
      ret = false;
      break;
    }
  }

  return ret;
}

int main() {
  while (true) {
    vector<pair<int, int>> points(5);
    for (int i = 0; i < 5; i++) {
      cin >> points[i].first >> points[i].second;
    }

    // Verifica se todos os 10 valores são 0
    if (all_of(points.begin(), points.end(), [](pair<int, int> p) { return p.first == 0 && p.second == 0; })) {
      break;
    }

    double maxArea = 0;
    // Combinação de 4 pontos dos 5 disponíveis
    for (int i = 0; i < 5; i++) {
      vector<pair<int, int>> quadrilateral;
      for (int j = 0; j < 5; j++) {
        if (i != j) {
          quadrilateral.push_back(points[j]);
        }
      }
      quadrilateral = sortPointsCounterClockwise(quadrilateral);
      if (isConvexQuadrilateral(quadrilateral)) {
        maxArea = max(maxArea, shoelaceArea(quadrilateral));
      }
    }

    cout << static_cast<int>(round(maxArea)) << endl;
  }

  return 0;
}
