# <a name="started"></a>Getting Started

```sh
git clone https://github.com/at-cg/minicycle
cd minicycle && make
# Map sequence to graph
./minicycle -cx lr test/MT.gfa test/MT-orangA.fa > out.gaf
```

## Table of Contents

- [Getting Started](#started)
- [Introduction](#intro)
- [Users' Guide](#uguide)
  - [Installation](#install)
  - [Sequence mapping](#map)
  - [Sequence mapping](#bench)
- [Future work](#future_work)
- [Credits](#credit)

## <a name="intro"></a>Introduction

Minicycle is a sequence-to-graph aligner. It uses a co-linear chaining algorithm to achieve optimal alignment and imposes penalties for gap costs. \
Minicycle can scale to human pangenome graphs for read alignment and offers practical usage of time and memory resources.

## <a name="uguide"></a>Users' Guide

### <a name="install"></a>Installation

#### Dependencies
1) [gcc9][gcc9] or later version
2) [zlib][zlib]


### <a name="map"></a>Sequence mapping
Minicycle is a versatile tool that can be used for both sequence-to-sequence mapping and sequence-to-graph mapping. Minicycle is built on top of the [Minichain][minichain] code-base and supports base level alignment with the [graph wavefront alignment algorithm][gwfa]. \
Minicycle offers support for both sequence-to-sequence alignment and sequence-to-graph mapping. For sequence-to-sequence alignment, Minicycle maps a read to a reference in fasta format and provide read mapping output in [PAF][paf] format. For sequence-to-graph mapping, Minicycle takes the graph in [GFA][gfa1] and [rGFA][rGFA] format as input, and provides read mapping in [GAF][gaf] format.

```sh
# Map sequence to sequence
./minicycle -cx lr test/MT-human.fa test/MT-orangA.fa > out.paf
# Map sequence to graph
./minicycle -cx lr test/MT.gfa test/MT-orangA.fa > out.gaf
```

## <a name="bench"></a>Benchmark
Minicycle has been compared to other sequence-to-graph aligners to demonstrate scalability and accuracy gains. The experiments were conducted using human pangenome graphs constructed from  [94 high-quality haplotype assemblies](https://github.com/human-pangenomics/HPP_Year1_Assemblies) provided by the Human Pangenome Reference Consortium and [CHM13 human genome assembly](https://www.ncbi.nlm.nih.gov/assembly/GCA_009914755.4) provided by the Telomere-to-Telomere consortium. The evaluation was performed on a simulated long-read dataset with 0.5x coverage, using graphs of two sizes. The results revealed superior read mapping precision ([as shown in the figure](#Plot)). Notably, on the largest graph constructed from all 95 haplotypes, Minicycle used 2 hours and 36 minutes, utilizing 44 GB RAM with 32 threads.

<p align="center" id="Plot">
  <a href="./data/plot.png">
    <img src="./data/plot.png" width="700" alt="Plot">
  </a>
</p>

<!-- 
## <a name="future_work"></a>Future work

* Extend minichain to support cyclic graphs.

* Extend minichain to support Graph generation. -->

## <a name="credit"></a>Credits
Minicycle utilizes code base of [Minichain][minichain], which is released under MIT License.
Reference: [Sequence to graph alignment using gap-sensitive co-linear chaining.][paper]

[gwfa]: https://arxiv.org/abs/2206.13574
[paper]: https://www.biorxiv.org/content/10.1101/2022.08.29.505691v2
[minichain]: https://github.com/at-cg/minichain
[zlib]: http://zlib.net/
[gcc9]: http://zlib.net/
[rgfa]: https://github.com/lh3/gfatools/blob/master/doc/rGFA.md
[gfa1]: https://github.com/GFA-spec/GFA-spec/blob/master/GFA1.md
[gaf]: https://github.com/lh3/gfatools/blob/master/doc/rGFA.md#the-graph-alignment-format-gaf
[paf]: https://github.com/lh3/miniasm/blob/master/PAF.md
