#!/bin/bash

VERSION_HEADER=Version.h
GITHASH=$(git describe --dirty --always --tags 2>/dev/null)
if [ $? -ne 0 ] ; then
    CHECKSUM=$(cat *.cpp *.h Makefile version.sh | md5sum)
    VSTR="Checksum : ${CHECKSUM:0:6}"
else
    VSTR="GitRev : $GITHASH"
fi

echo "#ifndef VERSION_H_" > $VERSION_HEADER
echo "#define VERSION_H_" >> $VERSION_HEADER
echo >> $VERSION_HEADER
echo "#define VERSION_STR \"$VSTR\"" >> $VERSION_HEADER
echo >> $VERSION_HEADER
echo "#endif // VERSION_H_" >> $VERSION_HEADER

