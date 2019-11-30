#!/bin/bash

if [ "$1" == "download" ]; then
  mkdir dumps -p
  cd dumps && wget https://dumps.wikimedia.org/enwikivoyage/latest/enwikivoyage-latest-pages-articles.xml.bz2
  echo "Decompressing dump archive. Please, wait ..."
  bzip2 -d enwikivoyage-latest-pages-articles.xml.bz2
  cd ..
fi

mkdir build -p
cd build && cmake .. && make -j4
echo "Started extraction"
./main
echo "Extraction finished"
cd ..
#echo "Started conversion .nt files charset from utf-8 to ascii"
#./file_type_convert.py
#echo "Finished conversion .nt files charset from utf-8 to ascii"