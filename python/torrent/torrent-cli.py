#!/usr/bin/env python

import sys

sys.path.insert(0, '/usr/share/torrent')

try:
    import torrent
    torrent.main(sys.argv[1:])
except KeyboardInterrupt, e:
    print >> sys.stderr, "\n\nExiting on user cancel."
    sys.exit(1)

 
