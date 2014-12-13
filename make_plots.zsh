#!/usr/bin/env zsh
IFNAME=$1
OPATH=plots/`basename $IFNAME`
mkdir -p $OPATH

#--------------------------------------------
fnc=make_plots.cc(\"$IFNAME\", \"$OPATH\")
root.exe -l -b -q "$fnc"
