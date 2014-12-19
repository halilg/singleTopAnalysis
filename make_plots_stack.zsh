#!/usr/bin/env zsh

#-- Configuration -------------------------------------------
hns=(h_fJetEta h_mtwMass h_metPt h_leptonPt h_leptonDeltaCorrectedRelIso h_leptonRhoCorrectedRelIso)

extension=pdf
dpath=plots/stack/
category=2J_0T_noSyst
#------------------------------------------------------------
# if provided, assign command line parameters to variables
[[ $2 != "" ]] && extension=$1
[[ $3 != "" ]] && category=$2
[[ $4 != "" ]] && dpath=$3

#------------------------------------------------------------
for hn in $hns; do 
    make -s make_plots_stack.exe
    ./make_plots_stack.exe $dpath $category $hn $extension
done

