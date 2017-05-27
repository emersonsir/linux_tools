cap_src="caps.source"
sed -n 's/^#define \(CAP_.*\) .*/\1/p' /usr/include/linux/capability.h | tr A-Z a-z | grep -v cap_to_ > caps.block
rm -f $cap_src
while read line
do
    echo "    \"$line\"," >> $cap_src
done < caps.block

g++ dump_caps.cpp -lcap
