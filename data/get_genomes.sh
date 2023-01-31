conda activate minichain_data
echo "Downloading Genomes..."
curl -o HPRC-yr1.agc https://zenodo.org/record/5826274/files/HPRC-yr1.agc?download=1
echo "Extracting Genomes..."
agc getcol -o . HPRC-yr1.agc
