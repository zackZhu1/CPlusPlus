//
// Created by Jiawen Zhu on 11/5/18.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

// Q1: Find smallest k elements from an unsorted array of size n
// solution1: sort
vector<int> FindSmallest1(vector<int>& nums, int k) {
    sort(nums.begin(), nums.end());
    return {nums.begin(), nums.begin() + k};
}

// solution2: minHeap
vector<int> FindSmallest2(const vector<int>& nums, int k) {
    priority_queue<int, vector<int>, greater<int>> minHeap(nums.begin(), nums.end());
    vector<int> results;
    results.reserve(k);
    while (k--) {
        results.push_back(minHeap.top());
        minHeap.pop();
    }
    return results;
}

// solution3: maxHeap
vector<int> FindSmallest3(const vector<int>& nums, int k) {
    priority_queue<int> maxHeap(nums.begin(), nums.begin() + k);
    vector<int> results;
    results.reserve(k);
    for (auto it = nums.begin() + k; it < nums.end(); ++it) {
        if (maxHeap.top() < *it) {
            continue;
        }
        maxHeap.pop();
        maxHeap.push(*it);
    }

    while (k--) {
        results.push_back(maxHeap.top());
        maxHeap.pop();
    }
    return results;
}


void PrintVector(const vector<int>& v) {
    cout << "{";
    for (int i : v) {
        cout << i << " ";
    }
    cout << "}" << endl;
}

int main() {
    vector<int> v = {5, 2, 3, 1, 4};
    // solution4: std::stable_partition
    // stable_partition(v.begin(), v.begin() + 3, v.end());

    PrintVector(FindSmallest2(v, 3));
    return 0;
}