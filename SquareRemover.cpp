#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#define NUM_MOVES 10000
#define RETMOVESIZE 30000
#define MAXNP1 17
#define MAXN 16
#define MAXSQR 15
#define MAX_SQUARES 225 //we have at most (N-1)^2 squares
#define MAXBUFSIZE 1000
using namespace std;
int colors, startSeed,n;
vector<string>board;
int idx;
int *buf,bufcnt;
void make_buf(int seed) {
	buf[0] = seed;
	for (int i = 1; i < 45000; ++i)
		buf[i] = (buf[i - 1] * 48271) % 2147483647;
}
//------------------------------------------------------------------------
struct change_tile {
	int pos[2];
	char dir=4;
	pair<int,int>left_num;
};
void replace(int row, int col) {
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			board[row + i][col + j] = buf[idx++];
}
int is_changable(int i,int j,int dir) {
	switch (dir) {
	case 0:
		if (i == 0 || j == 0) return -1;
		else {
			dir = (board[i - 1][j] == board[i + 1][j] ? 0 : -1);
			if (dir>=0) dir = (board[i][j - 1] == board[i + 1][j] ? 3 : -1);
		}
		break;
	case 1:
		if (i == n - 1 || j == n - 1) return -1;
		else {
			dir = (board[i + 1][j] == board[i - 1][j] ? 2 : -1);
			if (dir>=0) dir = (board[i][j + 1] == board[i - 1][j] ? 1 : -1);
		}
		break;		
	case 2:
		if (i == n - 1 || j == n - 1) return -1;
		else {
			dir = (board[i + 1][j] == board[i - 1][j] ? 2 : -1);
			if (dir>=0) dir = (board[i][j + 1] == board[i - 1][j] ? 1 : -1);
		}
		break;
	case 3:
		if (i == n - 1 || j == n - 1) return -1;
		else {
			dir = (board[i + 1][j] == board[i - 1][j] ? 2 : -1);
			if(dir>=0) dir= (board[i][j+1] == board[i - 1][j] ? 1 : -1);
		}
		break;
	}
	return dir;
}
change_tile check_3(int i,int j, change_tile get_score) {
	if (board[i][j] == board[i + 1][j] &&//3
		board[i][j] == board[i + 1][j + 1]) {
		int dir = is_changable(i+1,j+1,3);
		if (dir) {
			get_score.dir = dir; 
		}
	}
}
change_tile search_get() {
	change_tile get_score;
	for (int i = 0; i < n - 1; ++i) {
		for (int j = 0; j < n - 1; j++) {
			if (board[i][j] == board[i + 1][j] && //4
				board[i][j] == board[i + 1][j + 1] && 
				board[i][j] == board[i][j + 1])
				replace(i, j);
			else {
				check_3(i, j,get_score);

			}
		}
	}
	
}
int f(char get,int pos[2],char dir) {
	int max_score = 0;
	vector<change_tile>scores;
	change_tile get_score;
	while (1){
		get_score = search_get();
		if (get_score.dir >= 0) scores.push_back(get_score);
		else break;
	}

	return max_score;
}
int main() {
	cout << "======Start Input=====" << endl;
	cout << "Color Number: " << endl; cin >> colors;
	cout << "Start Seed: " << endl; cin >> startSeed;
	cout << "N: " << endl; cin >> n;
	cout << "Start Board: " << endl;
	string sb_temp;
	for (int i = 0; i < n; i++) {
		cin >> sb_temp;
		start_board.push_back(sb_temp);
	}
	buf = new int(45000);
	make_buf(startSeed);

	return 0;
}