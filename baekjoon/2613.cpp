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
        2. target의 기준 => M개의 그룹으로 묶었을 때 각 그룹의 합
        3. for문을 탐색할 때 (j는 그 전 그룹을 형성했던 가장 오른쪽 idx), (i는 현재 그룹을 형성 할 idx)
        4. 만약 sum[i] - sum[j] > s라면 j+1부터 i번째 까지의 원소들의 합이 s보다 크므로
            j+1부터 i-1번째 까지의 원소들을 한 그룹으로 형성 가능하다는 의미.
        5. 이때 j는 i-1를 할당해줘서 4번을 반복
        6. 위 과정을 반복했을 때 4 3 1 1 1 1 같은 예시에서 답은 2 2 2가 나옴.
        7. 6번을 고치기 위해, 어떤 그룹에서 원소들의 개수가 1보다 크다면, 1이 될때 까지 또는 형성된 그룹의
            개수가 M이 될 때 까지 선택된 그룹에서 원소 하나를 빼고, 그 선택된 그룹 앞에다가 삽입을 해준다.
                -> 뒤에다가 삽입할 경우 형성된 그룹의 순서가 꼬여서 문제의 조건을 만족시키지 못하는 경우가 존재
*/

int N, M;
int arr[333];
int sum[333];
vector<int> ans;
int result = MAX; // M개의 그룹으로 묶었을 때 각 그룹의 합의 최솟값

bool canGroup(int s)
{
    vector<int> vec;
    int j = 0;
    int cnt = 1;
    for (int i = 1; i <= N; i++)
    {
        if (arr[i] > s)
            return false;
        if (sum[i] - sum[j] > s)
        {
            cnt++;
            vec.push_back(i - j - 1);
            j = i - 1;
        }
    }

    vec.push_back(N - j);

    if (cnt <= M)
    {
        if (cnt < M)
        {
            int t = M - cnt;
            for (int i = 0; t > 0 && i < vec.size(); i++)
            {
                while (t > 0 && vec[i] > 1)
                {
                    vec[i]--;
                    vec.insert(vec.begin() + i, 1);
                    t--;
                }
            }
        }
        if (s < result)
            ans = vec;
        return true;
    }
    return false;
}

int main()
{
    FIO;
    cin >> N >> M;
    for (int i = 1; i <= N; i++)
    {
        cin >> arr[i];
        sum[i] = sum[i - 1] + arr[i];
    }

    int l = 1, r = sum[N];
    while (l <= r)
    {
        int mid = (l + r) / 2; //  M개의 그룹으로 묶었을 때 각 그룹의 합
        if (canGroup(mid))
        {
            result = min(result, mid);
            r = mid - 1;
        }
        else
            l = mid + 1;
    }

    cout << result << "\n";
    for (auto e : ans)
        cout << e << " ";
    cout << "\n";
}