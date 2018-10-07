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

//setters
void Node::setG(int g) { this->g = g; }
void Node::setF(int f) { this->f = f; }
void Node::setH(int h) { this->h = h; }
void Node::setCost(int c) { this->cost = c; }

//getters
int Node::getG() { return g; }
int Node::getF() { return f; }
int Node::getH() { return h; }
int Node::getIX() { return ix; }
int Node::getJY() { return jy; }
int Node::getWall() { return wall; }
int Node::getCost() { return cost; }
int Node::getNN() { return nneighbours; }
std::vector<Node*> Node::getNeighbours() { return neighbours; }
