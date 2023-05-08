#include <iostream>
#include <algorithm>

class A {
public:
    int m_a;

    // Default constructor
    A(int a) : m_a{a} {
        std::cout << "Default\n";
    }

    // Copy constructor
    A(const A &other) : m_a{other.m_a} {
        std::cout << "Copy\n";
    }
};

const A &my_func(std::vector<A> &vec) {
    vec.push_back(A{1});
    std::cout << "Address of new A-object " << &vec[vec.size() - 1] << "\n";
    return vec[vec.size() - 1];
}

bool check_if_found(const std::vector<A> &vec, const A &elem) {
    for (int i = 0; i < vec.size(); ++i) {
        if (&vec[i] == &elem) {
            std::cout << &vec[i] << "\n";
            std::cout << &elem << "\n";
        }
        return true;
    }
    return false;
}

int main(int argc, char **argv) {
    std::vector<A> my_vec = std::vector<A>();
    const A &my_a{my_func(my_vec)};
    std::cout << "Address of A-object returned " << &my_a << "\n";

    // Put a pointer into a vector
    std::vector<const A *> other_vec = std::vector<const A *>();
    other_vec.push_back(&my_a);
    std::cout << "Address of pointer in vector " << &other_vec[0] << "\n";  // Address of pointer
    std::cout << "Value of pointer object " << other_vec[0] << "\n";

    // Find element
    bool result = check_if_found(my_vec, *other_vec[0]);
    std::cout << "Found " << result << "\n";

}