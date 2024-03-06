directory_name="/Users/md.rakibulislam/IIT Life/All Semester in IIT Life/4th Semester/4th Semester Lab Codes/CSE-401/Directory"

for file in "$directory_name"/*.c "$directory_name"/*.cpp; 
do
    if [ -f "$file" ]; then
        filename=$(basename "$file")
        size=$(wc -c < "$file")
        lines=$(wc -l < "$file")
        echo "FileName: $filename ----> SizeOfFile: $size ----> Lines of code: $lines"
    fi
done
