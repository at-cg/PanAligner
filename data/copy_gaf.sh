mkdir compare_erros/PanAligner
mkdir compare_erros/minigraph
mkdir compare_erros/GraphAligner

echo "Copying gafs for minigraph..."
cp Results/minigraph/CHM13Y_95H_5%.gaf compare_erros/minigraph/95H.gaf
cp Results/minigraph/CHM13Y_80H_5%.gaf compare_erros/minigraph/80H.gaf
cp Results/minigraph/CHM13Y_40H_5%.gaf compare_erros/minigraph/40H.gaf
cp Results/minigraph/CHM13Y_10H_5%.gaf compare_erros/minigraph/10H.gaf
# cp Results/minigraph/CHM13Y_L_5%.gaf compare_erros/minigraph/1H.gaf

echo "Copying gafs for PanAligner..."
cp Results/minichain/CHM13Y_95H_5%.gaf compare_erros/PanAligner/95H.gaf
cp Results/minichain/CHM13Y_80H_5%.gaf compare_erros/PanAligner/80H.gaf
cp Results/minichain/CHM13Y_40H_5%.gaf compare_erros/PanAligner/40H.gaf
cp Results/minichain/CHM13Y_10H_5%.gaf compare_erros/PanAligner/10H.gaf
# cp Results/minichain/CHM13Y_L_5%.gaf compare_erros/PanAligner/1H.gaf

echo "Copying gafs for GraphAligner..."
cp Results/GraphAligner/CHM13Y_95H_5%_stable.gaf compare_erros/GraphAligner/95H.gaf
cp Results/GraphAligner/CHM13Y_80H_5%_stable.gaf compare_erros/GraphAligner/80H.gaf
cp Results/GraphAligner/CHM13Y_40H_5%_stable.gaf compare_erros/GraphAligner/40H.gaf
cp Results/GraphAligner/CHM13Y_10H_5%_stable.gaf compare_erros/GraphAligner/10H.gaf
# cp Results/GraphAligner/CHM13Y_L_5%_stable.gaf compare_erros/GraphAligner/1H.gaf
