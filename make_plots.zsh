#!/usr/bin/env zsh
FNAME=\"$1\"
root.exe -l -b -q "make_plots.cc($FNAME)"
