#pragma once

#include <iostream>
#include <vector>
#include <map>
#include<queue>
#include <string>
#include <fstream>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////
class Edge  //边
{
public:

	//constructors 构造函数
	Edge(string, string, string, int, int, bool);
	Edge();

	//destructor 析构函数（用于销毁对象）
	~Edge();

	//operator overloading 运算符重载，定义该对象的小于和等于
	bool operator < (const Edge& e) const;
	Edge& operator = (const Edge& e);

	//members 元素
	string  from;  //起始地
	string to;  //目的地
	int w;      //
	int vw;     //
	string value;  //字符串的值(名称)
	bool is_visited; //是否被访问


};
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
class Graph  //关系图
{

private:
	void readData();    //read data from files  从文件中读取数据
	void putData(string, vector<string>);    //put data in the graph DS  将数据放入图表DS中
	pair<int, int> Dijkstra(string, string, int);    //Dijkstra shortest path algorithm (Dijkstra最短路径算法)

public:
	Graph();    //constructor 构造函数
	~Graph();    //destructor 析构函数

	void bounce();    //get distribution of degree of seberation related to on actor/actress
	void degOfSeperation(string, string, int);    //get degree of seperation and relation strength between two actors/actress 获得两个演员/女演员之间的分离程度和关系强度
	void queries(int);    //read queries from file  从文件中读取查询
	void printChain(string, string);    //print chain of movies between two actors/actress  在两位演员/女演员之间打印电影链

	//members  元素
	map<string, vector<Edge> > adjList;    //graph DS DS图表
	map<string, vector<Edge> > temp;    //temp adjlist 
	map<string, pair<int, int> > dist;    //map store degree of seperation and relation strength between two actors/actress
	map<string, pair<string, string> > prev;    //map store chain of movies between two actors/actress

};
///////////////////////////////////////////////////////////////////////////////////////////////
