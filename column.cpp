// columnar.cpp
#include <bits/stdc++.h>
using namespace std;
string sanitize(const string &s){
    string t;
    for(char c: s) if(isalpha(c)) t+=toupper(c);
    return t;
}
vector<int> key_order(const string &key){
    int n=key.size();
    vector<pair<char,int>> v;
    for(int i=0;i<n;++i) v.push_back({toupper(key[i]), i});
    sort(v.begin(), v.end());
    vector<int> order(n);
    for(int i=0;i<n;++i) order[v[i].second]=i;
    return order;
}
string columnar_encrypt(const string &pt, const string &key){
    string s = sanitize(pt);
    int k = key.size();
    if(k==0) return s;
    int rows = (s.size() + k -1)/k;
    string padded = s;
    while((int)padded.size() < rows*k) padded.push_back('X');
    vector<string> cols(k);
    for(int r=0;r<rows;++r)
        for(int c=0;c<k;++c)
            cols[c].push_back(padded[r*k + c]);
    // output columns in order of sorted key
    vector<pair<char,int>> ord;
    for(int i=0;i<k;++i) ord.push_back({toupper(key[i]), i});
    sort(ord.begin(), ord.end());
    string ct;
    for(auto &p: ord) ct += cols[p.second];
    return ct;
}
string columnar_decrypt(const string &ct, const string &key){
    string s = sanitize(ct);
    int k = key.size();
    if(k==0) return s;
    int rows = (s.size())/k;
    vector<pair<char,int>> ord;
    for(int i=0;i<k;++i) ord.push_back({toupper(key[i]), i});
    sort(ord.begin(), ord.end());
    vector<string> cols(k);
    int idx=0;
    for(auto &p: ord){
        cols[p.second] = s.substr(idx, rows);
        idx += rows;
    }
    string pt;
    for(int r=0;r<rows;++r)
        for(int c=0;c<k;++c)
            pt.push_back(cols[c][r]);
    return pt;
}
int main(){
    cout<<"Columnar Transposition demo\nMode (e/d): "; char m; if(!(cin>>m)) return 0;
    cin.ignore();
    cout<<"Key (word): "; string key; getline(cin,key);
    cout<<"Text:\n"; string txt; getline(cin, txt);
    if(m=='e') cout<<columnar_encrypt(txt,key)<<"\n";
    else cout<<columnar_decrypt(txt,key)<<"\n";
    return 0;
}
