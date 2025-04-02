//#include <bits/stdc++.h>

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
#include <deque>
#include <bitset>
#include <iterator>
#include <list>
#include <stack>
#include <map>
#include <set>
#include <functional>
#include <numeric>
#include <utility>
#include <limits>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define f first
#define s second
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3fLL

typedef long long ll;
typedef pair<int, int> ii;


int main(){ _
  string mensagem;
	cin >> mensagem;

	stack<char> pilha;
	bool upperFound = false;

	for (char c : mensagem) {
			if(isupper(c)) upperFound = true;
			if (!pilha.empty() && islower(pilha.top()) && isupper(c)) {
					// Se a pilha não estiver vazia e a letra atual for maiúscula e a letra no topo da pilha for minúscula
					pilha.pop(); // Podemos converter ambas para a mesma letra
			} else {
					pilha.push(c); // Caso contrário, adicionamos a letra à pilha
			}
	}

	cout << (upperFound ? pilha.size() : 0) << endl;

	exit(0);
}
