#!/usr/bin/env zsh

#/*  QCD_Ele.root
#    SChannel.root
#    SbarChannel.root
#    TChannel.root
#    TTBar.root
#    TTBarFullLep.root
#    TTBarSemiLep.root
#    TWChannel.root
#    TbarChannel.root
#    TbarWChannel.root
#    W1Jet.root
#    W2Jets.root
#    W3Jets.root
#    W4Jets.root
#    WJets.root
##    WW.root
#    WZ.root
#    ZJets.root
#    ZZ.root  */

#dataset=TChannel
#dataset=TWChannel
#dataset=SbarChannel
#dataset=TTBar
#dataset=WJets
dataset=ZJets
#dataset=WW
#dataset=WZ
#dataset=ZZ
#dataset=QCDEle
#dataset=Data

tag=2J_0T_noSyst
prefix=TreesEle
EVENTS=-1  # -1 for all events
RDIR=/ #TreesEle
RTREE=${dataset}_${tag}

FROOT_O=${prefix}_${dataset}_${tag}.root
if [[ $dataset == "Data" ]]; then
    FPATH=.
    FROOT_I=${prefix}_${dataset}_${tag}.json
else
    FPATH=MC
    FROOT_I=${prefix}_${dataset}_${tag}.root
fi

#echo $FROOT_O

if [[ $1 != "-na" ]]; then
    make analysis.exe || exit
    ./analysis.exe $EVENTS $FPATH/$FROOT_I $FROOT_O $RDIR $RTREE
fi

if [[ $1 == "-p" ]]; then
    mkdir -p plots/$FROOT_O
    ./make_plots.zsh $FROOT_O
fi



