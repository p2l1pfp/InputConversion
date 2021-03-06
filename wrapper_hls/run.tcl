# get the configuration
#source config.tcl

set mainAlgo pf_input_track_conv
set topFunc ${mainAlgo}_hw

# open the project, don't forget to reset
open_project -reset "track-conv-test"
set_top ${topFunc}
add_files src/wrapper.cpp 
# add_files ../submodules/GlobalCorrelator_HLS/tmux_create_test.h
# add_files ../submodules/GlobalCorrelator_HLS/firmware/data.h
#add_files ../submodules/GTT_MET_HLS/submodules/common/DataFormats/interface/Track.h
add_files ../submodules/GTT_MET_HLS/eta/src/eta_top.cc
add_files ../submodules/GTT_MET_HLS/p_T/src/p_T_top.cc
add_files -tb test.cpp

# reset the solution
open_solution -reset "solution"
set_part {xcvu9p-flgb2104-2-i}
create_clock -period 3.125 -name default
set_clock_uncertainty 1.5

config_interface -trim_dangling_port
# do stuff
csim_design
csynth_design
cosim_design -trace_level all
export_design -format ip_catalog -vendor "cern-cms" -version 0.1 -description "${mainAlgo}"

# exit Vivado HLS
exit
