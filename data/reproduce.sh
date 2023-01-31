echo "Getting dependencies..."
sh get_deps.sh
echo "Downloading genomes..."
sh get_genomes.sh
echo "Simulating Reads..."
sh simulated_reads.sh
echo "Generating graphs..."
sh generate_graphs.sh
echo "Mapping reads to linear CHM13Y reference..."
sh Linear_run.sh
echo "Mapping reads to graphs..."
sh graph_run.sh
echo "Copying gafs..."
sh copy_gaf.sh
echo "Evaluating results..."
sh evaluate.sh
echo "Results reproduced!"