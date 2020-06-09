#ifndef MET_H
#define MET_H

#include <iostream>
#include <cmath>
#include "ap_int.h"
#include "ap_fixed.h"

//#include "../../submodules/GTT_MET_HLS/submodules/common/DataFormats/interface/Track.h"

//#include "../../submodules/GlobalCorrelator_HLS/tmux_create_test.h"
//from https://gitlab.cern.ch/GTT/common/-/blob/master/DataFormats/interface/Track.h
//https://twiki.cern.ch/twiki/bin/viewauth/CMS/HybridDataFormat#Fitted_Tracks_written_by_KalmanF
enum TrackBitWidths { 
//MSB
    kValid              = 1,                                    // Valid bit

    kMVAExtraSize       = 6,                                    // Space for two specialized MVA selections
    kTrackMVASize       = 3,                                    // Width of track quality MVA
    kHitPatternSize     = 7,                                    // Width of the hit pattern for stubs
    kBendChi2Size       = 3,                                    // Width of the Bend-Chi2
    kChi2RZSize         = 4,                                    // Width of Chi2 for r-z
    kChi2RPhiSize       = 4,                                    // Width of Chi2 for r-phi
    kTrackQualitySize   = kMVAExtraSize + kTrackMVASize \
                        + kHitPatternSize + kBendChi2Size \
                        + kChi2RZSize + kChi2RPhiSize,          // Width of track quality

    kD0Size             = 13,                                   // Width of D0
    kD0MagSize          = 5,                                    // Width of D0 magnitude (signed)
    kZ0Size             = 12,                                   // Width of z-position
    kZ0MagSize          = 5,                                    // Width of z-position magnitude (signed)
    kEtaSize            = 16,                                   // Width of eta
    kEtaMagSize         = 3,                                    // Width of eta magnitude (signed)
    kPhiSize            = 12,                                   // Width of phi
    kPhiMagSize         = 0,                                    // Width of phi magnitude (signed)
    kChargeSize         = 1,                                    // Charge of pT
    kChargeMagSize      = 1,                                    // Width of charge magnitude (signed)
    kPtSize             = 14,                                   // Width of pT
    kPtMagSize          = 0,                                    // Width of pT magnitude (unsigned)
//LSB
    kTrackParamsSize    = kD0Size + kZ0Size + kEtaSize \
                        + kPhiSize + kChargeSize + kPtSize,     // Width of track parameters

    kTrackWordSize      = kValid \
                        + kTrackQualitySize \
                        + kTrackParamsSize,                     // Width of the Track Finding Word in bits
};
// spare
typedef ap_uint<kValid>                                             valid_t;        // valid bit

// track quality types
typedef ap_uint<kTrackQualitySize>                                  trackQuality_t; // All track quality bits
typedef ap_uint<kMVAExtraSize>                                      extraMVA_t;      // Specialized MVA selection
typedef ap_uint<kTrackMVASize>                                      trackMVA_t;     // Track quality MVA
typedef ap_uint<kHitPatternSize>                                    hit_t;          // Hit mask bits
typedef ap_uint<kBendChi2Size>                                      bendChi2_t;     // Bend-Chi2
typedef ap_uint<kChi2RZSize>                                        chi2rz_t;       // Chi2 r-z
typedef ap_uint<kChi2RPhiSize>                                      chi2rphi_t;     // Chi2 r-phi

// track parameters types
typedef ap_fixed<kD0Size, kD0MagSize, AP_RND_CONV, AP_SAT>          tkd0_t;           // D0
typedef ap_fixed<kZ0Size, kZ0MagSize, AP_RND_CONV, AP_SAT>          tkz0_t;           // Track z
typedef ap_fixed<kEtaSize, kEtaMagSize, AP_RND_CONV, AP_SAT>        tanlam_t;         // Track eta
typedef ap_fixed<kPhiSize, kPhiMagSize, AP_RND_CONV, AP_SAT>        tkphi_t;          // Track phi
typedef bool                                                        q_t;              // Charge of track PT
typedef ap_ufixed<kPtSize, kPtMagSize, AP_RND_CONV, AP_SAT>         tkpt_t;           // Track PT
typedef ap_fixed<kPtSize+kChargeSize,0, AP_RND_CONV, AP_SAT>        rinv_t;           // 1/RT


//#include "../../submodules/GlobalCorrelator_HLS/firmware/data.h"
typedef ap_int<16> pt_t;
typedef ap_int<10>  etaphi_t;
typedef ap_int<5>  vtx_t;
typedef ap_uint<3>  particleid_t;
typedef ap_int<10> z0_t;

typedef ap_uint<96> input_t;
typedef ap_uint<64> output_t;

void pf_input_track_conv_hw(input_t in, output_t& out);

/* void unpack_track(input_t word, TkObj& tk){
    uint lo=0;
    tk.tkPt = word(lo,TrackBitWidths::kPtSize);

    tk.tkCharge;
    tk.tkPhiFloat; // global angle (independent of sector)
    tk.tkPhi; // relative to the sector center
    tk.tkEta;
    tk.tkZ0;
    tk.tkD0;

    // Track quality
    tk.tkChi2rphi;
    tk.tkChi2rz;
    tk.tkBendChi2;
    tk.tkHitPattern;
    tk.tkMVA;
    tk.tkMVASpecialized;

    // Track valid bit
    tk.tkValid;
}
*/

#endif
