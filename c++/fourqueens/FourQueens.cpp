#include "common.h"
#include "FourQueens.h"

valarray<double> FourQueens::powv = FourQueens::powers();

/////////////////////////////////////////////////////////////////////////////
FourQueens::FourQueens() : tree(VSIZE)
{
	buildTree();
}

/////////////////////////////////////////////////////////////////////////////
FourQueens::~FourQueens()
{
}

/////////////////////////////////////////////////////////////////////////////
void FourQueens::buildTree()
{
	Node *root = tree.mkRoot(0);

	UInt32Vec path;
	for (uint32_t i = 0; i < VSIZE; i++) {
		makeNode(root, path, 1, i, i+1);
	}
}

/////////////////////////////////////////////////////////////////////////////
void FourQueens::makeNode(Node *parent, UInt32Vec & path, uint32_t level, 
	uint32_t index, uint32_t object)
{
	path.push_back(object);
	
	uint32_t npath = FourQueens::pathToUInt32(path);
	
	Node *node = tree.addNode(parent, index, npath);	

	if (level < VSIZE) {
		for (uint32_t i = 0; i < VSIZE; i++) {			
			makeNode(node, path, level+1, i, i+1);	
		}	
	} 

	path.pop_back();
}

/////////////////////////////////////////////////////////////////////////////
uint32_t FourQueens::pathToUInt32(const UInt32Vec & path)
{
	uint32_t npath = 0;

	UInt32Vec::const_iterator it = path.begin();

	for (uint32_t i = 0; it != path.end(); it++, i++) {
		npath = npath + (*it * (uint32_t)powv[i]);
	}

	return npath;
}

/////////////////////////////////////////////////////////////////////////////
FourQueens::UInt32Vec FourQueens::normalize(uint32_t npath)
{
	UInt32Vec path;

	uint32_t n;
	for (uint32_t i = 0; i < VSIZE; i++) {
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
valarray<double> FourQueens::powers()
{
	valarray<double> v(VSIZE);
	valarray<double> results;

	for (uint32_t i = 0; i < VSIZE; i++) {
		v[i] = VSIZE-1-i;
	}

	results = pow(double(VSIZE+1), v);

	return results;
}

/////////////////////////////////////////////////////////////////////////////
void FourQueens::solve(ostream &os)
{
	solve(tree, os);
}

/////////////////////////////////////////////////////////////////////////////
void FourQueens::solve(Node *node, ostream &os)
{
	uint32_t object = node->object;

	Node *pNode;
	for (uint32_t i = 0; i < VSIZE; i++) {
		if ((pNode = node->nodes[i]) != NULL)
			solve(pNode, os);
	}
}

/////////////////////////////////////////////////////////////////////////////
void FourQueens::printPath(uint32_t object, ostream &os)
{
	UInt32Vec path = normalize(object);

	UInt32Vec::const_iterator it = path.begin();
	for ( ; it != path.end(); it++) {
		if (*it == 0)
			os << '_';
		else 
			os << *it;
	}

	os << endl;
}
