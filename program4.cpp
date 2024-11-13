#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <climits>

/* Solution to program 4
* @param n the number of paintings
* @param W the maximum width of the platform
* @param heights the heights of the paintings
* @param widths the widths of the paintings
* @return a tuple containing the number of platforms used, the optimal total
height, and the number of paintings on each platform
*/
std::tuple<int, int, std::vector<int>> program4(int n, int W, std::vector<int>
heights, std::vector<int> widths){
    // Initialize dp array and platforms used array
    std::vector<int> dp(n + 1, INT_MAX);
    std::vector<int> platforms(n + 1, 0);
    std::vector<int> paintings_on_platform;

    dp[0] = 0; // Base case: no paintings, no height cost

    // Dynamic programming to calculate the minimum total height
    for (int i = 1; i <= n; ++i) {
        int total_width = 0;
        int max_height = 0;

        // Iterate backwards to consider placing paintings on the same platform
        for (int j = i; j > 0; --j) {
            total_width += widths[j - 1];
            if (total_width > W) break; // Exceeded the width of the platform

            max_height = std::max(max_height, heights[j - 1]);
            if (dp[j - 1] + max_height < dp[i]) {
                dp[i] = dp[j - 1] + max_height;
                platforms[i] = j - 1; // Track where the platform starts
            }
        }
    }

    // Reconstruct the platform usage
    int current = n;
    while (current > 0) {
        int start = platforms[current];
        paintings_on_platform.push_back(current - start); // Number of paintings on this platform
        current = start;
    }

    std::reverse(paintings_on_platform.begin(), paintings_on_platform.end());

    return std::make_tuple(paintings_on_platform.size(), dp[n], paintings_on_platform);

// return std::make_tuple(0, 0, std::vector<int>()); // replace with your own result.
//return std::make_tuple(n, 0, heights);
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
    auto result = program4(n, W, heights, widths);
    std::cout << std::get<0>(result) << std::endl;
    std::cout << std::get<1>(result) << std::endl;
    for(int i = 0; i < std::get<0>(result); i++){
        std::cout << std::get<2>(result)[i] << std::endl;
    }
    return 0;
}
