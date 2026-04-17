typedef pair<int, int> pi;
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        int n = grid.size(), m = grid[0].size();
        queue<pi> q;
        int cnt = 0;
        for(int r = 0; r < n; r++) {
            for(int c = 0; c < m; c++) {
                if (grid[r][c] != '1') continue;
                cnt++;
                q.push({r, c});
                while(!q.empty()) {
                    pi cur = q.front(); q.pop();
                    int a = cur.first, b = cur.second;
                    if (grid[a][b] == '0') continue;
                    grid[a][b] = '0';
                    for(int i = 0; i < 4; i++) {
                        int na = a + dir[i][0], nb = b + dir[i][1];
                        if(na >= 0 && na < n && nb >= 0 && nb < m && grid[na][nb] == '1')
                            q.push({na, nb});
                    }
                }
            }
        }
        return cnt;
    }
};
