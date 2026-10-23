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

if [[ -n "$1" ]]; then
 "${SCRIPT_DIR}/XbSymbolDatabaseUnitTest" "$1" --verbose
else
 "${SCRIPT_DIR}/XbSymbolDatabaseUnitTest" --verbose
fi
