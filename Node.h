#include <vector>

class Node {
	public:
	int g, f, h;
	int ix, jy;	//position in grid
	int wall; 	//1 if wall
	int cost;
	int nneighbours;

	//Node *parent only if we need to know the exact path taken
	//ommitted Node *parent for this implementation
	//Node *parent;
	std::vector<Node*> neighbours;
	//constructors
	Node();
	Node(int i, int j, int w);
	//adds neihbour nodes
	void addNeighbours(std::vector<std::vector<Node> > (&nodeset));
};

