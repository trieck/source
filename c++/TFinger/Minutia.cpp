#include "StdAfx.h"
#include "Minutia.h"

Minutia::Minutia()
    : type(MT_ISOLATED), x(0), y(0)
{
}

Minutia::Minutia(const Minutia &rhs)
{
    *this = rhs;
}

Minutia::~Minutia()
{
}


Minutia &Minutia::operator = (const Minutia &rhs)
{
    if (this != &rhs) {
        type = rhs.type;
        x = rhs.x;
        y = rhs.y;
    }

    return *this;
}
