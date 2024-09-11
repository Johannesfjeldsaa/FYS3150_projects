#! /bin/sh


cd build 


if [ ! -d ../output ]; then
  mkdir ../output
fi

file="../output/problem2data.out"

if [ -f "$file" ]; then
    echo "The file $file already exists. Overwrite? (y/n) \c"
    read reply
    case $reply in
        [Yy])
            echo "Overwriting file"
            ./problem2 > "$file"
            ;;
        *)
            echo "Skipping. Exiting."
            exit 0
            ;;
    esac
else
    echo "File does not exist. Creating a new file."
    ./problem2 > "$file"
fi