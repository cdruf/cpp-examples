#include <iostream>
#include "MyWeightedDiGraph.h"
#include "constants.h"
#include "my_bellman_ford.h"


int main(int argc, char **argv) {
    std::cout.setf(std::ios::boolalpha);

    const int num_nodes = 5;
    std::vector<WeightedEdge> arcs = std::vector<WeightedEdge>();
    arcs.push_back(WeightedEdge{0, 1, 3.0});
    arcs.push_back(WeightedEdge{0, 2, 5.0});
    arcs.push_back(WeightedEdge{0, 3, 2.0});
    arcs.push_back(WeightedEdge{1, 4, 7.0});
    arcs.push_back(WeightedEdge{2, 4, 6.0});
    arcs.push_back(WeightedEdge{3, 4, 3.0});
    MyWeightedDiGraph g = MyWeightedDiGraph{num_nodes, arcs};

    // Initialize predecessor and distance vectors
    std::vector<int> preds = std::vector<int>(num_nodes, -1);  // -1 represents none
    std::vector<double> dists = std::vector<double>(num_nodes, constants::INF);
    dists[0] = 0.0;

    // Run algo
    BellmanFordResult result = bellman_ford(g);
    std::cout << "Negative cycle: " << result.negative_cycle << "\n";
    for (int node = 0; node < g.m_num_nodes; node++) {
        std::cout << node << ": distance=" << result.dists[node] << ", predecessor=" << result.preds[node] << "\n";
    }

    std::cout << "\n\n\nExample with negative cycle\n\n\n";

    arcs = std::vector<WeightedEdge>();
    arcs.push_back(WeightedEdge{0, 1, 3.0});
    arcs.push_back(WeightedEdge{1, 2, -6.0});
    arcs.push_back(WeightedEdge{2, 0, 2.0});
    arcs.push_back(WeightedEdge{0, 2, 7.0});
    arcs.push_back(WeightedEdge{2, 3, 6.0});
    arcs.push_back(WeightedEdge{3, 4, 6.0});
    g = MyWeightedDiGraph{num_nodes, arcs};

    // Initialize predecessor and distance vectors
    preds = std::vector<int>(num_nodes, -1);  // -1 represents none
    dists = std::vector<double>(num_nodes, INF);
    dists[0] = 0.0;

    // Run algo
    result = bellman_ford(g);
    std::cout << "Negative cycle: " << result.negative_cycle << "\n";

    std::cout << "\n\n\nAnother example\n\n\n";

}