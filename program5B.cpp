#include <iostream>
#include <vector>
#include <tuple>
/* Solution to program 5B
* @param n the number of paintings
* @param W the maximum width of the platform
* @param heights the heights of the paintings
* @param widths the widths of the paintings
* @return a tuple containing the number of platforms used, the optimal total height, and the number of paintings on each platform
*/
std::tuple<int, int, std::vector<int>> program5B(int n, int W, std::vector<int> heights, std::vector<int> widths){
    /************************
    * ADD YOUR CODE HERE *
    ***********************/
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
    auto result = program5B(n, W, heights, widths);

    std::cout << std::get<0>(result) << std::endl;
    std::cout << std::get<1>(result) << std::endl;
    for(int i = 0; i < std::get<0>(result); i++){
        std::cout << std::get<2>(result)[i] << std::endl;
    }
    return 0; 
}

/*
Problem Definition:
You are given n paintings, each with a height and a width. You want to display all the paintings on a platform. 
The platform has a maximum width W. You can place paintings on the platform in any order. 
However, you can only place a painting on the platform if the total width of the paintings on the platform does not exceed W. 
If the total width of the paintings on the platform exceeds W, you must start a new platform. 
The height of a platform is the height of the tallest painting on the platform. 
Your goal is to minimize the total height of the platforms used to display all the paintings because the height is the cost of it. 

 ProblemG:
 Given the heights h1...hn and the base widths w1...wn of n paintings, along with
 the width W of the display platform, nd an arrangement of the paintings on platforms
 that minimizes the total height.

 Algorithm 5: Design a (n2) time dynamic programming algorithm for solving ProblemG. Give a top-down recursive implementation of Algorithm5 using memoization.
*/