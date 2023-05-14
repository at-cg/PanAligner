echo "Mapping reads with minigraph..."
./minigraph/minigraph -t32 -cx lr CHM13Y_95H.gfa Reads/CHM13Y_5%_reads.fa  > Results/minigraph/CHM13Y_95H_5%.gaf
./minigraph/minigraph -t32 -cx lr CHM13Y_80H.gfa Reads/CHM13Y_5%_reads.fa  > Results/minigraph/CHM13Y_80H_5%.gaf
./minigraph/minigraph -t32 -cx lr CHM13Y_40H.gfa ReadsCHM13Y_5%_reads.fa  > Results/minigraph/CHM13Y_40H_5%.gaf
./minigraph/minigraph -t32 -cx lr CHM13Y_10H.gfa Reads/CHM13Y_5%_reads.fa  > Results/minigraph/CHM13Y_10H_5%.gaf
echo "Mapping reads with PanAligner..."
../minichain -t32 -cx lr CHM13Y_95H.gfa Reads/CHM13Y_5%_reads.fa > Results/PanAligner/CHM13Y_95H_5%.gaf
../minichain -t32 -cx lr CHM13Y_80H.gfa Reads/CHM13Y_5%_reads.fa > Results/PanAligner/CHM13Y_80H_5%.gaf
../minichain -t32 -cx lr CHM13Y_40H.gfa Reads/CHM13Y_5%_reads.fa > Results/PanAligner/CHM13Y_40H_5%.gaf
../minichain -t32 -cx lr CHM13Y_10H.gfa Reads/CHM13Y_5%_reads.fa > Results/PanAligner/CHM13Y_10H_5%.gaf
echo "Mapping reads with GraphAligner..."
/usr/bin/time -v ./bin/GraphAligner -t32 -x vg -g CHM13Y_95H.gfa -f Reads/CHM13Y_5%_reads.fa  -a Results/GraphAligner/CHM13Y_95H_5%.gaf
/usr/bin/time -v ./bin/GraphAligner -t32 -x vg -g CHM13Y_80H.gfa -f Reads/CHM13Y_5%_reads.fa  -a Results/GraphAligner/CHM13Y_80H_5%.gaf
/usr/bin/time -v ./bin/GraphAligner -t32 -x vg -g CHM13Y_40H.gfa -f Reads/CHM13Y_5%_reads.fa  -a Results/GraphAligner/CHM13Y_40H_5%.gaf
/usr/bin/time -v ./bin/GraphAligner -t32 -x vg -g CHM13Y_10H.gfa -f Reads/CHM13Y_5%_reads.fa  -a Results/GraphAligner/CHM13Y_10H_5%.gaf
./k8 mgutils.js stableGaf CHM13Y_10H.gfa Results/GraphAligner/CHM13Y_10H_5%.gaf > Results/GraphAligner/CHM13Y_10H_5%_stable.gaf
./k8 mgutils.js stableGaf CHM13Y_40H.gfa Results/GraphAligner/CHM13Y_40H_5%.gaf > Results/GraphAligner/CHM13Y_40H_5%_stable.gaf
./k8 mgutils.js stableGaf CHM13Y_80H.gfa Results/GraphAligner/CHM13Y_80H_5%.gaf > Results/GraphAligner/CHM13Y_80H_5%_stable.gaf
./k8 mgutils.js stableGaf CHM13Y_95H.gfa Results/GraphAligner/CHM13Y_95H_5%.gaf > Results/GraphAligner/CHM13Y_95H_5%_stable.gaf
echo "Mapped reads to graphs"
