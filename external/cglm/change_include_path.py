# by default, cglm has the include paths for all header files to be
# "../include/cglm/*"

# i hate this, so i changed it using this script :3

# this is the only modification to the original source code

import os

for (root, dirs, files) in os.walk('./src'):
    for f in files:
        print(root[2:]+"/"+f)
        with open(root[2:]+"/"+f, "r") as fp:
            new_contents = fp.read()
            new_contents = new_contents.replace("include/", "")
            new_contents = new_contents.replace("cglm/", "")
            new_contents = new_contents.replace("../", "")
        with open(root[2:]+"/"+f, "w") as fp:
            fp.write(new_contents)

