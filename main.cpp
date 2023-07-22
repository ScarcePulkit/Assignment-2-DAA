/**
 * @file main.cpp
 * @brief This file contains the implementation of the Ford Fulkerson algorithm
 * @details This file contains the implementation of the Ford Fulkerson algorithm
 *         for the problem of finding the maximum output flow from the source to the destination and min-cur flow.
 * 
 * 
*/

/*
    Pulkit Agrawal - 2020A7PS2072H
    Ishan Chhangani - 2020A7PS0230H
    Abhirath NB - 2020A7PS0260H
    Samandeep Singh - 2020A7PS0065H
*/

#include<bits/stdc++.h>
using namespace std;

#define endl "\n"
#define ll long long

// to store the residual graph
vector<vector<int>> adj_res;

// dfs to check the reachability from scr after getting residual graph
void dfs_mincut(int src, vector<bool> &vis){
	/**
     * @brief This function is used to find the connected components of the vertex src in the residual graph
     * @param int src - the vertex whose connected components are to be found
     * @param vector<bool> &vis - the vector to store the visited vertices
     * @return void
    */

	//marking the node as visited
	vis[src] = true;
	int n = adj_res.size();
	for(int i = 0; i < n; i++){
		if(vis[i]){
			continue;
		}
		if(adj_res[src][i] > 0){
			dfs_mincut(i,vis);
		}
	}
}

bool dfs(int src, int dest, vector<int> &path, vector<vector<int>> &adj, vector<bool> &vis){
    /**
     * @brief This function is used to find the path from src to dest in the residual graph
     * @param int src - the source vertex
     * @param int dest - the destination vertex
     * @param vector<int> &path - the vector to store the path from src to dest
     * @param vector<vector<int>> &adj - the adjacency matrix of the residual graph
     * @param vector<bool> &vis - the vector to store the visited vertices
     * @return bool - true if path exists, false otherwise
    */

    // base case
    if(src == dest){
        return true;
    }
    // marking the curr node as visited
    vis[src] = true;
    int n = adj.size();

    for(int i = 0; i < n; i++){
        // if visited then simply continue
        if(vis[i]){
            continue;
        }

        // if adj[src][i] > 0 then there exits an edge from src to i
        if(adj[src][i] > 0){
            path.push_back(i);
            // checking if there is a path from i to dest
            if(dfs(i,dest,path,adj,vis)){
                return true;
            }
            // popping the last element from the path if no path found
            path.pop_back();
        }
    }
    return false;
}

int find_ford_fulkerson(vector<vector<int>> &adj,int src, int dest, vector<vector<int>> &adj_g){
    /**
     * This function is used to find the maximum output flow from the source to the destination - Ford Fulkerson Algorithm
     * @param vector<vector<int>> &adj - the adjacency matrix of the graph
     * @param int src - the source vertex
     * @param int dest - the destination vertex
     * @param vector<vector<int>> &adj_g - the adjacency matrix of the flow graph
    */

    // creating a residual graph
	adj_res = adj;
    int n = adj.size();
    // creating a set to store the forward edges
    set<pair<int,int>> f_edges;

    // storing the forward edges
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(adj[i][j] > 0){
                f_edges.insert({i,j});
            }
        }
    }

    // path vector store the path from src to dest
    vector<int> path;
    vector<bool> vis(n,false);
    path.push_back(src);

    // checking the path from src to dest until no path exists
    while(dfs(src,dest,path, adj_res, vis)){
        int bottleneck = 1e9;
        int s = path.size();

        // finding the bottleneck capacity
        for(int i = 0; i < s-1; i++){
            int u = path[i];
            int v = path[i+1];
            bottleneck = min(bottleneck, adj_res[u][v]);
        }
        
        // updating the residual graph and the flow graph
        for(int i = 0; i < s-1; i++){
            int u = path[i];
            int v = path[i+1];

            if(f_edges.find({u,v}) != f_edges.end()){
                adj_g[u][v] += bottleneck;
            }
            else{
                adj_g[v][u] -= bottleneck;
            }
            //adj_g[u][v] += bottleneck;

            adj_res[u][v] -= bottleneck;
            adj_res[v][u] += bottleneck;
        }
        path.clear();
        path.push_back(src);
        for(int i = 0; i < n; i++){
        	vis[i] = false;
        }
    }


    // finding the maximum output flow from the source
    int ans = 0;
    for(int i = 0; i < n; i++){
        ans += adj_g[src][i];
    }

    return ans;
}

void task1(){
    /**
     * @brief - Task1 and Task2 of the assignment
     * @return void
    */

	// n - no. of vertices , m - no. of edges
    int n, m;
    cin >> n >> m;
    
    // src - source vertex, dest - destination vertex
    int src, dest;
    cin >> src >> dest;

    // edges - vector of edges
    vector<vector<int>> edges;
    for(int i = 0; i < m; i++){
        int u,v,cp;
        cin>>u>>v>>cp;
        edges.push_back({u,v,cp});
    }

    // to store the adjacency matrix
    vector<vector<int>> adj(n,vector<int>(n,0));
    for(auto it: edges){
        int u = it[0];
        int v = it[1];
        int cp = it[2];
        adj[u][v] = cp;
    }
    
    // creating a graph to store the flow of the edges
    vector<vector<int>> adj_g(n,vector<int>(n,0));
    // performing the ford fulkerson algorithm
    //task 1
    int ans1 = find_ford_fulkerson(adj,src,dest,adj_g);
    cout<<"Maximum Flow: "<<ans1<<endl;

    // S - the nodes which are reachable from source in residual graph
    // T - the nodes which are unreachable from source in residual graph
    vector<int> S;
    vector<int> T;

    // for checking the visited nodes
    vector<bool> vis(n,false);
    dfs_mincut(src,vis);
    for(int i = 0; i < n; i++){
    	if(vis[i]){
    		//cout<<i<<" ";
    		S.push_back(i);
    	}
    	else
    	{
    		T.push_back(i);
    	}
    }

    // to store the edges of the min-cut;
    vector<pair<int,int>> min_cut;
    for(int i = 0; i < S.size(); i++){
    	for(int j = 0; j < T.size(); j++){
    		// forward edges
    		if(adj[S[i]][T[j]] > 0){
    			min_cut.push_back({S[i],T[j]});
    		}
    		
    		// backward edges
    		if(adj[T[j]][S[i]] > 0){
    			min_cut.push_back({T[j],S[i]});	
    		}
    	}
    }
	cout<<endl;
	cout<<"MIN-CUT EDGES: \n";
    // printing the min-cut edges
    for(auto &x: min_cut){
    	cout<<x.first<<"->"<<x.second<<endl;
    }
}

void task3(){
    /**
     * @brief - Task3 of the assignment
     * @return void
    */

	int n,m,s;
	cin>>n>>m>>s;

	vector<pair<int,int>> ed;
	for(int i = 0; i < s; i++){
		int u,v;
		cin>>u>>v;
		ed.push_back({u,n+v});
	}

	vector<vector<int>> adj(n+m+2,vector<int>(n+m+2,0));
    
    for(auto &it: ed){
        int u = it.first;
        int v = it.second;
        int cp = 1;
        adj[u][v] = cp;
    }

    for(int i = 0; i < s; i++){
    	adj[0][ed[i].first] = 1;
    }

    for(int i = 0; i < s; i++){
    	adj[ed[i].second][n+m+1] = 1;
    }

    // creating a graph to store the flow of the edges
    vector<vector<int>> adj_g(n+m+2,vector<int>(n+m+2,0));
    // performing the ford fulkerson algorithm
    //task 1
    int ans1 = find_ford_fulkerson(adj,0,n+m+1,adj_g);
    cout<<"Maximum bipartite matching: "<<ans1<<endl;
}

int main(){
    /**
     * @brief This is the main function.
     * First it takes the input from the input.txt file.
     * Then it prints the output to the output.txt file.
     * call for the task1, task2, task3.
     * @param void
    */

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout); 

	//calling the task1 && task2
	task1();
	//calling the task3
    //task3();

    


}