import time




set_dic = ()
list_dic = []

def set_load(dictionary):
    file = open(dictionary, "r")

    for line in file:
        word = line.rstrip()
        set_dic.add(word)

    close(file)
    return True

def list_load(dictionary):
    file = open(dictionary, "r")

    for line in file:
        word = line.rstrip()
        list_dic.append(word)

    close(file)
    return True


def set_check(word):
    if word.lower() in set_dic:
        return True
    return False

def list_check(word):
    if word in list_dic:
        return True
    return False


start1 = time.time()
set_load()
end1 = time.time()
print("set_load", end1 - start1)

start2 = time.time()
list_load()
end2 = time.time()
print("list_load", end2 - start2)


def full_check(text):
    file = open(text)






