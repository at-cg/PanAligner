## <a name="started"></a>Getting Started

```sh
git clone https://github.com/at-cg/minichain
cd minichain && make
# Map sequence to graph
./minichain -cx lr test/MT.gfa test/MT-orangA.fa > out.gaf
```

## Table of Contents

- [Getting Started](#started)
- [Introduction](#intro)
- [Users' Guide](#uguide)
  - [Installation](#install)
  - [Sequence mapping](#map)
- [Future work](#future_work)
- [Credits](#credit)

## <a name="intro"></a>Introduction

minichain is a sequence-to-DAG mapper, which utilises gap sensetive co-linear chaining heuristic to align long reads to DAG. \
minichain is scalable to Pangenome graphs generated with whole-genome human haplotypes and can map reads within reasonable runtime and memory limits.

## <a name="uguide"></a>Users' Guide

### <a name="install"></a>Installation

#### Dependencies
1) [gcc9][gcc9] or later version
2) [zlib][zlib]


### <a name="map"></a>Sequence mapping
minichain can be used for sequence-to-sequence mapping as well as sequence-to-DAG mapping. Since minichain utilises [minigraph][minigraph] code-base, hence base level alignment is supported with [graph wavefront alignment algorithm][gwfa].
```sh
# Map sequence to sequence
./minichain -cx lr test/MT-human.fa test/MT-orangA.fa > out.paf
# Map sequence to graph
./minichain -cx lr test/MT.gfa test/MT-orangA.fa > out.gaf
```

## <a name="future_work"></a>Future work

* Extend minichain to support cyclic graphs.

* Extend minichain to support Graph generation.

## <a name="credit"></a>Credits
minichain utilises code base of [minigraph][minigraph], which is released under MIT License.
Reference: [The design and construction of reference pangenome graphs with minigraph.][paper]

[gwfa]: https://arxiv.org/abs/2206.13574
[paper]: https://doi.org/10.1186/s13059-020-02168-z
[minigraph]: https://github.com/lh3/minigraph
[zlib]: http://zlib.net/
[gcc9]: http://zlib.net/
[rgfa]: https://github.com/lh3/gfatools/blob/master/doc/rGFA.md
[gfa1]: https://github.com/GFA-spec/GFA-spec/blob/master/GFA1.md
