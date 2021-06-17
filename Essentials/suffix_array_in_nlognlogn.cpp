#include <bits/stdc++.h>

using namespace std;

struct Suffix_array {
  string S;
  int N;
  vector<int> p, c;
  Suffix_array(string s) {
    S = s;
    S += "$";
    N = S.size();
    p.resize(N);
    c.resize(N);
  }
  void build_suffix_array() {
    //iteration 0
    {
      vector<pair<char, int>> x(N);
      for(int i = 0; i < N; i++)
        x[i] = {S[i], i};

      sort(x.begin(), x.end());

      for(int i = 0; i < N; i++)
        p[i] = x[i].second;
      c[p[0]] = 0;
      for(int i = 1; i < N; i++) {
        if(x[i].first == x[i - 1].first)
          c[p[i]] = c[p[i - 1]];
        else 
          c[p[i]] = c[p[i - 1]] + 1;
      }
    }

    int k = 0;
    while((1 << k) < N) {

      vector<pair<pair<int, int>, int>> x(N);
      for(int i = 0; i < N; i++)
        x[i] = {{c[i], c[(i + (1 << k)) % N]}, i};

      sort(x.begin(), x.end());

      for(int i = 0; i < N; i++)
        p[i] = x[i].second;

      c[p[0]] = 0;
      for(int i = 1; i < N; i++) {
        if(x[i].first == x[i - 1].first)
          c[p[i]] = c[p[i - 1]];
        else 
          c[p[i]] = c[p[i - 1]] + 1;
      }

      k++;
    }
  }
  vector<int> get_suffix_array() {
    return p;
  }
};
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  string s;
  cin >> s;
  Suffix_array p(s);

  p.build_suffix_array();
  vector<int> a = p.get_suffix_array();

  for(int i = 0; i <= (int)s.size(); i++) {
    cout << a[i] << " ";
  }
  cout << '\n';
  return 0;
}