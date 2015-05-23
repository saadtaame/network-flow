#include <cstdio>
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;
const long long INF = (1ll << 60);

#define sym(e) (((e) & 1) ? (e)-1 : (e)+1)

class FlowNetwork
{   vector<int> last, to, prev;
    vector<long long> c, f;
    int n, m, id;

    void add_aux(int x, int y, long long w)
    {   prev[id] = last[x];
        last[x] = id;
        to[id] = y;
        c[id] = w;
        id = id + 1;
    }

    /* find blocking flow */
    long long dfs(int x, int t, vector<int> &level, long long need = INF)
    {   if(need <= 0) return 0;
        if(x == t) return need;
        long long can = 0;
        for(int i = last[x]; i != -1; i = prev[i])
        {   int y = to[i];
            if(level[y] == 1 + level[x] && c[i] > f[i])
            {   long long a = dfs(y, t, level, min(c[i]-f[i], need - can));
                f[i] += a;
                f[sym(i)] -= a;
                can += a;
            }
        }
        if(can == 0) level[x] = -1;
        return can;
    }

    public:
    FlowNetwork(int n_, int m_)
    {   n = n_, m = 2 * m_;

        last.resize(n);
        to.resize(m);
        prev.resize(m);
        c.resize(m);
        f.resize(m);

        fill(last.begin(), last.end(), -1);
        id = 0;
    }

    void print_flow()
    {   for(int i = 0; i < n; i++)
        {   for(int j = last[i]; j != -1; j = prev[j])
            {   if(f[j] <= 0) continue;
                cout << "(" << i << "," << to[j] << ": " << f[j] << ")" << endl;
            }
        }
    }

    /* add directed edge (x,y) with capacity w */
    void add(int x, int y, long long w)
    {   add_aux(x, y, w);
        add_aux(y, x, 0);
    }

    /* compute maximum flow */
    long long flow(int s, int t)
    {   fill(f.begin(), f.end(), 0);

        long long mx_f = 0;
        vector<int> level(n);

        while(1)
        {   fill(level.begin(), level.end(), -1);
            queue<int> q;

            level[s] = 0;
            q.push(s);

            while(q.empty() == false)
            {   int x = q.front(); q.pop();
                for(int i = last[x]; i != -1; i = prev[i])
                {   int y = to[i];
                    if(level[y] == -1 && c[i] > f[i])
                    {   level[y] = 1 + level[x];
                        q.push(y);
                    }
                }
            }

            if(level[t] == -1) break;
            mx_f += dfs(s, t, level);
        }

        return mx_f;
    }
};

int main(void)
{   return 0;
}
