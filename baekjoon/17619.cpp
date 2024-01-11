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
    1. x1이 짧은 순으로 정렬한다.
    2. 첫 원소의 x2을 cur_len에 할당해준다.
    3. 첫 원소의 idx를 cur_idx에 할당해준다.
    4. 1번째 원소부터 정렬된 vec를 탐색.
    5. 탐색하는 과정에서 vec[i].x1이 cur_len보다 작거나 같다면 vec[i].idx와 cur_idx를 merge
        -> 정렬하기 전 vec[i].idx번째 통나무와 cur_idx번째 통나무 간에 이동이 가능함을 의미.
    6. 끝까지 다 탐색했다면 Q 만큼 입력되는 값들을 find로 root값들을 각각 찾는다.
        -> 여기서 루트값들이 같다면 서로 이동할 수 있음을 의미.
    이 문제의 요점은 서로 다른 위치와 길이의 통나무들이 퍼져있어도 정렬해서 두개의 원소들을 비교해가며
    union-find로 같은 집합을 만들어주고, 끝까지 훑어주면 이동할 수 있는 통나무들의 집합들이 형성된다는 점을
    알 수 있음
*/

class node
{
public:
    int x1;
    int x2;
    int idx;
    node(int x1, int x2, int idx) : x1(x1), x2(x2), idx(idx) {}
    node() {}
};

int N, Q;
int parent[100005];
vector<node> vec;

bool compare(node a, node b)
{
    return a.x1 < b.x1;
}

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

int main()
{
    FIO;
    cin >> N >> Q;
    for (int i = 0; i <= N; i++)
        parent[i] = i;

    for (int i = 1; i <= N; i++)
    {
        int x1, x2, y;
        cin >> x1 >> x2 >> y;
        vec.push_back(node(x1, x2, i));
    }

    sort(vec.begin(), vec.end(), compare);

    int cur_idx = vec[0].idx;
    int cur_len = vec[0].x2;
    for (int i = 1; i < vec.size(); i++)
    {
        if (vec[i].x1 <= cur_len)
        {
            merge(cur_idx, vec[i].idx);
        }
        if (cur_len <= vec[i].x2)
        {
            cur_len = vec[i].x2;
            cur_idx = vec[i].idx;
        }
    }

    for (int i = 0; i < Q; i++)
    {
        int a, b;
        cin >> a >> b;
        a = find(a);
        b = find(b);
        if (a == b)
            cout << 1 << "\n";
        else
            cout << 0 << "\n";
    }
}