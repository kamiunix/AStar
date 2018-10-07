#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <typeinfo>
#include "Node.h"

using namespace std;

//find distance from a to b
int heuristic(Node &a, Node &b) {
	int x = a.getIX() - b.getIX();
	int y = a.getJY() - b.getJY();
	int dist = pow(x, 2) + pow(y, 2);
	dist = sqrt(dist);

	return dist;
}

/*	use A * algorithm to find most optimal path
 *	@param array[size_t][size_t]
 *	@result bool path exists 1 or not 0
 */
bool DoesPathExist(vector<vector<int> > (&grid)) {
	int x = grid.size();
	int y = grid[0].size();
	vector<vector<Node> > nodeset(x, vector<Node>(y));
	//Node nodeset[x][y];
	//Node openset[x*y];
	//Node closedset[x*y];
	vector<Node*> openset;
	vector<Node*> closedset;

	//initialize grid array of nodes
	for(int i=0; i<x; i++) {
		for (int j=0; j<y; j++) {
			Node tmp(i,j, grid[i][j]);
			nodeset[i][j] = tmp;
		}
	}
	//calculate every nodes neighbours
	for(int i=0; i<x; i++) {
		for (int j=0; j<y; j++) {
			nodeset[i][j].addNeighbours(nodeset);
		}
	}

	Node* start = &nodeset[0][0];
	Node* end = &nodeset[x-1][y-1];

	openset.push_back(start);

	//while openset not empty find lowest cost
	while (!openset.empty()) {
		int best = 0;
		for(int i = 0; i < openset.size(); i++) {
			//node not null
			if (openset[i]->getIX() > -1) {
				if (openset.at(i)->getF() < openset.at(best)->getF()) {
					best = i;
				}
			}
		}	
		
		//where to start calculating new neighbours
		Node* current = openset.at(best);

		//found shortestpath to end
		if (current->getIX() == end->getIX() && current->getJY() == end->getJY()) {
			return 1;
		}

		//TODO:
		//POSSIBLE ERROR IN INNER CONDITIONNAL
		//remove current from openset
		for(int i = 0; i < openset.size(); i++) {
			//node not null
			if (openset.at(i)->getIX() == current->getIX() && 
					openset.at(i)->getJY() == current->getJY()) {
				openset.erase(openset.begin()+i);
			}
		}	
		//add to closedset
		closedset.push_back(current);

		//calculate neibhours of current
		vector<Node*> neighbours = current->getNeighbours();
		for (int i=0; i<current->getNN(); i++) {
			Node* neighbour = neighbours.at(i);

			//dont calculate neighbour because wall
			if (neighbour->getWall() == 1) continue;

			bool inclosed = false;
			//check neighbour not in closedset
			for (int j=0; j<closedset.size(); j++) {
				//dont compute if in closed set
				if (closedset.at(j)->getIX() == neighbour->getIX() && 
						closedset.at(j)->getJY() == neighbour->getJY()) {
					inclosed = true;
					continue;
				}
			}
			if (inclosed) continue;

			int tmpg = current->getG() + 1;

			//check if neighbour in openset
			bool inopen = false;
			for (int j=0; j<openset.size(); j++) {
				//check if better g in openset
				if (openset.at(j)->getIX() == neighbour->getIX() && 
						openset.at(j)->getJY() == neighbour->getJY()) {
					inopen = true;
					//tmpg is better than previous path
					if (tmpg < neighbour->getG()) {
						neighbour->setG(tmpg);
					}
				}
			}
			//better wasnt found
			if (!inopen) {
				neighbour->setG(tmpg);
				openset.push_back(neighbour);
			}

			//calculate how far it is from the end and score node
			neighbour->setH(heuristic(*neighbour, *end));
			neighbour->setF(neighbour->getG() + neighbour->getH());
		}
		
	}

	//openset is empty, so no path was found
	return 0;
}

//test harness
int main(int argc, char* argv[]) {
	int x=0;
	int y=0;
	string fname;
	if (argc < 2) {
		cout << "No file provided. Running with default\n";
		fname = "./tests/default";
	}
	else fname = argv[1];

	string line;
	ifstream file;
	file.open(fname);
	if (file.is_open()) {
		vector<vector<int> > grid;
		while(getline(file, line)) {
			x=line.length();
			grid.push_back(vector<int>());
			//extend by 1 y
			for(int i=0; i<line.length(); i++) {
				if (line[i] == '0') grid[y].push_back(0);
				else if (line[i] == '1') grid[y].push_back(1);
			}
			y+=1;
		}
		

		file.close();

		cout << "Finding path in grid: \n";
		cout << "\nstart\n|\nv";

		for (int i=0; i<y; i++) {
			cout << endl;
			for (int j=0; j<x; j++) {
				cout << grid[i][j] << " ";
			}
		}

		cout << "<--end\n\nCalculating path... \n(1 if found, 0 if not found): ";
		bool result = DoesPathExist(grid);
		cout << result << endl;

		return result;

	}
	else {
		cout << "File was not found.\n";
		return -1;
	}
}
