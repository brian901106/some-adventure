dir = "resources/claw/1/rotate/-5/"
ext = ".bmp"
start = 3
end = 43
result = ""

#front_include = "{"
#rear_include = "}"


for i in range(start,end):
      result = result + '"' +dir + str(i) + ext + '"' + ","

result = result[:-1]
result = "{" + result + "}"
print(result)

