/**********************************************************************
 *
 * CISC 4080: Computer Algorithms
 * Project 3: Topological Sorting
 *
 * Author: Abadali Sheikh
 * Date:   March 6th 2018
 *
 * A topological sorting algorithm for directed acyclic graphs (DAGs)
 * based on the suggested method in the text. The program allows for any
 * vertices of any dataype read from input stream.
 *
 **********************************************************************/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

// misc datatypes
template <typename VertexType> struct Edge {
   VertexType from;
   VertexType to;
};

template <typename VertexType> struct Graph {
   vector<VertexType> vertices;
   vector<Edge<VertexType>> edges;
};

// function declarations
template <typename VertexType>
istream& operator>>(istream& is, Edge<VertexType>& e);

template <typename VertexType>
ostream& operator<<(istream& is, const Edge<VertexType>& e);

template <typename VertexType> Graph<VertexType> getData(string fileName);

template <typename VertexType> vector<VertexType> topSort(Graph<VertexType> g);

int main(int argc, char** argv)
{
   /*
    * get the data
    */
   if (argc != 2) {
      cerr << "Usage: " << argv[0] << " datafile\n";
      return 1;
   }
   Graph<char> g = getData<char>(argv[1]);

   /*
    * do the topological sort
    */
   vector<char> tSort = topSort(g);

   /*
    * report results
    */
   for (auto vertex: tSort)
      cout << vertex << " ";
   cout << endl;

   return 0;
}

/*
 * function definitions
 */

// input operator: read an edge from an input stream
// edge has form (v,w) where vertices v and w are of type VertexType
template <typename VertexType>
istream& operator>>(istream& is, Edge<VertexType>& e)
{
   VertexType initial, terminal;
   char lparen, comma, rparen;
   is >> lparen >> initial >> comma >> terminal >> rparen;
   if (!is) return is;
   if (lparen != '(' || comma != ',' || rparen != ')') {
      cerr << "Bad format " << lparen <<  initial << comma 
           <<  terminal <<  rparen
           << " ... edge ignored\n";
      return is;
   }
   e.from = initial;
   e.to = terminal;
   return is;
}

// output operator: write an edge to an output stream
// edge has form (v,w) where vertices v and w are of type VertexType
template <typename VertexType> 
ostream& operator<<(ostream& os, const Edge<VertexType>& e)
{
   os<< '(' << e.from << ',' << e.to << ')';
   return os;
}

// read graph data from a file
template <typename VertexType> Graph<VertexType> getData(string fileName)
{
   ifstream dataStream(fileName.c_str());
   if (!dataStream) {
      cerr << "can't open " << fileName << endl;
      exit(1);
   }

   Edge<VertexType> e;
   Graph<VertexType> g;
    
   // vertices
   char ch;
   while (dataStream >> ch && !(isspace(ch) || ch == '(')) {
      dataStream.putback(ch);
      VertexType temp;
      dataStream >> temp;
      g.vertices.push_back(temp);
   }
   dataStream.putback(ch);

   // edges
   while (dataStream >> e) 
      g.edges.push_back(e);

   return g;
}
/*
 * Input: Graph G(V,E)
 * Output: A vector consisting of all the vertices in topological order
 *
 */
template <typename VertexType> vector<VertexType> topSort(Graph<VertexType> g)
{
    map<VertexType, int> indegree_map; // contains
    vector<VertexType> List; //
    vector<VertexType> set;
    
    //A map of each vertex & its in_degree
    for (unsigned int i = 0; i < g.edges.size(); i++)
        indegree_map[g.edges[i].to] += 1;
   
    //identify all sources to set (in-degree == 0)
    for (unsigned int j = 0; j < g.vertices.size(); j++) {
        if (indegree_map[g.vertices[j]] == 0)
            set.push_back(g.vertices[j]);
    }

    while (!set.empty()) {
        //Store found sources & delete from Graph
        VertexType temp = set.front();
        set.erase(set.begin());
        List.push_back(temp);
        
        //for each outgoing edge decrement in-degree
        //if in-degree == 0 add to set
        for (unsigned  int k = 0; k < g.edges.size(); k++) {
            if (g.edges[k].from == temp) {
                indegree_map[g.edges[k].to] -= 1;
                if (indegree_map[g.edges[k].to] == 0)
                    set.push_back(g.edges[k].to);
                g.edges.erase(g.edges.begin() + k);
                k--;
            }
        }
    }
    return List;
}
