#include "RAND1.hpp"

using namespace std;

vector<double> run_RAND1(string graph_path, int sample_size) {
  sgraph_t comp;
  prepare_sgraph(graph_path, comp);

  vector<double> RAND1_between_centrality_result;

  RAND1(comp, RAND1_between_centrality_result, sample_size);
  return RAND1_between_centrality_result;
}
