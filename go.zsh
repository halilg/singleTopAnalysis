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
#dataset=TTBar
dataset=Data
tag=2J_0T_noSyst
prefix=TreesEle
EVENTS=10  # -1 for all events

if [[ $dataset == "Data" ]]; then
    FPATH=.
    FROOT_I=${prefix}_${dataset}_${tag}.json
else
    FPATH=MC
    FROOT_I=${prefix}_${dataset}_${tag}.root
fi


RDIR=/ #TreesEle
RTREE=${dataset}_${tag}

if [[ ${RDIR} == / ]]; then
    FROOT_O=h-$FROOT_I
else
    FROOT_O=h-$FROOT_I
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



