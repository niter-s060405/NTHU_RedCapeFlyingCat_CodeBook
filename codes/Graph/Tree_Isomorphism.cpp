/*
Tested : https://cses.fi/paste/b7954f004cf15c4c11d70c4/
Author : niter
*/
// Please change "mul" to a random number (> N) before submit
struct Tree_Hash { // 1-based
    using T = __int128;
    const T mod = (T)(1e18 + 3), mul = 435216;
    vector<vector<int>> E;
    Tree_Hash(int _n) : E(_n + 1) {}
    void add_edge(int u, int v) {
        E[u].push_back(v); E[v].push_back(u);
    }
    pair<T, T> h(int v, int p = -1) {
        vector<pair<T, T>> s;
        for (auto &i:E[v]) if (i != p) {
            s.push_back(h(i, v));
        }
        T res = s.size() + 1, prod = mul;
        sort(s.begin(), s.end());
        for (auto &[i, j] : s) {
            res = (res + i * prod) % mod;
            prod = prod * j % mod;
        }
        return {res, prod};
    }
    T cal(int v = 1) {
        int n = 0, c1 = -1, c2 = -1;
        auto dfs = [&](auto&& f, int v, int p) -> int {
            int sz = 1, mx = 0;
            for (int u : E[v]) if (u != p) {
                int s = f(f, u, v);
                sz += s;
                mx = max(mx, s);
            }
            mx = max(mx, n - sz);
            if (n && mx * 2 <= n) (~c1 ? c2 : c1) = v;
            return sz;
        };
        n = dfs(dfs, v, -1); dfs(dfs, v, -1);
        E.push_back({c1, (c2 == -1) ? c1 : c2});
        return h(E.size() - 1).first;
    }
};
