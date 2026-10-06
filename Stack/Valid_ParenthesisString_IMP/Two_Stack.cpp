class Solution {
    //time n space: O(n)
    //index n position wrt to opening n asterisk matters
    
public:
    bool checkValidString(string s) {
        stack<int> open, extra;
        int n= s.size();
        for(int i=0; i< n;i++){
            char c= s[i];
            if(c=='(') open.push(i);
            else if(c=='*') extra.push(i);
            else{
                if(!open.empty()){
                    open.pop();
                }
                else if(!extra.empty()) {
                    extra.pop();
                }else return false;
            }
        }
        while(!open.empty()){
            if(!extra.empty() && extra.top()> open.top()){
                open.pop();
                extra.pop();
            }else return false;
        }
        return true;
    }
};
