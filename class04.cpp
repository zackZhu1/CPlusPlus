//
// Created by Jiawen Zhu on 11/4/18.
//

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <set>
using namespace std;

// unordered_set example
int someFunction(const vector<int>& input) {
    unordered_set<int> set;
    for (int i : input) {
        set.insert(i);
    }
    return set.size();
}


class Car {
public:
    Car(int price) {
        price_ = price;
    }
    int price() const {
        return price_;
    }
private:
    int price_;
};
// unordered_map example
class CarInventory {
public:
    CarInventory() {}

    void AddCar(int car_id, int price) {
        inventory_[car_id] = Car(price);
    }

    int CheckPrice(int car_id) const {
        if (inventory_.count(car_id) > 0) {
            return inventory_.at(car_id).price();
        }
        return 0;
    }

private:
    unordered_map<int, Car> inventory_;
};

void PrintUnique(const vector<int>& sorted_array) {
    unordered_set<int> sorted_unique;
    for (int i : sorted_array) {
        sorted_unique.insert(i);
    }
    for (int i : sorted_unique) {
        cout << i << " ";
    }
    cout << "\n";
}

void PrintSortedUnique(const vector<int>& sorted_array) {
    set<int> sorted_unique;
    for (int i : sorted_array) {
        sorted_unique.insert(i);
    }
    for (int i : sorted_unique) {
        cout << i << " ";
    }
    cout << "\n";
}



int main() {
//    vector<int> vector = {3, 4, 5};
//    int* first_element_ptr = &vector[0];
//    cout << *first_element_ptr << endl;
//    for (int i = 0; i < 100; i++) {
//        vector.push_back(i);
//    }
//    cout << *first_element_ptr << endl; // segment fault

    vector<int> input = {1, 1, 2, 3};
    cout << someFunction(input) << endl;
    PrintUnique(input);
    PrintSortedUnique(input);
}