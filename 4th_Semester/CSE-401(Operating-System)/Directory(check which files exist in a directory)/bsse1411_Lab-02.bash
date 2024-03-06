read -p "Enter the directory path: " directory_name

if [ ! -d "$directory_name" ]; then
    echo "Error: Directory '$directory_name' not found."
    exit 1
fi

for file in "$directory_name"/*.{c,cpp}; 
do
    if [ -f "$file" ]; then
        filename=$(basename "$file")
        size=$(wc -c < "$file")
        lines=$(wc -l < "$file")
        echo "FileName: $filename ----> SizeOfFile: $size ----> Lines of code: $lines"
    fi
done
