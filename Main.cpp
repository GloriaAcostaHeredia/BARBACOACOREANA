#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <utility>
#include <queue>

using namespace std;

const int N = 1005;
const int dx[] = { -1, 0, 1, 0 };
const int dy[] = { 0, 1, 0, -1 };

char board[N][N];
int n, m;

struct State {
    int x, y, step;
};

bool valid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m && board[x][y] != '#';
}

bool isPacman(int x, int y) {
    return board[x][y] == 'P';
}

bool isGhost(int x, int y) {
    return board[x][y] == 'G';
}

bool isDot(int x, int y) {
    return board[x][y] == '.';
}

bool isPowerPellet(int x, int y) {
    return board[x][y] == 'O';
}

bool isWall(int x, int y) {
    return board[x][y] == '#';
}

int bfs(int x, int y, int dest_x, int dest_y) {
    bool visited[N][N];
    memset(visited, false, sizeof(visited));

    queue<State> q;
    q.push({ x, y, 0 });
    visited[x][y] = true;

    while (!q.empty()) {
        State s = q.front();
        q.pop();

        if (s.x == dest_x && s.y == dest_y) {
            return s.step;
        }

        for (int i = 0; i < 4; ++i) {
            int nx = s.x + dx[i], ny = s.y + dy[i];
            if (valid(nx, ny) && !visited[nx][ny]) {
                q.push({ nx, ny, s.step + 1 });
                visited[nx][ny] = true;
            }
        }
    }

    return -1;
}

int main() {
    cin >> n >> m;

    int pacman_x, pacman_y;
    vector<pair<int, int>> ghosts;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> board[i][j];
            if (isPacman(i, j)) {
                pacman_x = i, pacman_y = j;
            }
            if (isGhost(i, j)) {
                ghosts.push_back(make_pair(i, j));
            }
        }
    }

    int ans = -1;
    for (auto ghost : ghosts) {
        int res = bfs(ghost.first, ghost.second, pacman_x, pacman_y);
        if (res != -1) {
            if (ans == -1 || res > ans) {
                ans = res;
            }
        }
    }

    cout << ans << endl;

    return 0;
}
