
#include "common.h"
#include "ebtree.h"

int main(int argc, char *argv[])
{
	EBTree tree;
	tree.open("d:\\tmp\\test.dat", OM_RW);

	return 0;
}