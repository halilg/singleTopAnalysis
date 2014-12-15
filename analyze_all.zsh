#!/usr/bin/env zsh

#datasets=($())
#categories=$()

for category in `./readcfg.exe categories`; do
    echo "@@@@@ category: $category"
    for dst in `./readcfg.exe datasets`; do
        echo "@@@ $dst"
        ./go.zsh $dst $category
        OFCODE=$?
        [[ $OFCODE == 0 ]] || exit
    done
done

echo "@@@@@ Rendering plots"
for rf in root/h-*.root; do
    ./make_plots.zsh $rf
done
./make_plots_stack.zsh