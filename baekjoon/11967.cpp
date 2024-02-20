#include <iostream>
using namespace std;
#include <string.h>
#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <algorithm>
#include <cmath>
#include <bitset>
#include <limits.h>
#include <map>

#define FIO ios_base::sync_with_stdio(0), cin.tie(0);
#define MAX 987654321
typedef long long ll;
typedef pair<int, int> pii;

/*
    MySol>
    dfs로 해결했다.
    그냥 기초적인 dfs에서 만약 어떤 방에 도착했는데 새로 불이 켜지는 방이 만들어진다면
    기존에 탐색할 때 쓰던 bool 2차원 배열을 reset시켜서 또 새로 켜진 방까지 탐색하도록 구현하면 된다.
*/

int N, M;

vector<pii> m[105][105];
int ans = 1;
bool l[105][105];
bool v[105][105];

int dir_y[4] = {-1, 1, 0, 0};
int dir_x[4] = {0, 0, -1, 1};

void dfs(int y, int x)
{
    v[y][x] = true;
    bool isLight = false;
    for (auto e : m[y][x])
    {
        if (l[e.first][e.second])
            continue;
        l[e.first][e.second] = true;
        isLight = true;
        ans++;
    }
    if (isLight)
        memset(v, false, sizeof(v));
    for (int dir = 0; dir < 4; dir++)
    {
        int dy = y + dir_y[dir];
        int dx = x + dir_x[dir];
        if (dy < 1 || dy > N || dx < 1 || dx > N)
            continue;
        if (!l[dy][dx])
            continue;
        if (v[dy][dx])
            continue;
        dfs(dy, dx);
    }
}

int main()
{
    FIO;

    cin >> N >> M;
    for (int i = 0; i < M; i++)
    {
        int x, y, a, b;
        cin >> x >> y >> a >> b;
        m[y][x].push_back({b, a});
    }

    l[1][1] = true;
    dfs(1, 1);
    cout << ans << "\n";
}