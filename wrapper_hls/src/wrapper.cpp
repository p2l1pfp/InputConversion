/*
HLS implementation of input conversion wrapper
*/
#include "wrapper.h"
#ifndef __SYNTHESIS__
#include <cstdio>
#endif

void pf_input_track_conv_hw(input_t in, output_t& out){
    #pragma HLS pipeline II=1
    out = in(0,64);
}
