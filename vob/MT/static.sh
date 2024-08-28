#/bin/bash

#cat records.log |awk '{print $4}' |awk -F":" '{print $1}' |uniq |wc -l

echo "user number: `cat records.log |awk '{print $4}' |awk -F":" '{print $1}' | sort | uniq |wc -l`"
