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
    1. 최대한 큰 큐브를 넣는다.
    2. 분할정복으로 상자에 큐브를 넣었을 때, 세가지 케이스의 빈 공간에 대한 탐색
    3. 내가 푼 방식에 대해서, 최대한 세로로 채우고,
        그 다음 최대한 가로로 채우고, 그 다음 최대한 높이로 채우는 방식으로 했다.
    4. 3번을 구현하는 과정에서 수학적으로 접근하여 시간을 줄인다.
*/

int l, w, h;
int n;
int cube[22];
bool canFull = true;
int ans = 0;

void f(int l_s, int l_e, int w_s, int w_e, int h_s, int h_e)
{
    if (!canFull || l_s == l_e || w_s == w_e || h_s == h_e)
        return;

    int ll = l_e - l_s;
    int lw = w_e - w_s;
    int lh = h_e - h_s;

    // 상자에 넣을 큐브 선택
    int selected_c = -1;
    for (int i = 19; i >= 0; i--)
    {
        int lwh = (int)pow(2, i);
        if (cube[i] > 0 && ll >= lwh && lw >= lwh && lh >= lwh)
        {
            selected_c = i;
            break;
        }
    }
    if (selected_c == -1)
    {
        canFull = false;
        return;
    }

    int t = (int)pow(2, selected_c); // 선택된 큐브의 한 변의 길이

    // 선택된 큐브가 세로로 들어갈 수 있는 최대 개수
    int cl = min(ll / t, cube[selected_c]);

    // 선택된 큐브가 가로로 들어갈 수 있는 최대 개수
    int cw = min(lw / t, cube[selected_c] / cl);

    // 선택된 큐브가 세로로 들어갈 수 있는 최대 개수
    int ch = min(lh / t, cube[selected_c] / (cl * cw));

    ans += cl * cw * ch;
    cube[selected_c] -= cl * cw * ch;

    // 상자에 큐브를 넣고 뒤에 남은 공간
    f(l_s + t * cl, l_e, w_s, w_s + t * cw, h_s, h_s + t * ch);

    // 상자에 큐브를 넣고 옆에 남은 공간
    f(l_s, l_e, w_s + t * cw, w_e, h_s, h_s + t * ch);

    // 상자에 큐브를 넣고 밑에 남은 공간
    f(l_s, l_e, w_s, w_e, h_s + t * ch, h_e);
}

int main()
{
    FIO;

    cin >> l >> w >> h;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int ii, cnt;
        cin >> ii >> cnt;
        cube[ii] = cnt;
    }

    f(0, l, 0, w, 0, h);
    if (canFull)
        cout << ans << "\n";
    else
        cout << -1 << "\n";
}