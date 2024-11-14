#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <climits>
using namespace std;

// helper func to make unique key for memoization
string make_key(int index, int current_width, int current_height) {
    return to_string(index) + "," + to_string(current_width) + "," + to_string(current_height);
}

// recursive function to calculate the cost of min.
int min_cost(int index, int current_width, int current_height, const vector<int>& heights,
             const vector<int>& widths, int W, unordered_map<string, int>& memo,
             unordered_map<string, bool>& start_new_platform) {
    if (index == heights.size()) {
        // base case all have been placed
        return current_height;
    }

    // unique key to identify the current state of the platform
    string key = make_key(index, current_width, current_height);
    if (memo.find(key) != memo.end()) {
        // return cached if not avail
        return memo[key];
    }

    // add current sculpture to the current platform if width
    int cost_with_current = INT_MAX;
    if (current_width + widths[index] <= W) {
        cost_with_current = min_cost(index + 1, current_width + widths[index],
                                     max(current_height, heights[index]),
                                     heights, widths, W, memo, start_new_platform);
    }

    // start a new platform with the current sculpture
    int cost_with_new_platform = current_height + min_cost(index + 1, widths[index],
                                                           heights[index], heights, widths, W, memo, start_new_platform);

    // store the minimum of the two options in memo and return it
    if (cost_with_new_platform < cost_with_current) {
        memo[key] = cost_with_new_platform;
        // new platfor mehre
        start_new_platform[key] = true;
    } else {
        memo[key] = cost_with_current;
        // new platform nto here
        start_new_platform[key] = false;
    }

    return memo[key];
}

// anmother. helper function to reconstruct platforms based on the memoized decisions
vector<int> reconstruct_platforms(int n, int W, const vector<int>& heights, const vector<int>& widths,
                                  const unordered_map<string, bool>& start_new_platform) {
    vector<int> platforms;
    int current_width = 0;
    int num_sculptures = 0;
    int current_height = 0;

    for (int i = 0; i < n; ++i) {
        // use the same key construction to check memoized decisions
        string key = make_key(i, current_width, current_height);

        if (i > 0 && start_new_platform.at(key)) {
            // a new platform starts here and then finalize the prev.
            platforms.push_back(num_sculptures);
            current_width = 0;
            num_sculptures = 0;
            current_height = 0;
        }

        // add the current sculpture to the current platform
        current_width += widths[i];
        current_height = max(current_height, heights[i]);
        num_sculptures++;
    }

    // add the last platform if there are any left
    if (num_sculptures > 0) {
        platforms.push_back(num_sculptures);
    }

    return platforms;
}

// main function to execute the solution. finally
tuple<int, int, vector<int>> program3(int n, int W, const vector<int>& heights, const vector<int>& widths) {
    unordered_map<string, int> memo;
    unordered_map<string, bool> start_new_platform;

    // compute the minimum cost using the recursive function
    int min_cost_value = min_cost(0, 0, 0, heights, widths, W, memo, start_new_platform);

    // reconstruct the platforms based on memoized decisions
    vector<int> platforms = reconstruct_platforms(n, W, heights, widths, start_new_platform);

    // return the tuple with the ## of platforms, min cost, and the sculpture count on each platform
    return make_tuple(platforms.size(), min_cost_value, platforms);
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
    auto result = program3(n, W, heights, widths);
    std::cout << std::get<0>(result) << std::endl;
    std::cout << std::get<1>(result) << std::endl;
    for(int i = 0; i < std::get<0>(result); i++){
        std::cout << std::get<2>(result)[i] << std::endl;
    }
    return 0;
}

