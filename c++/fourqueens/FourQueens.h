#pragma once

#include "MultiwayTree.h"

/////////////////////////////////////////////////////////////////////////////
class FourQueens
{
public:
	FourQueens();
	~FourQueens();

	void solve(ostream &os);

private:
	typedef MultiwayTree<uint32_t> MultiIntTree;
	typedef MultiIntTree::Node Node;
	typedef std::vector<uint32_t> UInt32Vec;

	enum { VSIZE = 4 };
	
	void buildTree();
	void makeNode(Node *parent, UInt32Vec &path, 
		uint32_t level, uint32_t index, uint32_t object);
	void solve(Node *node, ostream &os);
	
	static uint32_t pathToUInt32(const UInt32Vec & path);
	static UInt32Vec normalize(uint32_t npath);
	static void printPath(uint32_t object, ostream &os);

	MultiIntTree tree;

	static valarray<double> powv;
	static valarray<double> powers();
};
