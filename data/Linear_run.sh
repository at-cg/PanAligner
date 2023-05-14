echo "Mapping reads with minigraph..."
./minigraph/minigraph -t32 -cx lr CHM13Y.fa Reads/CHM13Y_5%_reads.fa > Results/minigraph/CHM13Y_L_5%.gaf
echo "Mapping reads with PanAligner..."
../PanAligner -t32 -cx lr CHM13Y.fa Reads/CHM13Y_5%_reads.fa  -y1 > Results/PanAligner/CHM13Y_L_5%.gaf
echo "Mapping reads with GraphAligner..."
/usr/bin/time -v ./bin/GraphAligner -t32 -x vg -g CHM13Y_L.gfa -f Reads/CHM13Y_5%_reads.fa  -a Results/GraphAligner/CHM13Y_L_5%.gaf
./k8 mgutils.js stableGaf CHM13Y_L.gfa Results/GraphAligner/CHM13Y_L_5%.gaf > Results/GraphAligner/CHM13Y_L_5%_stable.gaf
