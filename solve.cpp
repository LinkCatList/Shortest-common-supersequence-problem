// #pragma GCC optimize("O3")
// #pragma GCC target("avx2")
#include <bits/stdc++.h>
// #include <x86intrin.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/t_policy.hpp>
using namespace std;
// using namespace __gnu_pbds;
// template <typename type, typename cmp = less<type>>
// using pbds_set = t<type, null_type, cmp, rb_t_tag,
// t_order_statistics_node_update>;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
// (づ°ω°)づﾐe★゜・。。・゜゜・。。・゜☆゜・。。・゜゜・。。・゜
const ll K = 460;
const ll inf = 2e9;
const ll big_num = 2e18;
string abc = "abcdefghijklmnopqrstuvwxyz";
const ll LG = 31;
const int mod = 1e9 + 7;
mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<ll> distr(2e9, 2e9 + 1e8);
class Hash{
public:
  Hash(string s, int SizeOfString){
    this->DegPoly.resize(SizeOfString+1);
    this->StringHash.resize(SizeOfString+1);
    this->StringHash[0] = 0;
    this->DegPoly[0] = 1;

    for(this->mod = distr(rnd); !IsPrime(this->mod); this->mod++);

    for(int i = 0; i<SizeOfString; i++){
      this->StringHash[i+1] = ((this->StringHash[i]*this->BasePoly)%this->mod+s[i])%this->mod;
      this->DegPoly[i+1] = (this->DegPoly[i]*this->BasePoly)%this->mod;
    }
  }

  int GetHashOfSubsting(int left, int right){
    return ((this->StringHash[right+1]-(this->StringHash[left]*this->DegPoly[right-left+1])%this->mod)%this->mod+this->mod)%this->mod;
  }

private:
  int mod = 1e9+7;
  int BasePoly = 179;
  vector<int>DegPoly;
  vector<int>StringHash;
  bool IsPrime(int n){
    for(int i = 2; i*i<=n; i++){
      if(n%i == 0){
        return false;
      }
    }
    return true;
  }
};
class CompressDna{
public:
  CompressDna(vector<string> &DnaCodes, int n){
    this->Dna.resize(n);
    this->DnaSize = n;
    for(int i = 0; i<n; i++){
      this->Dna[i] = DnaCodes[i];
    }
    //random_shuffle(this->Dna.begin(), this->Dna.end());
    for(int i = 0; i<this->DnaSize; i++){
      MatchUsed[this->Dna[i]] = false;
    }
    for(int i = 0; i<this->DnaSize; i++){
      for(int j = 0; j<this->DnaSize; j++){
        getMaxCommonPrefix[{this->Dna[i], this->Dna[j]}] = -1;
        getMaxCommonSuffix[{this->Dna[i], this->Dna[j]}] = -1;
      }
    }
  }

  vector<int>CalcZFunction(string s){
    int StringSize = s.size();
    vector<int>z_function(StringSize, 0);

    int left = 0;
    int right = 0;

    for(int i = 1; i<StringSize; i++){
      if(i<=right){
        z_function[i] = min(right-i, z_function[i-left]);
      }
      while(i+z_function[i]<StringSize && s[z_function[i]] == s[i+z_function[i]]){
        z_function[i]++;
      }
      if(i+z_function[i]>right){
        left = i;
        right = i+z_function[i];
      }
    }
    return z_function;
  }

  string buildDnaString(){
    string CompressedDna = "";
    int MinCount = inf;
    string StartDna = "";
    for(int i = 0; i<this->DnaSize; i++){
      if(this->countMaximum[this->Dna[i]]<MinCount){
        MinCount = this->countMaximum[this->Dna[i]];
        StartDna = this->Dna[i];
      }
    }

    set<string>NonDelete;
    for(int i = 0; i<this->DnaSize; i++){
      NonDelete.insert(this->Dna[i]);
    }
    while(NonDelete.size() != 1){
      string FirstGood = "", SecondGood = "";
      int MaximumOverlap = 0;
      for(auto FirstString:NonDelete){
        for(auto SecondString:NonDelete){
          if(FirstString == SecondString)continue;
          if(this->getMaxCommonPrefix[{FirstString, SecondString}]>=MaximumOverlap){
            MaximumOverlap = this->getMaxCommonPrefix[{FirstString, SecondString}];
            FirstGood = FirstString;
            SecondGood = SecondString;
          }
        }
      }
      NonDelete.erase(FirstGood);
      NonDelete.erase(SecondGood);
      string AddString = "";
      for(int i = 0; i<FirstGood.size()-MaximumOverlap; i++){
        AddString.push_back(FirstGood[i]);
      }
      for(int i = 0; i<SecondGood.size(); i++){
        AddString.push_back(SecondGood[i]);
      }
      NonDelete.insert(AddString);
    }
    for(auto Get:NonDelete){
      CompressedDna = Get;
    }
    return CompressedDna;
  }
  string MaximizeDnaString(){
    makeUnique();
    findMaximumCommonPrefixSuffix();
    Count();
    int Iterations = 100;
    string FinalDnaString = "";
    for(int i = 0; i<Iterations; i++){
      random_shuffle(this->Dna.begin(), this->Dna.end());
      string CurrentDnaString = buildDnaString();
      if(CurrentDnaString.size()>FinalDnaString.size()){
        FinalDnaString = CurrentDnaString;
      }
    }
    return FinalDnaString;
  }
private:
  vector<string>Dna;
  int DnaSize;
  map<pair<string, string>, int>getMaxCommonPrefix;
  map<pair<string, string>, int>getMaxCommonSuffix;
  map<string, bool>MatchUsed;
  map<string, int>countMaximum;
  void makeUnique(){
    for(int i = 0; i<this->DnaSize; i++){
      for(int j = 0; j<this->DnaSize; j++){
        if(i == j){
          continue;
        }
        string temp = this->Dna[j]+"#"+this->Dna[i];
        vector<int>z_function = CalcZFunction(temp);

        for(int k = 0; k<z_function.size(); k++){
          if(z_function[k] == this->Dna[j].size()){
            this->Dna[j] = "";
          }
        }
      }
    }
  }
  void findMaximumCommonPrefixSuffix(){
    for(int i = 0; i<this->DnaSize; i++){
      for(int j = 0; j<this->DnaSize; j++){
        Hash h1(this->Dna[i], this->Dna[i].size());
        Hash h2(this->Dna[j], this->Dna[j].size());
        for(int a = 0; a<min(this->Dna[i].size(), this->Dna[j].size()); a++){
          if(h1.GetHashOfSubsting(0, a) == h2.GetHashOfSubsting(this->Dna[j].size()-a-1, this->Dna[j].size()-1)){
            getMaxCommonPrefix[{this->Dna[i], this->Dna[j]}] = a+1;
          }
          if(h2.GetHashOfSubsting(0, a) == h1.GetHashOfSubsting(this->Dna[i].size()-a-1, this->Dna[i].size()-1)){
            getMaxCommonSuffix[{this->Dna[i], this->Dna[j]}] = a+1;
          }
        }
      }
    }
  }
  void Count(){
    for(auto [genom, prefix]:getMaxCommonPrefix){
      countMaximum[genom.first] += (prefix != -1);
      countMaximum[genom.second] += (prefix != -1);
    }
    for(auto [genom, prefix]:getMaxCommonSuffix){
      countMaximum[genom.first] += (prefix != -1);
      countMaximum[genom.second] += (prefix != -1);
    }
  }

};
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n;
  cin>>n;

  vector<string>Dna(n);
  for(int i = 0; i<n; i++){
    cin>>Dna[i];
  }

  CompressDna compressed(Dna, n);
  cout<<compressed.MaximizeDnaString()<<"\n";
  return 0;
}
