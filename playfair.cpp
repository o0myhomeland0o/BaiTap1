// playfair.cpp
#include <bits/stdc++.h>
using namespace std;
string prepare(const string &s){
    string t;
    for(char c: s) if(isalpha(c)) {
        char u = toupper(c);
        if(u=='J') u='I';
        t.push_back(u);
    }
    return t;
}
array<int,2> findPos(const vector<string>&mat, char ch){
    for(int r=0;r<5;++r) for(int c=0;c<5;++c) if(mat[r][c]==ch) return {r,c};
    return {-1,-1};
}
vector<string> buildMat(const string &key){
    string p = prepare(key);
    vector<bool> used(26,false);
    used['J'-'A'] = true; // merge J
    vector<char> seq;
    for(char c: p){
        if(!used[c-'A']) { seq.push_back(c); used[c-'A']=true; }
    }
    for(char c='A'; c<='Z'; ++c){
        if(!used[c-'A']) seq.push_back(c);
    }
    vector<string> mat(5,string(5,' '));
    int idx=0;
    for(int r=0;r<5;++r) for(int c=0;c<5;++c) mat[r][c] = seq[idx++];
    return mat;
}
vector<pair<char,char>> makeDigraphs(const string &pt){
    string s = prepare(pt);
    vector<pair<char,char>> res;
    for(size_t i=0;i<s.size();){
        char a = s[i];
        char b = (i+1<s.size()? s[i+1] : 'X');
        if(a==b){
            res.push_back({a,'X'});
            i+=1;
        } else {
            res.push_back({a,b});
            i+=2;
        }
    }
    if(res.size()>0){
        auto &last = res.back();
        if(last.second==0) last.second='X';
    }
    return res;
}
string playfair_encrypt(const string &pt, const string &key){
    auto mat = buildMat(key);
    auto dig = makeDigraphs(pt);
    string out;
    for(auto &p: dig){
        char a=p.first, b=p.second;
        auto pa = findPos(mat,a), pb = findPos(mat,b);
        int ra=pa[0], ca=pa[1], rb=pb[0], cb=pb[1];
        if(ra==rb){
            out.push_back(mat[ra][(ca+1)%5]);
            out.push_back(mat[rb][(cb+1)%5]);
        } else if(ca==cb){
            out.push_back(mat[(ra+1)%5][ca]);
            out.push_back(mat[(rb+1)%5][cb]);
        } else {
            out.push_back(mat[ra][cb]);
            out.push_back(mat[rb][ca]);
        }
    }
    return out;
}
string playfair_decrypt(const string &ct, const string &key){
    auto mat = buildMat(key);
    vector<pair<char,char>> dig;
    string s = prepare(ct);
    for(size_t i=0;i<s.size(); i+=2) dig.push_back({s[i], s[i+1]});
    string out;
    for(auto &p: dig){
        char a=p.first,b=p.second;
        auto pa = findPos(mat,a), pb = findPos(mat,b);
        int ra=pa[0], ca=pa[1], rb=pb[0], cb=pb[1];
        if(ra==rb){
            out.push_back(mat[ra][(ca+5-1)%5]);
            out.push_back(mat[rb][(cb+5-1)%5]);
        } else if(ca==cb){
            out.push_back(mat[(ra+5-1)%5][ca]);
            out.push_back(mat[(rb+5-1)%5][cb]);
        } else {
            out.push_back(mat[ra][cb]);
            out.push_back(mat[rb][ca]);
        }
    }
    return out;
}
int main(){
    cout<<"Playfair demo\nMode (e/d): "; char m; if(!(cin>>m)) return 0;
    cin.ignore();
    cout<<"Key: "; string key; getline(cin,key);
    cout<<"Text:\n"; string txt; getline(cin,txt);
    if(m=='e') cout<<playfair_encrypt(txt,key)<<"\n";
    else cout<<playfair_decrypt(txt,key)<<"\n";
    return 0;
}
