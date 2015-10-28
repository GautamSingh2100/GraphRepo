/**************************************************************************************/
/***** Author : Gautam Kumar , Works @ Amdocs DVCI , Graph Version 1.0          ******/
/***** This is the simple Graph library , Initial version, with basic data type *****/
/***** Assumption of this library A01 : using hash basd graph                   ****/
/**********************************************************************************/

#include<iostream>
#include<stack>
#include<queue> 
#include<list>

using namespace std ;

/***** default number of the number of Vertex ****/
const int MAXV = 1000 ; 


/***** eadge of the graph  , with next vertex and its distance *****/
class Edge
{
  public :
	int v      ;       /***** the node that current vertex point                     *****/
	int d      ;       /***** distance between the current node and the pointed node *****/
	Edge *next ;       /***** It contains the list of all the node that given node points , its like next of the list ****/
	
	Edge(int , int ) ;
	
} ;

/**** constructor : with next node index and its distance ****/
Edge::Edge(int vv , int dd = 0)
{
	v = vv ;
	d = dd ;
	next = NULL ;
}


/***** edge of the graph  , with current vertex and next vertex and distance between them *****/
/***** one sinario where it can be used , Kruskal's Algorithm *****/
 class Edgeuv
{
	public :
	int u ;   /**** current Vertex          ****/
	int v ;   /**** next Vertex             ****/
 	int d ;   /**** distance between vertex ****/
 	Edgeuv *next ; /**** contains the list of all the edge ****/
 	Edgeuv(int , int ,int) ; 	
};

Edgeuv::Edgeuv(int uu , int vv , int dd)
{
	u = uu ;
	v = vv ;
	d = dd ;
	next = NULL ;
}


/***** Its for the node table  ****/
class Vertex
{
	public:
	int     in   ;   /***** Number of vertex pointing the given vertex                  ****/
 	int     out  ;   /***** Number of vertex that current node is pointing to           ****/
	Edge  * next ;   /***** It contains the list of all the node that given node points , its like next of the list****/
};

struct QNode 
{
	int u ; 
	int d ;
} ;

/**** Graph class  , from which we can entract ****/
class Graph
{
	int     V       ;        /***** V is the value , Max number of node a given graph can contains  *****/
	Vertex  *vTable ;        /***** Vertex table , contains all the vertex                          *****/
	Edgeuv  *eHead  ;        /***** Edge table , contains list of all the edges of the graph        *****/
	int     E_count ;        /***** its tell all the number of edges in the graph                   *****/


    /******************************/
	/****** private members ******/
	/****************************/
	
    /***** depth first search in the graph from u to v ***/
	bool dfs_search(int u,int v,int *visted ,int *parent) ;
	/***** breadth first search from u to v ****/
	bool bfs_search(int u,int v) ;
	/***** print all the vertex information , using BFS *****/
	void bfs_display(int u);
	/**** print all the information , using DFS *****/
	void dfs_display(int u , int *visted);
	
	public:
	    /**** default constructor *****/
		Graph() ;
		/**** normal constructor , create table of V number of vertex  *****/
		Graph(int V ) ;
				
		void insert(int form,int to , int duv = 0) ;    /** Insert edge                 **/
		void display(int u ,int opt  = 0);              /** dispaly the connectivity    **/
		bool search(int u,int v,int opt = 0) ;       	/** search the node form u to v **/
		void Dijakshtra(int ) ;
		/**** destructor , to destroy the whole graph ****/
		//~Graph() ;		
};


/**** creating graph with empty graph with V node , ****/
Graph::Graph()
{
	this->V = MAXV; 	
	E_count  = 0 ;
	vTable = new Vertex[this->V] ;
	eHead = NULL ; 
	for(int i = 0 ; i < this->V ; i++)
	{
		(&this->vTable[i])->in   = 0 ;
		(&this->vTable[i])->out  = 0 ;
		(&this->vTable[i])->next = NULL ;
	}  		
}


/**** creating graph with empty graph with V node , ****/
Graph::Graph(int V )
{
	this->V  = V; 	
	E_count  = 0 ;
	vTable   = new Vertex[this->V] ;
	eHead    = NULL ; 
	for(int i = 0 ; i < this->V ; i++)
		{
			(&this->vTable[i])->in   = 0 ;
			(&this->vTable[i])->out  = 0 ;
			(&this->vTable[i])->next = NULL ;
		}  		
}


/***** Add node in  the vertex table ****/
void Graph::insert(int from,int to,int dis)
{
	Edge *e = new Edge(to,dis);
	Edge *temp ;
	
	/**** checking the vertex , is in range ****/
	/**** is greater than V , increas the graph ***/
	/**** if less than 0 , return ****/
	
	if(from < 0 || to < 0)  
	{
		return ; 
	}
	
	if(from > V || to > V )
	{
		// resizeGraph() ;
		//insert(from, to , dis) ;
		return ;
	}
	
	/**** if the vertex is not pointing any node | vertex pointing nothing****/
	if((&this->vTable[from])->next == NULL)
		{
			(&this->vTable[from])->next = e ;   /*** i like arrow in the code ***/
			(&this->vTable[to])->in++ ;
			(&this->vTable[from])->out++;
			
			++E_count ;
			Edgeuv  *edge = new Edgeuv(from , to , dis) ;
			this->eHead = edge ; 
			return ;
		}
	
	 e->next = (&this->vTable[from])->next ;
	(&this->vTable[from])->next = e ;
    // calculating in degree and the out degree
	(&this->vTable[to])->in++ ;
	(&this->vTable[from])->out++;

	++E_count ;
	Edgeuv  *edge = new Edgeuv(from , to , dis) ;
	
	/**** inserting the vertex into the edge list ****/
	edge->next =  this->eHead ; 
	this->eHead = edge ;
}

/**** display the containt of the grap, ****/
void Graph::display(int u  ,int opt )
{
	int *visted = new int[this->V + 1] ;
	for(int i = 0 ; i < V + 1;  i++)
		visted[i] = 0 ;

	if(opt == 0)	
		dfs_display(u,visted) ;
	else
		bfs_display( u);
	delete visted ;   //     if require then send to
}

/**** calling the DFS function , to display the grap recursively ****/
void Graph::dfs_display(int u,int *visted)
{
	
	visted[u] = 1 ;		
	cout << u << "   " ;
	for(Edge *ptr = vTable[u].next ; ptr ; ptr = ptr->next )
	{
		if(!visted[ptr->v])
		{
			dfs_display(ptr->v , visted) ;                    //  back tracking after this call   somthing above 	
									 //	somthing below
		}
	}
}

/**** dispalying the the graph usnig BFS *****/
void Graph::bfs_display(int u)
{
    int *visted = new int[V] ;
	for(int i = 0 ; i  < V ; i ++)
		visted[i] = 0 ;

	queue <int> Q ;
	
	visted[u] = 1 ;
	Q.push(u) ;
	while(!Q.empty())
	{
		int cur = Q.front();
		Q.pop() ;
		if(visted[cur] == 1)
		{
		 visted[cur] = 2 ;
		 cout << cur << "  ";
			for(Edge *ptr = (&vTable[cur])->next ; ptr ; ptr = ptr->next)
			{	
				if(visted[ptr->v] == 0)
				{
				visted[ptr->v] = 1 ;
				Q.push(ptr->v) ;					
				}
		 	}	
		}
	}

	delete visted ;
}


/**** searching the path in the graph, ****/
bool Graph::search(int u,int v ,int opt)
{
	int *visted = new int[V] ;
	int *parent = new int[V] ;
	for(int i = 0 ; i < V ;  i++) 
	{
		visted[i] = 0 ;
		parent[i] = -1 ;
	}
	
	parent[0] =  -1 ;
	
	bool flag = false ;
	
	if(opt == 0)	
	{	
	    flag = dfs_search(u,v,visted ,parent) ;
		if(flag)
		{	int v1 = v ;
			cout<< v1<<"<---" ;
			while(parent[v] != -1)
			{
				cout<< parent[v] << "<---" ;
				v = parent[v] ;
			}
		}
			
	}
	else
	{
		flag =  bfs_search(u,v);
	}	
	
	delete visted ;   //     if require then send to
	delete parent ;
	return flag ;
}


/**** searching the path from u to v , using dfs *****/
bool Graph::dfs_search(int u,int v,int *visted,int *parent)
{

	visted[u] = 1 ;		
	for(Edge *ptr = vTable[u].next ; ptr ; ptr = ptr->next )
	{
		if(!visted[ptr->v] )
		{
			parent[ptr->v] = u ;
			if(ptr->v == v)			
				return true ;

		        if(dfs_search(ptr->v ,v, visted ,parent))                    //  back tracking after this call  somthing 
				return true  ;							                     //above somthing below
		}
	}
	
	return false ;
}

/***** searching the path form u to v using bfs ****/
bool Graph::bfs_search(int u,int v)
{
    int *visted = new int[V] ;
	int *parent = new int[V] ;
	
	for(int i = 0 ; i  < V ; i ++)
	{
		visted[i] = 0 ;
		parent[i] = -1 ;
	}
	
	parent[u] = -1 ;

	queue <int> Q ;
	visted[u] = 1 ;
	Q.push(u) ;
	bool flag  = false ;
	while(!Q.empty()&& !flag)
	{
		int cur = Q.front() ;
		Q.pop();
		if(visted[cur] == 1)
		{
		  visted[cur] = 2 ;
		  
		  for(Edge *ptr = (&vTable[cur])->next ; ptr ; ptr = ptr->next)
		   { 
		         if(ptr->v == v)
				 {
					flag = true ;
					parent[ptr->v]   = cur ;
					break ;
				 }
					
			if(visted[ptr->v] == 0)
			{				
				visted[ptr->v] = 1 ;			// 0->  white   1 ->> gray  ->> black			
				parent[ptr->v]   = cur ;				
				visted[v] = 1 ; 
				Q.push(ptr->v) ;		
			}
		   }
	    }
		
	}

	if(flag)
	{
		cout << v ;
		while(parent[v] != -1)
		{
			cout<< "<---" << parent[v] ;
			v = parent[v] ;
		}
		
	}
	delete visted ;
	delete parent ;
	return flag ;
}

/**** Dijakshtra's Shortest path algorithm ****/
void Graph::Dijakshtra(int u)
{
	int *visted = new int[V] ;
	int *parent = new int[V] ;
	int *dis    = new int[V] ;
	QNode node ; 
	queue <QNode> dijQ ;
	for(int i = 0 ;  i< V; i++)
	{
		visted[i] = 0 ;
		parent[i] = -2 ;
		dis[i] = 2345667 ;
	}
	
	dis[u] = 0 ;
    node.u = u ;
    node.d = 0 ;
	dijQ.push(node) ;
	parent[u] = -1 ;	
	
	while(!dijQ.empty())
	{
		node = dijQ.front() ;
		dijQ.pop() ;
		if(!visted[node.u])
		{
			visted[node.u] = 1 ;
			for(Edge *e = vTable[node.u].next ; e ; e = e->next )
			{
				if(!visted[e->v]  )
				{
					
					if((dis[node.u]  + e->d ) < dis[e->v] )
					{
						dis[e->v] = dis[node.u]  + e->d  ;
						parent[e->v] = node.u ;
						node.u = e->v ;
					    node.d = dis[e->v] ;
					    dijQ.push(node) ;		
					}
								
				}
			}
		}
	}

	for(int i = 0 ; i < V ; i++)
		cout << " Vertex : " << i <<"  dis "<< dis[i] << "  	Parent  : " << parent[i] <<endl ;
}	

int main()
{
	int edge[][3] = {{0,1,2},{0,2,3},{0,3,1},{1,3,4},{1,5,6},{2,3,7},{3,4,2},{3,5,2},{5,4,1}} ;
	int E = 9 ;
	Graph *G = new Graph(10) ;

	for(int i = 0 ; i < E ; i++)
		G->insert(edge[i][0] ,edge[i][1],edge[i][2]) ;


    cout << "\n\n" ;	
	G->display(0 , 1) ;
    cout << "\n\n" ;
	G->display(1 ,1) ;
	cout<<"\n\n" ;
	cout << "\n"<<G->search(5 , 4 , 1)<<endl ;
	cout<<"\n\n" ;
	cout<<"\n"<<G->search(0 , 5 , 1) << endl     ;
	cout<<"\n\n" ;
	cout<<"\n"<<G->search(7 , 0)<< endl;
	cout<<"\n\n" ;
	cout<<"\n"<<G->search(8 , 1)<<endl;
	cout<<"\n\n" ;
    G->Dijakshtra(0) ;
	return 0 ;
}

