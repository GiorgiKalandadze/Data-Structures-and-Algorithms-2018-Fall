#include <bits/stdc++.h>

using namespace std;

vector<pair<int, int>> queries[500];
int ans[100002];
vector<int> array_mod[500];
int n, n_queries;
int BIG_STEP;

void add_ans(int step)
{
    for (int i = 0; i < step; i++)
    {
        if (array_mod[i].size() == 0)
            continue;
        ans[i] += array_mod[i][0];
        for (int j = 1; j < array_mod[i].size(); j++)
        {
            array_mod[i][j] += array_mod[i][j - 1];
            ans[i + j * step] += array_mod[i][j];
        }
    }
}

void prepare_array(int step)
{
    for (int i = 0; i <= step; i++)
        array_mod[i].clear();
    for (int i = 0; i <= n; i++)
        array_mod[i % step].push_back(0);
}

int main()
{
    cin >> n >> n_queries;
    BIG_STEP = int(sqrt(n));
    while (n_queries--)
    {
        int start, len, step;
        cin >> start >> len >> step;
        if (step > BIG_STEP)
        {
            for (int j = 0; j < len; j++)
            {
                ans[start] += 1;
                start += step;
            }
            continue;
        }
        queries[step].push_back({start, len});
    }
    for (int step = 1; step <= BIG_STEP; step++)
    {
        prepare_array(step);
        for (int i = 0; i < queries[step].size(); i++)
        {
            int row = queries[step][i].first % step;
            int start = queries[step][i].first / step;
            int en = queries[step][i].second + start - 1;
            array_mod[row][start]++;
            if (en + 1 < array_mod[row].size())
                array_mod[row][en + 1]--;
        }
        add_ans(step);
    }
    for (int i = 1; i <= n; i++)
        cout << ans[i] << " ";
    cout << endl;
}
