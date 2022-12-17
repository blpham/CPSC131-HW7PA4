#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int largestIsland(vector<vector<int>> grid) {
        int n = grid.size();
        int largest = dfs(grid, 0, 0, new vector<vector<bool>> visited);
        for (int i = 0; i < n; i++) { // iterate through each cell in grid
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0) { // check all 0's in the grid
                    grid[i][j] = 1; // change the value to a 1
                    largest = max(largest, dfs(grid, i, j, new vector<vector<bool>> visited)); // find the max between the current largest and use dfs to check every possible island
                    grid[i][j] = 0; // change the value back to a 0
                }
            }
        }
        return largest;
    }

private:
    int dfs(vector<vector<int>> grid, int x, int y, vector<vector<bool>> visited) {
        if(x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size() || grid[x][y] == 0 || visited[x][y]) { // check if it is a valid coordinate
            return 0;
        }
        visited[x][y] = true; // mark whether or not the coordinate has been visited
        return 1 + dfs(grid, x + 1, y, visited) + // recurse
            dfs(grid, x - 1, y, visited) +        // check the coordinates around the current coordinate
            dfs(grid, x, y + 1, visited) +        // and add them together to get the size of the island
            dfs(grid, x, y - 1, visited);
    }
};