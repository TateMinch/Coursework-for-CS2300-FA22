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

if len(data) == 0:
    sys.exit("Invalid input")

for i in range(len(data)):
    if len(data[i]) != 9:
        sys.exit("Invalid input: must be 9 elements in each row")

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
# parallel projection (part 1)
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 

#First line is plane and direction
q = [data[0][0], data[0][1], data[0][2]]
n = [data[0][3], data[0][4], data[0][5]]
v = [data[0][6], data[0][7], data[0][8]]

outF = open("tminch_output_1_A.txt", "w")
#for every line after the first, parallel project three points
for i in range(1, len(data)):
    x = [data[i][0],data[i][1],data[i][2]]
    temp = [q[i] - x[i] for i in range(3)]
    dotProduct1 = 0
    for j in range(len(temp)):
        dotProduct1 += temp[j] * n[j]
    dotProduct2 = 0
    for j in range(len(v)):
        dotProduct2 += v[j] * n[j]

    v = [dotProduct1 / dotProduct2 * v[i] for i in range(len(v))]
    xPrime = [round(x[i] + v[i],2) for i in range(len(v))]
    for item in xPrime:
        outF.write(str(item)[:4] + " ")

    #Do it again for second point on line
    x = [data[i][3],data[i][4],data[i][5]]
    temp = [q[i] - x[i] for i in range(3)]
    dotProduct1 = 0
    for j in range(len(temp)):
        dotProduct1 += temp[j] * n[j]
    dotProduct2 = 0
    for j in range(len(v)):
        dotProduct2 += v[j] * n[j]

    v = [dotProduct1 / dotProduct2 * v[i] for i in range(len(v))]
    xPrime = [round(x[i] + v[i],2) for i in range(len(v))]
    for item in xPrime:
        outF.write(str(item)[:4] + " ")

    #Do it again for third point on the line
    x = [data[i][6],data[i][7],data[i][8]]
    temp = [q[i] - x[i] for i in range(3)]
    dotProduct1 = 0
    for j in range(len(temp)):
        dotProduct1 += temp[j] * n[j]
    dotProduct2 = 0
    for j in range(len(v)):
        dotProduct2 += v[j] * n[j]

    v = [dotProduct1 / dotProduct2 * v[i] for i in range(len(v))]
    xPrime = [round(x[i] + v[i],2) for i in range(len(v))]
    for item in xPrime:
        outF.write(str(item)[:4] + " ")

    outF.write("\n")

outF = open("tminch_output_1_B.txt", "w")
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
# perspective projection (part 2)
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
for i in range(len(data)):
    x = [data[i][0],data[i][1],data[i][2]]
    v = [-x[i] for i in range(len(x))]
    temp = [q[i] - x[i] for i in range(3)]
    dotProduct1 = 0
    for j in range(len(temp)):
        dotProduct1 += temp[j] * n[j]
    dotProduct2 = 0
    for j in range(len(v)):
        dotProduct2 += v[j] * n[j]

    v = [dotProduct1 / dotProduct2 * v[i] for i in range(len(v))]
    xPrime = [round(x[i] + v[i],2) for i in range(len(v))]
    for item in xPrime:
        outF.write(str(item)[:4] + " ")

    #Do it again for second point on line
    x = [data[i][3],data[i][4],data[i][5]]
    temp = [q[i] - x[i] for i in range(3)]
    dotProduct1 = 0
    for j in range(len(temp)):
        dotProduct1 += temp[j] * n[j]
    dotProduct2 = 0
    for j in range(len(v)):
        dotProduct2 += v[j] * n[j]

    v = [dotProduct1 / dotProduct2 * v[i] for i in range(len(v))]
    xPrime = [round(x[i] + v[i],2) for i in range(len(v))]
    for item in xPrime:
        outF.write(str(item)[:4] + " ")

    #Do it again for third point on the line
    x = [data[i][6],data[i][7],data[i][8]]
    temp = [q[i] - x[i] for i in range(3)]
    dotProduct1 = 0
    for j in range(len(temp)):
        dotProduct1 += temp[j] * n[j]
    dotProduct2 = 0
    for j in range(len(v)):
        dotProduct2 += v[j] * n[j]

    v = [dotProduct1 / dotProduct2 * v[i] for i in range(len(v))]
    xPrime = [round(x[i] + v[i],2) for i in range(len(v))]
    for item in xPrime:
        outF.write(str(item)[:4] + " ")

    outF.write("\n")

outF.close()

