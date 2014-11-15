#include "common.h"
#include "Queens.h"

/////////////////////////////////////////////////////////////////////////////
Queens::Queens(uint32_t size) : board_size(size)
{

}

/////////////////////////////////////////////////////////////////////////////
Queens::~Queens()
{
}

/////////////////////////////////////////////////////////////////////////////
void Queens::solve(ostream &os)
{
    UInt32Vec path;

    for (uint32_t i = 0; i < board_size; i++) {
        solve(path, os, i+1);
    }
}

/////////////////////////////////////////////////////////////////////////////
void Queens::solve(UInt32Vec &path, ostream &os, uint32_t object)
{
    path.push_back(object);

    if (!isFeasible(path)) {
        path.pop_back();
        return;
    }

    if (path.size() == board_size) { // feasible leaf
        printPath(path, os);
        path.pop_back();
        return;
    }

    for (uint32_t i = 0; i < board_size; i++) {
        solve(path, os, i+1);
    }

    path.pop_back();
}

/////////////////////////////////////////////////////////////////////////////
bool Queens::isFeasible(const UInt32Vec &path)
{
    uint32_t m, n, d, h;
    for (uint32_t i = 0; i < path.size(); i++) {
        if ((m = path[i]) == 0)
            return true;

        for (uint32_t j = i + 1; j < path.size(); j++) {
            if ((n = path[j]) == 0)
                return true;

            if (m == n) {
                return false; // can't be in same column
            }

            d = abs(int(m - n)); // distance
            h = j- i; // height

            if (d == h) { // diagonal
                return false;
            }
        }
    }

    return true;
}

/////////////////////////////////////////////////////////////////////////////
void Queens::printPath(const UInt32Vec & path, ostream &os) const
{
    string tbl(4 * path.size() + 1, '-');
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
                os << " * |";
            } else {
                os << "   |";
            }
        }

        os << endl << tbl << endl;
    }

    os << endl;
}

