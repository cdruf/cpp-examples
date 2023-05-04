

#ifndef CPP_EXAMPLES_MYWEIGHTEDDIGRAPH_H
#define CPP_EXAMPLES_MYWEIGHTEDDIGRAPH_H

#include <iostream>
#include <vector>


struct WeightedEdge {
    int s; // source
    int d; // destination
    double w; // weight
};

/**
 * Basic implementation of a directed graph where the nodes are numbered 0, ..., N-1.
 */
class MyWeightedDiGraph {

public:
    int m_num_nodes;
    int m_num_arcs;
    std::vector<WeightedEdge> m_edge_list;
    std::vector<std::vector<WeightedEdge>> adj; // adjacency list
    std::vector<std::vector<WeightedEdge>> adj_reverse; // adjacency list in opposite direction of arcs

    MyWeightedDiGraph(int num_nodes, const std::vector<WeightedEdge> &edge_list) :
            m_num_nodes{num_nodes},
            m_edge_list{edge_list},
            m_num_arcs{static_cast<int>(edge_list.size())} {
        adj = std::vector(num_nodes, std::vector<WeightedEdge>());
        adj_reverse = std::vector(num_nodes, std::vector<WeightedEdge>());
        for (WeightedEdge e: edge_list) {
            adj[e.s].push_back(e);
            adj_reverse[e.d].push_back(e);
        }
    }
};


#endif //CPP_EXAMPLES_MYWEIGHTEDDIGRAPH_H
