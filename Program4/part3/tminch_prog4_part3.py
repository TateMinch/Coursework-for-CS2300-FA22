import sys
import numpy as np
import math
import random

if len(sys.argv) != 2:
    sys.exit("Incorrect usage: python3 <ProgName> <inputfile>")

data = []
# read in file
with open (str(sys.argv[1])) as textFile:
    for line in textFile:
        row = [float(item.strip()) for item in line.split()]
        data.append(row)

#if matrix is not square throw error
for i in range(len(data)):
    if len(data[i]) != len(data):
        sys.exit("Invalid input: Non square matrix")

#Iterate through matrix to determine if there are negative values
# or if the matrix is not Right Stochastic
for i in range(len(data)):
    summation = 0
    for j in range(len(data[i])):
        if data[i][j] < 0:
            sys.exit("Invalid Input: Contains negative values")
        summation+= data[j][i]
    if abs(1 - summation) > 0.001:
        sys.exit("Invalid Input: Not Stochastic")

#if it gets past this point, input is valid
#calculate/output eigenvector for webpages and the vector whos elements
#are the webpages indices after sorting from the highest rank to the lowest
guess = []
for i in range(len(data)):
    addin = [random.uniform(0,1)]
    guess.append(addin)

for i in range(10):
    guess = np.matmul(np.array(data), np.array(guess))
    guess = np.multiply(np.array(guess), 1/np.amax(np.array(guess)))

unsortedRank = []
sortedRank = []
rankIndices = []
for i in range(len(guess)):
    for j in range(len(guess[i])):
        sortedRank.append(guess[i][j])
        unsortedRank.append(guess[i][j])

sortedRank.sort(reverse=True)

for i in range(len(sortedRank)):
    for j in range(len(sortedRank)):
        if sortedRank[i] == unsortedRank[j] and j + 1 not in rankIndices:
            rankIndices.append(j + 1)
            break

print([float(f'{item:.2f}') for item in unsortedRank])
print(rankIndices)
        