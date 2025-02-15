#!/usr/bin/env python3

import numpy as np
import pandas as pd
import sys

num_rows = sys.argv[1]
num_cols = sys.argv[2]
min_val = sys.argv[3]
max_val = sys.argv[4]

# generate random matrix, but with two rows that are the same
np.random.seed(0)
matrix = np.random.randint(int(min_val), int(max_val), (int(num_rows), int(num_cols)))
matrix[1] = matrix[0]

# print the matrix to stdout
print(pd.DataFrame(matrix).to_csv(index=False, header=False, sep=','))

