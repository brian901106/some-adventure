dir = "resources/fail_page/"
ext = ".bmp"
start = 140
end = 169
result = ""

#front_include = "{"
#rear_include = "}"


for i in range(start,end):
      result = result + '"' +dir + str(i) + ext + '"' + ","

result = result[:-1]
result = "{" + result + "}"
print(result)

