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
std::tuple<int, int, std::vector<int>> program5A(int n, int W, std::vector<int> heights, std::vector<int> widths){
    
    if(n == 0){ // Base case
        return std::make_tuple(0, 0, std::vector<int>());
    }

    if(memoArray[n] != -1){ // If the value is already computed, return it
        return std::make_tuple(memoArray[n], 0, std::vector<int>());
    }

    int minHeight = INT_MAX; 
    int currentMaxHeight = 0;

    // Loop through the paintings to find the optimal height
    for (int j = n; j > 0; --j){
        int totalWidth = sumOfPriorWidths[n] - sumOfPriorWidths[j - 1]; // Calculate the total width of the paintings from j to n

        if (totalWidth > W){ 
            break; // Total width cannot exceed W
        }

        currentMaxHeight = std::max(currentMaxHeight, heights[j - 1]); // Compare current height with previous height and update if needed
        int heightOfCurrentPartition = currentMaxHeight + std::get<1>(program5A(j - 1, W, heights, widths)); // Calculate the height of the current partition
        


    }


    
//    return std::make_tuple(0, 0, std::vector<int>()); // replace with your own result.
    return std::make_tuple(n, 0, heights);
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