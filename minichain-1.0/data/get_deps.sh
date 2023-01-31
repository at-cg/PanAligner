echo "Getting agc, pbsim2, imagemagick and samtools with conda..."
conda create -n minichain_data
conda activate minichain_data
conda install -y -c bioconda agc pbsim2 samtools seqkit gfatools
conda install -y -c conda-forge imagemagick gnuplot 
conda deactivate

echo "Getting k8 ..."
curl -L https://github.com/attractivechaos/k8/releases/download/v0.2.4/k8-0.2.4.tar.bz2 | tar -jxf -
cp k8-0.2.4/k8-`uname -s` k8

echo "Getting Minigraph ..."
git clone https://github.com/lh3/minigraph
cd minigraph && make
cd ..

echo "Getting Minimap2 ..."
git clone https://github.com/lh3/minimap2
cd minimap2 && make
cd ..

echo "Getting paftools.js and mgutils.js ..."
cp minigraph/misc/mgutils.js mgutils.js 
cp minimap2/misc/paftools.js paftools.js 

echo "Getting GraphAligner..."
git clone https://github.com/maickrau/GraphAligner.git
cd GraphAligner
git submodule update --init --recursive
conda env create -f CondaEnvironment_linux.yml
conda activate GraphAligner
make -j32
conda deactivate
cd ..

echo "Getting GraphChainer..."
git clone https://github.com/algbio/GraphChainer.git
git submodule update --init --recursive
conda env create -f CondaEnvironment.yml
conda activate GraphChainer
make -j32
conda deactivate
cd ..

echo "Getting P6C4.model ..."
wget https://raw.githubusercontent.com/yukiteruono/pbsim2/master/data/P6C4.model

echo "Installed dependencies."
