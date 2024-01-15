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

/*
    MySol>
    1) 기하학 + 분리집합
    2) 분리집합으로 겹치는 사각형들을 모두 합집합으로 묶어줌.
    3) 문제는 기하학적으로 겹치는지 안겹치는지 확인하는 것임.
    3-1) 일단 a와 b가 입력되면 a의 y2 > b의 y2로 경우의 수를 줄임
        -> 어차피 0 ~ N-1까지의 2중 for문으로 탐색하기 때문에 생략되는 경우는 존재하지 않음
    4) a와 b의 x범위가 아예 겹치질 않는다면 false
    4-1) x범위는 겹치는데 y범위가 겹치질 않는다면 false
    4-2 b가 a안에 존재할 때 -> 벽면에 겹치거나, b가 y2를 제외한 나머지 변이 a를 넘어가는 범위가 없으면 false
    5) 나머지는 true
*/

class node
{
public:
    int x1;
    int y1;
    int x2;
    int y2;
    node() {}
    node(int x1, int y1, int x2, int y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}
};

int N;
vector<node> vec;
int parent[1005];
bool v[1005];
bool isZero = false;
int find(int x)
{
    if (parent[x] == x)
        return x;
    return parent[x] = find(parent[x]);
}

void merge(int a, int b)
{
    a = find(a);
    b = find(b);
    if (a == b)
        return;
    if (a > b)
        parent[a] = b;
    else
        parent[b] = a;
}

bool isOverlap(int a, int b) // a의 y2가 b의 y2보다 크거나 같다고 가정
{
    if (vec[a].y2 < vec[b].y2)
        return false;

    if (vec[a].x2 < vec[b].x1 || vec[b].x2 < vec[a].x1)
        return false;

    if (vec[a].y1 > vec[b].y2)
        return false;

    if (vec[a].y2 == vec[b].y2 || vec[a].y1 == vec[b].y2 || vec[a].y1 == vec[b].y1)
        return true;

    if (vec[a].x2 == vec[b].x2 || vec[a].x2 == vec[b].x1 || vec[a].x1 == vec[b].x2 || vec[a].x1 == vec[b].x1)
        return true;

    if (vec[b].y1 > vec[a].y1)
    {
        if (vec[b].x2 < vec[a].x2 && vec[b].x1 > vec[a].x1)
        {
            return false;
        }
    }

    return true;
}

int main()
{
    FIO;

    cin >> N;

    for (int i = 0; i < N; i++)
        parent[i] = i;

    for (int i = 0; i < N; i++)
    {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        vec.push_back(node(x1, y1, x2, y2));
        if ((x1 == 0 && (y2 >= 0 && y1 <= 0)) || (x2 == 0 && (y2 >= 0 && y1 <= 0)))
            isZero = true;
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i == j)
                continue;
            if (isOverlap(i, j))
                merge(i, j);
        }
    }

    int ans = 0;

    for (int i = 0; i < N; i++)
    {
        int p = find(i);
        if (v[p])
            continue;
        v[p] = true;
        ans++;
    }
    if (isZero)
        ans--;

    cout << ans << "\n";
}