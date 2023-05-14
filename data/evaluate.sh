conda activate PanAligner_data
echo "Evaluating results for graphs..."

./k8 paftools.js mapeval Results/GraphAligner/CHM13Y_95H_5%_stable.gaf > CHM13Y_95H/GraphAligner_95H.eval
./k8 paftools.js mapeval Results/GraphAligner/CHM13Y_40H_5%_stable.gaf > CHM13Y_40H/GraphAligner_40H.eval
./k8 paftools.js mapeval Results/GraphAligner/CHM13Y_10H_5%_stable.gaf > CHM13Y_10H/GraphAligner_10H.eval

./k8 paftools.js mapeval Results/minigraph/CHM13Y_95H_5%.gaf > CHM13Y_95H/minigraph_95H.eval
./k8 paftools.js mapeval Results/minigraph/CHM13Y_40H_5%.gaf > CHM13Y_40H/minigraph_40H.eval
./k8 paftools.js mapeval Results/minigraph/CHM13Y_10H_5%.gaf > CHM13Y_10H/minigraph_10H.eval

./k8 paftools.js mapeval Results/PanAligner/CHM13Y_95H_5%.gaf > CHM13Y_95H/PanAligner_95H.eval
./k8 paftools.js mapeval Results/PanAligner/CHM13Y_40H_5%.gaf > CHM13Y_40H/PanAligner_10H.eval
./k8 paftools.js mapeval Results/PanAligner/CHM13Y_10H_5%.gaf > CHM13Y_10H/PanAligner_10H.eval

# echo "Evaluating results for linear genome..."
# ./k8 paftools.js mapeval Results/minigraph/CHM13Y_L_5%.gaf > CHM13Y/minigraph.eval
# ./k8 paftools.js mapeval Results/PanAligner/CHM13Y_L_5%.gaf > CHM13Y/PanAligner.eval
# ./k8 paftools.js mapeval  Results/GraphAligner/CHM13Y_L_5%_stable.gaf > CHM13Y/GraphAligner.eval

cd CHM13Y_95H
gnuplot roc.gp
convert -density 1200 95H.eps 95H.jpg
cd ..
cd CHM13Y_40H
gnuplot roc.gp
convert -density 1200 40H.eps 40H.jpg
cd ..
cd CHM13Y_10H
gnuplot roc.gp
convert -density 1200 10H.eps 10H.jpg
cd ..
# cd CHM13Y
# gnuplot roc.gp
# convert -density 1200 Linear.eps -resize 1920x1080 Linear.jpg
# cd ..
