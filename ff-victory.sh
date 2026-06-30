#!/bin/sh
# https://ubuntuforums.org/showthread.php?t=1157670&page=4
beep -f 784 -r 3 -l 100 \
  -D 100 \
  -n -f 784 -l 600 \
  -n -f 622 -l 600 \
  -n -f 698 -l 600 \
  -n -f 784 -l 200 \
  -D 200 \
  -n -f 698 -l 200 \
  -n -f 784 -l 800
