#pragma once

#include <iostream>
#include <vector>
#include <map>
#include<queue>
#include <string>
#include <fstream>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////
class Edge
{
public:

	//constructors
	Edge(string, string, string, int, int, bool);
	Edge();

	//destructor
	~Edge();

	//operator overloading
	bool operator < (const Edge& e) const;
	Edge& operator = (const Edge& e);

	//members
	string  from;
	string to;
	int w;
	int vw;
	string value;
	bool is_visited;


};
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
class Graph
{

private:
	void readData();    //read data from files
	void putData(string, vector<string>);    //put data in the graph DS
	pair<int, int> Dijkstra(string, string, int);    //Dijkstra shortest path algorithm

public:
	Graph();    //constructor
	~Graph();    //destructor

	void bounce();    //get distribution of degree of seberation related to on actor/actress
	void degOfSeperation(string, string, int);    //get degree of seperation and relation strength between two actors/actress
	void queries(int);    //read queries from file
	void printChain(string, string);    //print chain of movies between two actors/actress

	//members
	map<string, vector<Edge> > adjList;    //graph DS   
	map<string, vector<Edge> > temp;    //temp adjlist
	map<string, pair<int, int> > dist;    //map store degree of seperation and relation strength between two actors/actress
	map<string, pair<string, string> > prev;    //map store chain of movies between two actors/actress

};
///////////////////////////////////////////////////////////////////////////////////////////////
