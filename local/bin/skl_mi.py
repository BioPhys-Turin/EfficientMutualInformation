#!/usr/bin/env python3

import numpy as np
import sys
from sklearn.metrics import mutual_info_score
import time

data = np.loadtxt(sys.stdin, delimiter=",")
# data = data.T

num_genes = data.shape[0]
mi_matrix = np.zeros((num_genes, num_genes))

# Compute M.I.
count = 0
start = time.time()
for i in range(num_genes):
	for j in range(i, num_genes):
		mi = mutual_info_score(data[i], data[j])
		print(f"Iteration {count}: vec1: {data[i]}, vec2: {data[j]}, mi = {mi}", file=sys.stderr)
		mi_matrix[i, j] = mi_matrix[j, i] = mi
		count += 1
elapsed_time = time.time() - start

print(f"Elapsed time: {elapsed_time:.20f} seconds, number of genes: {num_genes}", file=sys.stderr)

# stdout
print(mi_matrix)