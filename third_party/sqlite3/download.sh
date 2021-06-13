#!/bin/bash
set -e

snapshot_name='sqlite-snapshot-202106031851'
file_name='sqlite3.tar.gz'
curl https://www.sqlite.org/snapshot/${snapshot_name}.tar.gz --output /tmp/${file_name}
tar -C /tmp/ -xvzf /tmp/${file_name}
cp /tmp/${snapshot_name}/sqlite3.h ./third_party/sqlite3/
cp /tmp/${snapshot_name}/sqlite3.c ./third_party/sqlite3/
rm -rf /tmp/${file_name}
rm -rf /tmp/${snapshot_name}


