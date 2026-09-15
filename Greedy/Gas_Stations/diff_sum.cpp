class Solution {
//time:O(n)
//space:O(1)
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int fuel= 0, total=0, start=0;

        for(int i=0;i<gas.size(); i++){
            int diff = gas[i] -cost[i];//net gas left after every move
            total += diff;
            fuel += diff;
            if(fuel<0){//if steps till this index goes neg then index between these indices are not valid 
                start = i+1;
                fuel =0;
            }
        }
        if(total<0) return -1;//net gas present is less then needed
        return start;
    }
};
