#include <bits/stdc++.h>
using namespace std;
//バカ遅いので誰か修正して！
struct HashString{
    using ll=long long;
    int N=0;
    vector<pair<ll,ll>> hash_data;
    string str;
    const ll mod=998244353;
    const ll mod2=79020979;
    const ll r=2092427;
    const ll r2=870083;
    ll mypow(ll x,ll n,ll MOD){
        ll ret=1;
        while(n>0){
            if(n&1){
                ret=ret*x%MOD;
            }
            x=x*x%MOD;
            n>>=1;
        }
        return ret;
    }
    HashString(){
        N=0;
        str="";
        hash_data.resize(1,make_pair(0,0));
    }
    HashString(const string &s){
        N=s.size();
        hash_data.resize(N+1,make_pair(0,0));
        str=s;
        ll powr=1;
        ll powr2=1;
        for(int i=0;i<N;i++){
            powr*=r;
            powr%=mod;
            powr2*=r;
            powr2%=mod2;
            hash_data[i+1].first=hash_data[i].first+s[i]*powr;
            hash_data[i+1].second=hash_data[i].second+s[i]*powr2;
            hash_data[i+1].first%=mod;
            hash_data[i+1].second%=mod2;
        }
    }
    HashString(const HashString &hs){
        N=hs.N;
        str=hs.str;
        hash_data=hs.hash_data;
    }
    pair<ll,ll> substr_hash(int left,int right){
        pair<ll,ll> ret=hash_data[right];
        ret.first-=hash_data[left].first-mod;
        ret.second-=hash_data[left].second-mod2;
        ret.first%=mod;
        ret.second%=mod2;
        ret.first*=mypow(r,5000000-left,mod);
        ret.second*=mypow(r2,5000000-left,mod2);
        ret.first%=mod;
        ret.second%=mod2;
        return ret;
    }
    int size(){
        return str.size();
    }
    void print_hash(int left,int right){
      cout<<substr_hash(left,right).first<<" "<<substr_hash(left,right).second<<'\n';
    }
};
istream& operator>>(istream& is, HashString& hs) {
    is >> hs.str;
    hs.N=hs.str.size();
    hs.hash_data.resize(hs.N+1,make_pair(0,0));
    for(int i=0;i<hs.N;i++){
        hs.hash_data[i+1].first=hs.hash_data[i].first+hs.str[i]*hs.mypow(hs.r,i+1,hs.mod);
        hs.hash_data[i+1].second=hs.hash_data[i].second+hs.str[i]*hs.mypow(hs.r2,i+1,hs.mod2);
        hs.hash_data[i+1].first%=hs.mod;
        hs.hash_data[i+1].second%=hs.mod2;
    }
    return is;
}
//鉄則演習問題集A56 String Hash
int main(){
    int N,Q;
    cin>>N>>Q;
    HashString S;
    cin>>S;
    for(int i=0;i<Q;i++){
        int a,b,c,d;
        cin>>a>>b>>c>>d;
        
        
        if(S.substr_hash(a-1,b)==S.substr_hash(c-1,d)){
            cout<<"Yes";
        }else{
            cout<<"No";
        }
        
        cout<<'\n';
    }
}
