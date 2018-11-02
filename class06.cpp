//
// Created by Jiawen Zhu on 11/1/18.
//

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// global integer has static storage duration

int global_integer = 10;

int& GetAnotherGlobalInteger() {
    // a locally defined static variable also has static storage duration
    static int another_global_integer = 100;
    return another_global_integer;
}

// it will be zero initialized during link time
int not_explicitely_initialized_global_integer;


class Car {
public:
    Car(int price) {
        price_ = price;
        cout << "Ctor is called" << endl;
    }
    void ShowOff() {
        cout << "My car is $" + to_string(price_) << endl;
    }
private:
    int price_;
};

void Paint(Car* car) {
    cout << "Paint this car." << endl;
}

void Example1() {
    unique_ptr<Car> car_ptr_container(new Car(10000));
    // use as a Car*
    car_ptr_container->ShowOff();

    // get a reference to the actual Car object
    Car& car_ref = *car_ptr_container;
    car_ref.ShowOff();

    // get raw pointer to the actual Car object
    Car* car_ptr = car_ptr_container.get();
    car_ptr->ShowOff();

    Paint(car_ptr_container.get());
}

void Example2() {
    unique_ptr<Car> car = make_unique<Car>(10000);
    // transfer ownership, don't use car anymore
    unique_ptr<Car> another_car = std::move(car);
    another_car->ShowOff();
}

// unique_ptr as function return type
unique_ptr<Car> Example3() {
    unique_ptr<Car> car = make_unique<Car>(10000);
    return car;
}

int main() {
    int first = GetAnotherGlobalInteger();
    int second = GetAnotherGlobalInteger();

    // created on heap, default initialization, *p is undefined
    int *int1 = new int;
    // created on stack, default initialization
    int int2;
    // created on heap, value initialization, *pp is 0
    int *pp = new int{};

    // default initialization, *ps is defined by string's default constructor
    string *ps = new string;
    // value initialization, *pps and *ps are the same
    string *pps = new string();

    // create a const int on heap, initializer must be provided
    const int* pc = new const int(1234);
    const string *pcs = new const string();

    // allocate 10 uninitialized ints
    int *ptr_arr_int = new int[10];
    // allocate 10 initialized ints
    int *ptr_arr_int2 = new int[10]{};

    // ptr_arr_int points to the first element of a dynamic allocated array.
    delete[] ptr_arr_int;

    // once this object is returned, the caller should be responsible for managing its lifetime
    unique_ptr<Car> car = Example3();
}