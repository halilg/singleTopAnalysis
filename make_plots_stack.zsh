#!/usr/bin/env zsh

dpath=plots/stack
hn=h_mtwMass
mkdir -p $dpath

dpath=\"$dpath\"

rfn0=\"h-TreesEle_TChannel_2J_1T_noSyst.root\"
rfn1=\"h-TreesEle_TTBar_2J_1T_noSyst.root\"
hn=\"$hn\"
extension=\".pdf\"

root.exe -l -b -q "make_plots_stack.cc($dpath, $hn, $extension)"


