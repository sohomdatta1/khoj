CC=g++

test-small: build
	/bin/bash -c "/usr/bin/time -v ./khoj '/home/sohom/linux'"

test-big: build
	/bin/bash -c "time ./khoj '/home/sohom/mediawiki'"

build: khoj.cc indexer.cc walkDir.cc logger.cc indexUtils.cc
	$(CC) khoj.cc indexer.cc walkDir.cc logger.cc indexUtils.cc -std=c++17 -o khoj -v -O2 -g
