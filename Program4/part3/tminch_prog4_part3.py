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

#fill guess array with random values between 1 and 0
guess = []
for i in range(len(data)):
    addin = [random.uniform(0,1)]
    guess.append(addin)

# get max from guess
oldMax = np.amax(np.array(guess))
for i in range(1000000):
    #matrix multiplication on guess and data
    guess = [[sum(a*b for a,b in zip(X_row,Y_col)) for Y_col in zip(*np.array(guess))] for X_row in np.array(data)]
    #normalize by max value
    max = np.amax(np.array(guess))
    for j in range(len(guess)):
        guess[j][0] = guess[j][0] / max
    #if eigenvalues have converged enough
    if abs(max - oldMax) < 0.0001:
        break
    else:
        oldMax = max

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
        