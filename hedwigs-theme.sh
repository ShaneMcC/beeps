#!/bin/sh
LENGTH=300
beep -f 617 -l $LENGTH \
-n -f 824 -l $((LENGTH * 3/2)) \
-n -f 980 -l $((LENGTH/2)) \
-n -f 873 -l $LENGTH \
-n -f 824 -l $((LENGTH * 2)) \
-n -f 1234 -l $LENGTH \
-n -f 1100 -l $((LENGTH*5/2)) \
-n -f 925 -l $((LENGTH*5/2)) \
-n -f 824 -l $((LENGTH*3/2)) \
-n -f 980 -l $((LENGTH/2)) \
-n -f 873 -l $LENGTH \
-n -f 777 -l $((LENGTH*2)) \
-n -f 873 -l $LENGTH \
-n -f 617 -l $((LENGTH*5/2))
