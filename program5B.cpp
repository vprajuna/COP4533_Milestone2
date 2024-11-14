#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <climits>

/*
  Algorithm 5: Design a (n2) time dynamic programming algorithm for solving ProblemG. 
  Program5B Give an iterative bottom-up implementation of Algorithm5.
*/

/* Solution to program 5B
* @param n the number of paintings
* @param W the maximum width of the platform
* @param heights the heights of the paintings
* @param widths the widths of the paintings
* @return a tuple containing the number of platforms used, the optimal total height, and the number of paintings on each platform
*/
std::tuple<int, int, std::vector<int>> program5B(int n, int W, std::vector<int> heights, std::vector<int> widths){
    std::vector<int> iterativeOptimalHeight(n + 1, INT_MAX); // Initialize the optimal height array with INT_MAX
    iterativeOptimalHeight[0] = 0; // Base case

    // Calculate the sum of the widths of all paintings before i
    std::vector<int> sumOfPriorWidths(n + 1, 0); 
    for (int i = 1; i <= n; ++i){
        sumOfPriorWidths[i] = sumOfPriorWidths[i - 1] + widths[i - 1];
    }

    // Iterative approach to compute the optimal height
    for (int i = 1; i <= n; ++i){
        int currentMaxHeight = 0;

        for (int j = i; j > 0; --j){
            int totalWidth = sumOfPriorWidths[i] - sumOfPriorWidths[j - 1]; // Calculate the total width of the paintings from j to n

            if (totalWidth > W){
                break; // Total width cannot exceed W
            }

            currentMaxHeight = std::max(currentMaxHeight, heights[j - 1]); // Compare current height with previous height and update if needed
            iterativeOptimalHeight[i] = std::min(iterativeOptimalHeight[i], currentMaxHeight + iterativeOptimalHeight[j - 1]); // Update the optimal height
        }
    }

    int minHeight = iterativeOptimalHeight[n]; // Minimal height

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
            if (iterativeOptimalHeight[i] == maxHeightPlatform + iterativeOptimalHeight[j - 1]){
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
    auto result = program5B(n, W, heights, widths);

    std::cout << std::get<0>(result) << std::endl;
    std::cout << std::get<1>(result) << std::endl;
    for(int i = 0; i < std::get<0>(result); i++){
        std::cout << std::get<2>(result)[i] << std::endl;
    }
    return 0; 
}