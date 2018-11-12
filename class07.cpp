//
// Created by Jiawen Zhu on 11/11/18.
//
#include <iostream>
#include <vector>
#include <numeric> // std::accumulate
#include <iterator>
#include <algorithm>
#include <unordered_map>
#include <functional>
using namespace std;

// 07_01
double GetAverage(const std::vector<int>& nums) {
    int sum = 0;
    for (int i = 0; i < nums.size(); i++) {
        sum += nums[i];
    }
    return static_cast<double>(sum) / nums.size();
}

// use range based for loop
double GetAverage2(const std::vector<int>& nums) {
    int sum = 0;
    for (const auto& num : nums) {
        sum += num;
    }
    return static_cast<double>(sum) / nums.size();
}

// use stl algorithm
double GetAverage3(const std::vector<int>& nums) {
    // return std::accumulate(begin(nums), end(nums), 0.0) / nums.size();
    return std::accumulate(nums.begin(), nums.end(), 0.0) / nums.size();
}

// 07_02
template<typename Iter>
double GetAverage4(Iter begin, Iter end) {
    return std::accumulate(begin, end, 0.0) / std::distance(begin, end);
}

// 07_03
int firstOccur(const std::vector<int>& A, int target) {
    int l = 0, r = A.size(), m;
    while (l + 1 < r) {
        m = l + (r - l) / 2;
        if (A[m] >= target) {
            r = m;
        } else {
            l = m;
        }
    }

    if (A[l] == target) {
        return l;
    } else if (A[r] == target) {
        return r;
    }
    return -1;
}

int firstOccur2(const std::vector<int>& A, int target) {
    auto it = std::lower_bound(A.cbegin(), A.cend(), target);
    return it == A.cend() || *it != target ? -1 : it - A.cbegin();
}

// 07_04 find the number of occurrence of a target in a vector
int findOccurrence(const std::vector<int>& v, int target) {
    return std::upper_bound(v.begin(), v.end(), target) - std::lower_bound(v.begin(), v.end(), target);
}

// 07_05
void rotate() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto p = std::rotate(begin(v), begin(v) + 2, end(v));
    std::cout << (*p == 1) << std::endl;
}


// print a vector ???
void printVector(std::vector<int>* v) {
    for (auto iter = v->begin(); iter != v->end(); ++iter) {
        std::cout << *iter;
    }
    std::cout << std::endl;
}

// 07_06  insertion sort
void InsertionSort(std::vector<int>* v) {
    for (auto iter = v->begin(); iter != v->end(); ++iter) {
        std::rotate(std::lower_bound(v->begin(), iter, *iter), iter, iter + 1);
    }
    printVector(v);
}

// 07_07 selection sort
void SelectionSort(std::vector<int>* v) {
    for (auto iter = v->begin(); iter != v->end(); ++iter) {
        std::rotate(iter, std::min_element(iter, v->end()), v->end());
        // printVector(v);
    }
}

class Car {};

class Civic : public Car {};

class TeslaModelS : public Car {};

class CarreraGT : public Car {};

// 07_08 function pointer
Car* BuyCar(int budget) {
    if (budget >= 750000) {
        return new CarreraGT();
    } else if (budget >= 800000) {
        return new TeslaModelS();
    } else {
        return new Civic();
    }
}

Car* BuyLuxuryCarOrNull(int budget) {
    if (budget >= 750000) {
        return new CarreraGT();
    } else if (budget >= 800000) {
        return new TeslaModelS();
    }
    return nullptr;
}

std::unique_ptr<Car> GetCar(int budget, const std::string& buyer, Car*(*buy_strategy)(int)) {
    Car* my_car = (*buy_strategy)(budget); // make the function call
    if (my_car == nullptr) {
        return nullptr;
    } else {
        return std::unique_ptr<Car>(my_car);
    }
}

// 07_09 functor
struct Person {
    std::string first_name, last_name;
};

std::ostream& operator<<(std::ostream& out, const Person& person) {
    return out << "{ " << person.first_name << ", " << person.last_name << " }";
}

bool isNameLengthLessThenFive(const Person& person) {
    return person.last_name.length() < 5;
}

// 07_10 functor with more flexibility
class IsLastNameLengthLessThenGivenLength {
public:
    explicit IsLastNameLengthLessThenGivenLength(int max_length) : max_length_(max_length) {}
    // overload operator function
    bool operator() (const Person& person) const {
        return person.last_name.length() < max_length_;
    }
private:
    int max_length_;
};

// 07_11 lambda expression
void lambdaExample() {
    std::vector<Person> persons = {{"Gabriel", "Gabriel"}, {"Laioffer", "Leo"}, {"Laioffer", "Yan"}};
    std::sort(persons.begin(), persons.end(),
            [](const Person& lhs, const Person& rhs) -> bool {
                return lhs.last_name < rhs.last_name;
            });
    for (const auto& person : persons) {
        std::cout << person << std::endl;
    }
}

// 07_12 std::function
bool CompareByFirstName(const Person& lhs, const Person& rhs) {
    return lhs.first_name < rhs.first_name;
}

void stdFunctionExample() {
    std::unordered_map<std::string, std::function<bool(const Person&, const Person&)>> comparision_strategies = {
            {"ByFirstName", CompareByFirstName},
            {"ByLastName", [](const Person& lhs, const Person& rhs) -> bool {
                return lhs.last_name < rhs.last_name;
            }}
    };

    std::vector<Person> persons = {{"Gabriel", "Gabriel"}, {"Laioffer", "Leo"}, {"Laioffer", "Yan"}};
    std::sort(persons.begin(), persons.end(), comparision_strategies["ByLastName"]);
    for (const auto& person : persons) {
        std::cout << person << std::endl;
    }
    std::cout << "---------------------" << std::endl;
    std::sort(persons.begin(), persons.end(), comparision_strategies["ByFirstName"]);
    for (const auto& person : persons) {
        std::cout << person << std::endl;
    }
}


int main() {
    std::vector<int> v1 = {1, 100, 4 ,23};
    std::cout << GetAverage4(std::begin(v1), std::end(v1)) << std::endl;
    int array[] = {3, 1, 6, 5};
    std::cout << GetAverage4(std::begin(array), std::end(array)) << std::endl;

    std::vector<int> v2 = {1, 2, 2, 3, 3, 4, 5};
    std::cout << firstOccur2(v2, 3) << std::endl;
    std::cout << findOccurrence(v2, 3) << std::endl;

    rotate();

    std::vector<int> v3 = {1, 5, 4, 3, 2};
    InsertionSort(&v3);

    std::vector<int> v4 = {1, 5, 4, 3, 2};
    SelectionSort(&v4);

    std::unique_ptr<Car> car = std::move(GetCar(800000, "Li Lu", BuyLuxuryCarOrNull));

    std::vector<Person> persons = {{"Gabriel", "Gabriel"}, {"Laioffer", "Leo"}, {"Laioffer", "Yan"}};
    std::cout << *std::find_if(persons.begin(), persons.end(), isNameLengthLessThenFive) << std::endl;

    std::cout << *std::find_if(persons.begin(), persons.end(), IsLastNameLengthLessThenGivenLength(5)) << std::endl;

    lambdaExample();

    stdFunctionExample();
}
