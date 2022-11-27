import sys
import math

if len(sys.argv) != 2:
    sys.exit("Incorrect usage: python3 <ProgName> <inputfile>")

data = []

#read in file contents
with open (str(sys.argv[1])) as textFile:
    for line in textFile:
        row = [float(item.strip()) for item in line.split()]
        data.append(row)

#not sure about this but check size of array
if len(data) == 0:
    sys.exit("Invalid input")

for i in range(len(data)):
    if len(data[i]) != 9:
        sys.exit("Invalid input")
        

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
#if it gets past this point, input is valid
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 

outF = open("PlanePointDistance.txt", "w")

# distance between point and plane
for i in range(len(data)):
    plane = [data[i][3], data[i][4], data[i][5]]
    normalization = math.sqrt(plane[0] ** 2 + plane[1] ** 2 + plane[2] ** 2)
    plane = [plane[j] / normalization for j in range(len(plane))]
    point = [data[i][6], data[i][7], data[i][8]]

    distance = 0
    for j in range(len(plane)):
        distance += plane[j] * point[j]

    outF.write(str(distance) + "\n")

outF.close() 

# does triangle intersect with line
linePoint1 = [data[0][0],data[0][1],data[0][2]]
linePoint2 = [data[0][3], data[0][4], data[0][5]]
direction = [data[0][6], data[0][7], data[0][8]]
for i in range(1,len(data)):
    trianglePoint1 = [data[i][0],data[i][1],data[i][2]]
    trianglePoint2 = [data[i][3],data[i][4],data[i][5]]
    trianglePoint3 = [data[i][6],data[i][7],data[i][8]]