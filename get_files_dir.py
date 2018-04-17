import os
for root, dirs, files in os.walk("./bootstrap_landing_page"):
    for file in files:
        if file.endswith(".h") :
            path = os.path.join(root, file)
            path = path[2:]
            print(path)
            #os.system("cloc " + path + " >> LOC.txt ")
            os.system("cloc " + path)
