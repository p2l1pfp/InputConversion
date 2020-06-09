/*
HLS implementation of input conversion wrapper
*/
#include "wrapper.h"
#ifndef __SYNTHESIS__
#include <cstdio>
#endif

#include "../../submodules/GTT_MET_HLS/eta/src/eta_top.cc"
#include "../../submodules/GTT_MET_HLS/p_T/src/p_T_top.cc"

void pf_input_track_conv_hw(input_t in, output_t& out){
    #pragma HLS pipeline II=1

    // unpack L1Track format
    uint lo = 0;
    uint len = 0;
    len=kPtSize+kChargeSize; rinv_t         rinv         = in(lo, lo+len); lo += len;
    len=kPhiSize;            tkphi_t        tkphi        = in(lo, lo+len); lo += len;
    len=kEtaMagSize;         tanlam_t       tanlam       = in(lo, lo+len); lo += len;
    len=kZ0MagSize;          tkz0_t         tkz0         = in(lo, lo+len); lo += len;
    len=kD0MagSize;          tkd0_t         tkd0         = in(lo, lo+len); lo += len;
    len=kChi2RPhiSize;       chi2rphi_t     chi2rphi     = in(lo, lo+len); lo += len;
    len=kChi2RZSize;         chi2rz_t       chi2rz       = in(lo, lo+len); lo += len;
    len=kBendChi2Size;       bendChi2_t     bendChi2     = in(lo, lo+len); lo += len;
    len=kHitPatternSize;     hit_t          hit          = in(lo, lo+len); lo += len;
    len=kTrackMVASize;       trackMVA_t     trackMVA     = in(lo, lo+len); lo += len;
    len=kMVAExtraSize;       extraMVA_t     extraMVA     = in(lo, lo+len); lo += len;
    len=kTrackQualitySize;   trackQuality_t trackQuality = in(lo, lo+len); lo += len;

    // selection
    if(false && !trackQuality) return;

    // converters
    in_pt_t conv_in_pt = rinv;
    out_pt_t conv_out_pt;
    p_T(conv_in_pt, &conv_out_pt);

    in_eta_t conv_in_eta = tanlam;
    out_eta_t conv_out_eta;
    bool parity=1;
    bool erase;
    eta(conv_in_eta, &conv_out_eta, parity, &erase);

    // pack in PF format
    pt_t pf_pt = conv_out_pt;
    pt_t pf_pterr = conv_out_pt;
    etaphi_t pf_eta = conv_out_eta;
    etaphi_t pf_phi = tkphi;
    z0_t pf_z0 = tkz0;
    bool pf_TightQuality = 1;

    out = (pf_TightQuality, pf_z0, pf_phi, pf_eta, pf_pterr, pf_pt);    
}
