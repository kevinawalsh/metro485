#!/bin/sh

SOURCE=${BASH_SOURCE[0]}
while [ -L "$SOURCE" ]; do # resolve $SOURCE until the file is no longer a symlink
  DIR=$( cd -P "$( dirname "$SOURCE" )" >/dev/null 2>&1 && pwd )
  SOURCE=$(readlink "$SOURCE")
  [[ $SOURCE != /* ]] && SOURCE=$DIR/$SOURCE # if $SOURCE was a relative symlink, we need to resolve it relative to the path where the symlink file was located
done
DIR=$( cd -P "$( dirname "$SOURCE" )" >/dev/null 2>&1 && pwd )

# Sets an icon on file or directory
# Usage setIcon.sh iconimage.jpg /path/to/[file|folder]
iconSource="$DIR/metro485.jpg"
iconDestination="$DIR/start-metro495-arduino.command"
icon=/tmp/`basename "$iconSource"`
rsrc=/tmp/icon.rsrc

# Check if icon is already set
if xattr -p com.apple.ResourceFork "$iconDestination" >/dev/null 2>&1; then
  exit 0
fi

# Create icon from the iconSource
cp "$iconSource" "$icon"

# Add icon to image file, meaning use itself as the icon
sips -i "$icon"

# Take that icon and put it into a rsrc file
DeRez -only icns "$icon" > "$rsrc"

# Apply the rsrc file to
SetFile -a C "$iconDestination"

if [ -f "$iconDestination" ]; then
    # Destination is a file
    Rez -append "$rsrc" -o "$iconDestination"
elif [ -d "$iconDestination" ]; then
    # Destination is a directory
    # Create the magical Icon\r file
    touch "$iconDestination"/$'Icon\r'
    Rez -append "$rsrc" -o "$iconDestination"/Icon?
    SetFile -a V "$iconDestination"/Icon?
fi

# Sometimes Finder needs to be reactivated
#osascript -e 'tell application "Finder" to quit'
#osascript -e 'delay 2'
#osascript -e 'tell application "Finder" to activate'

rm "$rsrc" "$icon"
