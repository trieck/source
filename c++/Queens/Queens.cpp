#include "common.h"
#include "Queens.h"

/////////////////////////////////////////////////////////////////////////////
Queens::Queens(uint32_t size) : board_size(size), tree(size)
{
	mkpowers();
	buildTree();
}

/////////////////////////////////////////////////////////////////////////////
Queens::~Queens()
{
}

/////////////////////////////////////////////////////////////////////////////
void Queens::buildTree()
{
	Node *root = tree.mkRoot(0);

	UInt32Vec path;
	for (uint32_t i = 0; i < board_size; i++) {
		makeNode(root, path, 1, i, i+1);
	}
}

/////////////////////////////////////////////////////////////////////////////
void Queens::makeNode(Node *parent, UInt32Vec & path, uint32_t level, 
	uint32_t index, uint32_t object)
{
	path.push_back(object);
	
	uint32_t npath = Queens::pathToUInt32(path);
	
	Node *node = tree.addNode(parent, index, npath);	

	if (level < board_size) {
		for (uint32_t i = 0; i < board_size; i++) {			
			makeNode(node, path, level+1, i, i+1);	
		}	
	} 

	path.pop_back();
}

/////////////////////////////////////////////////////////////////////////////
uint32_t Queens::pathToUInt32(const UInt32Vec & path) const
{
	uint32_t npath = 0;

	UInt32Vec::const_iterator it = path.begin();

	for (uint32_t i = 0; it != path.end(); it++, i++) {
		npath = npath + (*it * (uint32_t)powv[i]);
	}

	return npath;
}

/////////////////////////////////////////////////////////////////////////////
Queens::UInt32Vec Queens::normalize(uint32_t npath) const
{
	UInt32Vec path;

	uint32_t n;
	for (uint32_t i = 0; i < board_size; i++) {
		if (i > 0) {
			n = (npath % (uint32_t)powv[i-1]) / (uint32_t)powv[i];
		} else {
			n = npath / (uint32_t)powv[i];
		}
		path.push_back(n);
	}

	return path;
}

/////////////////////////////////////////////////////////////////////////////
void Queens::mkpowers()
{
	valarray<double> v(board_size);
	
	for (uint32_t i = 0; i < board_size; i++) {
		v[i] = board_size-1-i;
	}

	powv = pow(double(board_size+1), v);
}

/////////////////////////////////////////////////////////////////////////////
void Queens::solve(ostream &os)
{
	solve(tree, os);
}

/////////////////////////////////////////////////////////////////////////////
void Queens::solve(Node *node, ostream &os)
{
	if (!isFeasible(node)) 
		return;

	if (node->nodes[0] == NULL) {	// feasible leaf
		printPath(node->object, os);
	}

	Node *pNode;
	for (uint32_t i = 0; i < board_size; i++) {
		if ((pNode = node->nodes[i]) != NULL)
			solve(pNode, os);
	}
}

/////////////////////////////////////////////////////////////////////////////
bool Queens::isFeasible(Node *node)
{
	UInt32Vec path = normalize(node->object);

	uint32_t m, n, d, h;
	for (uint32_t i = 0; i < path.size(); i++) {
		if ((m = path[i]) == 0)
			return true;

		for (uint32_t j = i + 1; j < path.size(); j++) {
			if ((n = path[j]) == 0)
				return true;

			if (m == n) {
				return false;	// can't be in same column
			}

			d = abs(int(m - n));	// distance
			h = j - i;				// height

			if (d == h) {	// diagonal
				return false;
			}
		}
	}

	return true;
}

/////////////////////////////////////////////////////////////////////////////
void Queens::printPath(uint32_t object, ostream &os) const
{
	UInt32Vec path = normalize(object);

	string tbl(3 * path.size() + 1, '-');
	os << tbl << endl;

	string queen;
	UInt32Vec::const_iterator it = path.begin();
	for ( ; it != path.end(); it++) {
		if (*it == 0) continue;

		for (uint32_t i = 0; i < board_size; i++) {
			if (i == 0) {
				os << "|";
			}

			if (i+1 == *it) {
				os << "* |";
			} else {
				os << "  |";
			}
		}
		os << endl << tbl << endl;
	}
	os << endl;
}
