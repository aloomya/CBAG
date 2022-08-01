#ifndef GRAPH_T_HPP
#define GRAPH_T_HPP

#include <stdio.h>

#include <algorithm>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>

#include "types.hpp"
#include "utility.hpp"

using namespace std;

struct graph_t {
  vector<vector<node_id_t> > nodes_vec;

  void insert_edge(node_id_t src, node_id_t dst);
  void init_size(size_t num_nodes);
  size_t size();
  void read_graph(string path);
  void i_init_internals();
};

inline void graph_t::insert_edge(node_id_t src, node_id_t dst) {
  nodes_vec[src].push_back(dst);
  nodes_vec[dst].push_back(src);
}

inline void graph_t::init_size(size_t num_nodes) {
  nodes_vec.resize(num_nodes);
}

inline size_t graph_t::size() { return nodes_vec.size(); }

inline void graph_t::read_graph(string path) {
  ifstream fin;
  fin.open(path.c_str(), ios::in);
  if (!fin.good()) {
    printf("Can't open the file [%s]\n", path.c_str());
    exit(1);
  }
  string name;
  fin >> name;
  size_t N, M, one_base, weighted;
  fin >> N >> M >> one_base >> weighted;
  init_size(N);
  for (int i = 0; i < M; ++i) {
    node_id_t src, dst;
    fin >> src >> dst;
    if (one_base) {
      src--;
      dst--;
    }
    int w;
    if (weighted) fin >> w;
    if (src < N && dst < N) {
      insert_edge(src, dst);
    }
  }
  fin.close();
}

struct sgraph_t {
  vector<vector<node_id_t> > nodes_vec;

  size_t size();
  void fill_graph(graph_t& g);
};

inline size_t sgraph_t::size() { return nodes_vec.size(); }

inline void sgraph_t::fill_graph(graph_t& g) {
  nodes_vec.clear();

  nodes_vec.resize(g.size());
  for (node_id_t i = 0; i < g.size(); ++i) {
    nodes_vec[i] = g.nodes_vec[i];
  }
}

#endif
