//
// Created by Jiawen Zhu on 11/4/18.
//

#include <iostream>
#include <vector>
#include <string>
using namespace std;
class Foo {
public:
    explicit Foo(int n): buffer_(n, 100) {
        cout << "Ctor" << endl;
    }
    Foo(const Foo& other) : buffer_(other.buffer_) {
        cout << "Copy ctor!" << endl;
    }
    Foo& operator=(const Foo& other) {
        cout << "Copy assign!" << endl;
        buffer_ = other.buffer_; // vector<int> 内部的copy assignment是deep copy
        return *this;
    }

    Foo(Foo&& other) : buffer_(std::move(other.buffer_)) {
        cout << "Move ctor!" << endl;
    }
    Foo& operator=(Foo&& other) {
        cout << "Copy assign!" << endl;
        swap(this->buffer_, other.buffer_);
        return *this;
    }
private:
    vector<int> buffer_;
};

Foo GetFoo(int n) {
    Foo foo(n); // this object is created on stack, lifetime is this function
    return foo; // but return by value, lifetime now is controlled by the caller???
}

Foo GetFoo2(int a, int b, bool first) {
    Foo foo(a), bar(b);
    if (first) {
        return foo;
    } else {
        return bar;
    }
}

int main() {
    Foo foo = GetFoo(100); // RVO, no copy
    Foo foo2 = GetFoo2(100 , 200, false);
    return 0;
}