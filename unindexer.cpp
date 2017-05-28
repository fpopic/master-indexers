//
// Created by fpopic on 26.05.17..
//

#include <cstdio>
#include <chrono>
#include <map>
#include <vector>
#include <sstream>

#define likely(x)       __builtin_expect((x),1)
#define unlikely(x)     __builtin_expect((x),0)

using namespace std;

typedef chrono::high_resolution_clock Time;
typedef chrono::duration<float> fsec;

void split(const string& str, const char& del, vector<string>& tokens) {
    stringstream ss;
    ss.str(str);
    string token;
    while (getline(ss, token, del)) {
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }
}

inline bool contains(map<int, int>& map, int key) { return map.find(key) != map.end(); }

void unindexize_recommendations(string input_path, string customers_lookup_path, string items_lookup_path) {
    auto start = Time::now();

    // reading items lookup

    FILE* items_lookup_file = fopen(items_lookup_path, "r");
    map<int, int> items_lookup; // <index, id>
    int itemId, itemIndex;
    while (fscanf(items_lookup_file, "%d,%d\n", &itemId, &itemIndex) == 2) {
        items_lookup[itemIndex] = itemId;
    }
    fclose(items_lookup_file);

    // reading customers lookup

    FILE* customers_lookup_file = fopen(customers_lookup_path, "r");
    map<int, int> customers_lookup; // <index, id>
    int customerId, customerIndex;
    while (fscanf(customers_lookup_file, "%d,%d\n", &customerId, &customerIndex) == 2) {
        customers_lookup[customerIndex] = customerId;
    }
    fclose(customers_lookup_file);

    // Top k recommendations format:
    // "customerId:itemId1,itemId2,...,itemIdx" where  0 <= x <= k

    FILE* input_file = fopen(input_path.c_str(), "r");
    string output_path = input_path + ".unindexed";
    FILE* output_file = fopen(output_path.c_str(), "w+");

    string line;
    int line_number = 0;
    vector<string> parts;

    while (fscanf("%d:%[^n]", &customerIndex, line) == 2) {
        customerId = customers_lookup.at(customerIndex);
        fprintf(output_path, "%d:", customerId);

        split(line, ',', parts);
        for (int i = 0; i < parts.size(); ++i) {
            itemIndex = stoi(parts[i]);
            itemId = items_lookup.at(itemIndex);
            fprintf(output_file, "%d", itemId);
            if (i != parts.size() - 1)
                fprintf(output_file, ",");
            else
                fprintf(output_file, "\n");
        }
        parts.clear();

        if (line_number % 1000 == 0) {
            printf("Unindexing line:#%d\n", line_number);
        }
        line_number++;
    }

    printf("Output file with %d lines saved.\n", line_number);

    fclose(input_file);
    fclose(output_file);

}

int main(int argc, char* argv[]) {

    if (argc != 4) {
        printf("Wrong input args, accepting only: \"<exe> <recommendations_input> <customers_lookup_input> <items_lookup_input>\"\n");
        return -1;
    }

    unindexize_recommendations(argv[1], argv[2], argv[3]);

    return 0;
}