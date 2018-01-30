
import os
import shutil
import sys

EXEC = "joec"

def compille():
	# JOAO PAULO MODIFICOU AQUI
	# OSEIAS MODIFICOU AQUI
	a = 2
	i = names.index("fb")
	names_fb = [x.name for x in os.scandir(names[i])]

	bison, flex = None, None
	for elem in names_fb:
		if (elem.endswith(".y")):
			bison = elem
		elif (elem.endswith(".l")):
			flex = elem
	
	if (bison is not None):
		file = path + "/fb/" + bison
		command = "bison -d " + file + " -o fb/y.tab.c"
		os.system(command)

	if (flex is not None):
		file = path + "/fb/" + flex
		command = "flex -o fb/lex.yy.c " + file
		os.system(command)

	command = "gcc -o " + EXEC + " fb/*.c src/*.c -Ifb/ -Iheader/"
	os.system(command)


def make_directories():

	if ("src" not in names):
		os.makedirs("src")

	if ("fb" not in names):
		os.makedirs("fb")

	if ("header" not in names):
		os.makedirs("header")

	print("Mova os arquivos para as pastas corretas")



ls = [x for x in os.scandir()]
names = [x.name for x in ls]
path = os.getcwd()

try:

	if (len(sys.argv) == 1):
		compille()

	elif (sys.argv[1] == "--create"):
		make_directories()





except IndexError as e:
	raise e



