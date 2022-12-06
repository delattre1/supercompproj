import random
n = input()
size = 2
for i in range(0, int(n), 1): 
    f = open("in-{}.txt".format(i), "w")
    f.write(str(size) + "\n")
    for j in range(size):
        f.write("{} {}\n".format(random.random()*100, random.random()*100))
    size += 1
