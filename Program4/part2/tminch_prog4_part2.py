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
#if it gets past this point, input is valid, do part 1
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 

outF = open("tminch_output_2_A.txt", "w")

# distance between point and plane
for i in range(len(data)):
    q = [data[i][0],data[i][1],data[i][2]]
    n = [data[i][3], data[i][4], data[i][5]]
    point = [data[i][6],data[i][7],data[i][8]]
    dot1 = 0
    dot2 = 0
    dot3 = 0
    for j in range(len(n)):
        dot1 += -n[j] * q[j]
        dot2 += n[j] * point[j]
        dot3 += n[j] * n[j]

    t = (dot1 + dot2) / dot3

    distance = t * math.sqrt(n[0] ** 2 + n[1] ** 2 + n[2] ** 2)

    outF.write(str(distance) + "\n")

outF.close() 

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
# (part 2) does triangle intersect with line
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 

def zeros_matrix(rows, cols):
    A = []
    for i in range(rows):
        A.append([])
        for j in range(cols):
            A[-1].append(0.0)

    return A


def copy_matrix(M):
    rows = len(M)
    cols = len(M[0])

    MC = zeros_matrix(rows, cols)

    for i in range(rows):
        for j in range(cols):
            MC[i][j] = M[i][j]

    return MC

outF = open("tminch_output_2_B.txt", "w")
intersect = False
linePoint1 = [data[0][0],data[0][1],data[0][2]]
linePoint2 = [data[0][3], data[0][4], data[0][5]]
v = [linePoint2[i] - linePoint1[i] for i in range(len(linePoint1))]
for i in range(1,len(data)):
    x = [data[i][0],data[i][1],data[i][2]]
    y = [data[i][3],data[i][4],data[i][5]]
    z = [data[i][6],data[i][7],data[i][8]]

    w = [y[j] - x[j] for i in range(len(x))]
    r = [z[j] - z[j] for i in range(len(x))]

    wrnegv = []

    for j in range(3):
        tempList = [w[j], r[j], -v[j]]
        wrnegv.append(tempList)

    B = []
    for j in range(3):
        B.append([linePoint1[j] - x[j]])

    AM = copy_matrix(data)
    n = len(data)
    BM = copy_matrix(B)
    
    indices = list(range(n)) # allow flexible row referencing ***
    for fd in range(n): # fd stands for focus diagonal
        fdScaler = 1.0 / AM[fd][fd]
        # FIRST: scale fd row with fd inverse. 
        for j in range(n): # Use j to indicate column looping.
            AM[fd][j] *= fdScaler
        BM[fd][0] *= fdScaler
        
        # SECOND: operate on all rows except fd row.
        for i in indices[0:fd] + indices[fd+1:]: # skip fd row.
            crScaler = AM[i][fd] # cr stands for current row
            for j in range(n): # cr - crScaler * fdRow.
                AM[i][j] = AM[i][j] - crScaler * AM[fd][j]
            BM[i][0] = BM[i][0] - crScaler * BM[fd][0]

    for i in range(len(BM)):
        for j in range(len(BM[i])):
            BM[i][j] = round(BM[i][j])

    if BM[0][0] < 1 and BM[0][0] > 0:
        if BM[1][0] < 1 and BM[1][0] > 0:
            if BM[0][0] + BM[1][0] < 1:
                intersect = True


    if intersect:
        pointOfIntersection = [linePoint1[j] + BM[2][0] * v[j] for j in range(3)]
        # print(pointOfIntersection)
        for j in range(len(pointOfIntersection)):
            outF.write(str(pointOfIntersection[j][0]) + " ")
    else:
        outF.write("Does Not Intersect")
    
    outF.write("\n")

outF.close()


    