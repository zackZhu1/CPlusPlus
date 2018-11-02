//
// Created by Jiawen Zhu on 11/1/18.
//

// model a has-relationship in C++
class Driver {
public:
    Driver(string name): name_(name) {}
    ~Driver() {
        cout << name_ << " is being destroyed";
    }

    const string& name() {
        return name_;
    }

private:
    string name_;
};

// solution1: composition
class Car {
public:
    CarWithDriver(int price, string owner_name): price_(price), owner_(owner_name) {}
    ~CarWithDriver() {
        cout << "A car worth $" << price_ << " is destroyed." << endl;
    }
private:
    Driver owner_; // Driver's lifetime is the same as CarWithDriver
    int price_;
};

// solution2: if subobject can be changed overtime
// by using raw pointer and couples it with ownership, we need to manually manage memory
class Car2 {
public:
    Car(int price, string owner_name) : price_(price), owner_(nullptr) {
        owner_ = new Driver(owner_name);
    }

    ~Car2() {
        if (owner_ != nullptr) {
            delete owner_;
        }
    }

private:
    Driver* owner_;
    int price_;
};

class Car3 {
public:
    Car3(int price, string owner_name): price_(price) {
        owner_ = unique_ptr<Driver>(new Driver(owner_name));
    }
private:
    unique_ptr<Driver> owner_; // Driver作为Car的resource
    int price_;
};

template<typename T>
class OwningPointer {
public:
    OwningPointer() : ptr_(nullptr) {}
    explicit OwningPointer(T* ptr) : ptr_(ptr) {}
    ~OwningPointer() {
        reset();
    }

    // Copy operations
    OwningPointer(const OwningPointer& other) = delete;
    OwningPointer& operator=(const OwningPointer& other) = delete;

    // Move operations
    OwningPointer(OwningPointer&& other) : ptr_(other.release()) {}
    OwningPointer& operator=(OwningPointer&& other) {
        reset(other.release());
        return *this;
    }

    void reset(T* ptr = nullptr) {
        delete ptr_;
        ptr_ = ptr;
    }

    T* release() {
        T* ret = ptr_;
        ptr_ = nullptr;
        return ret;
    }

    T* get() const {
        return ptr_;
    }
private:
    T* ptr_;
};


int main() {

}