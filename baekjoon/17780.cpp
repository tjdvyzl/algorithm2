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
    조금 복잡한 구현 문제
    중간중간 call by reference 방식으로 변수에 접근했었는데
    이상한 버그가 생겨서 애먹었다..
*/

const int WHITE = 0;
const int RED = 1;
const int BLUE = 2;
bool isFinish = false;

class node
{
public:
    int y;
    int x;
    int d;
    node() {}
    node(int y, int x, int d) : y(y), x(x), d(d) {}
};

int N, K;
int m[13][13];
int dir_y[5] = {0, 0, 0, -1, 1};
int dir_x[5] = {0, 1, -1, 0, 0};
vector<node> vec;
vector<int> mm[13][13];

bool isOut(int y, int x)
{
    if (y > N || y < 1 || x > N || x < 1)
        return true;
    return false;
}

void setOppositeDirection(int i)
{
    if (vec[i].d == 1)
        vec[i].d = 2;
    else if (vec[i].d == 2)
        vec[i].d = 1;
    else if (vec[i].d == 3)
        vec[i].d = 4;
    else if (vec[i].d == 4)
        vec[i].d = 3;
}

void _move(int i, int dy, int dx)
{
    int yy = vec[i].y;
    int xx = vec[i].x;
    int color = m[dy][dx];
    if (color == RED)
        reverse(mm[yy][xx].begin(), mm[yy][xx].end());

    for (auto e : mm[yy][xx])
    {
        vec[e].y = dy, vec[e].x = dx;
        mm[dy][dx].push_back(e);
    }
    if (mm[dy][dx].size() >= 4)
        isFinish = true;
    mm[yy][xx].clear();
    vec[i].y = dy, vec[i].x = dx;
}

//  0은 흰색, 1은 빨간색, 2는 파란색이다.
// 흰색: 그냥 이동
// 빨강: 모든 말 순서 reverse
// 파랑: 이동방향 반대로 하고, 바뀐 방향으로 1칸 이동(이때 가려는 칸이 파란색이거나 체스판 밖이면 제자리에 위치)

int main()
{
    FIO;
    cin >> N >> K;
    for (int y = 1; y <= N; y++)
        for (int x = 1; x <= N; x++)
            cin >> m[y][x];

    for (int i = 0; i < K; i++)
    {
        int r, c, d; // row, column, direction
        cin >> r >> c >> d;
        vec.push_back(node(r, c, d));
        mm[r][c].push_back(i);
    }

    int cnt = 0;

    while (!isFinish && cnt <= 1000)
    {
        cnt++;
        for (int i = 0; i < K; i++)
        {
            if (mm[vec[i].y][vec[i].x][0] != i)
                continue;

            int dy = vec[i].y + dir_y[vec[i].d];
            int dx = vec[i].x + dir_x[vec[i].d];
            if (isOut(dy, dx) || m[dy][dx] == BLUE)
            {
                setOppositeDirection(i);
                dy = vec[i].y + dir_y[vec[i].d];
                dx = vec[i].x + dir_x[vec[i].d];
                if (!isOut(dy, dx) && m[dy][dx] != BLUE)
                    _move(i, dy, dx);
            }
            else
                _move(i, dy, dx);
        }
    }
    cnt = (cnt > 1000) ? -1 : cnt;
    cout << cnt << "\n";
}