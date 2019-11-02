#pragma once

/////////////////////////////////////////////////////////////////////////////
class Queens
{
public:
    Queens(uint32_t size);
    ~Queens();

    void solve(ostream &os);
private:
    typedef std::vector<uint32_t> UInt32Vec;
    void solve(UInt32Vec &path, ostream &os, uint32_t object);

    bool isFeasible(const UInt32Vec &path);
    void printPath(const UInt32Vec &path, ostream &os) const;

    uint32_t board_size;
};
