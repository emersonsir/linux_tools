#!/bin/bash

SOURCE="${BASH_SOURCE[0]}"
while [ -h "$SOURCE" ] ; do SOURCE="$(readlink "$SOURCE")"; done
DIR="$( cd -P "$( dirname "$SOURCE" )" && pwd )"

#java -jar ${DIR}/../../build/libs/jgrep-1.0.jar -g "(drive)r(type)" ${DIR}/preferreddrivers.xml
#java -jar ${DIR}/../../build/libs/jgrep-1.0.jar "(drive)r(type)" ${DIR}/preferreddrivers.xml
java -jar ${DIR}/../../build/libs/jgrep-1.0.jar -g "kkk" ${DIR}/sns_texture.png
