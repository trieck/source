import element

ET_UNDEF = 0
ET_INTEGER = 1
ET_STRING = 2
ET_LIST = 3
ET_DICT = 4


class Lex:
    def __init__(self, fp):
        self.fp = fp

    @staticmethod
    def decode(b):
        if b == '':
            return ''
        return b.decode('latin-1')

    def peek(self):
        c = self.fp.read(1)
        self.fp.seek(-1, 1)
        return self.decode(c)

    def getch(self):
        return self.decode(self.fp.read(1))

    def gettok(self):
        c = self.peek()
        if c == 'd':
            self.getch()
            return ET_DICT
        elif c == 'i':
            self.getch()
            return ET_INTEGER
        elif c == 'l':
            self.getch()
            return ET_LIST
        elif c.isdigit():
            return ET_STRING
        else:
            self.getch()
            return c

    def dictionary(self):
        e = element.Dictionary()
        c = self.peek()
        while c != 'e' and c != '':
            k = self.string()
            v = self.getelement()
            e[k.value] = v
            c = self.peek()

        self.gettok()  # 'e'

        return e

    def integer(self):
        e = element.Integer()
        x = ""
        c = self.peek()
        while c != 'e' and c != '':
            x += self.getch()
            c = self.peek()

        self.gettok()  # 'e'
        e.value = int(x)

        return e

    def list(self):
        e = element.List()
        c = self.peek()
        while c != 'e' and c != '':
            e.value.append(self.getelement())
            c = self.peek()

        self.gettok()  # 'e'

        return e

    def string(self):
        e = element.String()
        x = ""
        cnt = 0
        c = self.peek()
        while c != ':' and c != '':
            x += self.getch()
            c = self.peek()

        length = int(x)
        self.gettok()  # ':'

        while cnt < length:
            c = self.getch()
            if c == '':
                break
            e.value += c
            cnt += 1

        return e

    def getelement(self):
        t = self.gettok()
        if t == ET_DICT:
            return self.dictionary()
        elif t == ET_INTEGER:
            return self.integer()
        elif t == ET_LIST:
            return self.list()
        elif t == ET_STRING:
            return self.string()
        else:
            raise Exception("undefined token \"%s\"." % t)
