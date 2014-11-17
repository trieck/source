class Element:
    value = 0


class Dictionary(Element):
    def __init__(self):
        self.value = {}

    def __getitem__(self, key):
        return self.value[key]

    def __setitem__(self, key, value):
        self.value[key] = value


class Integer(Element): pass


class List(Element):
    def __init__(self):
        self.value = []


class String(Element):
    def __init__(self):
        self.value = ""

