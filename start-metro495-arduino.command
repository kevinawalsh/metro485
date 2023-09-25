#!/bin/bash

SOURCE=${BASH_SOURCE[0]}
while [ -L "$SOURCE" ]; do # resolve $SOURCE until the file is no longer a symlink
  DIR=$( cd -P "$( dirname "$SOURCE" )" >/dev/null 2>&1 && pwd )
  SOURCE=$(readlink "$SOURCE")
  [[ $SOURCE != /* ]] && SOURCE=$DIR/$SOURCE # if $SOURCE was a relative symlink, we need to resolve it relative to the path where the symlink file was located
done
DIR=$( cd -P "$( dirname "$SOURCE" )" >/dev/null 2>&1 && pwd )

echo; echo "==== Changing to directory $DIR ===="
cd $DIR
./set_icon.sh
cd $DIR/daemon
echo; echo "==== Compiling daemon ===="
make
echo; echo "==== Opening patch ===="
open ../metro485.maxpat
echo; echo "==== Opening arduino serial port ===="
./metro485

echo; echo "==== SOMETHING WENT WRONG ===="
echo "Maybe close this window (and click 'Terminate') then run the program again?"
echo "Or hit enter to try again..."
while read line; do
  echo; echo "==== Opening arduino serial port ===="
  ./metro485
  echo; echo "==== SOMETHING WENT WRONG ===="
  echo "Maybe close this window (and click 'Terminate') then run the program again?"
  echo "Or hit enter to try again..."
done
