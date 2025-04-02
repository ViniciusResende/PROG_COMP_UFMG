#include <iostream>
#include <queue>
#include <stack>
#include <type_traits>
 
using namespace std;

template<typename T>
typename enable_if<is_same<T, queue<typename T::value_type>>::value, bool>::type
verify(T* ds, int value) {
  int expected = ds->front();
  ds->pop();

  return expected == value;
}

template<typename T>
typename enable_if<is_same<T, stack<typename T::value_type>>::value || is_same<T, priority_queue<typename T::value_type>>::value, bool>::type
verify(T* ds, int value) {
  int expected = ds->top();
  ds->pop();

  return expected == value;
}

int main() {
  int entries = 0;
  while(cin >> entries) {
    queue<int> q;
    stack<int> s;
    priority_queue<int> pq;
    bool isQueue = true, isStack = true, isPriorityQ = true;
    int command, value;
    
    for(int i = 0; i < entries; i++) {
      cin >> command;
      cin >> value;

      if(command == 1) {
        q.push(value);
        s.push(value);
        pq.push(value);
      } else {
        if (isQueue) isQueue = verify(&q, value);
        if (isStack) isStack = verify(&s, value);
        if (isPriorityQ) isPriorityQ = verify(&pq, value);
      }
    }

    if(isQueue && !isStack && !isPriorityQ) {
      cout << "queue" << endl;
    } else if(!isQueue && isStack && !isPriorityQ) {
      cout << "stack" << endl;
    } else if(!isQueue && !isStack && isPriorityQ) {
      cout << "priority queue" << endl;
    } else if(!isQueue && !isStack && !isPriorityQ) {
      cout << "impossible" << endl;
    } else {
      cout << "not sure" << endl;
    }
  }

  return 0;
}