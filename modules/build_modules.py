# lua doesn't have a good standard library so
# we need to use a little bit of python :/

import os

def list_directories():
    paths = []

    # supposed to be called walker but walter is funnier
    walter = os.scandir("./modules")
    for path in walter:
        if path.is_dir():
            paths.append(path.name)
    return paths

def generate_c_file():
    modules = list_directories()

    fd = open("modules/modules.c", "w")

    for m in modules:
        fd.write("#include \"" + m + "/register_module.h\"\n")

    fd.close()

generate_c_file()
