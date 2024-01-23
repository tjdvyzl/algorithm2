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

#define FIO ios_base::sync_with_stdio(0), cin.tie(0);
#define MAX 987654321
typedef unsigned long long ll;
typedef pair<int, int> pii;

/*
    MySol>
    개인적으로 백조의 호수보다 어려웠던 구현문제
    1. 왼쪽에서 오른쪽으로, 오른쪽에서 왼쪽으로 x가 맞으면 맞은 위치로부터 동 서 남 북을 bfs돌린다.
    2. 돌리는 과정에서 영역을 최대 3가지로 볼 수 있는데,
    2-1. 완전히 다 별개인 클러스터가 있을거고, 어떤 경우엔 같은 집단인 하나의 클러스터일 수도 있다.
    2-2. 예를 들어서, 오른쪽에서 왼쪽으로 타겟이 맞았고, 서쪽과 북쪽을 bfs 했는데 서로 이어져있는 클러스터
         일 수도 있다.
    3. 한 영역을 모두 bfs 했는데 땅과 맞닿는 클러스터라면 떨어지지않는 클러스터이다.
    4. 한 영역을 모두 bfs 했는데 땅과 맞닿지 않는 클러스터라면 떨어지는 클러스터이다.
    4-1. bfs로 탐색하는 과정에서 특정 클러스터를 bfs하는 전용 2차원 bool 배열인 v와,
          모든 클러스터 영역을 방문처리하는 2차원 bool 배열인 vv가 있다.
    4-2. vv는 한번 탐색한 클러스터 영역을 또 방문하지 않도록 중복방지 역할이다.
    5. 떨어지는 클러스터는 하나밖에 없다고 했으므로 만약 한 영역을 모두 bfs 했는데 땅과 맞닿지 않는
        클러스터를 찾았다면 그것을 vector로 저장해서 떨어지는 것을 구현해준다.
*/

int R, C, N;
char m[105][105];
bool vv[105][105];
bool v[105][105];
int dir_y[4] = {-1, 1, 0, 0};
int dir_x[4] = {0, 0, -1, 1};
vector<pii> vec;

bool isOut(int y, int x)
{
    if (y > R || y < 1 || x > C || x < 1)
        return true;
    return false;
}

bool bfs(int y, int x)
{
    memset(v, false, sizeof(v));
    vec.clear();
    queue<pii> q;
    q.push({y, x});
    v[y][x] = true;
    vv[y][x] = true;
    bool isConnectedToGround = false;
    while (!q.empty())
    {
        pii t = q.front();
        q.pop();
        vec.push_back(t);
        if (isOut(t.first + 1, t.second))
            isConnectedToGround = true;
        for (int dir = 0; dir < 4; dir++)
        {
            int dy = t.first + dir_y[dir];
            int dx = t.second + dir_x[dir];
            if (isOut(dy, dx))
                continue;
            if (vv[dy][dx] || v[dy][dx] || m[dy][dx] == '.')
                continue;
            v[dy][dx] = true;
            vv[dy][dx] = true;
            q.push({dy, dx});
        }
    }
    return isConnectedToGround;
}

void fall()
{
    bool isFinish = false;
    vector<pii> tmp;
    while (!isFinish)
    {
        tmp.clear();
        for (auto e : vec)
        {
            if (isOut(e.first + 1, e.second) || (!v[e.first + 1][e.second] && m[e.first + 1][e.second] == 'x'))
            {
                isFinish = true;
                break;
            }
            tmp.push_back({e.first + 1, e.second});
        }
        if (!isFinish)
        {
            for (auto e : vec)
            {
                m[e.first][e.second] = '.';
                v[e.first][e.second] = false;
            }
            for (auto e : tmp)
            {
                m[e.first][e.second] = 'x';
                v[e.first][e.second] = true;
            }
        }
        vec.clear();
        vec = tmp;
    }
}

void showmap()
{
    for (int y = 1; y <= R; y++)
    {
        for (int x = 1; x <= C; x++)
        {
            cout << m[y][x];
        }
        cout << "\n";
    }
}

void shot(int y, int x)
{
    m[y][x] = '.';
    memset(vv, false, sizeof(vv));
    for (int dir = 0; dir < 4; dir++)
    {
        vec.clear();
        int dy = y + dir_y[dir];
        int dx = x + dir_x[dir];
        if (isOut(dy, dx) || vv[dy][dx] || m[dy][dx] == '.')
            continue;
        bool t = bfs(dy, dx);
        if (!t)
        {
            fall();
            break;
        }
    }
}

int main()
{
    FIO;
    cin >> R >> C;
    for (int y = 1; y <= R; y++)
        for (int x = 1; x <= C; x++)
            cin >> m[y][x];

    cin >> N;
    bool isLtoR = true;
    for (int i = 0; i < N; i++)
    {
        int h;
        cin >> h;
        if (isLtoR)
        {
            for (int x = 1; x <= C; x++)
            {
                if (m[R - h + 1][x] == 'x')
                {
                    shot(R - h + 1, x);
                    break;
                }
            }
        }
        else
        {
            for (int x = C; x >= 1; x--)
            {
                if (m[R - h + 1][x] == 'x')
                {
                    shot(R - h + 1, x);
                    break;
                }
            }
        }
        isLtoR = !isLtoR;
    }
    showmap();
}