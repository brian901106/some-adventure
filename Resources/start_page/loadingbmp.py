dir = "resources/start_page/light/"
ext = ".bmp"
start = 1
end = 60
result = ""

#front_include = "{"
#rear_include = "}"


for i in range(start,end):
      result = result + '"' +dir + str(i) + ext + '"' + ","

result = result[:-1]
result = "{" + result + "}"
print(result)

