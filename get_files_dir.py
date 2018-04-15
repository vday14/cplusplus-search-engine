import os
for root, dirs, files in os.walk("."):
    for file in files:
        if file.endswith(".cpp") :
            path = os.path.join(root, file)
            path = path[2:]
            print(path)
            #os.system("cloc " + path + " >> LOC.txt ")
            os.system("cloc " + path)
