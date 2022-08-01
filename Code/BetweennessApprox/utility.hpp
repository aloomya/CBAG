#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <math.h>
#include <stdio.h>
#include <sys/time.h>

#include <algorithm>
#include <iostream>
#include <numeric>

#include "graph_t.hpp"

using namespace std;

template <typename T>
void fill_vec(vector<T>& vec, size_t N, T val) {
  vec.resize(N);
  fill(vec.begin(), vec.end(), val);
}

#endif
