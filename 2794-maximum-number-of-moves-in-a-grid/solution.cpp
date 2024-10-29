typedef pair<int, int> pi;
class Solution {
public:
    int maxMoves(vector<vector<int>>& grid) {
        int moves[3][2] = {{-1, 1}, {0, 1}, {1, 1}};
        int ans = 0;
        for(int r = 0; r < grid.size(); r++){
            int x = r, y = 0;
            queue<pair<pi, int>> q; //node, dis
            bool vis[grid.size()][grid[0].size()];
            memset(vis, 0, sizeof(vis));
            q.push({{x, y}, 0});
            vis[x][y] = true;
            while(!q.empty()){
                int x1 = q.front().first.first, y1 = q.front().first.second;
                int dis = q.front().second; q.pop();
                // cout << "from " << x << " " << y << endl;
                for(int i = 0; i < 3; i++){
                    int x2 = x1 + moves[i][0], y2 = y1 + moves[i][1];
                    if(x2 >= grid.size() || y2 >= grid[0].size() || x2 < 0 || y2 < 0 || vis[x2][y2] || grid[x2][y2] <= grid[x1][y1])
                        continue;
                    vis[x2][y2] = true;
                    // cout << "visiting " << x2 << " " << y2 << endl;
                    q.push({{x2, y2}, dis + 1});
                    ans = max(ans, dis + 1);          
                }
            }
        }
        return ans;
    }
};
