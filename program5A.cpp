#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <climits>

/*
 Algorithm 5: Design a (n2) time dynamic programming algorithm for solving ProblemG. 
 Give a top-down recursive implementation of Algorithm5 using memoization.
*/

/* Solution to program 5A
* @param n the number of paintings
* @param W the maximum width of the platform
* @param heights the heights of the paintings
* @param widths the widths of the paintings
* @return a tuple containing the number of platforms used, the optimal total height, and the number of paintings on each platform
*/

std::vector<int> sumOfPriorWidths; // Sum of the widths of the paintings from 0 to i
std::vector<int> memoArray; // Memoization array

// Recursive function to compute the optimal height using memoization
int recursiveOptimalHeight(int n, int W, std::vector<int> heights, std::vector<int> widths){
    if(n == 0){ // Base case
        return 0;
    }

    if(memoArray[n] != -1){ // If the value is already computed, return it
        return memoArray[n];
    }

    int minHeight = INT_MAX; // Minimal height
    int currentMaxHeight = 0;

    // Loop through the paintings to find the optimal height
    for (int j = n; j > 0; --j){
        int totalWidth = sumOfPriorWidths[n] - sumOfPriorWidths[j - 1]; // Calculate the total width of the paintings from j to n

        if (totalWidth > W){ 
            break; // Total width cannot exceed W
        }

        currentMaxHeight = std::max(currentMaxHeight, heights[j - 1]); // Compare current height with previous height and update if needed
        int heightOfCurrentPartition = currentMaxHeight + recursiveOptimalHeight(j - 1, W, heights, widths); // Calculate the height of the current partition
        minHeight = std::min(minHeight, heightOfCurrentPartition); // Update the minimal height
    }

    memoArray[n] = minHeight; // Store the minimal height in the memoization array
    return minHeight;
}

// Main function 
std::tuple<int, int, std::vector<int>> program5A(int n, int W, std::vector<int> heights, std::vector<int> widths){
    memoArray.assign(n + 1, -1); 
    sumOfPriorWidths.assign(n + 1, 0); 

    // Calculate the sum of the widths of all paintings before i
    for (int i = 1; i <= n; ++i){
        sumOfPriorWidths[i] = sumOfPriorWidths[i - 1] + widths[i - 1];
    }

    int minHeight = recursiveOptimalHeight(n, W, heights, widths); // Call recursive function 

    std::vector<int> resultingPlatforms; 
    
    int i = n; 
    while (i > 0){
        int maxHeightPlatform = 0;
        for (int j = i; j > 0; --j){
            int totalWidth = sumOfPriorWidths[i] - sumOfPriorWidths[j - 1]; // Calculate the total width of the paintings from j to n

            if (totalWidth > W){
                break; // Total width cannot exceed W
            }

            maxHeightPlatform = std::max(maxHeightPlatform, heights[j - 1]); // Compare current height with previous height and update if needed
            // Group paintings into platforms based on the minimal height
            if (recursiveOptimalHeight(i, W, heights, widths) == maxHeightPlatform + recursiveOptimalHeight(j - 1, W, heights, widths)){
                resultingPlatforms.push_back(i - j + 1);
                i = j - 1;
                break;
            }
        }
    }
    std::reverse(resultingPlatforms.begin(), resultingPlatforms.end());
    return std::make_tuple(resultingPlatforms.size(), minHeight, resultingPlatforms);
}
int main(){
    int n, W;
    std::cin >> n >> W;
    std::vector<int> heights(n);
    std::vector<int> widths(n);
    for(int i = 0; i < n; i++){
        std::cin >> heights[i];
    }
    for(int i = 0; i < n; i++){
        std::cin >> widths[i];
    }
    auto result = program5A(n, W, heights, widths);

    std::cout << std::get<0>(result) << std::endl;
    std::cout << std::get<1>(result) << std::endl;
    for(int i = 0; i < std::get<0>(result); i++){
        std::cout << std::get<2>(result)[i] << std::endl;
    }
    return 0; 
}