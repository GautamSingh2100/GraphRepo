#include<iostream>
#include<list>
#include<stdlib.h>
//#include"MyUnion.h"
using namespace std;
const int MAX = 1000;

class MyUnion 
{ 
	int U[MAX] ;
	void child_to_parent(int u);
	public :
		MyUnion() ;
		int find(int u) ;
		bool	Union(int u,int v) ;
		void display() ;
};

MyUnion::MyUnion()   /// 		it is like Make process      self pointing 
{
			for(int i = 0 ; i < MAX ; i++)
				U[i]  = i ;
}

int MyUnion::find(int u)
{
	if(u < 0 && u > MAX)
		{
			cout << "boundary error" ;
			return -1;
		}
	if(U[u] == u)
		return u ;
		
	return U[u] = find(U[u]) ;
}

bool MyUnion::Union(int u,int v)
{
	int r1 , r2 ;
	r1 = find(u) ;
	r2 = find(v) ;
	if(r1 == -1 || r2 == -1)	return false ;
	if(r1 == r2)
		return false ;
	
	U[r1] = U[r2] ;
	return true ;
}

void MyUnion::display()
{
	for(int i  = 0 ; i < 7 ; i++)
		{
		child_to_parent(i) ;
		cout<< "\n\n" ;
		}
}

void MyUnion::child_to_parent(int u)
{
	cout<< u<< "   <<---";
	if(U[u] == u)
		return ;
	child_to_parent(U[u]) ;
}

/********/


class Edge
{
  public :
	int u ;
	int v ;
	int d ;
	Edge()
	{	u = 0 ;
		v = 0;
		d = 0 ;
	}
} ;

class Graph
{
	int E ;
	Edge *table ;
	int E_count ;
	list <Edge> l1 ;
	public:
		Graph(int E ) ;
		void insert(int uu,int  vv , int duv) ;
		void display();   // dispaly the connectivity
		void kruskal();
		void edgesort();
};

Graph::Graph(int e )
{
	table = new Edge[e] ;		
	E_count = -1 ;
	E = e ;
}

void Graph::edgesort()
{
	Edge temp;  int swap = 0 ;
	for(int i = 0 ; i <= E_count -1; i++)
	{	swap  = 0 ;
		for(int j = i ; j <= E_count - i -1 ; j++)
		{
			if(table[j].d > table[j+1].d)
			{
				temp = table[j] ;
				table[j] = table[j+1] ;
				table[j+1] = temp ;
				swap++ ;
			}
		}
	    if(swap == 0)
		break ;
	}
}
void Graph::insert(int uu,int vv,int dd)
{

	E_count++ ;
	table[E_count].u = uu ;
	table[E_count].v = vv ;
	table[E_count].d = dd ;
}

void Graph::display()	// display the spanig tree
{

	list <Edge>::iterator iter ;
	for(iter = l1.begin() ; iter !=l1.end() ; iter++)
		cout<< iter->u << "--" <<iter->v <<"  <-->"<<iter->d <<endl ;
}

void Graph::kruskal()
{
	int u,v,d ;
	MyUnion  *obj = new MyUnion() ;
	edgesort() ;

	for(int i = 0 ; i <= E_count ; i++)
	{
		u = table[i].u  ;
		v = table[i].v ;
		d = table[i].d ;
	
		if(obj->find(u) != obj->find(v))
		{
			obj->Union(u,v) ;
			l1.push_back(table[i]) ;
		}
	}
}



int main()
{
	Graph *G  = new Graph(1000);
	G->insert(0,1,1);
	G->insert(0,3,2);
	G->insert(1,2,2);
	G->insert(1,4,3);
	G->insert(2,4,3);
	G->insert(3,4,3);
	G->insert(3,5,2);
	G->insert(3,6,4);
	G->insert(5,6,2);
	G->insert(5,7,3);
	G->insert(4,7,2);
	G->kruskal() ;
	G->display() ;
return 0 ;
}
