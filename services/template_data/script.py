import os
from functools import reduce

def get_directory_structure(rootdir):
    """
    Creates a nested dictionary that represents the folder structure of rootdir
    """
    dir = {}
    rootdir = rootdir.rstrip(os.sep)
    start = rootdir.rfind(os.sep) + 1
    for path, dirs, files in os.walk(rootdir):
        folders = path[start:].split(os.sep)
        subdir = dict.fromkeys(files)
        parent = reduce(dict.get, folders[:-1], dir)
        parent[folders[-1]] = subdir
    return dir


if __name__ == "__main__":
    req = dict(get_directory_structure(os.getcwd())) # get current working directory
    req = req[list(req.keys())[0]]["CSES-Solutions"]
    for tag in req.keys():
        for problem in req[tag].keys():
            for solution in req[tag][problem].keys():
                path = "CSES-Solutions/" + tag + "/" + problem + "/" + solution
                f = open(path, "r")
                