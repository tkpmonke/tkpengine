# lua doesn't have a good standard library so
# we need to use a little bit of python :/

# this file is a mess...
# viewer discrestion is advised

import os
import os.path


module_names: 'dict[str, Module]' = dict()


class Module:

    def __init__(self, name: str):
        self.name: str = name
        self.parent: str = ""
        self.children = []
        self.depth: int = 1

    def has_parent(self):
        try:
            with open("modules/" + self.name + "/module_info", "r") as fd:
                for line in fd:
                    values: 'list[str]' = line.split('=')

                    match values[0]:
                        case "parent":
                            return True

        except FileNotFoundError:
            return False

    def parse(self):
        try:
            with open("modules/" + self.name + "/module_info", "r") as fd:
                for line in fd:
                    values: 'list[str]' = line.split('=')

                    match values[0]:
                        case "enabled":
                            if values[1] == "false\n":
                                return 1
                        case "parent":
                            self.parent = values[1][:-1]
                            module_names[self.parent].children.append(self)
                            self.depth = module_names[self.parent].depth+1
                            return 2

        except FileNotFoundError:
            # do fucking nothing because this god forsaken language
            # can't handle when a file can't be found
            return 0

    def include(self, fd):
        fd.write("#include \"" + self.name + "/register_module.h\"\n")

    def register(self, fd):
        s = ""
        for i in range(self.depth):
            s += "\t"

        if os.path.isfile("modules/" + self.name + "/register_module.h"):
            fd.write(s + "register_module_" + self.name + "();")

        if len(self.children) != 0:
            fd.write("\n" + s + "{\n")
            for i in self.children:
                i.register(fd)
            fd.write(s + "}\n")
        else:
            fd.write("\n")

    def deregister(self, fd):
        s = ""
        for i in range(self.depth):
            s += "\t"

        if os.path.isfile("modules/" + self.name + "/register_module.h"):
            fd.write(s + "deregister_module_" + self.name + "();")

        if len(self.children) != 0:
            fd.write("\n" + s + "{\n")
            for i in self.children:
                i.deregister(fd)
            fd.write(s + "}\n")
        else:
            fd.write("\n")


def list_directories():
    paths = []

    # supposed to be called walker but walter is funnier
    walter = os.scandir("./modules")
    for path in walter:
        if path.is_dir():
            paths.append(path.name)
    return paths


def generate_c_file():
    module_dirs = list_directories()
    modules: 'list[Module]' = []

    fd = open("modules/modules.c", "w")
    fd.write("/* auto generated initilzation for modules */\n\n")

    for m in module_dirs:
        if os.path.isfile("modules/" + m + "/register_module.h"):
            module: Module = Module(m)
            module_names[m] = module

            if not module.has_parent():
                modules.append(module)

    for name, m in module_names.items():
        d = m.parse()
        if (d == 1):
            continue

        m.include(fd)

    fd.write("\nvoid modules_register() {\n")
    for i in modules:
        i.register(fd)
    fd.write("}\n")

    fd.write("\nvoid modules_deregister() {\n")
    for i in modules:
        i.deregister(fd)
    fd.write("}")

    fd.close()


generate_c_file()
