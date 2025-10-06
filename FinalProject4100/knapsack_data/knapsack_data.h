#ifndef KNAPSACK_DATA_H
#define KNAPSACK_DATA_H

// Auto-generated test data for knapsack problem

namespace test_data {

    // Small dataset
    namespace small {
        const int SIZE = 5;
        const int CAPACITY = 24;
        
        const int profits[SIZE] = {45, 12, 6, 22, 20};
        const int weights[SIZE] = {8, 5, 4, 18, 3};
    }

    // Medium dataset
    namespace medium {
        const int SIZE = 25;
        const int CAPACITY = 390;
        
        const int profits[SIZE] = {28, 27, 43, 75, 79, 149, 26, 70, 127, 76, 134, 91, 21, 60, 128, 107, 91, 59, 75, 106, 46, 43, 117, 44, 111};
        const int weights[SIZE] = {27, 43, 21, 7, 34, 39, 12, 29, 10, 40, 23, 45, 44, 28, 41, 17, 50, 9, 7, 47, 19, 23, 10, 19, 11};
    }

    // Large dataset
    namespace large {
        const int SIZE = 50;
        const int CAPACITY = 1756;
        
        const int profits[SIZE] = {121, 166, 212, 263, 143, 91, 144, 140, 103, 221, 118, 229, 289, 224, 215, 68, 205, 212, 93, 186, 236, 112, 91, 168, 147, 119, 286, 213, 226, 192, 106, 225, 133, 265, 246, 248, 64, 108, 260, 58, 256, 130, 152, 118, 66, 104, 283, 291, 195, 274};
        const int weights[SIZE] = {50, 37, 93, 73, 60, 92, 68, 28, 43, 27, 41, 81, 78, 43, 84, 64, 84, 61, 56, 38, 27, 75, 73, 21, 16, 24, 29, 90, 30, 97, 64, 86, 18, 59, 58, 86, 69, 77, 42, 80, 11, 97, 24, 97, 78, 44, 92, 53, 24, 47};
    }
} // namespace test_data

#endif // KNAPSACK_DATA_H