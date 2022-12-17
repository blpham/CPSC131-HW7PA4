#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <unordered_set>

using namespace std;

class Solution {
public:
    vector<int> offsets = {0, 1, 0, -1, 0}; // offsets are used to get the coordinates of the cells surrounding the current cell
    int largestIsland(vector<vector<int>>& grid) {
        int n = grid.size();
        unordered_map<int,int> area; // map containing an island id and its area
        
        int maxArea = 0;
        int currArea = 0;
        int island_id = 2; // give each island an id to differentiate between them
        
        for(int i = 0; i < n; i++) { // iterate through entire grid
            for(int j = 0; j < n; j++) {
                if(grid[i][j] == 1) { // first find the areas of the islands already in the grid
                    calc(grid, i, j, currArea, n, island_id); // get the area of the current island
                    maxArea = max(maxArea, currArea); // compare the max area to the current area we just calculated
                    area[island_id] = currArea; // store the area into the map with its id
                    currArea = 0; // resest currArea back to 0
                    island_id++; // increase island_id so the next island will have a different id
                }
            }
        }
        
        for(int i = 0; i < n; i++) { // iterate through entire grid
            for(int j = 0; j < n; j++) {
                if(grid[i][j] == 0) { // now check the areas of the islands after changing the 0 to a 1
                    unordered_set<int> st; // create hashset to hold coordinate and id's for each offset
                    for(int k = 0; k < 4; k++) { // check each offset of the current 
                        int x = i + offsets[k];
                        int y = j + offsets[k + 1];
                        if(x < 0 || y < 0 || x >= n || y >= n || grid[x][y] == 0) // check that it's a valid coordinate
                            continue;
                        st.insert({grid[x][y]}); // put into the hashset to get id's for each offset
                    }
                    
                    int total = 1; // the total area will start at 1 to include the 0 that we include in the island
                    for(auto i : st) { // iterate through each offset of the current coordinate
                        total += area[i]; // add each value to get the area of the island
                    }
                    maxArea = max(maxArea, total); // compare that total to the current max area
                }
            }
        }
        
        return maxArea;
    }
	
	// calculate the area of the island using DFS
    void calc(vector<vector<int>>& grid, int i, int j, int& currArea, int& n, int& island_id) {
        currArea++; // increase the area by 1
        // store the island id to which the current cell belongs to
        grid[i][j] = island_id; 
        for(int k = 0; k < 4; k++) { // check each offset of the current coordinate
            int x = i + offsets[k];
            int y = j + offsets[k + 1];
            if(x < 0 || y < 0 || x >= n || y >= n || grid[x][y] != 1) // make sure the coordinate is valid
                continue;
            calc(grid, x, y, currArea, n, island_id); // recurse with the new coordinates using DFS
        }
    }
};