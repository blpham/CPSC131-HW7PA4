#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int m = grid.size();
		int n = grid[0].size();
		int area = 0;
		int offsets[] = {0, 1, 0, -1, 0}; // offsets are used to get surrounding coordinates
        for (int i = 0; i < m; i++) { // iterate through each coordinate in the grid
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) { // only check the existing islands (if the coordinate value is 1)
                    int a = 1; // area of the current island (starting at 1 to include the first coordinate)
                    grid[i][j] = 0; // change to 0 to keep track of coordinates we've already checked
                    queue<pair<int, int>> todo; // create queue of pairs to hold the coordinates 
                    todo.push({i, j}); // add the current coordinates to the queue
                    while (!todo.empty()) {
                        pair<int, int> p = todo.front(); // create a pair containing the x, y coordinates of the current
                        todo.pop(); // remove from the queue so we don't check it again
                        for (int k = 0; k < 4; k++) { // check all 4 directions around the curr coordinate
                            int r = p.first + offsets[k]; // change the x coordinate by the offset
							int c = p.second + offsets[k + 1]; // change the y coordinate by the offset
                            if (r >= 0 && r < m && c >= 0 && c < n && grid[r][c]) { // check if it is valid
                                grid[r][c] = 0; // change to 0 to tell that it's already been checked
                                a++; // increase area by 1
                                todo.push({r, c}); // push new offset coordinates into the queue to check its surrounding coordinates
                            }
                        }
                    }
                    area = max(area, a); // set the area to the max between the current max area and the new area just calculated
                }
            }
        }
        return area;
    }
};