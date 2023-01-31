echo "Mapping reads with minimap2..."
./minimap2/minimap2 -t32 -cx map-pb CHM13Y.fa Reads/CHM13Y_reads_5%.fa  > Results/minimap2/CHM13Y_L_5%.gaf
echo "Mapping reads with minigraph..."
./minigraph/minigraph -t32 -cx lr CHM13Y.fa Reads/CHM13_reads_5%.fa > Results/minigraph/CHM13Y_L_5%.gaf
echo "Mapping reads with minichain..."
../minichain -t32 -cx lr CHM13Y.fa Reads/CHM13_reads_5%.fa  -y1 > Results/minichain/CHM13Y_L_5%.gaf
echo "Mapping reads with GraphAligner..."
/usr/bin/time -v ./bin/GraphAligner -t32 -x vg -g CHM13Y_L.gfa -f Reads/CHM13_reads_5%.fa  -a Results/GraphAligner/CHM13Y_L_5%.gaf
./k8 mgutils.js stableGaf CHM13Y_L.gfa Results/GraphAligner/CHM13Y_L_5%.gaf > Results/GraphAligner/CHM13Y_L_5%_stable.gaf
echo "Mapping reads with GraphChainer..."
/usr/bin/time -v ./bin/GraphChainer -t32 -g CHM13Y_L.gfa -f Reads/CHM13_reads_5%.fa  -a Results/GraphChainer/CHM13Y_L_5%.gaf
./k8 mgutils.js stableGaf CHM13Y_L.gfa Results/GraphChainer/CHM13Y_L_5%.gaf > Results/GraphChainer/CHM13Y_L_5%_stable.gaf
echo "Mapped reads to Linear CHM13Y genome."
