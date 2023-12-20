#!/bin/bash
# Install all dependencies

echo "Installing minigraph..."
git clone https://github.com/lh3/minigraph.git
cd minigraph && make -j
cd ../

make clean
echo "Compiling PanAligner..."
make -j

mkdir ~/.PanAligner_deps
cp minigraph/minigraph ~/.PanAligner_deps/
cp PanAligner ~/.PanAligner_deps/
rm -rf minigraph


# wget https://docs.conda.io/en/latest/miniconda.html#linux-installers
# bash Miniconda3-latest-Linux-x86_64.sh

echo "Installing seqtk..."
source ~/.bashrc
conda create --force -n PA -y
conda activate PA
conda install -c bioconda seqtk -y
