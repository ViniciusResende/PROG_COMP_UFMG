#include <iostream>
#include <vector>
#include <math.h>
 
using namespace std;

class DisjointSet {
  private:
    int *ranks, *parents, size;
  public:
    DisjointSet(int size) {
      this->ranks = (int*)malloc(sizeof(int)*size);
      this->parents = (int*)malloc(sizeof(int)*size);
      this->size = size;

      for(int i = 0; i < this->size; i++) this->parents[i] = i;
    }

    int find(int el) {
      if(this->parents[el] != el) {
        this->parents[el] = find(this->parents[el]);
      }

      return parents[el];
    }

    void elementUnion(int a, int b) {
      int aSet = this->find(a);
      int bSet = this->find(b);

      if(aSet == bSet) return;

      if(this->ranks[aSet] < this->ranks[bSet]) {
        this->parents[aSet] = bSet;
      } else if (this->ranks[aSet] > this->ranks[bSet]) {
        this->parents[bSet] = aSet;
      } else {
        this->parents[bSet] = aSet;
        this->ranks[aSet]++;
      }
    }
};

struct Point {
  int x = -1, y = -1;
};

float eucledianDistance(Point a, Point b) {
  return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

struct Sensor {
  Point coords;
  int radius;
};

int main() {
  int M, N, K;
  cin >> M >> N >> K;

  DisjointSet disjointSet(K + 4); // 4 = North wall, South wall, East wall and West wall
  std::vector<Sensor> sensors(K);
  for(int i = 0; i < K; i++) {
    Sensor s;
    cin >> s.coords.x;
    cin >> s.coords.y;
    cin >> s.radius;

    sensors[i] = s;

    for(int j = 0; j < K; j++) {
      if(i == j) continue;
      if(sensors[j].coords.x == -1) break;

      Sensor s2 = sensors[j];
      float dist = eucledianDistance(s.coords, s2.coords);
      if(dist <= s.radius + s2.radius) { // collision
        disjointSet.elementUnion(i + 4, j + 4);
      }
    }
  }

    for(int i = 0; i < K; i++) {
    Sensor s = sensors[i];
    if(s.coords.y + s.radius >= N) { // North collision
      disjointSet.elementUnion(0, i + 4);
    }
    if(s.coords.y - s.radius <= 0) { // South collision
      disjointSet.elementUnion(1, i + 4);
    }
    if(s.coords.x + s.radius >= M) { // East collision
      disjointSet.elementUnion(2, i + 4);
    }
    if(s.coords.x - s.radius <= 0) { // West collision
      disjointSet.elementUnion(3, i + 4);
    }
  }

  if(disjointSet.find(0) == disjointSet.find(1)) { // North <> South connected
    cout << "N" << endl;
  } else if(disjointSet.find(0) == disjointSet.find(2)) { // North <> East connected
    cout << "N" << endl;
  } else if(disjointSet.find(1) == disjointSet.find(3)) { // South <> West connected
    cout << "N" << endl;
  } else if(disjointSet.find(2) == disjointSet.find(3)) { // East <> West connected
    cout << "N" << endl;
  } else {
    cout << "S" << endl;
  }

  return 0;
}