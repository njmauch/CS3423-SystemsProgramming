#!/usr/bin/env python3

import sys
import re
import glob
import os

if(len(sys.argv)) != 5:
    print("Usage: " + sys.argv[0] + "<data directory> <template file> <date> <output directory>")
    sys.exit(1)

delimiter = "\n"
pattern = r"[A-Z]{2,3}([0-9]{4}).crs"
line_number = 1

for path in glob.glob(os.path.join(sys.argv[1], '*.crs')):
    matches = re.search(pattern, path)
    courseNum = matches.group(1)
    try:
        with open(path, 'r') as f:
            all_lines = f.read().rstrip()
            tokens = re.split(delimiter, all_lines)
            tokens1 = tokens[0].split(" ")
            dept_code = tokens1[0]
            dept_name = tokens1[1]
            course_name = tokens[1]
            tokens2 = tokens[2].split(" ")
            course_sched = tokens2[0]
            course_start = tokens2[1]
            course_end = tokens2[2]
            credit_hours = tokens[3]
            num_students = int(tokens[4])
            if num_students > 50:
              if not os.path.exists(sys.argv[4]):
                os.mkdir(sys.argv[4])
              str1 = ".warn"
              outputName = dept_code + courseNum + str1
              warnFile = os.path.join(sys.argv[4], outputName)
              with open(sys.argv[2], 'r') as infile:
                with open(warnFile, 'w') as outfile:
                  all_text = infile.read().rstrip()
                  subbed = re.sub(r"\[\[dept_code\]\]", dept_code, all_text,)
                  subbed = re.sub(r"\[\[course_num\]\]", courseNum, subbed,)
                  subbed = re.sub(r"\[\[date\]\]", sys.argv[3], subbed,)
                  subbed = re.sub(r"\[\[course_name\]\]", course_name, subbed,)
                  subbed = re.sub(r"\[\[course_start\]\]", course_start, subbed,)
                  subbed = re.sub(r"\[\[course_end\]\]", course_end, subbed,)
                  subbed = re.sub(r"\[\[num_students\]\]", str(num_students), subbed,)
                  subbed = re.sub(r"\[\[dept_name\]\]", dept_name, subbed,)
                  outfile.write(subbed)                    
    except IOError:
        print("Error opening one of the files.")
        sys.exit(1)
        
