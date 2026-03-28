typedef pair<int, pair<int, int>> pii;
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> dis(m, vector<int>(n, -1));
        int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        queue<pii> q;
        for(int r = 0; r < m; r++) {
            for(int c = 0; c < n; c++) {
                if (dis[r][c] == 0 || dis[r][c] == 1 || mat[r][c] == 1) continue;
                q.push({0, {r, c}});
                while(!q.empty()) {
                    pii cur = q.front(); q.pop();
                    int curdis = cur.first;
                    int curr = cur.second.first, curc = cur.second.second;
                    if (dis[curr][curc] != -1 && dis[curr][curc] <= curdis) continue;
                    if (mat[curr][curc] == 0) curdis = 0;
                    else curdis++;
                    dis[curr][curc] = curdis;
                    for(int i = 0; i < size(dir); i++) {
                        int nr = curr + dir[i][0], nc = curc + dir[i][1];
                        if(nr >= 0 && nr < m && nc >= 0 && nc < n) 
                            q.push({curdis, {nr, nc}});
                    }
                }
            }
        }
        return dis;
    }
};
