#include <iostream>
#include <cmath>
#include <vector>
#include "Node.h"

using namespace std;

//find distance from a to b
int heuristic(Node &a, Node &b) {
	int x = a.ix - b.ix;
	int y = a.jy - b.jy;
	int dist = pow(x, 2) + pow(y, 2);
	dist = sqrt(dist);

	return dist;
}

/*	use A * algorithm to find most optimal path
 *	@param array[size_t][size_t]
 *	@result bool path exists 1 or not 0
 */
template <size_t size_x, size_t size_y>
bool DoesPathExist(int (&grid)[size_x][size_y]) {
	vector<vector<Node> > nodeset(size_x, vector<Node>(size_y));
	//Node nodeset[size_x][size_y];
	//Node openset[size_x*size_y];
	//Node closedset[size_x*size_y];
	vector<Node*> openset;
	vector<Node*> closedset;

	//initialize grid array of nodes
	for(int i=0; i<size_x; i++) {
		for (int j=0; j<size_y; j++) {
			Node tmp(i,j, grid[i][j]);
			nodeset[i][j] = tmp;
		}
	}
	//calculate every nodes neighbours
	for(int i=0; i<size_x; i++) {
		for (int j=0; j<size_y; j++) {
			nodeset[i][j].addNeighbours(nodeset);
		}
	}

	Node* start = &nodeset[0][0];
	Node* end = &nodeset[size_x-1][size_y-1];

	openset.push_back(start);

	//while openset not empty find lowest cost
	while (!openset.empty()) {
		int best = 0;
		for(int i = 0; i < openset.size(); i++) {
			//node not null
			if (openset[i]->ix > -1) {
				if (openset.at(i)->f < openset.at(best)->f) {
					best = i;
				}
			}
		}	
		
		//where to start calculating new neighbours
		Node* current = openset.at(best);

		//found shortestpath to end
		if (current->ix == end->ix && current->jy == end->jy) {
			return 1;
		}

		//TODO:
		//POSSIBLE ERROR IN INNER CONDITIONNAL
		//remove current from openset
		for(int i = 0; i < openset.size(); i++) {
			//node not null
			if (openset.at(i)->ix == current->ix && openset.at(i)->jy == current->jy) {
				openset.erase(openset.begin()+i);
			}
		}	
		//add to closedset
		closedset.push_back(current);

		//calculate neibhours of current
		vector<Node*> neighbours = current->neighbours;
		for (int i=0; i<current->nneighbours; i++) {
			Node* neighbour = neighbours.at(i);

			//dont calculate neighbour because wall
			if (neighbour->wall == 1) continue;

			bool inclosed = false;
			//check neighbour not in closedset
			for (int j=0; j<closedset.size(); j++) {
				//dont compute if in closed set
				if (closedset.at(j)->ix == neighbour->ix && closedset.at(j)->jy == neighbour->jy) {
					inclosed = true;
					continue;
				}
			}
			if (inclosed) continue;

			int tmpg = current->g + 1;

			//check if neighbour in openset
			bool inopen = false;
			for (int j=0; j<openset.size(); j++) {
				//check if better g in openset
				if (openset.at(j)->ix == neighbour->ix && openset.at(j)->jy == neighbour->jy) {
					inopen = true;
					//tmpg is better than previous path
					if (tmpg < neighbour->g) {
						neighbour->g = tmpg;
					}
				}
			}
			//better wasnt found
			if (!inopen) {
				neighbour->g = tmpg;
				openset.push_back(neighbour);
			}

			//calculate how far it is from the end and score node
			neighbour->h = heuristic(*neighbour, *end);
			neighbour->f = neighbour->g + neighbour->h;
		}
		
	}

	//openset is empty, so no path was found
	return 0;
}

//test harness
int main() {
	
	cout << "Finding path in grid: \n";
	cout << "\nstart\n|\nv";
	int x=5; 
	int y=9;
	int grid[5][9] = {{0,0,1,0,1,1,1,1,0},{1,0,0,0,0,1,1,0,0},{0,1,0,0,0,0,0,1,1},
		{1,1,0,0,0,1,0,0,0},{1,1,1,0,1,1,1 ,0,0}};

	for (int i=0; i<x; i++) {
		cout << endl;
		for (int j=0; j<y; j++) {
			cout << grid[i][j] << " ";
		}
	}

	cout << "<--end\n\nCalculating path... \n(1 if found, 0 if not found): ";
	bool result = DoesPathExist(grid);
	cout << result << endl;

	return result;
}
