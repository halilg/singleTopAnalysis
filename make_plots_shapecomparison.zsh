#!/usr/bin/env zsh

dpath=\"plots/combined/\"
rfn0=\"h-TreesEle_TChannel_2J_1T_noSyst.root\"
rfn1=\"h-TreesEle_TTBar_2J_1T_noSyst.root\"
hn=\"h_fJetEta\"
extension=\".pdf\"

root.exe -l -b -q "make_plots_shapecomparison.cc($dpath, $rfn0, $rfn1, $hn, $extension)"


