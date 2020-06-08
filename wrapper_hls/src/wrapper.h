#ifndef MET_H
#define MET_H

#include <iostream>
#include <cmath>
#include "ap_int.h"
#include "ap_fixed.h"

typedef ap_uint<96> input_t;
typedef ap_uint<64> output_t;

void pf_input_track_conv_hw(input_t in, output_t& out);

#endif
