#include <bits/stdc++.h>
const ll inf = 2e9;

class CompressDna{
public:
  CompressDna(vector<string> &DnaCodes, int n){
    this->Dna.resize(n);
    this->DnaSize = n;
    for(int i = 0; i<n; i++){
      this->Dna[i] = DnaCodes[i];
    }
    random_shuffle(this->Dna.begin(), this->Dna.end());
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

  vector<int>calc_z_function(string s){
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
    makeUnique();
    findMaximumCommonPrefixSuffix();
    Count();
    string CompressedDna = "";
    int MinCount = inf;
    string StartDna = "";
    for(int i = 0; i<this->DnaSize; i++){
      if(this->countMaximum[this->Dna[i]]<MinCount){
        MinCount = this->countMaximum[this->Dna[i]];
        StartDna = this->Dna[i];
      }
    }

    int lastMaximumPrefix = 0;
    for(int i = 0; i<this->DnaSize; i++){
      for(int j = lastMaximumPrefix; j<StartDna.size(); j++){
        CompressedDna.push_back(StartDna[j]);
      }
      MatchUsed[StartDna] = true;
      lastMaximumPrefix = 0;
      string CurDna = "";
      for(int j = 0; j<this->DnaSize; j++){
        if(getMaxCommonPrefix[{this->Dna[j], StartDna}]>lastMaximumPrefix && MatchUsed[this->Dna[j]] == false){
          lastMaximumPrefix = getMaxCommonPrefix[{this->Dna[j], StartDna}];
          CurDna = this->Dna[j];
        }
      }
      if(CurDna.size() == 0){
        for(int j = 0; j<this->DnaSize; j++){
          if(MatchUsed[this->Dna[j]] == false){
            CurDna = this->Dna[j];
            break;
          }
        }
      }
      StartDna = CurDna;
    }
    return CompressedDna;
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
        vector<int>z_function = calc_z_function(temp);

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
        for(int a = 0; a<min(this->Dna[i].size(), this->Dna[j].size()); a++){
          if(this->Dna[i].substr(0, a+1) == this->Dna[j].substr(this->Dna[j].size()-a-1, this->Dna[j].size()+1)){
            getMaxCommonPrefix[{this->Dna[i], this->Dna[j]}] = a+1;
          }
          if(this->Dna[j].substr(0, a+1) == this->Dna[i].substr(this->Dna[i].size()-a-1, this->Dna[i].size()+1)){
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
  cout<<compressed.buildDnaString()<<"\n";
  return 0;
}
