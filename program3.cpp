#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <unordered_map>
#include <string>
using namespace std;

// helper func for memoization key
string make_key(int index, int current_width) {
    return to_string(index) + "," + to_string(current_width);
}

// recursive function to  help calc the min cost with memoization
int min_height_cost(int index, int current_width, int current_height, const vector<int>& heights,
                    const vector<int>& widths, int W, std::unordered_map<string, int>& memo) {
    if (index == heights.size()) {
        return current_height; // if index is size of heights, all sculptures have been placed
    }

    string key = make_key(index, current_width);
    if (memo.find(key) != memo.end()) {
        return memo[key]; // if memo has been generated, then the computed cost exists for this config. so return stored res
    }

    int cost_with_current = INT_MAX;
    if (current_width + widths[index] <= W) { // if sculpture does not exceed W add to platform. update variables accordingly, call min_height_cost (recursively) to update for next increment index
        cost_with_current = min_height_cost(index + 1, current_width + widths[index],
                                            max(current_height, heights[index]),
                                            heights, widths, W, memo);
    }

    // starting a new platform with current sculpture
    // adds current_height to existing platform, finalize, start new. reset current_width / current_height to height/w of sculp
    // recursive call min_height_cost for next sculpture
    int cost_with_new_platform = current_height + min_height_cost(index + 1, widths[index],
                                                                  heights[index], heights, widths, W, memo);

    // store minimum of two options and return (stored in memo)
    memo[key] = min(cost_with_current, cost_with_new_platform);
    return memo[key];

}

tuple<int, int, vector<int>> program3(int n, int W, vector<int> heights, vector<int> widths) {
    unordered_map<string, int> memo; // stores computed results
    int min_cost = min_height_cost(0, 0, 0, heights, widths, W, memo); // set to 0
    int num_platforms = 0;
    vector<int> sculptures;
    int current_width = 0, max_height = 0, num_sculptures = 0;

    // loop over each sculpture to decide if it fits on current platform. if adding and it exceeds W, start new platform
    for (int i = 0; i < n; ++i) {
        if (current_width + widths[i] > W) {
            sculptures.push_back(num_sculptures);
            num_platforms++;
            current_width = 0;
            max_height = 0;
            num_sculptures = 0;
        }

        // add width of curr sculpture to curr width
        // update max height to tallest platform
        // max func. compares max_height with current sculpture and will swap if current is taller
        current_width += widths[i];
        max_height = max(max_height, heights[i]);
        num_sculptures++;
    }
    // each time new platform starts, count is pushed to sculptures
    sculptures.push_back(num_sculptures);
    num_platforms++;

    // returns tuple with nm platforms, min cost, and the count of sculptures on each platform
    return make_tuple(num_platforms, min_cost, sculptures);
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
