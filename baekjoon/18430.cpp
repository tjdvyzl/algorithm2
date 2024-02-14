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

#define FIO ios_base::sync_with_stdio(0), cin.tie(0);
#define MAX 987654321
typedef long long ll;
typedef pair<int, int> pii;

/*
    MySol>
    간단한 백트래킹 문제
    단, 재귀함수를 시작할 때 마다 y와 x를 모두 1,1부터 시작하도록 구현하면 시간초과가 난다.
    조금 더 생각해보면 x는 굳이 1부터 시작할 필요가 없고, 그 전에 설치된 x 이상의 좌표부터
    탐색하면 더 빠르게 해결할 수 있다.
*/

int N, M;
int m[6][6];
bool v[6][6];
int ans = 0;

pii rect[4][3] = {{{0, -1}, {0, 0}, {1, 0}}, {{-1, 0}, {0, 0}, {0, -1}}, {{-1, 0}, {0, 0}, {0, 1}}, {{0, 1}, {0, 0}, {1, 0}}};

bool isOut(int y, int x)
{
    if (y > N || y < 1 || x > M || x < 1)
        return true;
    return false;
}

bool canInput(int y, int x, int dir)
{
    for (int idx = 0; idx < 3; idx++)
    {
        int dy = y + rect[dir][idx].first;
        int dx = x + rect[dir][idx].second;
        if (isOut(dy, dx) || v[dy][dx])
            return false;
    }
    return true;
}

int input(int y, int x, int dir)
{
    int res = m[y][x];
    for (int idx = 0; idx < 3; idx++)
    {
        int dy = y + rect[dir][idx].first;
        int dx = x + rect[dir][idx].second;
        v[dy][dx] = true;
        res += m[dy][dx];
    }
    return res;
}

void backup(int y, int x, int dir)
{
    for (int idx = 0; idx < 3; idx++)
    {
        int dy = y + rect[dir][idx].first;
        int dx = x + rect[dir][idx].second;
        v[dy][dx] = false;
    }
}

void f(int yy, int xx, int sum)
{
    ans = max(ans, sum);

    for (int y = 1; y <= N; y++)
    {
        for (int x = xx; x <= M; x++)
        {
            if (v[y][x])
                continue;
            for (int dir = 0; dir < 4; dir++)
            {
                if (canInput(y, x, dir))
                {
                    int t = input(y, x, dir);
                    f(y, x, sum + t);
                    backup(y, x, dir);
                }
            }
        }
    }
}

int main()
{
    FIO;
    cin >> N >> M;
    for (int y = 1; y <= N; y++)
    {
        for (int x = 1; x <= M; x++)
        {
            cin >> m[y][x];
        }
    }

    f(1, 1, 0);

    cout << ans << "\n";
}