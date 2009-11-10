#pragma once

#include "MultiwayTree.h"

/////////////////////////////////////////////////////////////////////////////
class Queens
{
public:
	Queens(uint32_t size);
	~Queens();

	void solve(ostream &os);

private:
	typedef MultiwayTree<uint32_t> MultiIntTree;
	typedef MultiIntTree::Node Node;
	typedef std::vector<uint32_t> UInt32Vec;

	void buildTree();
	void makeNode(Node *parent, UInt32Vec &path, 
		uint32_t level, uint32_t index, uint32_t object);
	void solve(Node *node, ostream &os);
	bool isFeasible(Node *node);
	
	uint32_t pathToUInt32(const UInt32Vec & path) const;
	UInt32Vec normalize(uint32_t npath) const;
	void printPath(uint32_t object, ostream &os) const;

	MultiIntTree tree;
	uint32_t board_size;

	valarray<double> powv;
	void mkpowers();
};
