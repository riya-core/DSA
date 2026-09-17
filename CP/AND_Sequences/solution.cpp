#include<bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
void solve(){
    int n;
    cin>>n;
    vector<int>a(n);
    int total_and = ~0; 
    for(int i= 0; i<n; i++){
        cin>>a[i];
        if(i == 0) total_and= a[i];
        else total_and &= a[i];
    }
    long long cnt = 0;
    for(int i= 0; i < n; i++){
        if (a[i] ==total_and){
            cnt++;
        }
    }
    if(cnt < 2){
        cout<<0<<"\n";
        return;
    }
    long long ans= (cnt*(cnt-1))%MOD;
    for(int i = 1; i<= n-2; i++){
        ans =(ans*i)%MOD;
    }
    cout<<ans<<"\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}
