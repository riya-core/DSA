class Solution {
    //greedy approach
public:
    bool checkValidString(string s) {
        int low =0, high =0;
        for( char c:s){ 
            if(c=='*'){
                low--;//as close
                high++;//as open
            }
            else if(c=='('){
                low++;
                high++;
            }else {
                low--;
                high--;
            }
            low = max(0, low);
            //in case of more asterisk no need
            //if close then trace via high only
            if(high<0) return false;
            //tracking close bracket valid via high as then if they are flooding the only max opening can't handle them
        }
        return low ==0;
        //if more open left n no care of asterisk count
        //also the high doesn't goes neg-> close is perfect
    }
};
//time:O(n)
//space:O (1)
