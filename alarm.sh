# http://www.reddit.com/r/linux/comments/18h8v5/does_anyone_have_or_know_a_source_for_beep_scripts/

for n in 1 2 3 4 5 6 7 8 9 0; do
      for f in 400 500 600 700 800 900 1000 1100 1200 1300 1400 1500 1600; do
        beep -f $f -l 20
      done
done
