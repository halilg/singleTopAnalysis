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

EVENTS=10000
FPATH=~/eos/cms/store/group/phys_top/SingleTop/Trees/MC
FROOT_I=TTBar.root
RDIR=TreesEle
RTREE=TTBar_2J_1T_noSyst
FROOT_O=h-${RTREE}-${RDIR}-$FROOT_I
echo $FROOT_O

if [[ $1 != "-na" ]]; then
    ./analysis.exe $EVENTS $FPATH/$FROOT_I $FROOT_O $RDIR $RTREE 
fi

if [[ $1 != "-np" ]]; then
    ./make_plots.zsh $FROOT_O
fi



