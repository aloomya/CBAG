#include "bc.hpp"

using namespace std;

void prepare_sgraph(string graph_path, sgraph_t& comp) {
  graph_t graph;
  graph.read_graph(graph_path);
  comp.fill_graph(graph);
}

void RAND1(sgraph_t& comp, vector<double>& BC_vec, int sample_size) {
  BC_vec.resize(comp.size());
  fill(BC_vec.begin(), BC_vec.end(), 0.0);

  srand(time(NULL));

  vector<node_id_t> chosenVertices;
  for (int i = 0; i < sample_size;) {
    int vertex = rand() % comp.size();
    if (std::find(chosenVertices.begin(), chosenVertices.end(), vertex) !=
        chosenVertices.end()) {
      continue;
    } else {
      chosenVertices.push_back(vertex);
      i++;
    }
  }

  brandes_block_RAND1(&BC_vec, &comp, &chosenVertices, 0);

  for (int i = 0; i < BC_vec.size(); i++) {
    BC_vec[i] = comp.size() * (BC_vec[i] / sample_size);
  }
}

void brandes_block_RAND1(vector<double>* dBC_vec, sgraph_t* comp,
                         vector<node_id_t>* source_vec, int cons) {
  int i;
  for (i = 0; i < source_vec->size(); i++) {
    iter_info_t iter_info;
    brandes_iter_RAND1(*dBC_vec, *comp, (*source_vec)[i], iter_info);
  }
}

void brandes_iter_RAND1(vector<double>& BC_vec, sgraph_t& comp, node_id_t s,
                        iter_info_t& iter_info) {
  iter_info.init_all(comp.size());
  BBFS_RAND1(iter_info, comp, s);
  RBFS_RAND1(BC_vec, comp, s, iter_info, true, false);
}

void BBFS_RAND1(iter_info_t& iter_info, sgraph_t& comp, node_id_t s) {
  sgraph_t& g = comp;

  vector<vector<node_id_t> >& P = iter_info.P;
  vector<int>& sigma_vec = iter_info.sigma_vec;
  vector<int>& dist_vec = iter_info.dist_vec;
  vector<node_id_t>& S = iter_info.S;

  queue<node_id_t> Q;

  sigma_vec[s] = 1;
  dist_vec[s] = 0;
  Q.push(s);
  while (!Q.empty()) {
    node_id_t v_i = Q.front();
    Q.pop();
    S.push_back(v_i);
    for (int i = 0; i < g.nodes_vec[v_i].size(); ++i) {
      node_id_t v_n = g.nodes_vec[v_i][i];
      if (dist_vec[v_n] < 0) {
        Q.push(v_n);
        dist_vec[v_n] = dist_vec[v_i] + 1;
      }
      if (dist_vec[v_n] == dist_vec[v_i] + 1) {
        sigma_vec[v_n] = sigma_vec[v_n] + sigma_vec[v_i];
        P[v_n].push_back(v_i);
      }
    }
  }
}

void RBFS_RAND1(vector<double>& dBC_vec, sgraph_t& comp, node_id_t s,
                iter_info_t& iter_info, bool add, bool sub) {
  vector<vector<node_id_t> >& P = iter_info.P;
  vector<int>& sigma_vec = iter_info.sigma_vec;
  vector<double>& delta_vec = iter_info.delta_vec;
  vector<node_id_t>& S = iter_info.S;

  fill_vec<double>(delta_vec, comp.size(), 0);

  for (int i = S.size() - 1; i >= 0; --i) {
    node_id_t w = S[i];
    for (int idx = 0; idx < P[w].size(); ++idx) {
      node_id_t v = P[w][idx];
      delta_vec[v] +=
          (((double)sigma_vec[v] / sigma_vec[w]) * (1 + delta_vec[w]));
    }
    if (w != s) {
      if (add) dBC_vec[w] += delta_vec[w] / 2.0;
      if (sub) dBC_vec[w] -= delta_vec[w] / 2.0;
    }
  }
}
