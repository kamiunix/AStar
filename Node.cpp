#include "Node.h"

//constructors
Node::Node() : ix(-1), jy(-1), g(0), f(0), h(0), wall(-1), nneighbours(0) {}
Node::Node(int i, int j, int w) : ix(i), jy(j), wall(w), g(0), f(0), h(0), nneighbours(0) {}

//adds neihbour nodes
void Node::addNeighbours(std::vector<std::vector<Node> > (&nodeset)) {
	int x = nodeset.size();
	int y = nodeset[0].size();
	if (ix<x-1) {
		neighbours.push_back(&nodeset[ix+1][jy]);
		nneighbours+=1;
	}
	if (ix>0) {
		neighbours.push_back(&nodeset[ix-1][jy]);
		nneighbours+=1;
	}
	if (jy<y-1) {
		neighbours.push_back(&nodeset[ix][jy+1]);
		nneighbours+=1;
	}
	if (jy>0) {
		neighbours.push_back(&nodeset[ix][jy-1]);
		nneighbours+=1;
	}
}
