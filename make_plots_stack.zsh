#!/usr/bin/env zsh

#-- Configuration -------------------------------------------
hns=(h_mtwMass h_metPt h_leptonPt h_leptonDeltaCorrectedRelIso h_leptonRhoCorrectedRelIso)
extension=pdf
dpath=plots/stack/

#------------------------------------------------------------
# if provided, assign command line parameters to variables
[[ $2 != "" ]] && extension=$1
[[ $3 != "" ]] && dpath=$2

#------------------------------------------------------------
for hn in $hns; do 
    fnc=make_plots_stack.cc(\"$dpath\", \"$hn\", \".$extension\")
    root.exe -l -b -q "$fnc"
done

