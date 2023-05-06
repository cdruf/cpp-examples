#include <iostream>
#include "SystemOfDifferences.h"

/**
 * Testing the SystemOfDifferences. Example taken from Cormen 24.4.
 */
int main(int argc, char **argv) {
    std::cout << "Hi!\n";

    // Create model
    SystemOfDifferences mdl{};

    // Create variables
    for (int i = 1; i <= 5; ++i) {
        mdl.add_var("v" + std::to_string(i));
    }

    // Create constraints
    mdl.add_constr("c1", 1, 2, 0);
    mdl.add_constr("c2", 1, 5, -1);
    mdl.add_constr("c3", 2, 5, 1);
    mdl.add_constr("c4", 3, 1, 5);
    mdl.add_constr("c5", 4, 1, 4);
    mdl.add_constr("c6", 4, 3, -1);
    mdl.add_constr("c7", 5, 3, -3);
    mdl.add_constr("c8", 5, 4, -3);

    // Solve model
    int status = mdl.solve();

    if (status == 1) {  // solution found
        mdl.base_solution(0, 0.0);
        // Expected solution is: -5, -3, 0, -1, -4
        for (int i = 0; i <= 5; ++i) {
            std::cout << mdl.vars[i].name << " == " << mdl.vars[i].value << "\n";
        }
        std::cout << "\n";
        mdl.base_solution(1, 0.0);
        // Expected solution is: 0, 2, 5, 4, 1
        for (int i = 0; i <= 5; ++i) {
            std::cout << mdl.vars[i].name << " == " << mdl.vars[i].value << "\n";
        }
    }

    std::cout << "Buy!\n";
}