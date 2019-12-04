#!/bin/bash

apt update
apt install virtuoso-opensource
apt install virtuoso-vad-{isparql,ods,tutorial}
cd /usr/share/virtuoso-opensource* && virtuoso-t -fd
cp ./../../extraction_framework/build/*.nt /usr/share/virtuoso-opensource*/vad