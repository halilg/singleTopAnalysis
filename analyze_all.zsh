#!/usr/bin/env zsh

datasets=(TChannel TWChannel SbarChannel TTBar WJets ZJets WW WZ ZZ QCDEle Data)
tags=(2J_0T_noSyst 2J_1T_noSyst 3J_1T_noSyst 3J_2T_noSyst)

for tag in $tags; do
    echo "@@@@@ tag: $tag"
    for dst in $datasets; do
        echo "@@@ $dst"
        ./go.zsh $dst $tag
        OFCODE=$?
        [[ $OFCODE == 0 ]] || exit
    done
done

echo "@@@@@ Rendering plots"
for rf in root/h-*.root; do
    ./make_plots.zsh $rf
done
./make_plots_stack.zsh