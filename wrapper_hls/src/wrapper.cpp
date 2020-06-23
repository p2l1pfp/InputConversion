/*
HLS implementation of input conversion wrapper
*/
#include "wrapper.h"
#ifndef __SYNTHESIS__
#include <cstdio>
#endif

// #include "../../submodules/GTT_MET_HLS/eta/src/eta_top.cc"
// #include "../../submodules/GTT_MET_HLS/p_T/src/p_T_top.cc"

void pf_input_track_conv_hw(input_t in, output_t& out){
    #pragma HLS pipeline II=1

    bool debugTracks=false;

    // unpack L1Track format
    rinv_t     rinv    ;
    tkphi_t    tkphi   ;
    tanlam_t   tanlam  ;
    tkz0_t     tkz0    ;
    tkd0_t     tkd0    ;
    chi2rphi_t chi2rphi;
    chi2rz_t   chi2rz  ;
    bendChi2_t bendChi2;
    hit_t      hit     ;
    trackMVA_t trackMVA;
    extraMVA_t extraMVA;
    valid_t    valid   ;

    unpack_L1T_track(in, rinv, tkphi, tanlam, tkz0, tkd0, chi2rphi, chi2rz, bendChi2, hit, trackMVA, extraMVA, valid);

    if(debugTracks){
        std::cout << "---------- " << std::endl;
        std::cout << "Algo reads " << std::endl;
        std::cout<<"rinv     "; for(int i=rinv_t    ::width-1; i>=0;i--){ std::cout << int( rinv    [i]);}std::cout << "  " << rinv    .to_double() << std::endl;
        std::cout<<"tkphi    "; for(int i=tkphi_t   ::width-1; i>=0;i--){ std::cout << int( tkphi   [i]);}std::cout << "  " << tkphi   .to_double() << std::endl;
        std::cout<<"tanlam   "; for(int i=tanlam_t  ::width-1; i>=0;i--){ std::cout << int( tanlam  [i]);}std::cout << "  " << tanlam  .to_double() << std::endl;
        std::cout<<"tkz0     "; for(int i=tkz0_t    ::width-1; i>=0;i--){ std::cout << int( tkz0    [i]);}std::cout << "  " << tkz0    .to_double() << std::endl;
        std::cout<<"tkd0     "; for(int i=tkd0_t    ::width-1; i>=0;i--){ std::cout << int( tkd0    [i]);}std::cout << "  " << tkd0    .to_double() << std::endl;
        std::cout<<"chi2rphi "; for(int i=chi2rphi_t::width-1; i>=0;i--){ std::cout << int( chi2rphi[i]);}std::cout << "  " << chi2rphi.to_double() << std::endl;
        std::cout<<"chi2rz   "; for(int i=chi2rz_t  ::width-1; i>=0;i--){ std::cout << int( chi2rz  [i]);}std::cout << "  " << chi2rz  .to_double() << std::endl;
        std::cout<<"bendChi2 "; for(int i=bendChi2_t::width-1; i>=0;i--){ std::cout << int( bendChi2[i]);}std::cout << "  " << bendChi2.to_double() << std::endl;
        std::cout<<"hit      "; for(int i=hit_t     ::width-1; i>=0;i--){ std::cout << int( hit     [i]);}std::cout << "  " << hit     .to_double() << std::endl;
        std::cout<<"trackMVA "; for(int i=trackMVA_t::width-1; i>=0;i--){ std::cout << int( trackMVA[i]);}std::cout << "  " << trackMVA.to_double() << std::endl;
        std::cout<<"extraMVA "; for(int i=extraMVA_t::width-1; i>=0;i--){ std::cout << int( extraMVA[i]);}std::cout << "  " << extraMVA.to_double() << std::endl;
        std::cout<<"valid    "; for(int i=valid_t   ::width-1; i>=0;i--){ std::cout << int( valid   [i]);}std::cout << "  " << valid   .to_double() << std::endl;
    }

    // std::cout << "valid " << valid << std::endl;


    // selection
    //if(!valid) return;

    // converters
    pt_t conv_pt;
    convert_pt(rinv,conv_pt);

    // in_pt_t conv_in_pt = rinv;
    // out_pt_t conv_out_pt;
    // p_T(conv_in_pt, &conv_out_pt);

    // in_eta_t conv_in_eta = tanlam;
    // out_eta_t conv_out_eta;
    // bool parity=1;
    // bool erase;
    // eta(conv_in_eta, &conv_out_eta, parity, &erase);
    // tanlam_t tan_lambda = (M_PI/2.)-(2.*atan(exp(-1.*track_in[i].floatEta())));

    // pack in PF format
    pt_t pf_pt = conv_pt;
    pt_t pf_pterr = conv_pt;
    etaphi_t pf_eta = 0; //conv_out_eta;
    etaphi_t pf_phi = tkphi;
    z0_t pf_z0 = tkz0;
    bool pf_TightQuality = 1;
    pack_pf_track(out, pf_pt, pf_pterr, pf_eta, pf_phi, pf_z0, pf_TightQuality);
}


void pack_L1T_track(ap_uint<kTrackWordSize> &tk,
                    rinv_t     rinv    ,
                    tkphi_t    tkphi   ,
                    tanlam_t   tanlam  ,
                    tkz0_t     tkz0    ,
                    tkd0_t     tkd0    ,
                    chi2rphi_t chi2rphi,
                    chi2rz_t   chi2rz  ,
                    bendChi2_t bendChi2,
                    hit_t      hit     ,
                    trackMVA_t trackMVA,
                    extraMVA_t extraMVA,
                    valid_t    valid   ){

    bool debug=false;
    if(debug){
        std::cout << "Packing obj content: " << std::endl;
        std::cout<<"rinv     "; for(int i=rinv_t    ::width-1; i>=0;i--){ std::cout << int( rinv    [i]);}std::cout << std::endl;
        std::cout<<"tkphi    "; for(int i=tkphi_t   ::width-1; i>=0;i--){ std::cout << int( tkphi   [i]);}std::cout << std::endl;
        std::cout<<"tanlam   "; for(int i=tanlam_t  ::width-1; i>=0;i--){ std::cout << int( tanlam  [i]);}std::cout << std::endl;
        std::cout<<"tkz0     "; for(int i=tkz0_t    ::width-1; i>=0;i--){ std::cout << int( tkz0    [i]);}std::cout << std::endl;
        std::cout<<"tkd0     "; for(int i=tkd0_t    ::width-1; i>=0;i--){ std::cout << int( tkd0    [i]);}std::cout << std::endl;
        std::cout<<"chi2rphi "; for(int i=chi2rphi_t::width-1; i>=0;i--){ std::cout << int( chi2rphi[i]);}std::cout << std::endl;
        std::cout<<"chi2rz   "; for(int i=chi2rz_t  ::width-1; i>=0;i--){ std::cout << int( chi2rz  [i]);}std::cout << std::endl;
        std::cout<<"bendChi2 "; for(int i=bendChi2_t::width-1; i>=0;i--){ std::cout << int( bendChi2[i]);}std::cout << std::endl;
        std::cout<<"hit      "; for(int i=hit_t     ::width-1; i>=0;i--){ std::cout << int( hit     [i]);}std::cout << std::endl;
        std::cout<<"trackMVA "; for(int i=trackMVA_t::width-1; i>=0;i--){ std::cout << int( trackMVA[i]);}std::cout << std::endl;
        std::cout<<"extraMVA "; for(int i=extraMVA_t::width-1; i>=0;i--){ std::cout << int( extraMVA[i]);}std::cout << std::endl;
        std::cout<<"valid    "; for(int i=valid_t   ::width-1; i>=0;i--){ std::cout << int( valid   [i]);}std::cout << std::endl;
    }
    ap_uint<rinv_t    ::width> word_rinv      = rinv    .range(rinv_t    ::width-1,0);
    ap_uint<tkphi_t   ::width> word_tkphi     = tkphi   .range(tkphi_t   ::width-1,0);
    ap_uint<tanlam_t  ::width> word_tanlam    = tanlam  .range(tanlam_t  ::width-1,0);
    ap_uint<tkz0_t    ::width> word_tkz0      = tkz0    .range(tkz0_t    ::width-1,0);
    ap_uint<tkd0_t    ::width> word_tkd0      = tkd0    .range(tkd0_t    ::width-1,0);
    ap_uint<chi2rphi_t::width> word_chi2rphi  = chi2rphi.range(chi2rphi_t::width-1,0);
    ap_uint<chi2rz_t  ::width> word_chi2rz    = chi2rz  .range(chi2rz_t  ::width-1,0);
    ap_uint<bendChi2_t::width> word_bendChi2  = bendChi2.range(bendChi2_t::width-1,0);
    ap_uint<hit_t     ::width> word_hit       = hit     .range(hit_t     ::width-1,0);
    ap_uint<trackMVA_t::width> word_trackMVA  = trackMVA.range(trackMVA_t::width-1,0);
    ap_uint<extraMVA_t::width> word_extraMVA  = extraMVA.range(extraMVA_t::width-1,0);
    ap_uint<valid_t   ::width> word_valid     = valid   .range(valid_t   ::width-1,0);


    if(debug){
        std::cout << "Packing words: " << std::endl;
        std::cout<<"rinv     "; for(int i=rinv_t    ::width-1; i>=0;i--){ std::cout << int( word_rinv    [i]);}std::cout << std::endl;
        std::cout<<"tkphi    "; for(int i=tkphi_t   ::width-1; i>=0;i--){ std::cout << int( word_tkphi   [i]);}std::cout << std::endl;
        std::cout<<"tanlam   "; for(int i=tanlam_t  ::width-1; i>=0;i--){ std::cout << int( word_tanlam  [i]);}std::cout << std::endl;
        std::cout<<"tkz0     "; for(int i=tkz0_t    ::width-1; i>=0;i--){ std::cout << int( word_tkz0    [i]);}std::cout << std::endl;
        std::cout<<"tkd0     "; for(int i=tkd0_t    ::width-1; i>=0;i--){ std::cout << int( word_tkd0    [i]);}std::cout << std::endl;
        std::cout<<"chi2rphi "; for(int i=chi2rphi_t::width-1; i>=0;i--){ std::cout << int( word_chi2rphi[i]);}std::cout << std::endl;
        std::cout<<"chi2rz   "; for(int i=chi2rz_t  ::width-1; i>=0;i--){ std::cout << int( word_chi2rz  [i]);}std::cout << std::endl;
        std::cout<<"bendChi2 "; for(int i=bendChi2_t::width-1; i>=0;i--){ std::cout << int( word_bendChi2[i]);}std::cout << std::endl;
        std::cout<<"hit      "; for(int i=hit_t     ::width-1; i>=0;i--){ std::cout << int( word_hit     [i]);}std::cout << std::endl;
        std::cout<<"trackMVA "; for(int i=trackMVA_t::width-1; i>=0;i--){ std::cout << int( word_trackMVA[i]);}std::cout << std::endl;
        std::cout<<"extraMVA "; for(int i=extraMVA_t::width-1; i>=0;i--){ std::cout << int( word_extraMVA[i]);}std::cout << std::endl;
        std::cout<<"valid    "; for(int i=valid_t   ::width-1; i>=0;i--){ std::cout << int( word_valid   [i]);}std::cout << std::endl;
    }

    tk = (word_valid, word_extraMVA, word_trackMVA, word_hit, word_bendChi2, word_chi2rz, word_chi2rphi, word_tkd0, word_tkz0, word_tanlam, word_tkphi, word_rinv);
    
    if(debug){
        std::cout << "Packed word: ";
        for(int i=kTrackWordSize-1; i>=0;i--) std::cout << int(tk.test(i));
        std::cout << std::endl;
    }
}

void unpack_L1T_track(ap_uint<kTrackWordSize> in,
                    rinv_t     &rinv    ,
                    tkphi_t    &tkphi   ,
                    tanlam_t   &tanlam  ,
                    tkz0_t     &tkz0    ,
                    tkd0_t     &tkd0    ,
                    chi2rphi_t &chi2rphi,
                    chi2rz_t   &chi2rz  ,
                    bendChi2_t &bendChi2,
                    hit_t      &hit     ,
                    trackMVA_t &trackMVA,
                    extraMVA_t &extraMVA,
                    valid_t    &valid   ){

    bool debug=false;
    if(debug){
        std::cout << "Packed word: ";
        for(int i=kTrackWordSize-1; i>=0;i--) std::cout << int(in.test(i));
        std::cout << std::endl;
    }

    unsigned int lo = 0;
    unsigned int len = 0;

    len=rinv_t    ::width; bit_copy(in, rinv    , lo); lo += len;
    len=tkphi_t   ::width; bit_copy(in, tkphi   , lo); lo += len;
    len=tanlam_t  ::width; bit_copy(in, tanlam  , lo); lo += len;
    len=tkz0_t    ::width; bit_copy(in, tkz0    , lo); lo += len;
    len=tkd0_t    ::width; bit_copy(in, tkd0    , lo); lo += len;
    len=chi2rphi_t::width; bit_copy(in, chi2rphi, lo); lo += len;
    len=chi2rz_t  ::width; bit_copy(in, chi2rz  , lo); lo += len;
    len=bendChi2_t::width; bit_copy(in, bendChi2, lo); lo += len;
    len=hit_t     ::width; bit_copy(in, hit     , lo); lo += len;
    len=trackMVA_t::width; bit_copy(in, trackMVA, lo); lo += len;
    len=extraMVA_t::width; bit_copy(in, extraMVA, lo); lo += len;
    len=valid_t   ::width; bit_copy(in, valid   , lo); lo += len;

    if(debug){
        std::cout << "Unpacked obj content: " << std::endl;
        std::cout<<"rinv     "; for(int i=rinv_t    ::width-1; i>=0;i--){ std::cout << int( rinv    [i]);}std::cout << std::endl;
        std::cout<<"tkphi    "; for(int i=tkphi_t   ::width-1; i>=0;i--){ std::cout << int( tkphi   [i]);}std::cout << std::endl;
        std::cout<<"tanlam   "; for(int i=tanlam_t  ::width-1; i>=0;i--){ std::cout << int( tanlam  [i]);}std::cout << std::endl;
        std::cout<<"tkz0     "; for(int i=tkz0_t    ::width-1; i>=0;i--){ std::cout << int( tkz0    [i]);}std::cout << std::endl;
        std::cout<<"tkd0     "; for(int i=tkd0_t    ::width-1; i>=0;i--){ std::cout << int( tkd0    [i]);}std::cout << std::endl;
        std::cout<<"chi2rphi "; for(int i=chi2rphi_t::width-1; i>=0;i--){ std::cout << int( chi2rphi[i]);}std::cout << std::endl;
        std::cout<<"chi2rz   "; for(int i=chi2rz_t  ::width-1; i>=0;i--){ std::cout << int( chi2rz  [i]);}std::cout << std::endl;
        std::cout<<"bendChi2 "; for(int i=bendChi2_t::width-1; i>=0;i--){ std::cout << int( bendChi2[i]);}std::cout << std::endl;
        std::cout<<"hit      "; for(int i=hit_t     ::width-1; i>=0;i--){ std::cout << int( hit     [i]);}std::cout << std::endl;
        std::cout<<"trackMVA "; for(int i=trackMVA_t::width-1; i>=0;i--){ std::cout << int( trackMVA[i]);}std::cout << std::endl;
        std::cout<<"extraMVA "; for(int i=extraMVA_t::width-1; i>=0;i--){ std::cout << int( extraMVA[i]);}std::cout << std::endl;
        std::cout<<"valid    "; for(int i=valid_t   ::width-1; i>=0;i--){ std::cout << int( valid   [i]);}std::cout << std::endl;
    }

}


void pack_pf_track(ap_uint<64> &tk,
                   pt_t     pf_pt   ,
                   pt_t     pf_pterr,
                   etaphi_t pf_eta  ,
                   etaphi_t pf_phi  ,
                   z0_t     pf_z0   ,
                   bool     pf_TightQuality){

    tk = (pf_TightQuality, pf_z0, pf_phi, pf_eta, pf_pterr, pf_pt);    
}

void unpack_pf_track(ap_uint<64> in,
                   pt_t     &pf_pt   ,
                   pt_t     &pf_pterr,
                   etaphi_t &pf_eta  ,
                   etaphi_t &pf_phi  ,
                   z0_t     &pf_z0   ,
                   bool     &pf_TightQuality){

    unsigned int lo = 0;
    unsigned int len = 0;
    len=pt_t    ::width; pf_pt           = in(lo, lo+len-1); lo += len;
    len=pt_t    ::width; pf_pterr        = in(lo, lo+len-1); lo += len;
    len=etaphi_t::width; pf_eta          = in(lo, lo+len-1); lo += len;
    len=etaphi_t::width; pf_phi          = in(lo, lo+len-1); lo += len;
    len=z0_t    ::width; pf_z0           = in(lo, lo+len-1); lo += len;
    len=1              ; pf_TightQuality = in(lo, lo+len-1); lo += len;
}

template<class in_t, class out_t> 
void bit_copy(in_t in, out_t &out, int offset=0){
    for(int i  =out_t::width-1; i>=0; i--){
        out[i] = in[i+offset];
    }    
}




template<class pt_inv_T, class pt_T>
void init_pt_inv_table(pt_T table_out[(1<<PT_INV_TAB_SIZE)]) {

    // table indices are pt, shifted by (kPtSize-PT_INV_TAB_SIZE) bits
    // index = pt -> integer -> bit-shift
    //ap_uint<kPtSize> integer_pt

    ap_ufixed<(2*(pt_inv_T::width) - pt_inv_T::iwidth), pt_inv_T::width - pt_inv_T::iwidth, AP_RND_CONV, AP_SAT> inv_enlarged; // enlarged type to shift bits
    ap_ufixed<(pt_inv_T::width+1), pt_inv_T::width, AP_RND_CONV, AP_SAT> frac_factor = pow(2,(pt_inv_T::width-pt_inv_T::iwidth));
    
    ap_uint<pt_T::width> i_shifted;

    // multiply result by 1=2^(PT-SIZE)
    table_out[0] = pt_T(0)-1;
    for (unsigned int i = 1; i < (1<<PT_INV_TAB_SIZE); i++) {
        i_shifted = i;
        i_shifted = i_shifted << (pt_T::width - PT_INV_TAB_SIZE);
        inv_enlarged = i_shifted;
        inv_enlarged = inv_enlarged / frac_factor; //pow(2,(pt_inv_T::width-pt_inv_T::iwidth));
        table_out[i] = round((1<<(pt_T::width)) * 1./inv_enlarged.to_double());
        // std::cout << i << " " << table_out[i] << std::endl;
    }
    return;
}

template<class pt_inv_T, class pt_T>
void convert_pt(pt_inv_T inv, pt_T &pt){
    //pt_inv_T is ap_fixed<> (signed)
    //pt_T is ap_ufixed<>  -->  ap_uint<> !
    // Initialize the lookup tables
#ifdef __HLS_SYN__
    bool initialized = false;
    pt_t inv_table[(1<<PT_INV_TAB_SIZE)];
#else 
    static bool initialized = false;
    static pt_t inv_table[(1<<PT_INV_TAB_SIZE)];
#endif
    if (!initialized) {
        init_pt_inv_table<pt_inv_T,pt_T>(inv_table);
        initialized = true;
    }

    //return;

    pt_inv_T abs_inv = inv;
    if(inv<0) abs_inv = -inv;
    //inv = inv>0 ? inv : -inv;

    // need larger type to accomodate shift (from frac to integer representation) w/o loss of precision
    ap_ufixed<(2*(pt_inv_T::width) - pt_inv_T::iwidth), pt_inv_T::width - pt_inv_T::iwidth, AP_RND_CONV, AP_SAT> inv_enlarged; // enlarged type to shift bits
    inv_enlarged = abs_inv;
    inv_enlarged = inv_enlarged << (pt_inv_T::width - pt_inv_T::iwidth);
    ap_uint<pt_inv_T::width> inv_as_uint = inv_enlarged;

    // index by the (PT_INV_TAB_SIZE) MSBs
    ap_uint<PT_INV_TAB_SIZE> index = inv_enlarged >> (pt_inv_T::width-PT_INV_TAB_SIZE);
    
    std::cout << "converting inv " << inv
              << ", to abs " << abs_inv
              << ", to enlarged " << inv_enlarged
              << ", uint " << inv_as_uint
              << ", index " << index
              << std::endl;
    pt = inv_table[index];

    return;

}
