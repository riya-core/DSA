//implied the take n not take thing from the dp then also make used the mathamatical computation type
//dp state here is like to decide what all can be made from the prev state of all the elements considering the duplicates present
// time:O(n.2^n)
// space:O(n)
class Solution {
    vector<vector<int>>ans;
    vector<int>cur;

    void solve(vector<pair<int,int>>& freq, int ind){
        if(ind == freq.size()){
            ans.push_back(cur);
            return;
        }
        int num = freq[ind].first,count = freq[ind].second;   

        for(int i=0; i<=count; i++){
            for(int j=0; j<i; j++){
                cur.push_back(num);
            }
            solve(freq,ind+1);
            for(int j=0; j<i; j++){
                cur.pop_back();
            }
        }
    }
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        int n = nums.size();
        map<int,int> mp;        

        for(int i: nums) mp[i]++;   

        vector<pair<int,int>> freq(mp.begin(), mp.end()); 
        solve(freq,0);
        return ans;
    }
};
