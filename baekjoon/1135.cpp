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
    1. 시간이 많이 걸리는 자식부터 탐색
    2. tree dp
*/

int n;
int arr[55];
vector<int> graph[55];
bool v[55];
int dp[55];

struct cmp
{
    bool operator()(int a, int b)
    {
        return dp[a] < dp[b];
    }
};

void f(int cur)
{
    if (cur != 0 && graph[cur].size() == 1)
        return;

    v[cur] = true;
    int &ret = dp[cur];
    priority_queue<int, vector<int>, cmp> pq;
    for (int i = 0; i < graph[cur].size(); i++)
    {
        int e = graph[cur][i];
        if (v[e])
            continue;
        f(e);
        pq.push(e);
    }
    int cnt = 1;
    while (!pq.empty())
    {
        int t = pq.top();
        pq.pop();
        ret = max(ret, dp[t] + cnt);
        cnt++;
    }
}

int main()
{
    FIO;

    cin >> n;

    int input;
    cin >> input;
    for (int i = 1; i < n; i++)
    {
        cin >> input;
        graph[input].push_back(i);
        graph[i].push_back(input);
    }

    f(0);

    cout << dp[0] << "\n";
}