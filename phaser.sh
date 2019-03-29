#!/bin/sh
# https://www.reddit.com/r/linux/comments/18h8v5/does_anyone_have_or_know_a_source_for_beep_scripts/
n=3000; while [ $n -gt 400 ]; do beep -f $n -l 5; n=$((n*97/100)); done
