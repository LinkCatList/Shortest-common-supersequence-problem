#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
// (づ°ω°)づﾐe★゜・。。・゜゜・。。・゜☆゜・。。・゜゜・。。・゜
const int K = 20;
const int inf = 2e9;
string abc = "abcdefghijklmnopqrstuvwxyz";
vector<ll> z_function(string s) {
  ll n = s.size();
  vector<ll> z(n, 0);
  ll l = 0, r = 0;
  for (ll i = 1; i < n; i++) {
    if (i <= r) {
      z[i] = min(r - i, z[i - l]);
    }
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
      z[i]++;
    }
    if (i + z[i] > r) {
      l = i;
      r = i + z[i];
    }
  }
  return z;
}
signed main(){
  ios::sync_with_stdio(0);
  cin.tie(0);
  ifstream cin("bebra.txt");
  ofstream cout("ans.txt");
  ll n;
  cin>>n;
  vector<string>v(n);
  for(ll i = 0; i<n; i++)cin>>v[i];
  string global_answer = "";
  ll sz_ga = inf;
  //for(ll qq = 0; qq<5; qq++){
    random_shuffle(v.begin(), v.end());

    for(ll i = 0; i<n; i++){
      for(ll j = 0; j<n; j++){
        if(i == j)continue;
        string s = v[i];
        string t = v[j];
        string tmp = t+"#"+s;
        vector<ll>ans = z_function(tmp);
        for(ll k = 0; k<(ll)ans.size(); k++){
          if(ans[k] == (ll)t.size()){
            v[j] = "";
          }
        }
      }
    }
    map<pair<string, string>, ll>mp1;
    map<pair<string, string>, ll>mp2;
    for(ll i = 0; i<n; i++){
      for(ll j = 0; j<n; j++){
        string s = v[i];
        string t = v[j];
        mp1[{s, t}] = -1;
        mp2[{s, t}] = -1;
        for(ll a = 0; a<min((ll)s.size(), (ll)t.size()); a++){
          if(s.substr(0, a+1) == t.substr((ll)t.size()-a-1, (ll)t.size()+1)){
            mp1[{s, t}] = a+1;
          }
          if(t.substr(0, a+1) == s.substr((ll)s.size()-a-1, (ll)s.size()+1)){
            mp2[{s, t}] = a+1;
          }
        }
      }
    }
    map<string, ll>cnt;
    for(auto i:mp1){
      cnt[i.first.first] += (i.second != -1);
      cnt[i.first.second] += (i.second != -1);
    }
    for(auto i:mp2){
      cnt[i.first.first] += (i.second != -1);
      cnt[i.first.second] += (i.second != -1);
    }
    ll mn = inf;
    string start = "";
    for(ll i = 0; i<n; i++){
      if(cnt[v[i]]<mn){
        start = v[i];
        mn = cnt[v[i]];
      }
    }
    map<string, bool>used;
    for(auto i:v)used[i] = false;
    ll mx = 0;
    string cur_answer = "";
    for(ll i = 0; i<n; i++){
      //cout<<mx<<" ";
      //cout<<start<<"\n";
      for(ll j = mx; j<(ll)start.size(); j++)cur_answer.push_back(start[j]);
      used[start] = true;
      string a = "";
      mx = 0;
      for(ll j = 0; j<n; j++){
        if(mp1[{v[j], start}]>mx && !used[v[j]]){
          mx = mp1[{v[j], start}];
          a = v[j];
        }
      }
      if(a == ""){
        for(ll j = 0; j<n; j++){
          if(!used[v[j]]){
            a = v[j];
            break;
          }
        }
      }
      start = a;
    }
    if((ll)cur_answer.size()<sz_ga){
      global_answer = cur_answer;
      sz_ga = (ll)cur_answer.size();
    }
  //}
  cout<<global_answer<<"\n";
  return 0;
}
