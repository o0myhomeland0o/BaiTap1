// caesar.cpp
#include <bits/stdc++.h>
using namespace std;
string caesar_encrypt(const string &s, int k){
    string out=s;
    k = (k%26+26)%26;
    for(size_t i=0;i<s.size();++i){
        char c=s[i];
        if(isupper(c)) out[i]=char('A' + (c-'A'+k)%26);
        else if(islower(c)) out[i]=char('a' + (c-'a'+k)%26);
        else out[i]=c;
    }
    return out;
}
string caesar_decrypt(const string &s, int k){
    return caesar_encrypt(s, -k);
}
int main(){
    cout<<"Caesar cipher demo\n";
    cout<<"Enter mode (e=enc, d=dec): ";
    char m; if(!(cin>>m)) return 0;
    cin.ignore();
    cout<<"Enter key (integer): ";
    int k; cin>>k; cin.ignore();
    cout<<"Enter text:\n";
    string txt; getline(cin, txt);
    if(m=='e') cout<<caesar_encrypt(txt,k)<<"\n";
    else cout<<caesar_decrypt(txt,k)<<"\n";
    return 0;
}
