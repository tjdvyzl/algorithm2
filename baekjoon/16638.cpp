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
#define MIN INT_MIN
typedef long long ll;
typedef pair<int, int> pii;

/*
    MySol>
    구현 + 백트래킹
    스택에 넣다보니까 연산을 반대로 한다는 점에서 조금 헷갈렸던 것 같다.
    앞에서부터 차례로 하면 operator가 -더라도 정상 계산이 되는데,
    반대로 하면 -를 생략하고 숫자를 연산해서 이상한 값이 나왔다.
    결국 반대로 연산하는 과정에서 앞에 operator가 -인지 아닌지 확인하고,
    -라면 따로 처리를 해줘야한다.
*/

const ll PLUS = LONG_LONG_MIN + 1;
const ll MINUS = LONG_LONG_MIN + 2;
const ll MULTIPLY = LONG_LONG_MIN + 3;

ll N;
string s;
vector<pii> pp_vec; // 괄호쌍
ll ans = INT_MIN;
vector<int> temp;
vector<ll> p(22, -1);

ll calc(ll f, ll o, ll s)
{
    if (o == PLUS)
        return f + s;
    if (o == MINUS)
        return f - s;
    if (o == MULTIPLY)
        return f * s;
    return 0;
}

ll getOperator(char o)
{
    if (o == '+')
        return PLUS;
    if (o == '-')
        return MINUS;
    if (o == '*')
        return MULTIPLY;
    return 0;
}

ll getRes()
{
    stack<ll> st;

    for (int i = 0; i < s.size(); i++)
    {
        if ('0' <= s[i] && s[i] <= '9')
        {
            if (p[i] != -1)
            {
                ll _first = s[i] - '0';
                ll _operator = getOperator(s[i + 1]);
                ll _second = s[i + 2] - '0';
                ll res = calc(_first, _operator, _second);

                if (!st.empty() && st.top() == MULTIPLY)
                {
                    _operator = st.top();
                    st.pop();
                    _first = st.top();
                    st.pop();
                    res = calc(_first, _operator, res);
                }

                if (!st.empty() && st.top() == MINUS)
                {
                    st.pop();
                    st.push(PLUS);
                    st.push(-res);
                }
                else
                    st.push(res);
                i += 2;
            }
            else
            {
                if (!st.empty() && st.top() == MULTIPLY)
                {
                    ll _operator = st.top();
                    st.pop();
                    ll _first = st.top();
                    st.pop();
                    ll res = calc(_first, _operator, s[i] - '0');
                    st.push(res);
                }
                else
                {
                    ll ss = s[i] - '0';
                    if (!st.empty() && st.top() == MINUS)
                    {
                        st.pop();
                        st.push(PLUS);
                        st.push(-ss);
                    }
                    else
                        st.push(ss);
                }
            }
        }
        else
        {
            ll _operator = getOperator(s[i]);
            st.push(_operator);
        }
    }

    ll res = 0;

    while (!st.empty())
    {
        ll s = st.top();
        st.pop();
        if (st.empty())
        {
            res = s;
            break;
        }
        ll o = st.top();
        st.pop();
        ll f = st.top();
        st.pop();
        res = calc(s, o, f);
        st.push(res);
    }

    return res;
}

void f(int idx)
{
    for (int i = idx; i < pp_vec.size(); i++)
    {
        if (p[pp_vec[i].first] != -1 || p[pp_vec[i].second] != -1)
            continue;
        p[pp_vec[i].first] = pp_vec[i].second;
        p[pp_vec[i].second] = pp_vec[i].first;
        temp.push_back(i);
        f(i + 1);
        temp.pop_back();
        p[pp_vec[i].first] = p[pp_vec[i].second] = -1;
    }

    ll res = getRes();

    ans = max(ans, res);
}

int main()
{
    FIO;
    cin >> N >> s;

    for (int i = 0; i < N - 2; i += 2)
        pp_vec.push_back({i, i + 2});

    ans = getRes();

    f(0);
    cout << ans << "\n";
}