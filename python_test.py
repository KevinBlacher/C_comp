from subprocess import *

p = Popen("New_Comp.exe", shell=True, stdin=PIPE, stdout=PIPE)

p.stdin.write("1\n6\n4\n1\n")
output = p.stdout.read()
p.stdin.write("2\n5\n")
print("%s", output)