// affine.cpp
#include <bits/stdc++.h>
using namespace std;
int egcd(int a,int b,int &x,int &y){
    if(b==0){ x=1; y=0; return a; }
    int x1,y1; int g=egcd(b,a%b,x1,y1);
    x=y1; y=x1 - (a/b)*y1;
    return g;
}
int modinv(int a,int m){
    int x,y; int g=egcd(a,m,x,y);
    if(g!=1) return -1;
    x%=m; if(x<0) x+=m; return x;
}
string affine_encrypt(const string &s,int a,int b){
    string out=s;
    for(size_t i=0;i<s.size();++i){
        char c=s[i];
        if(isupper(c)) out[i]=char('A' + (a*(c-'A')+b)%26);
        else if(islower(c)) out[i]=char('a' + (a*(c-'a')+b)%26);
        else out[i]=c;
    }
    return out;
}
string affine_decrypt(const string &s,int a,int b){
    int ainv = modinv(a,26);
    if(ainv==-1) return "[error: a not invertible]";
    string out=s;
    for(size_t i=0;i<s.size();++i){
        char c=s[i];
        if(isupper(c)) out[i]=char('A' + (ainv*((c-'A')-b+26*10))%26);
        else if(islower(c)) out[i]=char('a' + (ainv*((c-'a')-b+26*10))%26);
        else out[i]=c;
    }
    return out;
}
int main(){
    cout<<"Affine cipher demo\nMode (e/d): "; char m; if(!(cin>>m)) return 0;
    cout<<"Enter a b: "; int a,b; cin>>a>>b; cin.ignore();
    cout<<"Enter text:\n"; string txt; getline(cin,txt);
    if(m=='e') cout<<affine_encrypt(txt,a,b)<<"\n";
    else cout<<affine_decrypt(txt,a,b)<<"\n";
    return 0;
}
