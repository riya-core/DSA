class Solution {
    //trackkking what inside each "bracket state"
public:
    int scoreOfParentheses(string s) {
        stack<int> st;
        st.push(0);
        for(char c :s){
            if(c =='('){
                st.push(0);
            } 
            else{
                int inside= st.top();
                st.pop();
                int value;
                if(inside== 0)
                    value =1;
                else
                    value= 2*inside;
                st.top() +=value;
            }
        }
        return st.top();
    }
};
//time n space:O(n)
