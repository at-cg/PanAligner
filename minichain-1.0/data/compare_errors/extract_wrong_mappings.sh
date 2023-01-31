cp ../k8-Linux .
cp ../paftools.js .
echo "Extracting wrong mappings for minichain..."
./k8-Linux paftools.js mapeval -Q0 minichain/1H.gaf | sed -n "/^E/p" -  > minichain/wrong_mappings_1H.gaf
./k8-Linux paftools.js mapeval minichain/1H.gaf | awk '{ print $6 }' | tail -n 1 - > minichain/count_mappings_1H.gaf
./k8-Linux paftools.js mapeval -Q0 minichain/10H.gaf | sed -n "/^E/p" -  > minichain/wrong_mappings_10H.gaf
./k8-Linux paftools.js mapeval minichain/10H.gaf | awk '{ print $6 }' | tail -n 1 - > minichain/count_mappings_10H.gaf
./k8-Linux paftools.js mapeval -Q0 minichain/40H.gaf | sed -n "/^E/p" -  >minichain/wrong_mappings_40H.gaf
./k8-Linux paftools.js mapeval minichain/40H.gaf | awk '{ print $6 }' | tail -n 1 - > minichain/count_mappings_40H.gaf
./k8-Linux paftools.js mapeval -Q0 minichain/80H.gaf | sed -n "/^E/p" -  > minichain/wrong_mappings_80H.gaf
./k8-Linux paftools.js mapeval minichain/80H.gaf | awk '{ print $6 }' | tail -n 1 - > minichain/count_mappings_80H.gaf
./k8-Linux paftools.js mapeval -Q0 minichain/95H.gaf | sed -n "/^E/p" -  >minichain/wrong_mappings_95H.gaf
./k8-Linux paftools.js mapeval minichain/95H.gaf | awk '{ print $6 }' | tail -n 1 - > minichain/count_mappings_95H.gaf
echo "Extracted wrong mappings for minichain!"

echo "Extracting wrong mappings for minigraph..."
./k8-Linux paftools.js mapeval -Q0 minigraph/1H.gaf | sed -n "/^E/p" -  > minigraph/wrong_mappings_1H.gaf
./k8-Linux paftools.js mapeval minigraph/1H.gaf | awk '{ print $6 }' | tail -n 1 - > minigraph/count_mappings_1H.gaf
./k8-Linux paftools.js mapeval -Q0 minigraph/10H.gaf | sed -n "/^E/p" -  > minigraph/wrong_mappings_10H.gaf
./k8-Linux paftools.js mapeval minigraph/10H.gaf | awk '{ print $6 }' | tail -n 1 - > minigraph/count_mappings_10H.gaf
./k8-Linux paftools.js mapeval -Q0 minigraph/40H.gaf | sed -n "/^E/p" -  > minigraph/wrong_mappings_40H.gaf
./k8-Linux paftools.js mapeval minigraph/40H.gaf | awk '{ print $6 }' | tail -n 1 - > minigraph/count_mappings_40H.gaf
./k8-Linux paftools.js mapeval -Q0 minigraph/80H.gaf | sed -n "/^E/p" -  > minigraph/wrong_mappings_80H.gaf
./k8-Linux paftools.js mapeval minigraph/80H.gaf | awk '{ print $6 }' | tail -n 1 - > minigraph/count_mappings_80H.gaf
./k8-Linux paftools.js mapeval -Q0 minigraph/95H.gaf | sed -n "/^E/p" -  > minigraph/wrong_mappings_95H.gaf
./k8-Linux paftools.js mapeval minigraph/95H.gaf | awk '{ print $6 }' | tail -n 1 - > minigraph/count_mappings_95H.gaf
echo "Extracted wrong mappings for minigraph!"


echo "Extracting wrong mappings for GraphAligner..."
./k8-Linux paftools.js mapeval -Q0 GraphAligner/1H.gaf | sed -n "/^E/p" -  > GraphAligner/wrong_mappings_1H.gaf
./k8-Linux paftools.js mapeval GraphAligner/1H.gaf | awk '{ print $6 }' | tail -n 1 - > GraphAligner/count_mappings_1H.gaf
./k8-Linux paftools.js mapeval -Q0 GraphAligner/10H.gaf | sed -n "/^E/p" -  > GraphAligner/wrong_mappings_10H.gaf
./k8-Linux paftools.js mapeval GraphAligner/10H.gaf | awk '{ print $6 }' | tail -n 1 - > GraphAligner/count_mappings_10H.gaf
./k8-Linux paftools.js mapeval -Q0 GraphAligner/40H.gaf | sed -n "/^E/p" -  > GraphAligner/wrong_mappings_40H.gaf
./k8-Linux paftools.js mapeval GraphAligner/40H.gaf | awk '{ print $6 }' | tail -n 1 - > GraphAligner/count_mappings_40H.gaf
./k8-Linux paftools.js mapeval -Q0 GraphAligner/80H.gaf | sed -n "/^E/p" -  > GraphAligner/wrong_mappings_80H.gaf
./k8-Linux paftools.js mapeval GraphAligner/80H.gaf | awk '{ print $6 }' | tail -n 1 - > GraphAligner/count_mappings_80H.gaf
./k8-Linux paftools.js mapeval -Q0 GraphAligner/95H.gaf | sed -n "/^E/p" -  > GraphAligner/wrong_mappings_95H.gaf
./k8-Linux paftools.js mapeval GraphAligner/95H.gaf | awk '{ print $6 }' | tail -n 1 - > GraphAligner/count_mappings_95H.gaf
echo "Extracted wrong mappings for GraphAligner!"


echo "Extracting wrong mappings for GraphChainer..."
./k8-Linux paftools.js mapeval -Q60 GraphChainer/1H.gaf | sed -n "/^E/p" -  > GraphChainer/wrong_mappings_1H.gaf
./k8-Linux paftools.js mapeval GraphChainer/1H.gaf | awk '{ print $6 }' | tail -n 1 - > GraphChainer/count_mappings_1H.gaf
./k8-Linux paftools.js mapeval -Q60 GraphChainer/10H.gaf | sed -n "/^E/p" -  > GraphChainer/wrong_mappings_10H.gaf
./k8-Linux paftools.js mapeval GraphChainer/10H.gaf | awk '{ print $6 }' | tail -n 1 - > GraphChainer/count_mappings_10H.gaf
./k8-Linux paftools.js mapeval -Q60 GraphChainer/40H.gaf | sed -n "/^E/p" -  > GraphChainer/wrong_mappings_40H.gaf
./k8-Linux paftools.js mapeval GraphChainer/40H.gaf | awk '{ print $6 }' | tail -n 1 - > GraphChainer/count_mappings_40H.gaf
./k8-Linux paftools.js mapeval -Q60 GraphChainer/80H.gaf | sed -n "/^E/p" -  > GraphChainer/wrong_mappings_80H.gaf
./k8-Linux paftools.js mapeval GraphChainer/80H.gaf | awk '{ print $6 }' | tail -n 1 - > GraphChainer/count_mappings_80H.gaf
./k8-Linux paftools.js mapeval -Q60 GraphChainer/95H.gaf | sed -n "/^E/p" -  > GraphChainer/wrong_mappings_95H.gaf
./k8-Linux paftools.js mapeval GraphChainer/95H.gaf | awk '{ print $6 }' | tail -n 1 - > GraphChainer/count_mappings_95H.gaf
echo "Extracted wrong mappings for GraphChainer!"
