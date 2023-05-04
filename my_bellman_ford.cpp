
#include <iostream>
#include "MyWeightedDiGraph.h"

const double INF = 10000000.0;

struct BellmanFordResult {
    bool negative_cycle;
    std::vector<int> preds;  // -1 represents none
    std::vector<double> dists;
};

BellmanFordResult bellman_ford(MyWeightedDiGraph g) {
    std::vector<int> preds = std::vector<int>(g.m_num_nodes, -1);  // -1 represents none
    std::vector<double> dists = std::vector<double>(g.m_num_nodes, INF);
    dists[0] = 0.0;

    std::cout << "Run Bellman-Ford\n";
    for (int i = 0; i < g.m_num_nodes; i++) {
        for (WeightedEdge e: g.m_edge_list) {
            if (dists[e.d] > dists[e.s] + e.w) {
                dists[e.d] = dists[e.s] + e.w;
                preds[e.d] = e.s;
            }
        }
    }
    for (WeightedEdge e: g.m_edge_list) {
        if (dists[e.d] > dists[e.s] + e.w) {
            return BellmanFordResult{true, std::vector<int>(), std::vector<double>()};
        }
    }
    return BellmanFordResult{false, preds, dists};

}

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
    std::vector<double> dists = std::vector<double>(num_nodes, INF);
    dists[0] = 0.0;
    BellmanFordResult result = bellman_ford(g);

    for (int node = 0; node < g.m_num_nodes; node++) {
        std::cout << node << ": distance=" << result.dists[node] << ", predecessor=" << result.preds[node] << "\n";
    }

    std::cout << "Done\n";

}