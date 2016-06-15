#include <iostream>
#include "SmallWorld.h"

using namespace std;

int main(){

	int t;
	cout << "Enter 0 for exit, 1 for non optimized code, 2 for optimized, 3 for bouns: " << endl;
	cin >> t;

	while (t){

		Graph G;
		if (t == 1 || t == 2) G.queries(t);
		else if (t == 3) G.bounce();

		cout << "Enter 0 for exit, 1 for non optimized code, 2 for optimized, 3 for bouns: " << endl;
		cin >> t;
	}

	//g.degOfSeperation();
    /*for (map<string, vector<Edge> >::iterator it = g.adjList.begin(); it != g.adjList.end(); it++){
	cout << it->first << endl;
	for (int i = 0; i < it->second.size(); i++) cout << it->second[i].from << "->" << it->second[i].to << "\t through" << it->second[i].value << endl;
	cout << endl;
	}
	*/
	return 0;
}


