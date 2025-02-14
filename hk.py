import numpy as np

rng = np.random.default_rng(3421)
data = np.random.randint(0, 100, (50, 10000000))

np.savetxt('data.csv', data, fmt='%d', delimiter=",")
# data = np.loadtxt('data.csv', delimiter=",")


from sklearn.metrics import mutual_info_score
import time
start = time.time()
H=mutual_info_score(data[0], data[1])
print(f"Elapsed time: {time.time() - start:.6f} seconds H={mutual_info_score(data[0], data[1])} cells={data.shape[1]}")