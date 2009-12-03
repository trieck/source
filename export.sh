#!/bin/bash

TMPDIR=tmp
ARCHIVE=source.tar.gz

if [ -x ${TMPDIR} ]; then
	rm -rf ${TMPDIR} 
fi

if [ -x ${ARCHIVE} ]; then
	rm -f ${ARCHIVE}
fi

svn export . ${TMPDIR}			&&	\
	cd ${TMPDIR}				&&	\
	tar cvzf ../${ARCHIVE} .	&&	\
	cd ..						&&	
	rm -rf ${TMPDIR}

