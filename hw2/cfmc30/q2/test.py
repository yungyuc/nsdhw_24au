import sys
sys.path.append('./build')
import fdct
v1 = [0.0, 2.0]
v2 = [2.0, 0.0]

res = fdct.ang(v1[0], v1[1], v2[0], v2[1])

print(res)
