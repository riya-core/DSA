class Solution {
    //space:O(k)
    //time:O(n logk)
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<pair<int, ListNode*>, vector<pair<int,ListNode *>>, greater<pair<int,ListNode *>>>pq;
        for(auto l: lists){
            if(l!= NULL) pq.push({l->val, l});
        }        
        ListNode * ans = NULL, *tail= NULL;
        while(!pq.empty()){
            auto [a,b] =pq.top();//safest to take by value as in case of reference
            //making pop then accessing b is wrong( which must be the real ans)
            //also push then pop is wrong
            if( tail == NULL){
                tail =ans =b;
            }else{
                tail->next = b;
                tail= tail->next;
            }
            pq.pop();
            //pq.pop() --> BLUNDER as then b points to next smallest value in pq (IN CASE OF REFERNCE IN LINE 10 as in prev code )
            if(b->next!= NULL) pq.push({b->next->val, b->next});
            // pq.pop();
            tail->next =NULL;
        }
        return ans;
    }
};
