class Solution {
    //time:O(n*2^n)
    //space:O(n)
    void backtrack(vector<int>& candidates, int target,vector<vector<int>>& ans, vector<int>& cur, int index){
        if(target == 0){
            ans.push_back(cur);
            return;
        }
        for(int i = index; i<candidates.size(); i++){
            if(i>index && candidates[i]== candidates[i- 1])//**resist from repeating same pattern in result 
            //as making the use or leaving that value is done using the backtrack call from i-1 only 
                continue;
            if(candidates[i]>target)
                break;
            cur.push_back(candidates[i]);
            backtrack(candidates,target- candidates[i], ans, cur, i + 1);
            cur.pop_back();
        }
    }
public:
    vector<vector<int>>combinationSum2(vector<int>& candidates, int target){
        sort(candidates.begin(),candidates.end());
        vector<vector<int>>ans;
        vector<int>cur;
        backtrack(candidates,target, ans, cur, 0);
        return ans;
    }
};
