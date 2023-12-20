#!/bin/bash

# For seqtk
source ~/.bashrc
conda activate PA
MG=~/.PanAligner_deps/minigraph
PA=~/.PanAligner_deps/PanAligner

# Check if the user provided input files and output file
if [ "$#" -ne 4 ]; then
    echo "Usage: $0 <graph_file> <reads_file> <output_file> <threads>"
    exit 1
fi
graph_file="$1"
reads_file="$2"
output_file="$3"
threads="$4"

echo "Graph file: $graph_file"
echo "Reads file: $reads_file"
echo "No. of threads: $threads"
echo ""

# 1. Alignment with Minigraph
echo "Alignment of reads using minigraph"
$MG -t"$threads" -cx lr "$graph_file" "$reads_file" > minigraph_graph.gaf
echo ""

#2. Spliting the read file
echo "Spliting the read file"
cut -f 1-12 minigraph_graph.gaf > temp_MG_graph.gaf
awk '{count[$1]++; lines[$1]=$0} END {for (key in count) if (count[key] == 1) print lines[key]}' temp_MG_graph.gaf > temp1.txt
awk -F'\t' 'BEGIN{OFS="\t"} {count = gsub(/[<>]/, "", $6); $13 = (count == 0) ? 1 : count; print}' temp1.txt > temp2.txt
awk -F'\t' 'BEGIN{OFS="\t"} { $14 = $11 / $2; print }' temp2.txt > temp3.txt
awk -F'\t' '$12==60 && $13==1 && $14>=0.9' temp3.txt > MG_reads.txt
rm temp*

cut -f1 MG_reads.txt > MG_read_IDs.txt
# echo "seqtk 1"
seqtk subseq "$reads_file" MG_read_IDs.txt > hybridReads.fa
# echo "seqtk 2"
grep "^>" "$reads_file" | cut -c 2- > input_read_IDs.txt
comm -23 <(sort input_read_IDs.txt) <(sort MG_read_IDs.txt) > PA_read_IDs.txt
seqtk subseq "$reads_file" PA_read_IDs.txt > reads2.fa
rm MG*
rm PA*
rm in*
echo ""

#3. Read Alignment using PanAligner
echo "Alignment of reads using PanAligner"
# cd PanAligner
$PA -t"$threads" -cx lr "$graph_file" reads2.fa > PanAligner_result.gaf
# cd ..

#4. Hybrid alignment result
grep "^>" hybridReads.fa | cut -c 2- > temp_MG_read_IDs.txt
grep -F -f temp_MG_read_IDs.txt minigraph_graph.gaf > "$output_file"

rm temp_MG_read_IDs.txt

#concatenating hybrid alignment reads
echo "Alignment is done"
cat reads2.fa >> hybridReads.fa
cat PanAligner_result.gaf >> "$output_file"
rm reads2.fa
rm PanAligner_result.gaf
rm minigraph_graph.gaf

echo ""
echo "Hybrid alignment ouput is stored in $output_file"
echo "Hybrid reads are stored in PanAligner/hybridReads.fa"

