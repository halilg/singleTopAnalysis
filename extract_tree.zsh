#!/usr/bin/env zsh
# Simple wrapper script for the ROOT macro extract_tree.cc 
# Arguments: <path of source ROOT file> <TDirectory> <name of TTree> [path of output ROOT file]
# if the path of the output ROOT file is not provided, the script names the output ROOT file as <TDir>_<TTree>.root
#
# Use example: ./extract_tree.zsh MCeos/TTBar.root TreesEle TTBar_2J_1T_noSyst small.root

IFNAME=\"$1\"
TDIR=\"$2\"
TTREE=\"$3\"

if [[ $# < 4 ]]; then
	OFNAME=\"${2}_${3}.root\"
else
	OFNAME=\"$4\"
fi
root.exe -l -b -q "extract_tree.cc($IFNAME, $TDIR, $TTREE, $OFNAME)"

