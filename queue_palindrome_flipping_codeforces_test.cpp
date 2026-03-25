// https://codeforces.com/contest/2158/submission/368202115
#include <cstdio>
#include <ctime>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>
using namespace std;

namespace macros {
    typedef long long ll;
    typedef vector<ll> vi;
    typedef pair<ll, ll> ii;
    typedef pair<ii, ll> iii;
    typedef vector<ii> vii;
    typedef vector<pair<ll, ll>> viii;

    #define FOR(i, a, b) for(ll i=ll(a); i<ll(b); i++)
    #define ROF(i, a, b) for(ll i=ll(a); i>=ll(b); i--)
    #define pb push_back
    #define mp make_pair
    #define all(a) (a).begin(), (a).end()
    #define ifile(a) freopen((a), "r", stdin)
    #define ofile(a) freopen((a), "w", stdout)
    #define sync ios_base::sync_with_stdio(false); cin.tie(NULL);
    #define PI 3.1415926535897932384626433832795
    #define mem(x, val) memset((x), (val), sizeof(x))
    #define sz(x) (ll)(x).size()
    #define endl '\n'
    #define clozackon ll t = 1; while (t--) { clock_t z = clock();
    #define clockoff debug("Elapsed Time: %.3f\n", (double)(clock() - z) / CLOCKS_PER_SEC); }
    #define oo 2000000000000000000LL
    #define EPS 1e-6
    #define MOD 1000000007
    #define etr "\n"
    #define INF 1E18 / 2
    #define MAX 200050
    #define UNIQUE(v) (v).erase(unique(all(v)), (v).end())
    void setIO(string prob) {
        freopen((prob + ".in").c_str(), "r", stdin);
        freopen((prob + ".out").c_str(), "w", stdout);
    }
}
using namespace macros;

template <typename T>
class Queue {
private:
    class Node {
    public:
        T data;
        Node* next;
        Node* prev;
        Node() : data(T()), next(nullptr), prev(nullptr) {}
        Node(T val) : data(val), next(nullptr), prev(nullptr) {}
    };
    Node* head;
    Node* tail;
    int length;

public:
    Queue() {
        head = new Node();
        tail = head;
        length = 0;
    }

    ~Queue() {
        while (!isEmpty()) {
            pop();
        }
        delete head;
    }

    void push(T val) {
        Node* newNode = new Node(val);
        if (isEmpty()) {
            tail = newNode;
        }
        newNode->next = head->next;
        newNode->prev = head;
        head->next = newNode;
        if (newNode->next != nullptr) {
            newNode->next->prev = newNode;
        }
        length++;
    }

    void pop() {
        if (isEmpty()) return;
        tail = tail->prev;
        delete tail->next;
        tail->next = nullptr;
        length--;
    }

    T& front() {
        if (!isEmpty()) {
            return tail->data;
        }
        throw runtime_error("Queue is empty");
    }

    bool isEmpty() const {
        return head->next == nullptr;
    }

    int size() const {
        return length;
    }
};

map<string, map<string, ll>> dist;
map<string, map<string, bool>> visited;
map<string, map<string, vector<pair<ll, ll>>>> path;

void findPath(const string& pattern) {
    int L = pattern.length();
    using Path = vector<pair<ll, ll>>;
    Queue<pair<string, Path>> q;
    q.push({pattern, {}});
    visited[pattern][pattern] = true;
    dist[pattern][pattern] = 0;
    path[pattern][pattern] = {};

    while (!q.isEmpty()) {
        auto curr = q.front();
        q.pop();
        string s = curr.first;
        Path currPath = curr.second;

        ll currDist = currPath.size();

        for (ll len = 2; len <= L; len++) {
            for (ll start = 0; start + len <= L; start++) {
                ll end = start + len - 1;
                bool isPalindrome = true;

                for (ll i = 0; i < len / 2; i++) {
                    if (s[start + i] != s[end - i]) {
                        isPalindrome = false;
                        break;
                    }
                }
                if (!isPalindrome) continue;

                string nextS = s;
                for (ll i = start; i <= end; i++)
                    nextS[i] = (s[i] == '0' ? '1' : '0');

                if (!visited[pattern][nextS]) {
                    visited[pattern][nextS] = true;
                    dist[pattern][nextS] = currDist + 1;

                    Path nextPath = currPath;
                    nextPath.push_back({start, end});
                    path[pattern][nextS] = nextPath;

                    q.push({nextS, nextPath});
                }
            }
        }
    }
}

void solve() {
    ll n;
    cin >> n;
    string s1, s2;
    cin >> s1 >> s2;
    if (n == 4) {
        if (path[s1][s2].size() > 2 * n) {
            cout << -1 << endl;
            return;
        }
        cout << path[s1][s2].size() << endl;
        for (auto step : path[s1][s2]) {
            cout << step.first + 1 << ' ' << step.second + 1 << endl;
        }
        return;
    }

    vector<pair<ll, ll>> ans;
    for (ll i = 0; i < n; i += 5) {
        if ((i + 4) < n) {
            for (auto step : path[s1.substr(i, 5)][s2.substr(i, 5)]) {
                ans.pb(mp(i + 1 + step.first, i + 1 + step.second));
            }
            s1.replace(i, 5, s2.substr(i, 5));
        }
    }
    for (ll i = (n - 1); i >= 0; i--) {
        if ((i + 4) < n) {
            for (auto step : path[s1.substr(i, 5)][s2.substr(i, 5)]) {
                ans.pb(mp(i + 1 + step.first, i + 1 + step.second));
            }
            s1.replace(i, 5, s2.substr(i, 5));
        }
    }

    if (ans.size() > 2 * n) {
        cout << -1 << endl;
        return;
    }
    cout << ans.size() << endl;
    for (auto e : ans)
        cout << e.first << ' ' << e.second << endl;
}

int main() {
    vector<string> chars = {"0", "1"};
    for (auto l1 : chars) {
        for (auto l2 : chars) {
            for (auto l3 : chars) {
                for (auto l4 : chars) {
                    string p1 = l1 + l2 + l3 + l4;
                    findPath(p1);
                    for (auto l5 : chars) {
                        string p2 = l1 + l2 + l3 + l4 + l5;
                        findPath(p2);
                    }
                }
            }
        }
    }

    sync;
    ll t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
