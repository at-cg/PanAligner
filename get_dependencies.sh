#!/bin/bash
# Install all dependencies

echo "Installing minigraph..."
git clone https://github.com/lh3/minigraph.git
cd minigraph && make
cd ../

echo "Compiling PanAligner..."
make


# wget https://docs.conda.io/en/latest/miniconda.html#linux-installers
# bash Miniconda3-latest-Linux-x86_64.sh

echo "Installing seqtk..."
conda install -c bioconda seqtk