#include <iostream>

using namespace std;


struct Node {
	int starters;
	int enders;
	Node* left;
	Node* right;
	Node() {
		left = NULL;
		right = NULL;
		starters = 0;
		enders = 0;
	}
};

void up(Node* &root, int left, int right, int index, bool isStart) {
	if (root == NULL) {
		root = new Node();
	}
	if (isStart) {
		root->starters++;
	}
	else {
		root->enders++;
	}

	if (right - left == 1) return;

	if (index < (left + right) / 2) {
		up(root->left, left, (left + right) / 2, index, isStart);
	}
	else {
		up(root->right, (left + right) / 2, right, index, isStart);
	}
}

int answer(Node* &root, int left, int right, int startIndex, int endIndex, bool isStart) {
	if (root == NULL) return 0;

	if (left >= startIndex && right - 1 <= endIndex) {
		if (isStart) {
			return root->starters;
		}
		else {
			return root->enders;
		}
	}

	if (left > endIndex || right <= startIndex) return 0;

	return answer(root->left, left, (left + right) / 2, startIndex, endIndex, isStart)
		+ answer(root->right, (left + right) / 2, right, startIndex, endIndex, isStart);
}

int main() {
	int N;
	cin >> N;
	Node* root = NULL;
	int lastIndex = 100001;
	int array[100001];

	for (int i = 0; i < lastIndex + 1; i++) {
		array[i] = 0;
	}

	for (int i = 0; i < N; i++) {
		int L, R;
		cin >> L >> R;
		L--;
		R--;

		int lS = answer(root, 0, lastIndex, 0, L - 1, true);
		int lE = answer(root, 0, lastIndex, 0, L, false);
		int leftResult = lS - lE - array[L];
		array[L] += leftResult;

		int rE = answer(root, 0, lastIndex, R + 1, lastIndex, false);
		int rS = answer(root, 0, lastIndex, R, lastIndex, true);
		int rightResult = rE - rS - array[R];
		array[R] += rightResult;

		int finalResult = leftResult + rightResult;
		cout << finalResult << endl;


		up(root, 0, lastIndex, L, true);
		up(root, 0, lastIndex, R, false);
	}

	return 0;
}