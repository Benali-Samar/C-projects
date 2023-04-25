#!/bin/bash
file="acount.txt"
value=$(cat $file)
echo "Read current balance:$value"

#sleep 10 seconds to simulate business calculation
progress=10
while [[ $progress -lt 101 ]]; do
	echo -n -e "\033[77DCalculating new balance..$progress%"
	sleep 1
	progress=$((10+progress))
done
echo ""

value=$((value+$1))
echo "Write new balance ($value) back to $file." 
echo $value > "$file"
echo "Done."
