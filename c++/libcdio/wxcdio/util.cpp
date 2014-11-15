
#include "common.h"
#include "util.h"

wxString Reverse(const wxString &input)
{
    wxString output;

    uint32_t nlen = input.length();

    output.Alloc(nlen);

    for (int i = nlen - 1; i >= 0; i--) {
        output += input[i];
    }

    return output;
}

wxString Comma(uint32_t i)
{
    wxString output;

    wxString input;
    input << i;

    uint32_t n = input.length();

    for (int j = n - 1, k = 1; j >= 0; j--, k++) {
        output += input[j];
        if (k % 3 == 0 && j > 0 && j < n - 1)
            output += _T(',');
    }

    return Reverse(output);
}