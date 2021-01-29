departmentCode=$1
courseNumber=$2
dateNow=$3
courseName=$4
courseStart=$5
courseEnd=$6
enrolled=$7
departmentName=$8
output=$9
template=$10
saveTo=$output/$departmentCode$courseNumber.warn
sed '{
    s/\[\[dept_code\]\]/'$departmentCode'/g
    s/\[\[course_num\]\]/'$courseNumber'/g
    s_\[\[date\]\]_'"$dateNow"'_g
    s/\[\[course_name\]\]/'"$courseName"'/g
    s~\[\[course_start\]\]~'"$courseStart"'~g
    s,\[\[course_end\]\],'"$courseEnd"',g
    s/\[\[num_students\]\]/'$enrolled'/g
    s/\[\[dept_name\]\]/'$departmentName'/g
}' $template > $saveTo
