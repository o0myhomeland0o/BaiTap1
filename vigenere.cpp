// vigenere.cpp
#include <bits/stdc++.h>
using namespace std;
string sanitizeKey(const string &k){
    string s;
    for(char c : k) if(isalpha(c)) s+=toupper(c);
    return s;
}
string vigenere_encrypt(const string &pt, const string &key){
    string k = sanitizeKey(key);
    if(k.empty()) return pt;
    string out = pt;
    int m=k.size(), j=0;
    for(size_t i=0;i<pt.size();++i){
        char c=pt[i];
        if(isalpha(c)){
            int ki = k[j % m] - 'A';
            if(isupper(c)) out[i]=char('A' + (c-'A'+ki)%26);
            else out[i]=char('a' + (c-'a'+ki)%26);
            ++j;
        } else out[i]=c;
    }
    return out;
}
string vigenere_decrypt(const string &ct, const string &key){
    string k = sanitizeKey(key);
    if(k.empty()) return ct;
    string out = ct;
    int m=k.size(), j=0;
    for(size_t i=0;i<ct.size();++i){
        char c=ct[i];
        if(isalpha(c)){
            int ki = k[j % m] - 'A';
            if(isupper(c)) out[i]=char('A' + (c-'A'-ki+26)%26);
            else out[i]=char('a' + (c-'a'-ki+26)%26);
            ++j;
        } else out[i]=c;
    }
    return out;
}
int main(){
    cout<<"Vigenere demo\nMode (e/d): "; char m; if(!(cin>>m)) return 0;
    cin.ignore();
    cout<<"Key: "; string key; getline(cin,key);
    cout<<"Text:\n"; string txt; getline(cin,txt);
    if(m=='e') cout<<vigenere_encrypt(txt,key)<<"\n";
    else cout<<vigenere_decrypt(txt,key)<<"\n";
    return 0;
}
