#!/usr/bin/env zsh

datasets=(TChannel TWChannel SbarChannel TTBar WJets ZJets WW WZ ZZ QCDEle Data)

for dst in $datasets; do
    echo $dst
    ./go.zsh $dst
done

