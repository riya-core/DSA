class Solution {
//st.top()==boundary from where a valid string starts
//contains an edge as -1
//when a valid then last stored is invalid
//if invalid remove the prev valid or invalid then insert the new boundary
public:
    int longestValidParentheses(string s) {
        stack<int>st;
        st.push(-1);
        int ans =0;
        for(int i=0;i< s.size(); i++){
            char c= s[i];
            if(c=='('){
                st.push(i);
            }else{
                st.pop();
                if(st.empty()){
                    st.push(i);
                }else{
                    ans = max(ans, i-st.top());
                }
            }
        }
        return ans;
    }
};
