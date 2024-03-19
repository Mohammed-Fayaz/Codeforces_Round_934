#include <bits/stdc++.h>

using namespace std;

vector<int> manacher_odd(string s) {
    int n = s.size();
    s = "$" + s + "^";
    vector<int> p(n + 2);
    int l = 1, r = 1;
    for (int i = 1; i <= n; i++) {
        p[i] = max(0, min(r - i, p[l + (r - i)]));
        while (s[i - p[i]] == s[i + p[i]]) {
            p[i]++;
        }
        if (i + p[i] > r) {
            l = i - p[i], r = i + p[i];
        }
    }
    return vector<int>(begin(p) + 1, end(p) - 1);
}

vector<int> manacher(string s) {
    string t;
    for (auto c: s) {
        t += string("#") + c;
    }
    auto res = manacher_odd(t + "#");
    return vector<int>(begin(res), end(res));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int TC;
    cin >> TC;

    while (TC--) {
        int n, q;
        cin >> n >> q;
        string s;
        cin >> s;

        vector<int> d = manacher(s);
        vector<int> d_odd(s.size()), d_even(s.size());

        set<int> s1, s2;
        for (int i = 0; i < n; i++){
            d_odd[i] = d[2 * i + 1] / 2;
            d_even[i] = (d[2 * i] - 1) / 2;

            if (i < n -1 && s[i] != s[i + 1]) s1.insert(i);
            if (i < n - 2 && s[i] != s[i + 2]) s2.insert(i);
        }

        while (q--) {
            int l, r;
            cin >> l >> r;
            l--, r--;

            long long sz = r - l + 1;

            long long res;
            auto it = s1.lower_bound(l);
            if (it == s1.end() || *it >= r){
                res = 0;
            } else {
                it = s2.lower_bound(l);
                if (it == s2.end() || *it >= r - 1){
                    res = ((sz - 1) / 2)  * (((sz - 1) / 2) + 1);
                } else {
                    res = ((sz - 1) * sz) / 2 - 1;
                }
            }

            if (sz % 2 == 0) {
                int centerIndex = ((l + r) / 2) + 1;
                if (d_even[centerIndex] < (r - l) / 2 + 1) {
                    res += sz;
                }
            } else {
                int centerIndex = (l + r) / 2;
                if (d_odd[centerIndex] < (r - l) / 2 + 1) {
                    res += sz;
                }
            }

            cout << res << endl;
        }
    }
    return 0;
}
