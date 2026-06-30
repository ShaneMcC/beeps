#!/bin/sh
# https://www.reddit.com/r/linux/comments/18h8v5/does_anyone_have_or_know_a_source_for_beep_scripts/

args=""; sep=""
for n in 1 2 3 ; do
    for f in 1 2 1 2 1 2 1 2 1 2 ; do
      args="$args$sep -f ${f}000 -l 20"; sep=" -n"
    done
done
beep $args
