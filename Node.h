#include <vector>

class Node {
	int g, f, h;
	int ix, jy;	//position in grid
	int wall; 	//1 if wall
	int cost;
	int nneighbours;

	//Node *parent only if we need to know the exact path taken
	//ommitted Node *parent for this implementation
	//Node *parent;
	std::vector<Node*> neighbours;

	public:
	//constructors
	Node();
	Node(int i, int j, int w);

	//adds neihbour nodes
	void addNeighbours(std::vector<std::vector<Node> > (&nodeset));


	//setters
	void setG(int g);
	void setF(int f);
	void setH(int h);
	void setCost(int c);
	
	//getters
	int getG();
	int getF();
	int getH();
	int getIX();
	int getJY();
	int getWall();
	int getCost();
	int getNN();
	std::vector<Node *> getNeighbours();
};

