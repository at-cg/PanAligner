#ifndef __graphUtils__
#define __graphUtils__
#include "gfa.h"
#include "gfa-priv.h"
#include "kalloc.h"
#include "ksort.h"
#include "kvec.h"
#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <algorithm>
#include <queue>
#include <limits>
#include "minigraph.h"
#include "mgpriv.h"
#include <chrono> 
#include <omp.h>


// Anchors
struct Anchors {
	int v;
	int x;
	int y;
	int c;
	int d;
};

struct Tuples {
	int v;
	int w;
	int pos;
	int path;
	int anchor;
	int task;
	int top_v;
	int d;
};


// for flow graph
struct flowGraph {
	int N, M, S, T;
	std::vector<int> f, p, t, c;

	flowGraph(int NN) : N(NN+2) {
		init(N);
		S = NN;
		T = NN + 1;
	}

	void init(int N) {
		f.clear();
		f.resize(N, 0);
		t.clear();
		t.resize(2);
		p = t;
		c = t;
	}

	void add_edge(int i, int j, int cap) {
		// std::cerr << "add edge " << i << " " << j << "  " << cap << std::endl;
		p.push_back(j);
		t.push_back(f[i]);
		c.push_back(cap);
		f[i] = t.size() - 1;
	}
};


class graphUtils
{
	public:
	gfa_t *g; // This is Graph 
	std::vector<int> *adj_;
	std::vector<std::vector<int>> conn_comp;
	std::vector<int> component;
	int num_comp;
	int n_vtx;
	std::vector<std::vector<int>>  *adj_cc;
	int num_cid;
	std::vector<std::vector<int>> top_order;
	//count of characters in a node
	std::vector<int> node_len;
	// Chaining (Revised Algorithm)
	std::vector<std::vector<std::vector<int>>> index; // index
	std::vector<std::vector<std::vector<int>>> rev_index; // rev_index
	std::vector<std::vector<std::vector<int>>> last2reach; // last2reach
	std::vector<std::vector<std::vector<int64_t>>> dist2begin; // dist2begin
	std::vector<std::vector<std::vector<int64_t>>> Distance; // dist2begin
	std::vector<std::vector<int>> component_idx;         // mapping between origional index and local index
	std::vector<std::vector<int>> idx_component;         // mapping between local index and origional index
	std::vector<std::vector<std::vector<int>>> path_cover; // Path Cover
	// in_node and out_node computation 
	std::vector<std::vector<std::vector<int>>> in_node;
	std::vector<std::vector<std::vector<int>>> out_node;
	/* Map Top_Sort */
	std::vector<std::vector<int>> map_top_sort;	
	float scale_factor;
	bool param_z;
	int lin_ref = 0;

  
    graphUtils(gfa_t *g); // This is constructor

    void read_graph();
    
    void print_graph();

    int is_cyclic();

    void Connected_components();

    void topologicat_sort();

    void MPC();

    std::vector<std::vector<int>> shrink(int cid);

	std::vector<std::vector<mg128_t>> get_anchors();

    void MPC_index();

	std::vector<mg128_t> Chaining(std::vector<mg128_t> anchors);

};

// map-algo.c
void get_Op(graphUtils *graphOp);

// RMaxQ
template<typename T>
struct SegmentTree {
	int N;
	std::vector<T> t;
	int ql, qr;
	T qx;

	int get_upper_bit(int N) {
		int x = N & -N;
		while (x != N) {
			N ^= x;
			x = N & -N;
		}
		return x << 1;
	}
	static int ID(int l, int r) {
		return l + r - 1;
	}
	SegmentTree(int N_, T value) : N(get_upper_bit(N_)) {
		reset(value);
	}
	void reset(T value) {
		t.clear();
		t.resize(N*2, value);
	}
	void add(int x, T value) {
		ql = x; qx = value;
		add_(0, N);
	}
	void add_(int l, int r) {
		t[ID(l, r)] = std::max(t[ID(l, r)], qx);
		if (l + 1 == r)
			return;
		int m = (l + r) >> 1;
		if (ql < m)
			add_(l, m);
		else
			add_(m, r);
	}
	T RMQ(int l, int r) {
		if (l > r)
			return t[0];
		ql = l; qr = r + 1;
		return RMQ_(0, N);
	}
	T RMQ_(int l, int r) {
		// if (ql==27579&&qr==27605+1) cout<<"now "<<ID(l,r)<<"  "<<l<<" "<<r<<" : "<<t[ID(l,r)].first<<" "<<t[ID(l,r)].second<<endl;
		if (ql <= l && r <= qr)
			return t[ID(l, r)];
		int m = (l + r) >> 1;
		if (qr <= m)
			return RMQ_(l, m);
		if (m <= ql)
			return RMQ_(m, r);
		return std::max(RMQ_(l, m), RMQ_(m, r));
	}
};

template<typename T, typename V>
struct Treap {
	struct Node {
		int ls, rs, size, pri;
		T key;
		V value, max;
	};
	std::vector<Node> t;
	int root;
	V default_value;
	Treap(const V &default_value = V()) : default_value(default_value) {
		root = 0;
		t.resize(1);
	}
	inline int randomm() {
		static int seed = 703; 
		return seed = int(seed * 48271LL % 2147483647);
	}
	inline int update(int now) {
		t[now].size = 1;
		t[now].max = t[now].value;
		if (t[now].ls) {
			t[now].size += t[t[now].ls].size;
			t[now].max = max(t[now].max, t[t[now].ls].max);
		}
		if (t[now].rs) {
			t[now].size += t[t[now].rs].size;
			t[now].max = max(t[now].max, t[t[now].rs].max);
		}
		return now;
	}
	inline int new_node (T key, V value) {
		t.push_back(Node({ 0, 0, 1, randomm(), key, value, value }));
		return t.size() - 1;
	}
	int merge(int x, int y) {
		if (!x || !y) return x + y;
		if (t[x].pri > t[y].pri) {
			t[x].rs = merge(t[x].rs, y);
			return update(x);
		}
		else {
			t[y].ls = merge(x, t[y].ls);
			return update(y);
		}
	}
	void split(int now, T key, int &x, int &y) {
		if (!now) {
			x = y = 0; 
			return;
		}
		if (t[now].key <= key) {
			x = now;
			split(t[now].rs, key, t[now].rs, y);
			update(x);
		}
		else {
			y = now;
			split(t[now].ls, key, x, t[now].ls);
			update(y);
		}
	}
	// void Del(int &root, int key) {
	// 	int x = 0, y = 0, z = 0;
	// 	split(root, key, x, z);
	// 	split(x, key - 1, x, y);
	// 	y = merge(t[y].ls, t[y].rs);
	// 	root = merge(merge(x, y), z);
	// }
	void add(T key, V value) {
		int x = 0, y = 0, z = 0;
		split(root, key, x, y);
		root = merge(merge(x, new_node(key, value)), y);
	}	
	V RMQ(T l, T r) {
		int now = root;
		while (now != 0 && (t[now].key < l || t[now].key > r)) {
			if (t[now].key < l)
				now = t[now].rs;
			else
				now = t[now].ls;
		}
		if (now == 0) {
			return default_value;
		}
		V ret = t[now].value;
		int x = t[now].ls;
		while (x != 0) {
			if (t[x].key >= l) {
				ret = max(ret, t[x].value);
				if (t[x].rs != 0)
					ret = max(ret, t[t[x].rs].max);
				x = t[x].ls;
			}
			else
				x = t[x].rs;
		}
		int y = t[now].rs;
		while (y != 0) {
			if (t[y].key <= r) {
				ret = max(ret, t[y].value);
				if (t[y].ls != 0)
					ret = max(ret, t[t[y].ls].max);
				y = t[y].rs;
			}
			else
				y = t[y].ls;
		}
		return ret;
	}
};

typedef Treap<int, std::pair<int64_t, int>> IndexT;

#endif
