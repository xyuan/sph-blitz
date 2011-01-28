#! /bin/bash

set -u
i=0
for outdir in $(ls -d outdata*); do
    printf "post.sh:%i processing: %s\n" $LINENO $outdir > "/dev/stderr"
    ../../scripts/dat2punto.sh $outdir
    nsnap=$(awk '!NF{n++} END {print n}' "$outdir"/punto.dat)
    printf "post.sh:%i numer of snapshots: %i\n" $LINENO $nsnap > "/dev/stderr"
    awk 'NF&&$6==1{s+=$4; n++} !NF{print s/n; s=n=0}' "$outdir"/punto.dat > "$outdir"/media.mom
    awk 'NF&&$6==2{s+=$4; n++} !NF{print s/n; s=n=0}' "$outdir"/punto.dat > "$outdir"/block.mom

    tac "$outdir"/punto.dat | awk '!NF&&NR>1{exit} NF{print}' > "$outdir"/punto.last
    awk 'NF{print; $1=-$1; $3=-$3; print} !NF{print}' "$outdir"/punto.dat > "$outdir"/punto.sym

    cp $outdir/punto.last /tmp/punto.last
    gnuplot gplot.gp
    printf "post.sh:%i last time step configuration is in punto.png\n" $LINENO> "/dev/stderr"
    let i++
    cp punto.png ~/Dropbox/punto$i.png
done


