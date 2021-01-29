#!/bin/bash
./p2 -l > p2LowOut.txt
./p2 -e p2One.txt -k onekey -o p2One.enc > p2OneOutDebug.txt
./p2 -d p2One.enc -k onekey -o p2One.dec > p2OneOutDecDebug.txt  
./p2 -d p2One.enc -k xyz -o p2One.bad > p2OneOutBadDebug.txt 
./p2 -e p2Two.txt -k twokey -o p2Two.enc > p2TwoOutDebug.txt
./p2 -d p2Two.enc -k twokey -o p2Two.dec > p2TwoOutDecDebug.txt

