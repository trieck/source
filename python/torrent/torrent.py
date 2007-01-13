
import sys
import lex
import element

def load_torrent(filename):
    try:
        fp = open(filename, "rb")
        lexer = lex.Lex(fp)
        torrent = lexer.getelement()
        fp.close()
        display(torrent)
    except (StandardError, IOError), e:
        print >> sys.stderr, e
        sys.exit(1)

def display(torrent): 
    if (not isinstance(torrent, element.Dictionary)):
        raise StandardError("bad torrent file.")

    print ("announce:\t%s" % torrent["announce"].value)
    print ("creation date:\t%d" % torrent["creation date"].value)
    print ("created by:\t%s" % torrent["created by"].value)

    # enum_trackers(torrent)
    display_info(torrent["info"])

def display_info(info):
    print "info:"
    print ("\t\tname:\t\t%s" % info["name"].value)
    # print ("\t\tlength:\t\t%d bytes" % info["length"].value)

    display_files(info["files"].value)

def display_files(files):
    print "\t\tfiles..."

def main(args):
    for i in args:
        load_torrent(i)
    sys.exit(0)


