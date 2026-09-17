class Solution {
//time:O(n2)
//correct but need a reverse and more dynamic thinking
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();
        const int INF = 1e9;
        vector<int>dp(n+1,INF);

        for (int i=n-1; i>=0;i--){
            int sum= 0;

            for(int j=i; j<n; j++){
                sum +=arr[j];
                if(sum==target){
                    dp[i]= min(dp[i], j - i + 1);
                    break;
                }
                if(sum >target)
                    break;
            }
            dp[i] =min(dp[i], dp[i + 1]);
        }
        int ans = INF;
        for(int i=0; i<n; i++){
            int sum = 0;
            for(int j =i; j<n; j++){
                sum +=arr[j];
                if(sum==target){
                    int len1 = j - i + 1;
                    if(dp[j+1] != INF){
                        ans = min(ans, len1 + dp[j + 1]);
                    }
                    break;
                }
                if(sum>target)
                    break;
            }
        }
        return ans== INF?-1:ans;
    }
};
