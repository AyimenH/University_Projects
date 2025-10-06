import random
import json
import os

def generate_dataset(size, profit_range=(1, 100), weight_range=(1, 50)):
    profits = [random.randint(profit_range[0], profit_range[1]) for _ in range(size)]
    weights = [random.randint(weight_range[0], weight_range[1]) for _ in range(size)]

    # Calculate a capacity between 30 and 70% of total weight
    total_weight = sum(weights)
    capacity = random.randint(int(total_weight * 0.3), int(total_weight * 0.7))

    return {
        "size": size,
        "profits": profits,
        "weights": weights,
        "capacity": capacity,
        "profit_range": profit_range,
        "weight_range": weight_range
    }

def generate_datasets():
    random.seed(42) # To make data consistently provide the same values when rerunning code

    #Modify datasets here!

    # First delete the original DataSet folder and contents
    # Next Modify the size and ranges
    # Next run “python knapsack_data_generator.py” in the Terminal
    # Finally run the program with your new data!

    datasets = {
        "small": generate_dataset(
            size = 5,
            profit_range = (5, 50),
            weight_range = (1, 20)
        ),
        "medium": generate_dataset(
            size = 25,
            profit_range = (20, 150),
            weight_range = (5, 50)
        ),
        "large": generate_dataset(
            size = 50,
            profit_range = (50, 300),
            weight_range = (10, 100)
        )
    }

    return datasets

# Converting to header file to import and read from main
def save_datasets(datasets, output_dir="knapsack_data"):
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    with open(f"{output_dir}/datasets.json", 'w') as f:
        json.dump(datasets, f, indent = 2)


    cpp_content = """#ifndef KNAPSACK_DATA_H
#define KNAPSACK_DATA_H

// Auto-generated test data for knapsack problem

namespace test_data {
"""

    for dataset_name, data in datasets.items():
        cpp_content += f"""
    // {dataset_name.capitalize()} dataset
    namespace {dataset_name} {{
        const int SIZE = {data['size']};
        const int CAPACITY = {data['capacity']};
        
        const int profits[SIZE] = {{{', '.join(map(str, data['profits']))}}};
        const int weights[SIZE] = {{{', '.join(map(str, data['weights']))}}};
    }}
"""

    cpp_content += "} // namespace test_data\n\n#endif // KNAPSACK_DATA_H"

    with open(f"{output_dir}/knapsack_data.h", 'w') as f:
        f.write(cpp_content)

def main():
    datasets = generate_datasets()
    save_datasets(datasets)

    print("Generated datasets summary:")
    for name, data in datasets.items():
        print(f"\n{name.upper()} Dataset:")
        print(f"Size: {data['size']} items")
        print(f"Capacity: {data['capacity']}")
        print(f"Total weight: {sum(data['weights'])}")
        print(f"Total potential profit: {sum(data['profits'])}")
        print(f"Profit range: {data['profit_range']}")
        print(f"Weight range: {data['weight_range']}")

if __name__ == "__main__":
    main()