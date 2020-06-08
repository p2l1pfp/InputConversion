#include "ap_int.h"
#include "ap_fixed.h"
#include "src/wrapper.h"

int main(){

    uint ntest=10;
    for(unsigned long itest=0; itest<ntest; itest++){
        input_t in(itest<<32); // + ((itest+1)<<32) + ((itest+2)<<64));
        output_t out(0);
        pf_input_track_conv_hw(in, out);
        std::cout << std::setfill('0') << std::setw(6) << std::hex
                  << (unsigned int)(out) << std::endl;
    }

    return 0;
}


