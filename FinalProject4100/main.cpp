#include <iostream>
#include <algorithm>
#include <chrono>
#include <functional>
#include <iomanip>
#include <numeric>
#include <vector>

#include "knapsack_data/knapsack_data.h"
using namespace std;
using namespace std::chrono;

// Struct for Greedy Algorithm
struct Item
{
    int profit;
    int weight;
    double ratio;
    int index;
};

// For Greedy Custom Sort
bool compareByRatio(Item a, Item b)
{
    return a.ratio > b.ratio;
}

// Pure Recursive Knapsack Solution based on Geeks for Geeks
int knapSackRecursive(const vector<int>& val, const vector<int>& wt, int W, int n)
{
    if (n == 0 || W == 0)    // Base Case
        return 0;

    if (wt[n - 1] > W)
        return knapSackRecursive(val, wt, W, n - 1);

    return max(knapSackRecursive(val, wt, W, n - 1),    // included
               val[n - 1] + knapSackRecursive(val, wt, W - wt[n - 1], n - 1));    // not included
}

// Greedy Heuristic based on Heuristic paper Algorithm 1
int knapSackGreedy(const vector<int>& profits, const vector<int>& weights, int capacity)
{
    vector<Item> items(profits.size());
    for(size_t i = 0; i < profits.size(); i++)
    {
        items[i].profit = profits[i];
        items[i].weight = weights[i];
        items[i].ratio = (double)profits[i] / weights[i];
        items[i].index = i;
    }

    sort(items.begin(), items.end(), compareByRatio);

    int totalWeight = 0;
    int totalProfit = 0;

    for(const auto& item : items)
    {
        if(totalWeight + item.weight <= capacity)
        {
            totalWeight += item.weight;
            totalProfit += item.profit;
        }
    }

    return totalProfit;
}

void runTest(const char* datasetName, const vector<int>& profits, const vector<int>& weights, int capacity)
{
    cout << "\nTesting " << datasetName << " dataset:" << endl;
    cout << "Size: " << profits.size() << " items, Capacity: " << capacity << endl;

    cout << "Total available weight: " << accumulate(weights.begin(), weights.end(), 0) << endl;
    cout << "Total available profit: " << accumulate(profits.begin(), profits.end(), 0) << endl;

    // Test Greedy Algorithm
    auto start = high_resolution_clock::now();
    int greedyProfit = knapSackGreedy(profits, weights, capacity);

    auto stop = high_resolution_clock::now();
    auto greedyDuration = duration_cast<microseconds>(stop - start);

    cout << "\nGreedy Algorithm:" << endl;
    cout << "Profit: " << greedyProfit << endl;
    cout << "Time: " << fixed << setprecision(6) << (greedyDuration.count() / 1000000.0) << " seconds" << endl;

    // Test Recursive Algorithim
    start = high_resolution_clock::now();
    int recursiveProfit = knapSackRecursive(profits, weights, capacity, profits.size());

    stop = high_resolution_clock::now();
    auto recursiveDuration = duration_cast<microseconds>(stop - start);

    cout << "\nDynamic Programming Algorithm:" << endl;
    cout << "Profit: " << recursiveProfit << endl;
    cout << "Time: " << fixed << setprecision(6) << (recursiveDuration.count() / 1000000.0) << " seconds" << endl;

    cout << "\n----------------------------------------" << endl;
}

int main()
{
    cout << "Knapsack Problem Algorithm Comparison" << endl;
    cout << "=====================================" << endl;

    vector smallProfits(test_data::small::profits, test_data::small::profits + test_data::small::SIZE);
    vector smallWeights(test_data::small::weights, test_data::small::weights + test_data::small::SIZE);

    vector mediumProfits(test_data::medium::profits, test_data::medium::profits + test_data::medium::SIZE);
    vector mediumWeights(test_data::medium::weights, test_data::medium::weights + test_data::medium::SIZE);

    vector largeProfits(test_data::large::profits, test_data::large::profits + test_data::large::SIZE);
    vector largeWeights(test_data::large::weights, test_data::large::weights + test_data::large::SIZE);

    runTest("Small", smallProfits, smallWeights, test_data::small::CAPACITY);
    runTest("Medium", mediumProfits, mediumWeights, test_data::medium::CAPACITY);
    runTest("Large", largeProfits, largeWeights, test_data::large::CAPACITY);

    return 0;
}