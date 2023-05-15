# <a name="started"></a>Getting Started

```sh
git clone https://github.com/at-cg/PanAligner
cd PanAligner && make
# Map sequence to graph
./PanAligner -cx lr test/MT.gfa test/MT-orangA.fa > out.gaf
```

## Table of Contents

- [Getting Started](#started)
- [Introduction](#intro)
- [Users' Guide](#uguide)
  - [Installation](#install)
  - [Sequence mapping](#map)
  - [Benchmark](#bench)
- [Future work](#future_work)
- [Credits](#credit)

## <a name="intro"></a>Introduction

PanAligner is an efficient end-to-end long-read aligner for cyclic pangenome graphs. It utilize co-linear chaining and iterative algorithms to achieve optimal alignment while imposing gap penalties. PanAligner leverages [minichain](https://github.com/at-cg/minichain.git) approach for aligning reads to directed acyclic graphs (DAGs). It incorporates open-source code from [minichain](https://github.com/at-cg/minichain.git), [minigraph](https://github.com/lh3/minigraph.git), and [GraphChainer](https://github.com/algbio/GraphChainer.git) for other necessary components besides co-linear chaining. PanAligner can scale to human pangenome graphs for read alignment and offers practical usage of time and memory resources.

## <a name="uguide"></a>Users' Guide

### <a name="install"></a>Installation

#### Dependencies
1) [gcc9][gcc9] or later version
2) [zlib][zlib]


### <a name="map"></a>Sequence mapping
PanAligner is a versatile tool that can be used for both sequence-to-sequence mapping and sequence-to-graph mapping. PanAligner is built on top of the [Minichain][minichain] code-base and supports base level alignment with the [graph wavefront alignment algorithm][gwfa]. \
PanAligner offers support for both sequence-to-sequence alignment and sequence-to-graph mapping. For sequence-to-sequence alignment, PanAligner maps a read to a reference in fasta format and provide read mapping output in [PAF][paf] format. For sequence-to-graph mapping, Minicycle takes the graph in [GFA][gfa1] and [rGFA][rGFA] format as input, and provides read mapping in [GAF][gaf] format.

```sh
# Map sequence to sequence
./PanAligner -cx lr test/MT-human.fa test/MT-orangA.fa > out.paf
# Map sequence to graph
./PanAligner -cx lr test/MT.gfa test/MT-orangA.fa > out.gaf
```

## <a name="bench"></a>Benchmark

PanAligner was evaluated against other sequence-to-graph aligners to assess its scalability and accuracy advantages. The evaluation utilized human pangenome graphs constructed from [94 high-quality haplotype assemblies](https://github.com/human-pangenomics/HPP_Year1_Assemblies) provided by the Human Pangenome Reference Consortium, along with the [CHM13 human genome assembly](https://www.ncbi.nlm.nih.gov/assembly/GCA_009914755.4) from the Telomere-to-Telomere consortium. Simulated long-read data with 0.5× sequencing coverage and 5% error-rate were used for the experiments, employing cyclic graphs of sizes 10H, 40H, and 95H, where the prefix integer represents the haplotype count in each graph. The results demonstrated superior read mapping precision, [as shown in the figure](#Plot). Notably, even on the largest graph with 95 haplotypes, PanAligner achieved efficient performance, requiring 2 hours and 36 minutes, 44 GB RAM, and 32 threads on [perlmutter CPU nodes](https://docs.nersc.gov/systems/perlmutter/architecture/#cpu-nodes).


<p align="center" id="Plot">
  <a href="./data/plot.png">
    <img src="./data/plot.png" width="750" alt="Plot">
  </a>
</p>

 
## <a name="future_work"></a>Future work
## Future Work

Future work for PanAligner will focus on the following directions:\

- Testing PanAligner's performance on pangenome graphs constructed using alternative methods like [PGGB][https://www.biorxiv.org/content/10.1101/2023.04.05.535718v1] and [Minigraph-Cactus](https://www.biorxiv.org/content/10.1101/2022.10.06.511217v2).
- Exploring formulations for haplotype-constrained co-linear chaining to control the exponential growth of combinatorial search space with the increasing number of haplotypes.
- Generalizing the proposed techniques for aligning reads to genome assembly graphs that contain cycles.


## <a name="credit"></a>Credits
PanAligner utilizes code base of [minigraph](https://github.com/lh3/minigraph.git) and [Minichain][minichain], released under MIT License.
Reference: [The design and construction of reference pangenome graphs with minigraph][paper_1] and [Sequence to graph alignment using gap-sensitive co-linear chaining.][paper_2]

[gwfa]: https://arxiv.org/abs/2206.13574
[paper_1]: https://genomebiology.biomedcentral.com/articles/10.1186/s13059-020-02168-z
[paper_2]: https://www.biorxiv.org/content/10.1101/2022.08.29.505691v2
[minichain]: https://github.com/at-cg/minichain
[zlib]: http://zlib.net/
[gcc9]: http://zlib.net/
[rgfa]: https://github.com/lh3/gfatools/blob/master/doc/rGFA.md
[gfa1]: https://github.com/GFA-spec/GFA-spec/blob/master/GFA1.md
[gaf]: https://github.com/lh3/gfatools/blob/master/doc/rGFA.md#the-graph-alignment-format-gaf
[paf]: https://github.com/lh3/miniasm/blob/master/PAF.md
