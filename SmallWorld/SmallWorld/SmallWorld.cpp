#include "SmallWorld.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//constructors
Edge::Edge(){
	this->w = 1;
	this->vw = 1;
	this->is_visited = false;
}

Edge::Edge(string from, string to, string value, int w = 1, int vw = 1, bool is_visited = false){
	this->from = from;
	this->to = to;
	this->value = value;
	this->w = w;
	this->vw = vw;
	this->is_visited = is_visited;
}

//destructor
Edge::~Edge(){

}

//operator overloading
bool Edge::operator < (const Edge& e) const {
	return vw > e.vw;
}


Edge& Edge::operator = (const Edge& e){
	this->from = e.from;
	this->to = e.to;
	this->value = value;
	this->is_visited = e.is_visited;
	this->w = e.w;
	this->vw = e.vw;
	return *this;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//constructors
Graph::Graph(){
	readData();
}

//destructor
Graph::~Graph(){

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//read data from files
void Graph::readData(){

	//read data from the file an fill the Graph
	ifstream myfile;
	try{

		myfile.open("smallworld.txt");

		cout << "indexing data, please be patient" << endl;

		if (myfile.is_open()){
			string s, movie = "", temp = "";
			vector<string> actors;
			//cout << "i am here" << endl;

			while (getline(myfile, s)){

				//read from file
				int con = 0;
				for (int i = 0; i < s.length(); i++){
					if (!con) movie += s[i];
					else if (con) temp += s[i];

					if (s[i] == '/'){
						if (!con) { movie = movie.substr(0, movie.length() - 1); con++; }
						else if (con && temp != "") { actors.push_back(temp.substr(0, temp.length() - 1)); }
						temp = "";
					}

				}
				if (temp != "") actors.push_back(temp);

				//put data into graph
				putData(movie, actors);
				
				movie = "";
				temp = "";
				actors = vector<string>();
			}
		}

		myfile.close();
		cout << "indexing done successfully" << endl;
	}
	catch (exception) { cout << "Can't open the file." << endl; }

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//put data in the graph DS
void Graph::putData(string movie, vector<string> actors){

	for (int i = 0; i < actors.size(); i++)
	     for (int j = 0; j < actors.size(); j++)
	          if (j != i) adjList[actors[i]].push_back(Edge(actors[i], actors[j], movie, 1));

	this->temp = this->adjList;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Dijkstra shortest path algorithm
pair<int, int>  Graph::Dijkstra(string src, string dest, int opt){

	dist[src].first = 0;    //DegOfSep of source node
	int srs = 1; //self relation strength
	string value = adjList[src][0].value;
	for (int i = 0; i < adjList[src].size(); i++)
		if (value != adjList[src][i].value) { srs++; value = adjList[src][i].value; }

	dist[src].second = srs;    //relation strength of source node

	priority_queue<Edge> pq;
	pq.push(Edge("", src, "", 0, 0, false));

	while (!pq.empty()){    //to visite all graph nodes

		Edge e = pq.top();
		pq.pop();
		
		//optimization
		if (opt == 2) if (e.to == dest) return dist[dest];

		map<string, pair<int, int> >::iterator it = dist.find(e.to);    //if the node is not found in the map
		if (it == dist.end()) { dist[e.to].first = 1000000000; dist[e.to].second = -1; }    //create node with intial values

		if (e.w > dist[e.to].first) continue;    //worse case
		
		for (int i = 0; i < adjList[e.to].size(); i++){    //loop at the node edges

			Edge ne = adjList[e.to][i];

			map<string, pair<int, int> >::iterator it = dist.find(ne.to);    //if the node is not found in the map
			if (it == dist.end()) { dist[ne.to].first = 1000000000; dist[ne.to].second = -1; }    //create node with intial values

			if (dist[ne.to].first > dist[ne.from].first + ne.w) {    //update shortest path, relation strength and movies chain
				ne.vw = dist[ne.to].first = dist[ne.from].first + ne.w;     //update shortest path
				
				int numOfMovies = 0;
				for (int i = 0; i < adjList[ne.from].size(); i++) 
				     if (adjList[ne.from][i].to == ne.to) numOfMovies++;

			    dist[ne.to].second = dist[ne.from].second + numOfMovies;    //update relation strength
				if (ne.from == src) dist[ne.to].second -= srs;

				prev[ne.to].first = ne.from;    //update movies chain
				prev[ne.to].second = ne.value;
			}
			else if (dist[ne.to].first == dist[ne.from].first + ne.w){    //update relation strength and movies chain

				int numOfMovies = 0;
				for (int i = 0; i < adjList[ne.from].size(); i++)
				     if (adjList[ne.from][i].to == ne.to) numOfMovies++;

				if (dist[ne.to].second < dist[ne.from].second + numOfMovies) {    //update relation strength
					dist[ne.to].second = dist[ne.from].second + numOfMovies;

					prev[ne.to].first = ne.from;    //update movies chain

					prev[ne.to].second = ne.value;
				}

				if (ne.from == src) dist[ne.to].second -= srs;
			}

			if (!ne.is_visited) pq.push(ne);    //push edge
			adjList[e.to][i].is_visited = true;    //mark edge as visited
		}

	}

	
	map<string, pair<int, int> >::iterator not_found = dist.find(dest);    //if desftination is not found
	if (not_found == dist.end()) return pair<int, int>(-1, -1); 

	return dist[dest];    //return shortest path and relation strength from source to destination
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//read queries from file
void Graph::queries(int opt){

	//read queries from file
	ifstream myfile;
	try{

		myfile.open("queries1.txt");

		if (myfile.is_open()){

			string s, actor1 = "", actor2 = "";
			cout << "Query \t Deg. \t Rel. \t Chain" << endl;
			while (getline(myfile, s)){

				int con = 0;
				for (int i = 0; i < s.length(); i++){
					if (!con) actor1 += s[i];
					else if (con) actor2 += s[i];
					if (s[i] == '/') { con++; actor1 = actor1.substr(0, actor1.length() - 1); }
				}

				//call processing function
				degOfSeperation(actor1, actor2, opt);

				this->dist.clear();    //reset dist map
				this->prev.clear();   //reset prev map
				this->adjList = this->temp;    //reset adjlist map

				actor1 = "";
				actor2 = "";
			}

			cout << endl;
		}
	}
	catch (exception e){ cout << "Can't open the file. " << endl; }

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//get distribution of degree of seberation related to on actor/actress
void Graph::bounce(){

	string src, dest;    
	int maxrs = -1;    //max relation strength
	int freq[13] = {};    //distribution of the degree of separation
	freq[0] = 1;    //self degree of seperation

	cout << "Enter the actor (source): ";
	cin.ignore();
	getline(cin, src);

	//call Dijkstra to get degree of seperation and relation strength between two actors/actress
	Dijkstra(src, "", 3); //pair of shortest path and relation strength

	for (map<string, pair<int, int> >::iterator it = dist.begin(); it != dist.end(); it++){
		int sep = (*it).second.first;
		if (sep < 12) freq[sep]++;
		else freq[12]++;

		if ((*it).second.second > maxrs) { maxrs = (*it).second.second; dest = (*it).first; }
	}

	cout << endl;
	cout << "Deg. of Separ. \t Frequency" << endl;
	cout << "---------------------------" << endl;

	for (int i = 1; i < 13; i++) {    //print distribution of the degree of separation
		if (i == 12) cout << ">" << i - 1 << "\t" << freq[i] << endl;
		else cout << i << "\t" << freq[i] << endl;
	}
	cout << endl;

	cout << "The strongest path (based on the relation strength): " << maxrs <<  endl;
	printChain(dest, src);     //print The strongest path (based on the relation strength)
	cout << endl << endl;

	this->dist.clear();    //reset dist map
	this->prev.clear();   //reset prev map
	this->adjList = this->temp;    //reset adjlist map
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//get degree of seperation and relation strength between two actors/actress
void Graph::degOfSeperation(string src, string dest, int opt){

	cout << endl;
	
	//call Dijkstra to get degree of seperation and relation strength between two actors/actress 
	pair<int, int> sprs = Dijkstra(src, dest, opt); //pair of shortest path and relation strength

	cout << src << "/" << dest << "\t" << sprs.first << "\t" << sprs.second << "\t";    //print degree of seperation and relation strength
	if (sprs.first != -1 && sprs.second != -1) printChain(dest, src);    //print chain of movies

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//print chain of movies between two actors/actress
void Graph::printChain(string dest, string src){

	string temp = dest;
	vector<string> vec;    //movies chain

	while (temp != src){
		vec.push_back(prev[temp].second);
		temp = prev[temp].first;
	}

	if (!vec.size()) return;
	
	cout << vec[vec.size() - 1];
	for (int i = vec.size() - 2; i >= 0; i--) cout << "->" << vec[i];    //print chain of movies
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////