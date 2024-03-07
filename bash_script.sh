#!/bin/bash

# Input parametrs
DIRECTORY="$1"

target_directory="/home/pmi-b1505"

cd ~

cd "$1"

function descendDirectories {
current_dir=$(pwd)

f_dir=$(pwd)
last_dir=$(basename "$f_dir")
echo "$last_dir"


if [ -z "$(ls -A $pwd)" ]; then
 echo "в каталоге нету папок"
else
 echo "$(find . -maxdepth 1 -type d ! -path . | sed 's|./||')"
fi

echo "..........................."

if [ "$current_dir" == "$target_directory" ]; then
 echo "Достигнута целевая аудитория: $target_directory"
else
cd ..
descendDirectories
fi
}

descendDirectories

