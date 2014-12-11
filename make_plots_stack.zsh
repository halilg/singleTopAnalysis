#!/usr/bin/env zsh

dpath=\"plots/stack/\"
rfn0=\"h-TreesEle_TChannel_2J_1T_noSyst.root\"
rfn1=\"h-TreesEle_TTBar_2J_1T_noSyst.root\"
hn=\"h_mtwMass\"
extension=\".pdf\"

root.exe -l -b -q "make_plots_stack.cc($dpath, $hn, $extension)"


