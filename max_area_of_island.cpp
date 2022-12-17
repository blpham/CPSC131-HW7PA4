#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    void dfs(int x, int y, vector<vector<int>>& v, vector<vector<int>>& grid, int& cnt) {
		cnt++;
		v[x][y] = 1;
		if (x > 0 && grid[x - 1][y] == 1 && !v[x - 1][y]) {
			dfs(x - 1, y, v, grid, cnt);
		}
		if (y > 0 && grid[x][y - 1]==1 && !v[x][y - 1]) {
			dfs(x, y - 1, v, grid, cnt);
		}
		if (x < grid.size() - 1 && grid[x + 1][y]==1 && !v[x + 1][y]) {
			dfs(x + 1, y, v, grid, cnt);
		}
		if (y < grid[0].size() - 1 && grid[x][y + 1] == 1 && !v[x][y + 1]) {
		    dfs(x, y + 1, v, grid, cnt);
		}
	}
	int maxAreaOfIsland(vector<vector<int>>& grid) {
		vector<vector<int>>v(grid.size(), vector<int>(grid[0].size(), 0));
		int maxi = 0;
		for (int i = 0; i < grid.size(); i++) {
			for (int j = 0; j < grid[0].size(); j++) {
				if (!v[i][j] && grid[i][j] == 1) {
					int cnt = 0;
					dfs(i, j, v, grid, cnt);
                    v[i][j] = 1;
					maxi = max(maxi, cnt);
				}
			}
		}
		return maxi;
	}
};

class Solution
{
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int maxArea = 0;
        for (int i = 0; i < m; i++) { // traverse through all rows
            for (int j = 0; j < n; j++) { // traverse through all columns
                if (1 == grid[i][j]) { // if grid value at this index is 1 (start of an island) start a BFS to find the size
                    maxArea = max(maxArea, bfs(grid, i, j));
                }
            }
        }
        return maxArea;
    }
private:
    int bfs(vector<vector<int>>& grid, int i, int j) {
        queue<pair<int, int>> q;
        q.push(pair<int, int>(i, j));
        int maxArea = 1;
        grid[i][j] = 0; // mark the value to avoid duplication
        vector<int> dir({-1, 0, 1, 0, -1});
        while (0 < q.size()) {
            int m = q.front().first; // row index
            int n = q.front().second; // col index
            q.pop(); // remove from queue
            for (int idx = 0; idx < dir.size() - 1; idx++) {
                int rowIdx = m + dir[idx];
                int colIdx = n + dir[idx + 1];
                if (0<=rowIdx && rowIdx<grid.size() && 0<=colIdx && colIdx<grid[0].size()
                    && 1==grid[rowIdx][colIdx]) {
                    q.push(pair<int, int>(rowIdx, colIdx));
                    maxArea++;
                    grid[rowIdx][colIdx] = 0;
                }
            }
        }
        return maxArea;
    }
};