typedef pair<int, int> pi;

class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        vector<vector<bool>> vis(image.size(), vector<bool>(image[0].size(), false));
        queue<pi> q;
        q.push({sr, sc});
        int og = image[sr][sc];
        while(!q.empty()) {
            pi coords = q.front();
            q.pop();
            if (vis[coords.first][coords.second]) continue;
            vis[coords.first][coords.second] = true;
            image[coords.first][coords.second] = color;
            for(int i = 0; i < 4; i++) {
                int nx = coords.first + dirs[i][0];
                int ny = coords.second + dirs[i][1];
                if (nx >= 0 && nx < image.size() && ny >= 0 && ny < image[0].size() && image[nx][ny] == og) {
                    q.push({nx, ny});
                }
            }
        }
        return image;
    }
};
