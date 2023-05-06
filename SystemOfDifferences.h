

#ifndef CPP_EXAMPLES_SYSTEMOFDIFFERENCES_H
#define CPP_EXAMPLES_SYSTEMOFDIFFERENCES_H

#include <iostream>
#include "MyWeightedDiGraph.h"
#include "my_bellman_ford.h"

struct SODVar {
    int idx;
    std::string name;
    double value;
};

struct SODConstr {
    std::string name;
    SODVar first; // positive coefficient of one
    SODVar second; // negative coefficient of one
    double rhs; // right hand side value
};

class SystemOfDifferences {
public:
    std::vector<SODVar> vars;
    std::vector<SODConstr> constrs;
    //std::unordered_map<std::string , int> var_name_to_idx;


    SystemOfDifferences() : vars{std::vector<SODVar>()}, constrs{std::vector<SODConstr>()} {
        // Add the source variable
        vars.push_back(SODVar{static_cast<int>(vars.size()), "source", 0.0});
    }

    /**
     * Add a new variable.
     * @param name The name of the new variable.
     * @return Index of the new variable.
     */
    int add_var(const std::string &name) {
        vars.push_back(SODVar{static_cast<int>(vars.size()), name, 0.0});
        return vars.size() - 1;
    }

    void add_constr(const std::string &name, int first, int second, double rhs) {
        constrs.push_back(SODConstr{name, vars[first], vars[second], rhs});
    }

    /**
     *
     * @return Status of optimization, where 0 means that the system does not have a solution and
     * 1 means the system is solved.
     */
    int solve() {
        // Create edge list
        std::vector<WeightedEdge> edge_list = std::vector<WeightedEdge>();
        // edge from the source to each variable
        for (SODVar &v: vars) {
            edge_list.push_back(WeightedEdge{vars[0].idx, v.idx, 0.0});
        }
        // edge for each constraint
        for (SODConstr &c: constrs) {
            edge_list.push_back(WeightedEdge{c.second.idx, c.first.idx, c.rhs});
        }

        // Create graph
        MyWeightedDiGraph constraint_graph{static_cast<int>(vars.size()), edge_list};

        // Run Bellman-Ford
        BellmanFordResult result = bellman_ford(constraint_graph);
        if (result.negative_cycle) {
            return 0;
        }
        // x = (d(source, v1), d(source, v2), ..., d(source, v_n))
        preds = std::move(result.preds);
        dists = std::move(result.dists);
        for (int i = 1; i < vars.size(); ++i) {
            vars[i].value = dists[i];
        }
        return 1;
    }

    /**
     * If there is a solution, there are infinite solutions. We can add an arbitrary value to all variables.
     * This method sets a specific value for the given variable and shifts all other values accordingly.
     */
    void base_solution(int idx, double val) {
        double diff = val - vars[idx].value;
        for (int i = 0; i < vars.size(); ++i) {
            vars[i].value += diff;
        }
    }

private:
    std::vector<int> preds;  // -1 represents none
    std::vector<double> dists;
};


#endif //CPP_EXAMPLES_SYSTEMOFDIFFERENCES_H
