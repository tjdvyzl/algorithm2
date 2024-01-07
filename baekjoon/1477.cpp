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
    1. 매개변수탐색으로 접근
    2. target으로 둘 기준 => 휴게소가 없는 구간의 길이
    3. 이분탐색을 하는 과정에서 휴게소를 둘 수 있는 모든 경우의 수를 탐색
    4. 탐색하면서 cur값을 갱신, 이때 cur은 현재 위치보다 가장 앞에있는 휴게소의 위치
    5. 탐색하면서 i - cur 값이 dis와 같은 시점에서 휴게소를 하나 설치
    6. 설치할 때마다 cnt값 증가
    7. 모두 탐색했다면, cnt와 M값을 비교해서, cnt가 M보다 작거나 같다면 return ture
        -> dis 길이만큼 차이가 나도록 휴게소를 설치할 수 있다는 얘기고,
            임의의 빈 공간에 추가적으로 휴게소를 설치했다는 의미로 해석가능
*/

vector<int> vec;
int n, m, len;
bool isLocated[1088];

bool canLocated(int dis)
{
    int cnt = 0;
    int cur = 0;
    for (int i = 1; i < len; i++)
    {
        if (isLocated[i])
        {
            cur = i;
            continue;
        }

        if (i - cur == dis)
        {
            cnt++;
            cur = i;
        }
    }

    if (cnt <= m)
        return true;
    return false;
}

int main()
{
    FIO;

    cin >> n >> m >> len;
    for (int i = 0; i < n; i++)
    {
        int input;
        cin >> input;
        vec.push_back(input);
        isLocated[input] = true;
    }

    sort(vec.begin(), vec.end());

    int l = 1, r = len;
    int result = 0; // 휴게소가 없는 구간의 길이 최솟값
    while (l <= r)
    {
        int mid = (l + r) / 2; // 휴게소가 없는 구간의 길이
        if (canLocated(mid))
        {
            result = mid;
            r = mid - 1;
        }
        else
        {

            l = mid + 1;
        }
    }

    cout << result << "\n";
}