class Solution {
    //grouping-->dsu
    //time:O(n+m)
    //space:O(27) ->alphabet count
    class DSU{
        vector<int>parent;
        public:
        DSU(){
            parent.resize(27);
            for( int i=0; i<27; i++){
                parent[i]=i;
            }
        }

        int id(char c){
            return c-'a';
        }

        int find(char a){
            int iid = id(a);
            if(parent[iid]==iid) return iid;
            return parent[iid] = find(parent[iid]+'a');
        }

        void unite(char a, char b){
            int pa= find(a), pb= find(b);
            if(pa== pb) return;
            if(pa<pb){
                parent[pb]= pa;
            }else{
                parent[pa]= pb;
            }
        }
    };
public:
    string smallestEquivalentString(string s1, string s2, string baseStr) {
        DSU d;
        for(int i=0;i<s1.size(); i++){
            d.unite(s1[i], s2[i]);
        }
        string ans ="";
        for(auto c: baseStr){
            int iid = d.find(c);
            ans += (iid+'a');
        }
        return ans;
    }
};
