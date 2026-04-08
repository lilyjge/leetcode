class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> adj[2001] = {};
        vector<int> prereq[2001] = {};
        bool cant[2001] = {};
        for (vector<int> dep : prerequisites) {
            adj[dep[1]].push_back(dep[0]);
            prereq[dep[0]].push_back(dep[1]);
            cant[dep[0]] = true;
        }
        queue<int> q;
        for(int i = 0; i < numCourses; i++) {
            if (!cant[i]) {
                q.push(i);
                cant[i] = true;
                // cout << "initial can take "  << i << endl;
            }
        } // cant -> havent
        while(!q.empty()) {
            int cur = q.front(); q.pop();
            // cout << "at " << cur << " cant " << cant[cur] << endl;
            if (!cant[cur]) continue;
            bool flag = false;
            for(int dep : prereq[cur]) {
                if (cant[dep]) {
                    flag = true; 
                    break;
                }
            }
            // cout << "flag " << flag << endl;
            if (flag) continue;
            cant[cur] = false;
            for (int nxt : adj[cur])
                q.push(nxt);
        }
        for(int i = 0; i < numCourses; i++) {
            if (cant[i]) return false;
        }
        return true;
    }
};
