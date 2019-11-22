#!/bin/bash

if [ "$1" == "download" ]; then
  mkdir dumps -p
  cd dumps && wget https://dumps.wikimedia.org/enwikivoyage/latest/enwikivoyage-latest-pages-articles.xml.bz2
  bzip2 -d enwikivoyage-latest-pages-articles.xml.bz2
  cd ..
fi

mkdir build -p
cd build && cmake .. && make -j4
./main