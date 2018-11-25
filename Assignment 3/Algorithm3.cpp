#include <bits/stdc++.h>

using namespace std;

int n;
vector < int > G[300020];
int answer[300020];

void go(int v, int p, int x) {
	int tot = 0;
	for (int i = 0; i < G[v].size(); ++i) {
		if (G[v][i] == p)
			continue;
		go(G[v][i], v, x);
		tot += answer[G[v][i]] + 1;
	}
	answer[v] = max(0, tot - x);
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i < n; ++i) {
		int x, y;
		scanf("%d %d", &x, &y);
		G[x].push_back(y);
		G[y].push_back(x);
	}
	int l = 0;
	int r = n;
	while (l < r) {
		int mid = (l + r) / 2;
		go(1, 0, mid);
		if (answer[1])
			l = mid + 1;
		else
			r = mid;
	}
	printf("%d", l);
}