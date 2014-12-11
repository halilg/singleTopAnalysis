#!/usr/bin/env zsh

#-- Configuration -------------------------------------------
hn=h_mtwMass #h_metPt h_leptonPt h_leptonDeltaCorrectedRelIso h_leptonRhoCorrectedRelIso
extension=pdf
dpath=plots/stack/

#------------------------------------------------------------
# if provided, assign command line parameters to variables
[[ $1 != "" ]] && hn=$1
[[ $2 != "" ]] && extension=$2
[[ $3 != "" ]] && dpath=$3

#------------------------------------------------------------
fnc=make_plots_stack.cc(\"$dpath\", \"$hn\", \".$extension\")
root.exe -l -b -q "$fnc"


