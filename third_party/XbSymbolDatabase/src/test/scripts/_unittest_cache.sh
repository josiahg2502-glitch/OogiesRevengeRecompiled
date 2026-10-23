#!/usr/bin/env bash

# source: https://stackoverflow.com/a/246128
SOURCE=${BASH_SOURCE[0]}
while [ -L "$SOURCE" ]; do # resolve $SOURCE until the file is no longer a symlink
  DIR=$( cd -P "$( dirname "$SOURCE" )" >/dev/null 2>&1 && pwd )
  SOURCE=$(readlink "$SOURCE")
  [[ $SOURCE != /* ]] && SOURCE=$DIR/$SOURCE # if $SOURCE was a relative symlink, we need to resolve it relative to the path where the symlink file was located
done
SCRIPT_DIR=$( cd -P "$( dirname "$SOURCE" )" >/dev/null 2>&1 && pwd )

#------------------

cache_fn () {
 #TODO: Find a way to open in new terminal window if possible "natively" as possible.
 #      Use & at the end to allow program run in background.
 "${SCRIPT_DIR}/XbSymbolDatabaseUnitTest" "$1" -out "${SCRIPT_DIR}/cache"
}

for x in "$@"; do
  # Check if input is a file
  if [ -f "$x" ]; then
   echo "file found: $x"
   cache_fn "$x"
  # Check if input is a directory
  elif [ -d "$x" ]; then
   #for f in $(find . -name '*.xbe' -or -name '*.bin'); do
   for f in $(find "$x" -name '*.xbe'); do
    echo "file found: $f"
    cache_fn "$f"
   done
  # otherwise, output invalid input
  else
   echo "$x is not found!"
  fi
done
