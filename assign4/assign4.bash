#! /bin/bash
template=$2
date=$3
output=$4
for file in $1/*; do
    for ((i=1;;i++)); do
        read "line$i" || break;
    done < $file

    courseNumber=$(echo $file | grep -Eo "[[:digit:]]{4}")
    
    read departmentCode departmentName <<< $line1
    read courseName <<< $line2
    read courseDays courseStart courseEnd <<< $line3
    read creditHours <<< $line4
    read enrolled <<< $line5

    if [ $enrolled -gt 50 ];
    then
        sh assign4.sed "$departmentCode" "$courseNumber" "$date" "$courseName" "$courseStart" "$courseEnd" "$enrolled" "$departmentName" "$output" "$template"
    fi
done
