#ifndef BC_HPP
#define BC_HPP

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <algorithm>

#include "utility.hpp"
#include "iter_info_t.hpp"

using namespace std;

void prepare_sgraph(string graph_path, sgraph_t& comp);

void RAND1(sgraph_t& comp, vector<double>& BC_vec, int sampleSize);

void brandes_block_RAND1(vector<double>* dBC_vec, sgraph_t* comp,
                         vector<node_id_t>* source_vec, int cons);

void brandes_iter_RAND1(vector<double>& BC_vec, sgraph_t& comp, node_id_t s,
                        iter_info_t& iter_info);

void BBFS_RAND1(iter_info_t& iter_info, sgraph_t& comp, node_id_t s);

void RBFS_RAND1(vector<double>& dBC_vec, sgraph_t& comp, node_id_t s,
                iter_info_t& iter_info, bool add, bool sub);

#endif
