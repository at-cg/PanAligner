#include "graphUtils.h"
//typedef std::pair<int, int> pairs;
std::vector<std::vector<std::vector<int>>> cyclic_innode, cyclic_outnode;
std::vector<std::vector<int64_t>> D_cyclic;
int edges_rm=0;

//Cyclic to DAG conversion
//Function to get the vertex order for SCC computation Using DFS
void Fillorder(std::vector<std::vector<int>> &un_adj, std::vector<bool> &visited, int u, std::stack<int> &stack)
{
    visited[u]=true;
    for (auto v:un_adj[u])
        {
            if (!visited[v])
            {
                Fillorder(un_adj, visited, v, stack);
            }
        }
    //// std::cerr<<u<<" ";
    stack.push(u);
}

//Function to get the Transpose of graph
void Transpose_G(std::vector<std::vector<int>> &un_adj, std::vector<std::vector<int>> &T_adj, int n_vtx)
{
    for (int v = 0; v < n_vtx; ++v)
    {
        for (auto x : un_adj[v])
            T_adj[x].push_back(v);
    }
}

//DFS to find SCC
void DFS_SCC(std::vector<std::vector<int>> &adj, std::vector<bool> &visited, int u, std::vector<int> &component, int num_components, std::stack<int> &stack)
{
    visited[u]=true;
    //// std::cerr<<u<<" ";
    component[u]=num_components;
    for (auto x : adj[u])
        if(!visited[x])
            DFS_SCC(adj, visited, x, component, num_components, stack);
}

/*void SCC_DFS(std::vector<std::vector<int>> &adj, std::vector<bool> &visited, std::vector<bool> &mask, int u, std::vector<int> &v_seq)
{
    if(mask[u]==true)
    {
        v_seq.push_back(u);
        visited[u]=true;
        for(auto &v : adj[u])
            if(visited[v]==false)
                SCC_DFS(adj, visited, mask, v, v_seq);
    }
}*/

//Computing SCC
void SCC(std::vector<std::vector<int> > &adj, int n_vtx)
{
    int vtx;
    std::stack<int> stack, dfs_order;
    size_t num_components, comp_size;
    std::vector<std::vector<int> > conn_comp, T_adj(n_vtx), adj_(n_vtx), comp_adj;
    std::vector<int> component, v_seq, s_index(n_vtx), v_sequence;
    
    for (int v = 0; v < n_vtx; ++v)
    {
        for (auto x : adj[v])
        {
            if(v!=x)
                adj_[v].push_back(x);
            //edge++;
        }
            
    }   
    //printGraph(adj, n_vtx);
    adj.clear();
    adj.resize(n_vtx);
    //printGraph(adj_, n_vtx);

    //Get the vertex order
    std::vector<bool> visited(n_vtx,false), mask(n_vtx, false);
    for (int u = 0; u < n_vtx; u++)
    {
        if (visited[u] == false)
        {
           Fillorder(adj_, visited, u, stack);
        }
    }
    visited.clear();

    //get the transpose graph
    Transpose_G(adj_, T_adj, n_vtx);

    //Get the SCC
    for (int i = 0; i < n_vtx; i++)
        visited.push_back(false);
    
    num_components = 0;
    component.resize(n_vtx);  

    while (!stack.empty())
    {
        int s = stack.top();
        stack.pop();
        if(visited[s]== false)
        {
            DFS_SCC(T_adj, visited, s, component, num_components, stack);
            num_components++;
            //// std::cerr<<"\n";
        }

    } 
    visited.clear();

    for (int i = 0; i < n_vtx; i++)
        visited[i]=false;

    // Storing Connected Components
    conn_comp.resize(num_components);
    for (int i = 0; i < n_vtx; i++)
    {
        conn_comp[component[i]].push_back(i); // Add Vertex to it's component
    }

    /*// std::cerr<<"Total number of SCCs are: "<<num_components<<"\n";
    for(size_t i=0; i< num_components; i++)
    {
        // std::cerr<<"SCC "<<i<<" : [";
        for (auto &v: conn_comp[i])
        {
            // std::cerr<<v<<" ";
        }
        // std::cerr<<"]\n";
    }*/

    /*for(size_t i=0; i< num_components; i++)
    {
        if(conn_comp[i].size() == 1)
        {
            for(auto &j : conn_comp[i])
                for(auto &v : adj_[j])
                    adj[j].push_back(v);
        }
        else
        {
            for(auto &k : conn_comp[i])
                mask[k]=true;
            for (auto &a: conn_comp[i])
            {
                if (visited[a]==false)
                    SCC_DFS(adj_, visited, mask, a, v_seq);

            }
            //vtx=conn_comp[i][0];
            //// std::cerr<<"starting vertex"<<vtx;
            //SCC_DFS(adj_, visited, mask, vtx, v_seq);


            for(size_t j=0; j< conn_comp[i].size(); j++)
            {
                //// std::cerr<<"\n"<<v_seq[j]<<" ";
                s_index[v_seq[j]]=j;
            }

            for(auto &k : conn_comp[i])
                for(auto &v : adj_[k])
                {
                    if(mask[v]==false)
                        adj[k].push_back(v);
                    else if(s_index[k] < s_index[v])
                        adj[k].push_back(v);
                }
            for(auto &k : conn_comp[i])
                mask[k]=false;
            
            v_seq.clear();  
            visited.clear();

        for (int i = 0; i < n_vtx; i++)
            visited[i]=false;      
        }
    }*/
    int num_cid=num_components;
    std::vector<std::vector<int> > component_idx(num_cid), idx_component(num_cid);
    // Map Components
    for (size_t cid = 0; cid < num_cid; cid++)
    {   
        //// std::cerr<<conn_comp[cid].size()<<" ";
        component_idx[cid].resize(conn_comp[cid].size());
        idx_component[cid].resize(n_vtx);
        for (size_t j = 0; j < conn_comp[cid].size(); j++)
        {
            //// std::cerr<<conn_comp[cid][j]<<" ";
            component_idx[cid][j] = conn_comp[cid][j]; // map global to local
            //// std::cerr<<component_idx[cid][j]<<"\n";
            idx_component[cid][conn_comp[cid][j]] = j; // map local to global
            //// std::cerr<<idx_component[cid][conn_comp[cid][j]]<<"\n";

        }
    }
    // Adjacency list for all strongly connected components
    std::vector<std::vector<int>> *adj_scc;
    adj_scc = new std::vector<std::vector<int>>[num_components];
    for (size_t cid = 0; cid < num_cid; cid++)
    {   
        for (size_t i=0; i<conn_comp[cid].size(); i++)
        {
            visited[conn_comp[cid][i]]=true;
        }

        adj_scc[cid].resize(conn_comp[cid].size());
        for (auto &j : conn_comp[cid])
        {   
            for (size_t k = 0; k < adj_[j].size(); k++)
            {   
                if(visited[adj_[j][k]]==true)// && idx_component[cid][j]!= idx_component[cid][adj_[j][k]])
                    {
                    adj_scc[cid][idx_component[cid][j]].push_back(idx_component[cid][adj_[j][k]]);
                    }
            }
        }
        for (size_t i=0; i<conn_comp[cid].size(); i++)
        {
            visited[conn_comp[cid][i]]=false;
        }
    } 
    visited.clear();

    //Printing adjancency list of each SCC
    for (size_t cid = 0; cid < num_cid; cid++)
    {   
        comp_size=adj_scc[cid].size();
        comp_adj.resize(comp_size);
        std::vector<bool> visit(comp_size, false);
        std::vector<int> s_index(comp_size, 0);
        for (size_t j = 0; j < comp_size; j++)
        {   
            for (auto &k : adj_scc[cid][j])
            {  
                comp_adj[j].push_back(k);
            }
        }
        //printGraph(comp_adj, comp_size);
        if(comp_size > 1)
        {
            /*for (size_t u = 0; u < comp_size; u++)
            {
                if (visit[u] == false)
                {
                    Fillorder(comp_adj, visit, u, dfs_order);
                }
            }*/
            Fillorder(comp_adj, visit, 0, dfs_order);
            for (size_t u = 0; u < comp_size; u++)
            {
                v_sequence.push_back(dfs_order.top());
                dfs_order.pop();
            }

            for (size_t i = 0; i < comp_size; i++)
            {
                //// std::cerr<<v_sequence[i]<<" ";
                s_index[v_sequence[i]]=i;
            }
            
            adj_scc[cid].clear();
            adj_scc[cid].resize(comp_size);
            for (unsigned int v = 0; v < comp_size; ++v)
            {
                for (auto x : comp_adj[v])
                {
                    if(s_index[v] < s_index[x])
                        adj_scc[cid][v].push_back(x);
                }
            }
            comp_adj.clear();
            visit.clear();
            s_index.clear();
            v_sequence.clear();
        }
        /*// std::cerr<<"DAG converted components \n";
        for (size_t j = 0; j < comp_size; j++)
        {   
            // std::cerr<<j;
            for (auto &k : adj_scc[cid][j])
            {  
                // std::cerr<<"->"<<k;
            }
            // std::cerr<<"\n";
        }*/
    }
    for (int i = 0; i < n_vtx; i++)
    {
        visited[i]=false;
    }
    
    //Converted DAG
    adj.clear();
    adj.resize(n_vtx);
    for (size_t cid = 0; cid < num_cid; cid++)
    {   
        for (size_t i=0; i<conn_comp[cid].size(); i++)
        {
            visited[conn_comp[cid][i]]=true;
        }
        for (auto &j : conn_comp[cid])
        {   
            for(auto &v : adj_[j])
                if(visited[v]==false)
                    adj[j].push_back(v);
            
            for(auto &u : adj_scc[cid][idx_component[cid][j]])
                adj[j].push_back(component_idx[cid][u]);
        }
        for (size_t i=0; i<conn_comp[cid].size(); i++)
        {
            visited[conn_comp[cid][i]]=false;
        }
    } 
    //printGraph(adj, n_vtx);
     
}
graphUtils::graphUtils(gfa_t *g)
{
    this->g = g;
}

// Read and store the Graph in Adjacency list
void graphUtils::read_graph()
{
    uint32_t v;
    n_vtx = gfa_n_vtx(g);
    // Resize node_len
    node_len.resize(n_vtx, 0);
    // Array of vectors
    adj_ = new std::vector<int>[n_vtx];
    /* Node_len */
    for (int v = 0; v < n_vtx/2; v++)
    {
        gfa_seg_t segment = (g)->seg[v];
        int len =  segment.len;
        node_len[2*v] = len;
        node_len[2*v + 1] = len;
    }
    // look for all the edges , if the sum of all the 
    // edges are zero then, that's a linear reference
    u_int32_t num_edges = 0;
    for (v = 0; v < n_vtx; v++)
    {
        gfa_arc_t *av = gfa_arc_a(g, v);
        int n_edges = gfa_arc_n(g, v);
        int v_ = av->v_lv >> 32;
        // std::cerr << " node : " << v << " node_len : " << node_len[v] << std::endl; 
        for (int i = 0; i < n_edges; i++)
        {
            num_edges++;
        }
    }


    for (v = 0; v < n_vtx; v++)
    {
        gfa_arc_t *av = gfa_arc_a(g, v);
        int n_edges = gfa_arc_n(g, v);
        if (num_edges == 0) // Linear Reference
        {
            lin_ref = 1; // Mark as a linear reference
        }else
        {
            int v_ = av->v_lv >> 32;
            // std::cerr << " node : " << v << " node_len : " << node_len[v] << std::endl; 
            for (int i = 0; i < n_edges; i++)
            {
                uint32_t w = av[i].w;
                adj_[v_].push_back(w);
            }
        }
    }

    if(param_z)
    {
        std::cerr<< "Number of nodes and edges in Cyclic graph : " <<n_vtx<<" "<<num_edges<<std::endl;
        // std::cerr<<"\nEdges in cyclic graph: "<<num_edges;
        // std::cerr<<"\nNumber of nodes in cyclic graph: "<<n_vtx<<std::endl;
    }
}

void graphUtils::print_graph()
{
    std::cerr << " This is Graph " << std::endl;
    for (size_t i = 0; i < n_vtx; i++)
    {
        std::cerr << i ;
        for (int &x : adj_[i])
        {
            std::cerr << "->"<<x;
        }
        std::cerr << std::endl;
    }
}

void DFS(std::vector<std::vector<int>> un_adj, std::vector<bool> &visited, int u, std::vector<int> &component, int num_components)
{
    std::stack<int> stack;

    // Push the source node
    stack.push(u);

    while (!stack.empty())
    {
        int s = stack.top();
        stack.pop();
        component[s] = num_components;

        if (!visited[s])
        {
            visited[s] = true;
        }
        
        for (auto v:un_adj[s])
        {
            if (!visited[v])
            {
                stack.push(v);
            }
        }
    } 

}

void graphUtils::Connected_components()
{
    //print_graph();
    std::vector<std::vector<int>> comp_adj;
    int comp_size, dag_edge=0, dag_vertex=0, adj_edge=0;
    size_t num_components;
    if (lin_ref == 1)
    {
        num_components = n_vtx;
        component.resize(n_vtx);
        for (int u = 0; u < n_vtx; u++) // Put unique nodes in unique cids
        {
            component[u] = u;
        }
    }else
    {

        // Create Adjacency list
        std::vector<std::vector<int>> un_adj;
        un_adj.resize(n_vtx); // u -> v
        for (int u = 0; u < n_vtx; u++)
        { //std::vector<std::vector<int>> adj(n_vtx);
            for (auto v:adj_[u])
            {
                un_adj[u].push_back(v);
                un_adj[v].push_back(u);
            }
        }

        num_components = 0;
        component.resize(n_vtx);  
        // run DFS
        std::vector<bool> visited(n_vtx,false);
        for (int u = 0; u < n_vtx; u++)
        {
            if (visited[u] == false)
            {
                DFS(un_adj,visited,u,component,num_components);
                num_components++;
            }
        } 
        un_adj.clear(); 
        visited.clear(); 
    }

    num_cid = num_components;
    // Storing Connected Components
    conn_comp.resize(num_components);
    for (int i = 0; i < n_vtx; i++)
    {
        conn_comp[component[i]].push_back(i); // Add Vertex to it's component
    }

    
    component_idx.resize(num_cid);
    idx_component.resize(num_cid);
    // Map Components
    for (size_t cid = 0; cid < num_cid; cid++)
    {
        component_idx[cid].resize(conn_comp[cid].size());
        idx_component[cid].resize(n_vtx);
        for (size_t j = 0; j < conn_comp[cid].size(); j++)
        {
            component_idx[cid][j] = conn_comp[cid][j]; // map global to local
            idx_component[cid][conn_comp[cid][j]] = j; // map local to global
        }
    }

    // Create Adjacency list for all connected components
    cyclic_innode.resize(num_cid);
    cyclic_outnode.resize(num_cid);
    adj_cc = new std::vector<std::vector<int>>[num_components];
    for (size_t cid = 0; cid < num_cid; cid++)
    {
        adj_cc[cid].resize(conn_comp[cid].size());
        for (auto const &j : conn_comp[cid])
        {   
            for (int k = 0; k < adj_[j].size(); k++)
            {   
                adj_cc[cid][idx_component[cid][j]].push_back(idx_component[cid][adj_[j][k]]); // Map local index
        
            }
        }
    }
    // In degree and Outdegree computation

    //// std::cerr<<"No. of vertices in each component are:"<<std::endl;
    for (size_t cid = 0; cid < num_cid; cid++)
    {   
        /*std::cerr<<"Cyclic component"<<cid;
        for (size_t j = 0; j < adj_cc[cid].size(); j++)
        {   
           std::cerr<<j;
            for (auto const &k : adj_cc[cid][j])
            {
                std::cerr<<"->"<<k;
            }
            std::cerr<<"\n";
        }*/
        comp_size=conn_comp[cid].size();
        comp_adj.resize(comp_size);
        cyclic_innode[cid].resize(comp_size);
        cyclic_outnode[cid].resize(comp_size);
        for (size_t j = 0; j < adj_cc[cid].size(); j++)
        {   
            for (auto const &k : adj_cc[cid][j])
            {
                //// std::cerr<<"->"<<adj_[j][k];
                cyclic_outnode[cid][j].push_back(k);
                if(k!= j)
                    {
                        cyclic_innode[cid][k].push_back(j);
                    }
                comp_adj[j].push_back(k);
                adj_edge++;
            }

        }
        SCC(comp_adj, comp_size);
        adj_cc[cid].clear();
        adj_cc[cid].resize(comp_size);
        //std::cerr<<"DAG Component"<<cid<<"\n";
        
        for (size_t j = 0; j < comp_adj.size(); j++)
        {   
            //std::cerr<<j;
            for (auto const &k : comp_adj[j])
            {
                adj_cc[cid][j].push_back(k);
                //std::cerr<<"->"<<k;
                dag_edge++;
                
                
            }
            dag_vertex++;
            //std::cerr<<"\n";
        }
        //// std::cerr<<"Total number of edges in Acyclic Component "<<cid<<" :"<<"-> [";
        //// std::cerr<<comp_count<<"] \n";
        comp_adj.clear(); 
    }
    //// std::cerr<<"Total number of edges in cyclic graph "<<comp_count1<<"\n";
    // std::cerr<<"\nTotal number of edges in DAG "<<dag_edge<<"\n";
    // std::cerr<<"Total number of nodes in DAG "<<dag_vertex<<"\n\n";
    // std::cerr<<"Number of edges removed :"<<adj_edge-dag_edge<<"\n\n";
    edges_rm=adj_edge-dag_edge;
    if(param_z)
    {
        std::cerr<< "Number of nodes and edges in DAG : " <<dag_vertex<<" "<<dag_edge<<std::endl;
        std::cerr<< "Number of edges removed : " <<edges_rm <<std::endl;
    }
}


int graphUtils::is_cyclic() // Check cyclicity of component and convert to acyclic graph iff component has cycles.

{
    // construct
    std::vector<std::vector<int>> in_degree;
    std::vector<std::vector<int>> out_degree;
    in_degree.resize(num_cid);
    out_degree.resize(num_cid);
    // queue
    std::vector<std::queue<int>> q;
    q.resize(num_cid);
    std::vector<bool> cid_cycle;
    cid_cycle.resize(num_cid);
    int cycle_count = 0;
    top_order.resize(num_cid);
    #pragma omp parallel for
    for (size_t cid = 0; cid < num_cid; cid++)
    {
        // Intialize
        in_degree[cid].resize(adj_cc[cid].size(), 0);
        out_degree[cid].resize(adj_cc[cid].size(), 0);
        // Compute
        for (int v = 0; v < adj_cc[cid].size(); v++)
        {
            out_degree[cid][v] = adj_cc[cid][v].size(); // [0]-> 1,3 (in adj_cc[cid][0] so out_degree of 0 is 2)
        }
        for (int u = 0; u < adj_cc[cid].size(); u++)
        {
            for (auto const &v : adj_cc[cid][u])
            {
                in_degree[cid][v]++; // [0]-> 1,3 (in adj_cc[cid][0] so in_degree of 1 and 3 is 1 for u = 0 and compute for all u's in ad_cc[cid])
            }
        }
        // kahn's Topological sort
        for (int v = 0; v < adj_cc[cid].size(); v++)
        {
            if (in_degree[cid][v] == 0)
            {
                q[cid].push(v);
            }
        }
        int count = 0;
        while (!q[cid].empty())
        {
            int u = q[cid].front();
            q[cid].pop();
            for (auto const &v : adj_cc[cid][u])
            {
                if (--in_degree[cid][v] == 0)
                {
                    q[cid].push(v); // front -->[0,1,2]--> back , (when you push, queue adds v in incrementing order)
                }
            }
            count++; // make count of vertices in top_order[cid]
        }
        // verify component is acyclic
        if (count != adj_cc[cid].size())
        {
            cycle_count++;
        }
    }
    for (size_t i = 0; i < num_comp; i++)
    {
        // std::cerr<<cid_cycle[i]<<" ";
    }
    
    q.clear();
    in_degree.clear();
    out_degree.clear();
    //std::cerr << "[Connected components : " << num_cid << ", components with cycle : " << cycle_count << "]\n"<< std::endl;
    return cycle_count;
}

void graphUtils::topologicat_sort()
{

    // construct
    std::vector<std::vector<int>> in_degree;
    std::vector<std::vector<int>> out_degree;
    in_degree.resize(num_cid);
    out_degree.resize(num_cid);
    map_top_sort.resize(num_cid);
    // queue
    std::vector<std::queue<int>> q;
    q.resize(num_cid);
    #pragma omp parallel for
    for (size_t cid = 0; cid < num_cid; cid++)
    {
        //    /*
        //     ###########################
        //     # kahn's Toplogical sort  #
        //     ###########################
        //     */

        // In degree and out degree computation

        // Intialize
        in_degree[cid].resize(adj_cc[cid].size(), 0);
        out_degree[cid].resize(adj_cc[cid].size(), 0);
        // Compute
        for (int v = 0; v < adj_cc[cid].size(); v++)
        {
            out_degree[cid][v] = adj_cc[cid][v].size(); // [0]-> 1,3 (in adj_cc[cid][0] so out_degree of 0 is 2)
        }
        for (int u = 0; u < adj_cc[cid].size(); u++)
        {
            for (auto const &v : adj_cc[cid][u])
            {
                in_degree[cid][v]++; // [0]-> 1,3 (in adj_cc[cid][0] so in_degree of 1 and 3 is 1 for u = 0 and compute for all u's in ad_cc[cid])
            }
        }
        // kahn's Topological sort
        for (int v = 0; v < adj_cc[cid].size(); v++)
        {
            if (in_degree[cid][v] == 0)
            {
                q[cid].push(v);
            }
        }
        int count = 0;
        while (!q[cid].empty())
        {
            int u = q[cid].front();
            q[cid].pop();
            top_order[cid].push_back(u);
            for (auto const &v : adj_cc[cid][u])
            {
                if (--in_degree[cid][v] == 0)
                {
                    q[cid].push(v); // front -->[0,1,2]--> back , (when you push, queue add v in incrementing order)
                }
            }
            count++; // make count of vertices in top_order[cid]
        }
        // verify component is acyclic
        if (count != adj_cc[cid].size())
        {
            // std::cerr << " Can't do Topological ordering : cycle exist " << std::endl; // Just to make sure in case boost has failed to compute cycles
        }
        // std::cerr << " Top sort for cid : " << cid << std::endl;
        // for (size_t i = 0; i < top_order[cid].size(); i++)
        // {
        //     std::cerr << component_idx[cid][top_order[cid][i]] << std::endl;
        // }
        // std::cerr << std::endl;
        
    }

    /* Mapping for Top_Sort */
    for (int cid = 0; cid < num_cid; cid++)
    {
        map_top_sort[cid].resize(top_order[cid].size());
        
        for (int v = 0; v < top_order[cid].size(); v++)
        {
            map_top_sort[cid][top_order[cid][v]] = v;
        }

    }
    in_degree.clear();
    out_degree.clear();
   // std::cerr << " Computed Topological Order " << std::endl;
}

std::vector<std::vector<int>> graphUtils::shrink(int cid)
{
    /*
    ######################
    #     shrinking      #
    ######################
    */
    // Compute Shrinking    
    size_t N = adj_cc[cid].size();
    std::vector<int> cids;
    // fill with vertex id
    for (size_t i = 0; i < N; i++)
    {
        cids.push_back(i);
    }

    std::vector<int> covered(N, 0);
    std::vector<std::vector<int>> ret;
    int K = path_cover[cid].size(), inf = path_cover[cid].size();
    std::vector<int> starts(N, 0), ends(N, 0);
    std::map<std::pair<int, int>, int> edge_covered;
    for (auto path : path_cover[cid]) {
        for (int i = 0; i < path.size(); i++) {
            covered[path[i]]++;
        if (i > 0)
            edge_covered[{ path[i - 1], path[i] }]++;
        }
        starts[path[0]]++;
        ends[path.back()]++;
    }
    flowGraph fg(N * 2);
    // i_in = i, i_out = i + N
    // add r(i, j) = c(j,i) + f(i,j) - l(i,j)
    auto add = [&](int i, int j, int cap, int l, int ff) {
    // std::cerr << "add edge " << i << " " << j << "  " << cap << "  " << l << " " <<ff << std::endl;
    fg.add_edge(i, j, 0 + ff - l);
    fg.add_edge(j, i, cap - ff);
    };
    for (int i = 0; i < N; i++)
    for (size_t jid : out_node[cid][i]) {
            size_t j = jid;
            int ff = edge_covered.count({i, j}) ? edge_covered[{i, j}] : 0;
            add(i + N, j, inf, 0, ff);
        }
    for (int i = 0; i < N; i++) {
        add(i, i + N, inf, 1, covered[i]);
        add(fg.S, i, inf, 0, starts[i]);
        add(i + N, fg.T, inf, 0, ends[i]);
    }

    int total = inf;
    std::vector<int> Q(fg.N, 0), pre(fg.N, -1), d(fg.N, 0);
    while (1) {
        int Qsize = 0;
        Q[Qsize++] = fg.S;
        for (int i = 0; i < fg.N; i++) {
            pre[i] = -1;
            d[i] = 0;
        }
        d[fg.S] = 1;
        for (int idx = 0; idx < Qsize && d[fg.T] == 0;) {
            int i = Q[idx++];
            for (int e = fg.f[i]; e; e = fg.t[e]) {
                int j = fg.p[e]; 
                if (fg.c[e] > 0 && d[j] == 0) {
                    d[j] = 1;
                    pre[j] = e;
                    Q[Qsize++] = j;
                }
            }
        }
        if (d[fg.T] == 0) break;
        std::vector<int> tmp;
        int flow = fg.c[pre[fg.T]];
        for (int i = fg.T; ;) {
            tmp.push_back(i);
            int e = pre[i];
            if (e == -1) break;
            flow = std::min(flow, fg.c[e]);
            i = fg.p[e ^ 1];
        }
        for (int i = fg.T; ;) {
            int e = pre[i];
            if (e == -1) break;
            fg.c[e] -= flow;
            fg.c[e^1] += flow;
            i = fg.p[e ^ 1];
        }
        if (flow == 0) exit(1);
        total -= flow;
    // std::cerr << " Now shrink by " << flow << " to " << total << std::endl;
    }

    // std::cerr << " Minimum Flow :  " << total << std::endl;

    // convert flow back to path cover
    // ret = pc;
    // ret.resize(total);

    for (int itr = 0; itr < total; itr++) {
        std::vector<int> tmp;
        for (int i = fg.S; i != fg.T; ) {
            if (0 <= i && i < N)
                tmp.push_back(cids[i]);
            int nxt = -1;
            for (int e = fg.f[i]; e; e = fg.t[e]) {
                int j = fg.p[e];
                int ff = fg.c[e] + ((i < N && i + N == j) ? 1 : 0);
                if ((e & 1) == 0 && ff > 0) {
                    nxt = j;
                    fg.c[e]--;
                    break;
                }
            }
            if (nxt == -1) {
                std::cerr << i << " not found nxt " << std::endl;
                return ret; // return ret
            }
            i = nxt;
        }
        ret.push_back(tmp);
    }
    return ret;
}

bool check_MPC(std::vector<std::vector<int>> adj, std::vector<int> path_verify, int k, int cid)
{
    int count = 0;
    for (int i = 0; i < path_verify.size() - 1; i++)
    {
        int u = path_verify[i];
        int v = path_verify[i+1];
        for (auto x:adj[u])
        {
            if (x == v)
            {
                count++; // count the edges which will be "vertex - 1"
            }
            
        }
        
    }
    if (count + 1 ==  path_verify.size())
    {
        std::cerr << "cid = " << cid << " path #" << k+1<< " MPC is OK! " << std::endl;
        return true;
    }
}

void graphUtils::MPC()
{
    /*
    ######################
    # MPC (greedy cover) #
    ######################
    */
    path_cover.resize(num_cid);
    in_node.resize(num_cid);
    out_node.resize(num_cid);
    #pragma omp parallel for
    for (size_t cid = 0; cid < num_cid; cid++)
   {

        in_node[cid].resize(adj_cc[cid].size());  // all nodes
        out_node[cid].resize(adj_cc[cid].size()); // all nodes
        // computing in_nodes and out_nodes
        for (int u = 0; u < adj_cc[cid].size(); u++)
        {
            for (auto const &v : adj_cc[cid][u])
            {
            in_node[cid][v].push_back(u);
            out_node[cid][u].push_back(v);
            }
        }
        /* Greedy MPC! */
        int T = 0;
        int covered_count = 0;
        std::vector<int> covered;
        std::vector<int> max_cover;
        std::vector<int> pre;
        std::vector<int> path;
        int V = adj_cc[cid].size(); 
        covered.resize(V,0);
        max_cover.resize(V,0);
        pre.resize(V,-1); // Initialise as "None"
        while (covered_count < V)
        {
            for (size_t i = 0; i < max_cover.size(); i++)
            {
                max_cover[i] = 0;
                pre[i] = -1;
            }
            
            for (auto const & v: top_order[cid])
            {
                if (covered[v] == 0)
                {
                    max_cover[v]++;
                }
                
                for (auto const& u : adj_cc[cid][v])
                {
                    if (max_cover[u] < max_cover[v])
                    {
                        max_cover[u] = max_cover[v];
                        pre[u] = v;
                    }   
                }
            }
            auto max = std::max_element(max_cover.begin(),max_cover.end());
            T = std::distance(max_cover.begin(),max); // argmax(max_cover[v])
            
            int new_covered = 0;
            while (covered_count < V)
            {
                if (T == -1)
                {
                    break;
                }else
                {
                    if (covered[T] == 0)
                    {
                        covered_count++;
                        covered[T] = 1;
                        new_covered++;
                    }
                    path.push_back(T);
                    T = pre[T];
                }
                
            }
            std::reverse(path.begin(),path.end()); //std::vector<std::vector<int>> adj(n_vtx);
            path_cover[cid].push_back(path);
            //std::cerr << "cid = " << cid << " path #" << path_cover[cid].size() << " : " << path.size() << " " << new_covered << " " << (V - covered_count) << std::endl;
            path.clear();
        }

        // Shrink Path Cover
        path_cover[cid] = shrink(cid);
        std::reverse(path_cover[cid].begin(),path_cover[cid].end());
        if (param_z)
        {
            /* Check MPC */
            bool check_path;
            for (int k = 0; k < path_cover[cid].size(); k++)
            {
                check_path = check_MPC(adj_cc[cid], path_cover[cid][k], k, cid);
                /* If MPC is correct then only proceed */
                if (check_path == false)
                {
                    std::cerr << " MPC Computation is wrong! " << std::endl;
                    exit(0);
                }
            }
        }
   }
   // Compute [min-max] paths for cids
  int min = path_cover[0].size();
  int max = min;
  for(int cid = 1; cid < num_cid; cid++)
  {
      min = min<path_cover[cid].size()?min:path_cover[cid].size();
      max = max>path_cover[cid].size()?max:path_cover[cid].size();
  }
  fprintf(stderr, "[M::%s] range MPC [%d-%d] \n", __func__,min,max);
  // std::cerr << "[range wcc [" << min << "-" << max << "]" << std::endl; 
   // std::cerr << " MPC Computed! " << std::endl;
    /*// std::cerr<<"Path cover \n";
    for (size_t cid = 0; cid < num_cid; cid++)
    {   
        // std::cerr<<"Component"<<cid<<"\n";
        for (size_t j = 0; j < path_cover[cid].size(); j++)
        {   
            // std::cerr<<j;
            for (auto const &k : path_cover[cid][j])
            {
                // std::cerr<<"->"<<k;
                
            }
            // std::cerr<<"\n";

        }
    }*/
}

//Function to calculate approximate distance(D_approx[u,v]) 
int64_t D_APPROX(int u, int v, int cid, std::vector<std::vector<std::vector<int>>> &path, std::vector<std::vector<std::vector<int64_t>>> &Distance, std::vector<std::vector<std::vector<int>>> &path_cover, std::vector<std::vector<std::vector<int>>> &index, std::vector<std::vector<std::vector<int>>> &last2reach, std::vector<std::vector<std::vector<int64_t>>> &dist2begin)
{
    int alpha_i;
    int64_t D_approx_temp, D_approx = std::numeric_limits<int64_t>::max()/2;
    if(v==u)
        D_approx=0;
    else
    {
        for(size_t i : path[cid][u])
        {
            if(index[cid][i][v] >= index[cid][i][u] && index[cid][i][v]!= -1 && index[cid][i][u]!=-1)
            {
                alpha_i=v;
                D_approx= std::min(D_approx, (dist2begin[cid][i][alpha_i]- dist2begin[cid][i][u]));
            }
            else
            {
                if(last2reach[cid][i][v]!= -1)
                {
                    alpha_i= path_cover[cid][i][last2reach[cid][i][v]];
                    D_approx_temp= dist2begin[cid][i][alpha_i]- dist2begin[cid][i][u] + Distance[cid][i][v];
                    if(D_approx_temp>= 0)
                        D_approx= std::min(D_approx, D_approx_temp);
                }
            }
        } 
    }
    assert(D_approx>=0);
    return D_approx;
}

void graphUtils::MPC_index()
{   
    int L2R_itr=0, max_L2R=0, min_L2R= std::numeric_limits<int>::max();
    int D_itr=0, max_D=0, min_D= std::numeric_limits<int>::max();
    int L2R_sum=0, D_sum=0;
    bool L2R_flag=false, L2R_temp, D_flag=false, D_temp;
    std::vector<std::vector<std::vector<int>>> L2R, path;
    std::vector<std::vector<std::vector<int64_t>>> Dis;
    std::vector<std::vector<std::vector<int64_t>>> D_approx;
    //std::vector<std::vector<bool>> processed;
    D_approx.resize(num_cid);
    D_cyclic.resize(num_cid);
    //processed.resize(num_cid);
    path.resize(num_cid);
    L2R.resize(num_cid);
    //l2r.resize(num_cid);
    index.resize(num_cid);
    rev_index.resize(num_cid);
    dist2begin.resize(num_cid);
    last2reach.resize(num_cid);
    Distance.resize(num_cid);
    Dis.resize(num_cid);
    #pragma omp parallel for
    for (size_t cid = 0; cid < num_cid; cid++)
    {
        /*
        ######################
        # last2reach & index #
        ######################
        */
        int K = path_cover[cid].size();
        int N = adj_cc[cid].size();
        /*std::cerr<<"DAG component"<<cid<<"\n";
        for (size_t j = 0; j < adj_cc[cid].size(); j++)
        {   
            std::cerr<<j;
            for (auto const &k : adj_cc[cid][j])
            {
               std::cerr<<"->"<<k;
            }
            std::cerr<<"\n";
        }*/

        // Compute index ( arranged in topological order by MPC , no need to sort)
        index[cid].resize(path_cover[cid].size(),std::vector<int>(adj_cc[cid].size(),-1));
        rev_index[cid].resize(path_cover[cid].size(),std::vector<int>(adj_cc[cid].size(),-1));
        dist2begin[cid].resize(path_cover[cid].size(),std::vector<int64_t>(adj_cc[cid].size(),0));
    
        for (size_t k = 0; k < path_cover[cid].size(); k++)
        {
            int i = 0;
            int64_t temp = 0;
            for (auto idx : path_cover[cid][k])
            {
                index[cid][k][idx] = i; // assuming topologically sorted in origional component
                rev_index[cid][k][i++] = idx;
                dist2begin[cid][k][idx] = temp;
                temp += (int64_t)node_len[component_idx[cid][idx]];
            }
        }

        // last2reach computation
        last2reach[cid].resize(path_cover[cid].size(),std::vector<int>(adj_cc[cid].size(),-1)); // Initialise last2reach
        Distance[cid].resize(path_cover[cid].size(),std::vector<int64_t>(adj_cc[cid].size(),std::numeric_limits<int64_t>::max()/2)); // Initilaise Distance
        L2R[cid].resize(path_cover[cid].size(), std::vector<int>(adj_cc[cid].size(),-1));
        Dis[cid].resize(path_cover[cid].size(),std::vector<int64_t>(adj_cc[cid].size(),std::numeric_limits<int64_t>::max()/2)); 
        path[cid].resize(N);
        //// std::cerr<<std::numeric_limits<int64_t>::max()/2<<"\n";
        //std::cerr<<"\nPath covers for component"<<cid<<"\n";
        for (int k = 0; k < K; k++)
        {   
            //std::cerr<<"\nk="<<k<<":";
            int i = 0;
            for (auto v:path_cover[cid][k])
            {
                last2reach[cid][k][v] = i++;
                L2R[cid][k][v]=last2reach[cid][k][v];
                path[cid][v].push_back(k);
                //std::cerr<<v<<"->";
            }
        }

        // Topological order (kahn's Algorithm)
        std::vector<int> incd(N, 0), Q;
        for (int i = 0; i < N; i++)
        {
            incd[i] = in_node[cid][i].size();
            if (incd[i] == 0)
            {
                Q.push_back(i);
            }
        }
        for (int i = 0; i < Q.size(); ) {
        int s = Q[i++];
        for (size_t t : out_node[cid][s]) {
            incd[t]--;
            if (incd[t] == 0)
                Q.push_back(t);
            }
        }
        /*std::cerr<<"\n Topological order, component "<<cid<<": ";
        for(int v : Q)
        {
            std::cerr<<v<<" ";
        }*/

        // last2reach computation
        while(!L2R_flag)
        {
            L2R_flag=true;
            for (int k = 0; k < K; k++)
            {
                for (int v : Q) 
                {
                    for (size_t u : cyclic_innode[cid][v]) 
                    {
                        last2reach[cid][k][v] = std::max(last2reach[cid][k][v], last2reach[cid][k][u]);
                    }
                    //Checking L2R values convergence
                    if(L2R[cid][k][v]!=last2reach[cid][k][v])
                    {
                        L2R_temp=false;
                        L2R_flag=(L2R_flag && L2R_temp);
                    }
                    else
                    {
                        L2R_temp=true;
                        L2R_flag=(L2R_flag && L2R_temp);
                    }
                    assert(last2reach[cid][k][v]>=-1);
                    L2R[cid][k][v]=last2reach[cid][k][v];
                }
            }
            L2R_itr++;
        }
        L2R_flag=false;
        //// std::cerr<<"Number of L2R computation iterations for componenet "<<cid<<": "<<L2R_itr<<"\n";
        max_L2R= std::max(max_L2R, L2R_itr);
        min_L2R= std::min(min_L2R, L2R_itr);
        L2R_sum= L2R_sum+ L2R_itr;
        L2R_itr=0;

        // Set all values in path to zero (for DP to be correct)
        for (int k = 0; k < K; k++)
        {
            for (auto v : path_cover[cid][k])
            {
                if(last2reach[cid][k][v] == index[cid][k][v])
                {
                    Distance[cid][k][v] = (int64_t)0;
                    Dis[cid][k][v]= (int64_t)0;
                }
            }
            
        }
        while(!D_flag)
        {
            D_flag=true;
            for (int k = 0; k < K; k++)
            {
                for (int v : Q) 
                {
                    if(last2reach[cid][k][v] == index[cid][k][v] && last2reach[cid][k][v]!= -1)
                        Distance[cid][k][v]= (int64_t)0;
                    else
                    {
                        for (size_t u : cyclic_innode[cid][v]) 
                        {
                            if (last2reach[cid][k][v] == last2reach[cid][k][u] && last2reach[cid][k][v]!= -1)
                            {
                                Distance[cid][k][v] = std::min(Distance[cid][k][v], (Distance[cid][k][u])+(int64_t)node_len[component_idx[cid][u]]);
                                //// std::cerr<<(int64_t)node_len[component_idx[cid][u]]<<" ";
                            }
                        }
                    }   
                    //Checking Dis values convergence
                    if(Dis[cid][k][v]!= Distance[cid][k][v])
                    {
                        D_temp=false;
                        D_flag=(D_flag && D_temp);
                    }
                    else
                    {
                        D_temp=true;
                        D_flag=(D_flag && D_temp);
                    }
                    assert(Distance[cid][k][v]>=0);
                    Dis[cid][k][v]=Distance[cid][k][v];
                }
            }
            //// std::cerr<<D_itr<<" ";
            D_itr++;
        }
        D_flag=false;
        //// std::cerr<<"\nNumber of approx Distance computation iterations for componenet "<<cid<<": "<<D_itr<<"\n";
        max_D= std::max(max_D, D_itr);
        min_D= std::min(min_D, D_itr);
        D_sum= D_sum + D_itr;
        D_itr=0;

        L2R[cid].clear();
        Dis[cid].clear();
        
        /*std::cerr << " cid : " << cid <<"\n";
        for(int k=0; k<K; k++)
        {
            for(int v: Q)
            {
                if(last2reach[cid][k][v]== -1)
                    std::cerr<< "Last2reach and Distance ("<<k<<","<<v<<"): " <<last2reach[cid][k][v]<<" "<<Distance[cid][k][v]<<"\n";
                //std::cerr<<last2reach[cid][k][v]<<" "<<l2r[cid][k][v]<<"\n";
                else
                    std::cerr<< "Last2reach and Distance ("<<k<<","<<v<<"): " <<path_cover[cid][k][last2reach[cid][k][v]]<<" "<<Distance[cid][k][v]<<"\n";; 
            }
        }*/

        // // Print last2reach 
        /*std::cerr << " last2reach " << std::endl;
         for (size_t i = 0; i < K; i++)
        {
             for (size_t j = 0; j < N; j++)
           {
                 std::cerr << last2reach[cid][i][j] << " " ;
             }
             std::cerr << std::endl;
         }
        std::cerr << " index " << std::endl;
        for (size_t i = 0; i < K; i++)
        {
            for (size_t j = 0; j < N; j++)
             {
                std::cerr <<  index[cid][i][j] << " " ;
            }
             std::cerr << std::endl;
        }
        // std::cerr << " dist2begin " << std::endl;
        // for (size_t i = 0; i < K; i++)
        // {
        //     for (size_t j = 0; j < N; j++)
        //     {
        //         std::cerr << dist2begin[cid][i][j] << "\t" ;
        //     }
        //     std::cerr << std::endl;
        // }

         std::cerr << "cid : " << cid << " K : " << K <<  " \nDistance: " << std::endl;
         for (size_t i = 0; i < K; i++)
        {
            for (size_t j = 0; j < N; j++)
            {
               std::cerr << Distance[cid][i][j] << " " ;
            }
            std::cerr << std::endl;
        }*/

        //D_cyclic calculation
        int64_t D_approx = std::numeric_limits<int64_t>::max()/2; 
        D_cyclic[cid].resize(adj_cc[cid].size(), std::numeric_limits<int64_t>::max()/2);
        if(edges_rm > 0)
        {
	        //std::cerr << "\ncid : " << cid << " D_cyclic : ";  
            for (size_t v = 0; v < N; v++)
            {
                for(size_t u: cyclic_outnode[cid][v])
                {   
                    D_approx= D_APPROX(u, v, cid, path, Distance, path_cover, index, last2reach, dist2begin);
                    D_cyclic[cid][v]= std::min(D_cyclic[cid][v], D_approx + (int64_t)node_len[component_idx[cid][v]]);
                }
                assert(D_cyclic[cid][v]>=0);
            } 
        }
	    //Correct Distanec for which las2reach = -1
        for (int k = 0; k < K; k++)
        {
            for (size_t v = 0; v < N; v++)
            {
                //std::cerr<<"\nD'_apx("<<v<<"): "<<D_cyclic[cid][v]<<"\n";
                if (last2reach[cid][k][v] == -1)
                {
                    Distance[cid][k][v] = (int64_t)0;
                }
            }
        }
        path[cid].clear();
        cyclic_innode[cid].clear();
        cyclic_outnode[cid].clear();
    }

    int mean_L2R= L2R_sum/num_cid;
    int mean_D= D_sum/num_cid;
    if(param_z)
    {
        fprintf(stderr, "[M::Last2reach_iterations] range iterations [%d-%d], mean= %d\n", min_L2R, max_L2R, mean_L2R);
        fprintf(stderr, "[M::Distance_iterations] range iterations [%d-%d], mean= %d\n", min_D, max_D, mean_D);
    }
    
}

bool compare_T(const Tuples &a, const Tuples &b){
    return std::tie( a.top_v , a.pos, a.task , a.anchor ) < std::tie( b.top_v , b.pos, b.task, b.anchor);
};

bool compare_dups(const Tuples &a, const Tuples &b){
    return std::tie( a.top_v , a.pos, a.task, a.d, a.path) == std::tie( b.top_v , b.pos, b.task, b.d, b.path);
};


std::vector<mg128_t> graphUtils::Chaining(std::vector<mg128_t> anchors)
{   //std::chrono::time_point<std::chrono::system_clock> start, end;
    //start = std::chrono::system_clock::now();
    if (param_z)
    {
        std::cerr << " Number of Anchors : " << anchors.size() << "\n";
    }
    // Initilaise chain_data
    std::vector<mg128_t> best;
    /* Divide Anchors corresponding to their cids */
    std::vector<std::vector<Anchors>> M;
    M.resize(num_cid);
    std::vector<std::vector<mg128_t>> idx_Anchor;
    idx_Anchor.resize(num_cid);
    bool C_flag= false, temp_flag;
    int ITR=0, max_ITR=0, min_ITR= std::numeric_limits<int>::max(), ITR_sum=0;
    for (int j = 0; j < anchors.size(); j++)
    {
        Anchors M_; // Anchor
        int minimizer_len = (int32_t)(anchors[j].y>>32&0xff);
        int node = (int)(anchors[j].x>>32);
        M_.v = node;
        M_.c = (int32_t)(anchors[j].y) - minimizer_len + 1;
        M_.d =  (int32_t)(anchors[j].y);
        M_.x =  (int32_t)(anchors[j].x) - minimizer_len + 1;
        M_.y =  (int32_t)(anchors[j].x);
        M[component[node]].push_back(M_);
        idx_Anchor[component[node]].push_back(anchors[j]);
    }
    std::vector<std::pair<std::vector<mg128_t>,int64_t>> best_chains;
    best_chains.resize(num_cid);
    for (int cid = 0; cid < num_cid; cid++)
    {
        // N : #Anchors 
        // K : #Paths
        int N = M[cid].size();
        int K = path_cover[cid].size();
        /* Initialise Search Trees */
        std::pair<int64_t, int> defaul_value = { std::numeric_limits<int64_t>::min(), -1 };
        std::vector<IndexT> I(K,IndexT(defaul_value));
        /* Initialise T */
        std::vector<Tuples> T; // Search Tree
        std::vector<std::pair<int64_t,int>> C, C_temp;
        C.resize(N);
        C_temp.resize(N);
	    int64_t sf = scale_factor;
	    int64_t cost =(int64_t) (M[cid][0].d-M[cid][0].c+1)*sf;
        for (int j = 0; j < N; j++)
        {
            int node = M[cid][j].v;
            int v = idx_component[cid][node];
            for (int k = 0; k < K; k++)
            {
                if (index[cid][k][v] != -1) // v is on the path "k"
                {
                    Tuples t;
                    // for task 0
                    t.anchor = j;
                    t.path = k;
                    t.pos = M[cid][j].x;
                    t.task = 0;
                    t.d = M[cid][j].d;
                    t.v = v; // sorting purpose
                    t.w = v; // vertex in which the anchor lies.
                    t.top_v = map_top_sort[cid][v];
                    T.push_back(t);
                    // for task 1
                    t.anchor = j;
                    t.path = k;
                    t.pos = M[cid][j].y;
                    t.task = 1;
                    t.d = M[cid][j].d;
                    t.v = v; 
                    t.w = v;
                    t.top_v = map_top_sort[cid][v];
                    T.push_back(t);
                }
                if (last2reach[cid][k][v] != -1 && last2reach[cid][k][v] != index[cid][k][v]) // v is not on the path "k" and if last2reach exist
                {
                    int w = last2reach[cid][k][v]; // vertex -> Index
                    w = rev_index[cid][k][w]; // index -> vertex
                    int len = node_len[component_idx[cid][w]];
                    Tuples t;
                    // for task 0
                    t.anchor = j;
                    t.path = k;
                    t.pos = std::numeric_limits<int>::max()/2; // Sigma[w] + 1
                    t.task = 0;
                    t.d = M[cid][j].d;
                    t.v = w;
                    t.w = v;
                    t.top_v = map_top_sort[cid][w];
                    T.push_back(t);
                }   
                if(index[cid][k][v] != -1 && D_cyclic[cid][v] > 0 && D_cyclic[cid][v] < std::numeric_limits<int64_t>::max()/2)
                {
                    Tuples t;
                    // for task 2
                    t.anchor = j;
                    t.path = k;
                    t.pos = std::numeric_limits<int>::max(); // Sigma[w] + 2
                    t.task = 2;
                    t.d = M[cid][j].d;
                    t.v = v; 
                    t.w = v; 
                    t.top_v = map_top_sort[cid][v];
                    T.push_back(t);
                }
            }
            /* Initialise C */ 
            C[j] = {cost , -1};
            C_temp[j]= {cost , -1}; 
        }

        /* Erase redundant and Sort the Tuples by T.v, T.pos, T.task */ 
        T.erase( std::unique( T.begin(), T.end(), compare_dups ), T.end() );
        std::sort(T.begin(),T.end(),compare_T);

        // Chaining
        while(!C_flag)
        {    
            C_flag=true;
            //std::cerr<<"Total number of tuples"<<T.size()<<"\n";
            for (auto t:T) // in Linearized Order of their nodes
            {
                //std::cerr<<"t.rank: "<<t.top_v<<" t.v: "<<t.v<<" t.w: "<<t.w<<" t.anchor:"<<t.anchor<<" t.path: "<<t.path<<" t.pos:"<<t.pos<<" t.task: "<<t.task<<"\n";
                if(t.task == 0)
                {
                    if(t.w==t.v)
                    {
                        int64_t val_1 = ( M[cid][t.anchor].c - 1 + M[cid][t.anchor].x - 1 + dist2begin[cid][t.path][t.v]);
                        int64_t val_2 = sf*(M[cid][t.anchor].d - M[cid][t.anchor].c + 1);
                        std::pair<int64_t,int> rmq = I[t.path].RMQ(0,M[cid][t.anchor].c - 1);
                        if (rmq.first > std::numeric_limits<int64_t>::min())
                        {
                            C[t.anchor] = std::max(C[t.anchor], { rmq.first - val_1 + val_2, rmq.second });
                        }
                        if (param_z)
                        {
                            std::cerr << " cid  : " << cid << " idx : " << t.anchor << " top_v :" << t.top_v << " pos : " << t.pos << " task : " << t.task << " path : " << t.path <<  " parent : " << C[t.anchor].second  <<  " node : " << M[cid][t.anchor].v << " index : " << index[cid][t.path][t.w] << " C[j] : " << C[t.anchor].first << " update_C : " << (rmq.first - val_1 + val_2) << " rmq.first : " << rmq.first  << " val_1 : " << val_1 << " dist2begin : " << dist2begin[cid][t.path][t.v] << " Distnace : " <<  0 <<  " M[i].d : " << t.d << "\n"; 
                        }
                    }
                    else
                    {
                        int64_t val_1 = ( M[cid][t.anchor].c - 1 + M[cid][t.anchor].x - 1 + dist2begin[cid][t.path][t.v] + Distance[cid][t.path][t.w]);
                        int64_t val_2 = sf*(M[cid][t.anchor].d - M[cid][t.anchor].c + 1);
                        std::pair<int64_t,int> rmq = I[t.path].RMQ(0,M[cid][t.anchor].c - 1);
                        if (rmq.first > std::numeric_limits<int64_t>::min())
                        {
                            C[t.anchor] = std::max(C[t.anchor], { rmq.first - val_1 + val_2, rmq.second });
                        }
                        if (param_z)
                        {
                            std::cerr << " cid  : " << cid << " idx : " << t.anchor << " top_v :" << t.top_v << " pos : " << t.pos << " task : " << t.task << " path : " << t.path <<  " parent : " << C[t.anchor].second  <<  " node : " << M[cid][t.anchor].v << " index : " << index[cid][t.path][t.w] << " C[j] : " << C[t.anchor].first << " update_C : " << (rmq.first - val_1 + val_2) << " rmq.first : " << rmq.first  << " val_1 : " << val_1 << " dist2begin : " << dist2begin[cid][t.path][t.v] << " Distnace : " <<  Distance[cid][t.path][t.w] <<  " M[i].d : " << t.d << "\n"; 
                        }
                    }
                }
                else if(t.task == 1)
                {
                    int64_t val_3 = ( M[cid][t.anchor].d + M[cid][t.anchor].y + dist2begin[cid][t.path][t.v]);
                    I[t.path].add(M[cid][t.anchor].d, {C[t.anchor].first + val_3 , t.anchor});
                    if (param_z)
                    {
                        std::cerr << " cid  : " << cid << " idx : " << t.anchor << " top_v :" << t.top_v << " pos : " << t.pos << " task : " << t.task << " path : " << t.path << " val_3 : " << val_3  << " M.y : " << M[cid][t.anchor].y <<  " dist2begin : "  << dist2begin[cid][t.path][t.v] << " M[i].d : " << t.d << "\n"; 
                    }
                }
                else
                {
                    int64_t val_1 = ( M[cid][t.anchor].c - 1 + M[cid][t.anchor].x - 1 + dist2begin[cid][t.path][t.v] + D_cyclic[cid][t.w]);
                    int64_t val_2 = sf*(M[cid][t.anchor].d - M[cid][t.anchor].c + 1);
                    int64_t val_3 = ( M[cid][t.anchor].d + M[cid][t.anchor].y + dist2begin[cid][t.path][t.v]);
                    std::pair<int64_t,int> rmq = I[t.path].RMQ(0,M[cid][t.anchor].c - 1);
                    if (rmq.first > std::numeric_limits<int64_t>::min())
                    {
                        C[t.anchor] = std::max(C[t.anchor], { rmq.first - val_1 + val_2, rmq.second });
                        I[t.path].add(M[cid][t.anchor].d, {C[t.anchor].first + val_3 , t.anchor});
                    }
                    if (param_z)
                    {
                        std::cerr << " cid  : " << cid << " idx : " << t.anchor << " top_v :" << t.top_v << " pos : " << t.pos << " task : " << t.task << " path : " << t.path <<  " parent : " << C[t.anchor].second  <<  " node : " << M[cid][t.anchor].v << " index : " << index[cid][t.path][t.w] << " C[j] : " << C[t.anchor].first << " update_C : " << (rmq.first - val_1 + val_2) << " rmq.first : " << rmq.first  << " val_1 : " << val_1 << " dist2begin : " << dist2begin[cid][t.path][t.v] << " Distnace(cyclic) : " << D_cyclic[cid][t.w]  <<  " M[i].d : " << t.d << "\n"; 
                        std::cerr << " cid  : " << cid << " idx : " << t.anchor << " top_v :" << t.top_v << " pos : " << t.pos << " task : " << t.task << " path : " << t.path << " val_3 : " << val_3  << " M.y : " << M[cid][t.anchor].y <<  " dist2begin : "  << dist2begin[cid][t.path][t.v] << " M[i].d : " << t.d << "\n"; 
                    }
                }
                //Checking C[j] scores convergence 
                if(C[t.anchor]!=C_temp[t.anchor])
                {
                    temp_flag=false;
                    C_flag=(C_flag && temp_flag);
                }
                else
                {
                    temp_flag= true;
                    C_flag=(C_flag && temp_flag);
                }
                C_temp[t.anchor]=C[t.anchor];
            }
            //reinitializing RMQ tree
            I.clear();
            I.resize(K,IndexT(defaul_value));
            ITR++;
        }
        C_flag=false;
        max_ITR= std::max(ITR, max_ITR);
        min_ITR= std::min(ITR, min_ITR);
        ITR_sum= ITR+ITR_sum;
        //std::cerr<<"Cid: "<<cid<<" Iterations for chaining "<<ITR<<"\n";
        ITR=0;
        if (N!=0)
        {
            // Traceback
            std::vector<mg128_t> temp_;
            std::vector<mg128_t> temp2_;
            std::pair<int64_t, int> best_;
            best_ = {0, -1};
            for (int j = 0; j < N; j++)
            {
                best_ = std::max(best_, { C[j].first, j });
            }

            std::pair<int64_t, int> best_temp;
            std::vector<bool> visited(N,false);
            float tau = 0.99;
            int64_t threshold = tau*(float)best_.first;
            int64_t score = best_.first;
            while (score >= threshold)
            {
                int flag = false;
                best_temp = {0, -1};
                for (int j = 0; j < N ; j++)
                {
                    if (visited[j] == false)
                    {
                        best_temp = std::max(best_temp, { C[j].first, j });
                    }
                }

                for (int i = best_temp.second; i != -1 ; i = C[i].second) {
                    if (visited[i] ==  true)
                    {
                        flag = true; // Not a disjoint set
                        temp2_.clear();
                        break;
                    }
                    
                    temp2_.push_back(idx_Anchor[cid][i]);
                    visited[i] = true; // we need disjoint set of anchors
                    if (param_z)
                    {
                        std::cerr << " cid  : " << cid << " idx : " << i <<  " parent : " << C[i].second  <<  " node : " << M[cid][i].v << " C[j] : " << C[i].first << " M.y : " << M[cid][i].y  <<  " M.d : " << M[cid][i].d << "\n";
                    }
                    if (i == C[i].second) {
                        std::cerr << "error, loops in C[j] : " << i << "  " << C[i].first << " "  << C[i].second << std::endl;
                        break;
                    }
                }

                // Push to Union of All Anchors iff the sets are disjoint
                if (flag == false)
                {
                    for (int i = 0; i < temp2_.size(); i++)
                    {
                        temp_.push_back(temp2_[i]);
                    }
                    temp2_.clear();
                }

                best_temp = {0, -1};
                for (int j = 0; j < N ; j++)
                {
                    if (visited[j] == false)
                    {
                        best_temp = std::max(best_temp, { C[j].first, j });
                    }
                }

                score = best_temp.first;
            }

            // Push into best chains
            std::pair<std::vector<mg128_t>, int64_t> chain_pair;
            chain_pair.first = temp_;
            chain_pair.second = best_.first;
            best_chains[cid] = chain_pair;
            temp_.clear();
        }
    }

    int mean_ITR= ITR_sum/num_cid;
    if(param_z)
    {
        fprintf(stderr, "[M::Chaining_iterations] range iterations [%d-%d], mean= %d\n", min_ITR, max_ITR, mean_ITR);
    }
    // Pick the chain with maximum score as best
    std::pair<int64_t, int> best_;
    int64_t best_chain_score = 0;
    for (int cid = 0; cid < num_cid; cid++)
    {
        if ( best_chains[cid].second > best_chain_score)
        {
            best_chain_score = best_chains[cid].second;
        }
    }

    // Now compute Threshold
    float tau = 0.95;
    int64_t threshold = tau*(float)best_chain_score;

    // Now pick all the chains from all the cid which satisfies threshold
    std::vector<int> best_cids;
    for (int cid = 0; cid < num_cid; cid++)
    {
        if (best_chains[cid].second >= threshold)
        {
            best_cids.push_back(cid);
        }
        
    }

    // Now pick all the chains from best_cids
    for (auto cid:best_cids)
    {
        for (int i = 0; i < best_chains[cid].first.size(); i++)
        {
            best.push_back(best_chains[cid].first[i]);
        }

    }

    std::reverse(best.begin(),best.end());

    /* Count the frequency of an anchor within the node, If the frequency is <5, then discard the anchor */
    std::map<int,int> freq;

    /* Initialise to 0 */
    for (int i = 0; i < best.size(); i++)
    {
        freq[(int)(best[i].x>>32)] = 0;
    }

    /* Count the frequency */
    for (int i = 0; i < best.size(); i++)
    {
        freq[(int)(best[i].x>>32)]++;
    }

    /* Iterate over all the keys and find a node for which anchor frequency < 5 */
    std::vector<int> red_nodes;
    for (auto tuple:freq)
    {
        if (tuple.second <= 5)
        {
            red_nodes.push_back(tuple.first);
        }
    }

    /* Find Index of all such nodes, for which the anchor frequency < 5 */
    std::vector<int> red_idx;
    for (int i = 0; i < best.size(); i++)
    {
        for (auto node:red_nodes)
        {
            if (node == (int)(best[i].x>>32)) // If found a redundant node, store the index
            {
                red_idx.push_back(i);
                continue;
            }
        }
    }
    if (param_z)
    {
        std::cerr << " Number of Best Anchors : " << best.size() << "\n";
    }

    /* Remove anchors from collected indices */ 
    int count_idx = 0;
    for (auto idx:red_idx)
    {
        idx = idx - count_idx;
        best.erase(best.begin()+idx);
        count_idx++;
    }

    /*if (param_z)
    {
        std::cerr << " Number of Best Anchors : " << best.size() << "\n";
    }*/
    //end = std::chrono::system_clock::now();
    //std::chrono::duration<double> elapsed_seconds = end - start;
    //std::cerr <<"Read "<<", elapsed time: " << elapsed_seconds.count() << "s\n";

   return best;

}