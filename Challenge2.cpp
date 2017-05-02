/*
 * Coding Challenge 2
 * Programmer: Lawrence Jacobs
 *
 * This program finds the most lucrative path from a starting point, S2, to
 * a final point, S2.
 *
 */

#include <string>
#include <vector.h>
#include "hashmap.h"
#include "set.h"
using namespace std;

/*Definition for struct "Edge"*/
struct Edge{
    string start;
    string end;
    int cost;
};

/*Function Prototypes*/
Vector<Edge*> findAllPaths(string, HashMap<string, Vector<Edge*>>,
                 Set<string>, string, Vector<Vector<Edge*>>&, Vector<Edge*>);

int main() {
    int ncities = 5;
    int nedges = 6;

    Vector<string> cities;
    cities.add("S1");
    cities.add("A");
    cities.add("B");
    cities.add("B");
    cities.add("S2");

    Vector<int> earnings;
    earnings.add(5);
    earnings.add(15);
    earnings.add(16);
    earnings.add(-1);
    earnings.add(0);

    /*Match each city to the money that can be earned there*/
    HashMap<string, int> M_i;
    for(int i = 0; i < cities.size(); i++) M_i.put(cities[i], earnings[i]);


    /*Keep track of edges between cities with a Hashmap*/
    HashMap<string, Vector<Edge*>> edges;
    Edge* edge1 = new Edge;
    edge1->start = "S1";
    edge1->end = "A";
    edge1->cost = -2;

    Edge* edge2 = new Edge;
    edge2->start = "S1";
    edge2->end = "B";
    edge2->cost = -3;

    Edge* edge3 = new Edge;
    edge3->start = "A";
    edge3->end = "C";
    edge3->cost = -1;

    Edge* edge4 = new Edge;
    edge4->start = "A";
    edge4->end = "B";
    edge4->cost = -9;

    Edge* edge5 = new Edge;
    edge5->start = "B";
    edge5->end = "S2";
    edge5->cost = -8;

    Edge* edge6 = new Edge;
    edge6->start = "C";
    edge6->end = "S2";
    edge6->cost = -1;

    /*Add edges to hashmap*/
    Vector<Edge*> reachables;
    reachables.add(edge1);
    reachables.add(edge2);
    edges.put("S1", reachables);
    reachables.clear();

    reachables.add(edge3);
    reachables.add(edge4);
    edges["A"] = reachables;
    reachables.clear();

    reachables.add(edge5);
    edges["B"] = reachables;
    reachables.clear();

    reachables.add(edge6);
    edges["C"] = reachables;
    reachables.clear();

    /*Initialize variables to be used by path-finding function*/
    string end = "S2";
    string start = cities[0];
    Set<string> visited;
    Vector<Edge*> soFar;
    Vector<Vector<Edge*>> vectOfSoFars;

    /*Find all paths*/
    findAllPaths(start, edges, visited, end, vectOfSoFars, soFar);
    int max = 0;

    /*Find max*/
    for(Vector<Edge*> vec : vectOfSoFars){
        int cost = 0;
        for (Edge* edge : vec){
            cost += M_i[edge->start];
            cost += edge->cost;
        }
        if (cost >= max) max = cost;
    }

    cout << max;

    return 0;
}

/*Recursive function to generate all possible paths to S2*/
Vector<Edge*> findAllPaths(string start, HashMap<string, Vector<Edge*>> map_edges,
                 Set<string> visited, string end, Vector<Vector<Edge*>>& vectOfSoFars, Vector<Edge*> soFar){

    if(visited.contains(end)){
        vectOfSoFars.add(soFar);
        return soFar;
    }

    Vector<Edge*> edges = map_edges[start];

    for (Edge* edge : edges){
        if(visited.contains(edge->end)) continue;
        visited.add(edge->end);
        soFar.add(edge);
        findAllPaths(edge->end, map_edges, visited, end, vectOfSoFars, soFar);
    }
    return soFar;
}
