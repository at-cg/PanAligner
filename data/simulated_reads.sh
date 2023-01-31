conda activate minichain_data

mkdir Reads
mkdir Ref
mkdir Results
mkdir Results/minimap2
mkdir Results/minigraph
mkdir Results/minichain
mkdir Results/GraphAligner
mkdir Results/GraphChainer

echo "Extracting reads..."
for i in $(seq 1 1 22)
do
	echo "Extracting chr$i ..."
	samtools faidx CHM13Y.fa chr$i > Ref/chr$i.fasta
done
samtools faidx CHM13Y.fa chrX > Ref/chr23.fasta
samtools faidx CHM13Y.fa chrY > Ref/chr24.fasta

echo "Indexing chromosomes..."
for i in $(seq 1 1 24)
do
	samtools faidx Ref/chr$i.fasta
	echo "Indexed chr$i"
done
echo "Indexed chromosomes."


echo "Simulating reads..."
for i in $(seq 1 1 24)
do
	echo "Simulating reads for chr$i ... "
	pbsim --depth 0.5 --length-min 10000 --length-mean 10000 --length-max 10000 --accuracy-mean 0.95 --accuracy-max 0.95 --accuracy-min 0.95 --hmm_model P6C4.model Ref/chr$i.fasta --prefix Ref/chr_
	mv Ref/chr__0001.maf Ref/chr$i.maf
	rm -rf Ref/chr_*
    echo "Simulated reads for chr$i"
done
echo "Finished simulating reads for CHM13Y with 5% error rate"

echo "Embedding metadata to reads..."
for i in $(seq 1 1 24)
do
	./k8 paftools.js pbsim2fq Ref/chr$i.fasta.fai Ref/chr$i.maf > Reads/read_chr$i.fa
	echo "Processed chr$i"
done
cat Reads/read_* > Reads/CHM13Y_reads_5%.fa
echo "Finished embedding metadata to reads with "pbsim2fq""


