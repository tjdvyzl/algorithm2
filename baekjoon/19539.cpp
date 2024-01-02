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
#define MAX 222222
typedef unsigned long long ll;

int n;
int h[10005];

/* MySol
    a라는 나무와 b라는 나무에 각각 1, 2만큼 크도록 물을 준다.
    즉, 만약 YES가 답이라면 1과 2의 비율이 같을거라는 얘기임.
    EX) 1 5라면 0 3 이고, 0 3이면 1 2와 같으니까 이때 5는 2 2개, 1 1개와 같음
    같은 원리로 입력된 나무 크기가 1이라면 1의 개수만 카운트해주고,
    1보다 크다면 2의 배수만큼 2의 개수를 카운트해주고,
    나머지 만큼 1의 개수를 카운트해준다.
    2의 개수와 1의 개수의 비율이 같다면 YES, 아니라면 NO임.
*/

int main()
{
    FIO;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int hh;
        cin >> hh;
        if (hh <= 0)
            continue;
        h[1] += hh - (hh / 2) * 2;
        h[2] += hh / 2;
    }

    while (h[2] > h[1])
    {
        h[2]--;
        h[1] += 2;
    }

    if (h[2] == h[1])
        cout << "YES\n";
    else
        cout << "NO\n";
}