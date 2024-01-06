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

int N, W;
vector<int> tree[500005];
bool v[500005];
int cnt = 0;

void dfs(int cur)
{
    if (cur != 1 && tree[cur].size() == 1)
    {
        cnt++;
        return;
    }
    for (int i = 0; i < tree[cur].size(); i++)
    {
        int e = tree[cur][i];
        if (v[e])
            continue;
        v[e] = true;
        dfs(e);
    }
}

int main()
{
    FIO;

    cin >> N >> W;
    for (int i = 0; i < N - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    dfs(1);

    cout << W / (double)cnt << "\n";
}