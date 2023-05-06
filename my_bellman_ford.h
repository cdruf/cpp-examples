


#ifndef MY_BF_H
#define MY_BF_H


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

#endif // MY_BF_H