
#include <boost/graph/adjacency_list.hpp>


#include <iostream>


int main(int argc, char **argv) {
    std::cout.setf(std::ios::boolalpha);

    using MyEdge = std::tuple<int, int, double>;  // source node, target node, arc weight
    using EdgeWeight = boost::property<boost::edge_weight_t, double>;
    // using Graph = boost::adjacency_list<>;
    using Graph = boost::adjacency_list<boost::listS, boost::vecS, boost::directedS, boost::no_property, EdgeWeight>;
    using Vertex = Graph::vertex_descriptor;
    using Edge = Graph::edge_descriptor;


    Graph g;
    const int num_nodes = 5;
    Vertex s = boost::add_vertex(g);
    Vertex v1 = boost::add_vertex(g);
    Vertex v2 = boost::add_vertex(g);
    Vertex v3 = boost::add_vertex(g);
    Vertex t = boost::add_vertex(g);

    // Print nodes
    std::pair<boost::adjacency_list<>::vertex_iterator,
            boost::adjacency_list<>::vertex_iterator> vs = boost::vertices(g);
    std::copy(vs.first, vs.second,
              std::ostream_iterator<boost::adjacency_list<>::vertex_descriptor>{std::cout, "\n"});

    int num_edges = 6;
    MyEdge edges[] = {MyEdge{s, v1, 3.0},
                      MyEdge{s, v2, 5.0},
                      MyEdge{s, v3, 2.0},
                      MyEdge{v1, t, 7.0},
                      MyEdge{v2, t, 6.0},
                      MyEdge{v3, t, 3.0},};
    for (MyEdge e: edges) {
        boost::add_edge(std::get<0>(e), std::get<1>(e), std::get<2>(e), g);
    }


    // Print edges
    auto es = boost::edges(g);
    std::copy(es.first, es.second,
              std::ostream_iterator<boost::adjacency_list<>::edge_descriptor>{
                      std::cout, "\n"});


    // vector for storing distance property
    std::vector<double> d{num_nodes};

    // vector for storing predecessors
    std::vector<Vertex> p{num_nodes};

    //  dijkstra_shortest_paths(g, s, distance_map(&d[0]));
    //dijkstra_shortest_paths(g, s, predecessor_map(&p[0]).distance_map(&d[0]));


}

