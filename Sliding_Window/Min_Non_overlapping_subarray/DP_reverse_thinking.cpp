class Solution {
    //time n space:O(n)
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n= arr.size(), sum=0, l=0, ans=INT_MAX;
        vector<int>dp(n+1, INT_MAX);
        //dp[i]== min length of valid subarray at index <=i***
        //reversing logic tried earlier
        //calculate the valid subarray from i then iterate to see to---->>
        //make dynamic look on the prev valid subarray lenght from the this subarray start****
        for(int r=0;r<n; r++){
            sum += arr[r];

            while(sum>target){
                sum-=arr[l];
                l++;
            }
            if(sum==target){
                int len = r-l+1;
                if(dp[l]!= INT_MAX) ans = min(ans,dp[l]+len);

                dp[r+1]= min(dp[r+1],len );
            }
            dp[r+1]= min(dp[r+1], dp[r]);
        }
        return (ans==INT_MAX)? -1: ans;
    }
};
