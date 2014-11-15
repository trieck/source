
#include <stdio.h>

int main(int argc, char *argv[])
{
    int c, d, e, f, intag = 0, incomment = 0;

    while ((c = getchar()) != EOF) {
        switch (c) {
        case '<':
            if (!incomment)
                intag = 1;

            d = getchar();	// check for html comment
            e = getchar();
            f = getchar();
            if (d != '!' && e != '-' && f != '-') {
                ungetc(f, stdin);
                ungetc(e, stdin);
                ungetc(d, stdin);
            } else {
                incomment = 1;
            }
            break;
        case '-':
            d = getchar();	// check for end html comment
            e = getchar();
            if (d != '-' && e != '>') {
                ungetc(e, stdin);
                ungetc(d, stdin);
                if (!intag && !incomment)
                    putchar(c);
            } else {
                incomment = 0;
            }
            break;
        case '>':
            intag = 0;
            break;
        default:
            if (!intag && !incomment)
                putchar(c);
        }
    }

    return 0;
}