#include <bits/stdc++.h>
mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
string Codes = "atcg";
string GenerateDna(int Size){
  string Dna = "";
  for(int i = 0; i<Size; i++){
    Dna.push_back(Codes[rnd()%Codes.size()]);
  }
  return Dna;
}
vector<string> GenerateTestcase(int Size){
  vector<string>Testcase(Size);
  for(int i = 0; i<Size; i++){
    Testcase[i] = GenerateDna(rnd()%4+1);
  }
  return Testcase;
}
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  for(int i = 1; i<=10; i++){
    cout<<i<<"\n";
    vector<string>InputDna = GenerateTestcase(i);
    for(auto Dna:InputDna){
      cout<<Dna<<" ";
    }
    cout<<"\n";
  }
  return 0;
}
