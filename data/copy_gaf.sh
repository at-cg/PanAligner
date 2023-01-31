mkdir compare_erros/minichain
mkdir compare_erros/minigraph
mkdir compare_erros/GraphAligner
mkdir compare_erros/GraphChainer

echo "Copying gafs for minigraph..."
cp Results/minigraph/CHM13Y_95H_5%.gaf compare_erros/minigraph/95H.gaf
cp Results/minigraph/CHM13Y_80H_5%.gaf compare_erros/minigraph/80H.gaf
cp Results/minigraph/CHM13Y_40H_5%.gaf compare_erros/minigraph/40H.gaf
cp Results/minigraph/CHM13Y_10H_5%.gaf compare_erros/minigraph/10H.gaf
cp Results/minigraph/CHM13Y_L_5%.gaf compare_erros/minigraph/1H.gaf

echo "Copying gafs for minichain..."
cp Results/minichain/CHM13Y_95H_5%.gaf compare_erros/minichain/95H.gaf
cp Results/minichain/CHM13Y_80H_5%.gaf compare_erros/minichain/80H.gaf
cp Results/minichain/CHM13Y_40H_5%.gaf compare_erros/minichain/40H.gaf
cp Results/minichain/CHM13Y_10H_5%.gaf compare_erros/minichain/10H.gaf
cp Results/minichain/CHM13Y_L_5%.gaf compare_erros/minichain/1H.gaf

echo "Copying gafs for GraphChainer..."
cp Results/GraphChainer/CHM13Y_95H_5%_stable.gaf compare_erros/GraphChainer/95H.gaf
cp Results/GraphChainer/CHM13Y_80H_5%_stable.gaf compare_erros/GraphChainer/80H.gaf
cp Results/GraphChainer/CHM13Y_40H_5%_stable.gaf compare_erros/GraphChainer/40H.gaf
cp Results/GraphChainer/CHM13Y_10H_5%_stable.gaf compare_erros/GraphChainer/10H.gaf
cp  Results/GraphChainer/CHM13Y_L_5%_stable.gaf compare_erros/GraphChainer/1H.gaf

echo "Copying gafs for GraphAligner..."
cp Results/GraphAligner/CHM13Y_95H_5%_stable.gaf compare_erros/GraphAligner/95H.gaf
cp Results/GraphAligner/CHM13Y_80H_5%_stable.gaf compare_erros/GraphAligner/80H.gaf
cp Results/GraphAligner/CHM13Y_40H_5%_stable.gaf compare_erros/GraphAligner/40H.gaf
cp Results/GraphAligner/CHM13Y_10H_5%_stable.gaf compare_erros/GraphAligner/10H.gaf
cp Results/GraphAligner/CHM13Y_L_5%_stable.gaf compare_erros/GraphAligner/1H.gaf
