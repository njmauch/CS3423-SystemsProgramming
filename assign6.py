import sys
import os
import subprocess
import shutil

isRecursive = False
rmTrash = "./rm_trash"

if not os.path.exists(rmTrash):
    os.makedirs(rmTrash)

for var in sys.argv[1:]:
    if var == "-r":
        isRecursive = True

if isRecursive:
    for var in sys.argv[1:]:
        if var == "-r":
            continue
        elif os.path.isdir(var):
            dirName = os.path.basename(var)
            path = os.path.dirname(var)
            checkPath = os.path.join(rmTrash, dirName)
            while os.path.exists(checkPath):
                i=1
                dirName += "-" + str(i)
                checkPath = os.path.join(rmTrash, dirName)
                i += 1
                shutil.move(os.path.join(path, os.path.basename(var)), os.path.join(path,dirName))
            shutil.move(os.path.join(path, dirName), rmTrash)
        elif not os.path.isdir(var):
            sys.stderr.write(sys.argv[0] + ": cannot remove " + var + ": Is a directory\n")
        elif os.path.isfile(var):
            fileName = os.path.basename(var)
            path = os.path.dirname(var)
            checkFile = os.path.join(rmTrash, fileName)
            while os.path.exists(checkFile):
                split = fileName.split(".")
                newFileName = "".join(split[:-1])+ "-" + str(i) + "." + parts[-1]
                i = 1
                fileName += "-" + str(i)
                checkFile = os.path.join(rmTrash, fileName)
                i += 1
            shutil.move(os.path.join(path, fileName, rmTrash))
        else:
            sys.stderr.write(sys.argv[0] + ": cannot remove " + var + ": No such file or directory\n")
else:
    for var in sys.argv[1:]:
        if os.path.isdir(var):
            sys.stderr.write(sys.argv[0] + ": cannot remove " + var + ": Is a directory\n")
        if not os.path.isfile(var):
            sys.stderr.write(sys.argv[0] + ": cannot remove " + var + ": No such file or directory\n")
        else:
            fileName = os.path.basename(var)
            path = os.path.dirname(var)
            checkFile = os.path.join(rmTrash, fileName)
            while os.path.exists(checkFile):
                split = fileName.split(".") 
                i = 1
                fileName = "".join(split[:-1])+ "-" + str(i) + "." + split[-1]
                checkFile = os.path.join(rmTrash, fileName)
                i += 1
                shutil.move(os.path.join(path, os.path.basename(var)), os.path.join(path, fileName))
            shutil.move(os.path.join(path, fileName), rmTrash)
