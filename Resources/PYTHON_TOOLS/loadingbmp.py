dir = "resources/goal_page/3095/"
ext = ".bmp"
start = 52
end = 94
result = ""

#front_include = "{"
#rear_include = "}"


for i in range(start,end):
      result = result + '"' +dir + str(i) + ext + '"' + ","

result = result[:-1]
result = "{" + result + "}"
print(result)
