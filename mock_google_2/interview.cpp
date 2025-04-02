typedef heap<int, int, greater<int, int>> max_heap;
priority_queue<int, vector<int>, less<int>> 
vector<int> solution(const vector<int>& input, int k) {
	max_heap windowHeap;
for(int i = 0; i < k; i++){
		windowHeap.push(make_pair(input[i], i)); // O(k * log k)
}

vector<int> response;

int leftIt = 0, rightIt = k - 1;
while(rightIt < input.size()) { O(n)
	response.push_back(windowHeap.top()); O(1)
leftIt++;
while(windowHeap.top().second < leftIt) windowHeap.pop(); 1 ->O(logn)
	rightIt++;
if(rightIt >= input.size()) break;
windowHeap.push(make_pair(input[rightIt], rightIt));  // O(log n)
}

return response;
}