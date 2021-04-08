/**
 *    author:  tourist
 *    created: 10.08.2018
**/
#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  cin >> tt;
  for (int qq = 1; qq <= tt; qq++) {
    cout << "Case #" << qq << ": ";
    long long r, c;
    int n;
    cin >> r >> c >> n;
    vector<long long> xa(n);
    vector<long long> ya(n);
    vector<long long> xb(n);
    vector<long long> yb(n);
    vector<pair<long long,long long>> p(n);
    for (int i = 0; i < n; i++) {
      long long x, y, d;
      cin >> x >> y >> d;
      xa[i] = max(1LL, x - d);
      ya[i] = max(1LL, y - d);
      xb[i] = min(r, x + d);
      yb[i] = min(c, y + d);
      p[i] = make_pair(x, y);
    }
    vector<long long> inter(1 << n, 0);
    for (int t = 0; t < (1 << n); t++) {
      long long ax = 1, ay = 1, bx = r, by = c;
      for (int i = 0; i < n; i++) {
        if (t & (1 << i)) {
          ax = max(ax, xa[i]);
          ay = max(ay, ya[i]);
          bx = min(bx, xb[i]);
          by = min(by, yb[i]);
        }
      }
      if (ax <= bx && ay <= by) {
        inter[t] = (bx - ax + 1) * (by - ay + 1);
        for (int i = 0; i < n; i++) {
          if (ax <= p[i].first && p[i].first <= bx) {
            if (ay <= p[i].second && p[i].second <= by) {
              inter[t]--;
            }
          }
        }
      }
    }
    vector<int> bc(1 << n);
    for (int t = 0; t < (1 << n); t++) {
      bc[t] = __builtin_popcount(t);
    }
    vector<long long> over(1 << n, 0);
    for (int t = 0; t < (1 << n); t++) {
      int u = t;
      while (u > 0) {
        over[t] += inter[u] * ((bc[u] & 1) ? 1 : -1);
        u = (u - 1) & t;
      }
    }
    long long low = r * c;
    for (int t = 1; t < (1 << n); t++) {
      long long cur = over[t] / bc[t];
      low = min(low, cur);
    }
    long long high = 0;
    for (int t = 1; t < (1 << n); t++) {
      long long only = over[(1 << n) - 1] - over[(1 << n) - 1 - t];
      long long cur = (only + bc[t] - 1) / bc[t];
      high = max(high, cur);
    }
    cout << high - low << '\n';
  }
  return 0;
}
