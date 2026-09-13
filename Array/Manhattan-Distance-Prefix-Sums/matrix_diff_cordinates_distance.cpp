#include <bits/stdc++.h>
using namespace std;

long long calculate_1d_sum(vector<int>& coords){
    sort(coords.begin(), coords.end());
    long long total_dist =0;
    long long prefix_sum = 0;
    for(int i = 0; i<(int)coords.size(); ++i){
        total_dist +=(1LL*i *coords[i])-prefix_sum;
        prefix_sum+=coords[i];
    }
    return total_dist;
}

void solve(){
    int n, m;
    cin>>n>>m;
    const int MAX_COLOR = 100000;
    vector<vector<int>>rows(MAX_COLOR+1);
    vector<vector<int>>cols(MAX_COLOR+1);

    for(int r = 0; r < n; ++r){
        for(int c = 0; c < m; ++c){
            int color;
            cin>>color;
            rows[color].push_back(r);
            cols[color].push_back(c);
        }
    }
    long long ans = 0;
    for(int color = 1;color<= MAX_COLOR;++color){
        if(!rows[color].empty()){
            ans += calculate_1d_sum(rows[color]);
            ans += calculate_1d_sum(cols[color]);
        }
    }
    cout<<ans<<"\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
