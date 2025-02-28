import numpy as np
import time

for i in range(1, 11):
    num = str(i)
    if i < 10: num = '0' + num
    finp = "DSA/TEST" + num + "/DSA.inp"
    with open(finp, 'r') as f:
        a = f.read().split()
        a = list(map(int, a[1:]))
        a = np.array(a)
        t = time.perf_counter()
        a = np.sort(a)
        tn = time.perf_counter()
        for i in range(1, len(a)):
            if a[i] < a[i - 1]:
                print("Wrong in test ", i)
                exit(0)
        print(int((tn - t) * 1000))