
import os
import shutil
import sys


EXEC = "joec"
JOE_EXTENSION = ".joe"
ASM_BIN = "asm_bin/"

def compille():

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
		print("[1: bison]")
		command = "bison -d " + file + " -o fb/y.tab.c"
		os.system(command)

	if (flex is not None):
		file = path + "/fb/" + flex
		print("[2: flex]")
		command = "flex -o fb/lex.yy.c " + file
		os.system(command)

	print("[3: gcc]")
	command = "gcc -g -o " + EXEC + " fb/*.c src/*.c -Ifb/ -Iheader/"
	os.system(command)


def make_directories():

	if ("src" not in names):
		os.makedirs("src")

	if ("fb" not in names):
		os.makedirs("fb")

	if ("header" not in names):
		os.makedirs("header")

	print("Mova os arquivos para as pastas corretas")


def compille_assembly(file_name):

	idx = file_name.find(".asm")
	if (idx != -1):

		base = file_name[:idx]

		print("[1: nasm]")
		command = "nasm -f elf64 " + file_name
		os.system(command)

		print("[2: gcc]")
		command = "gcc -g " + base + ".o" + " -o " + ASM_BIN + base
		os.system(command)

		command = base + ".o"
		os.remove(command)

		print("[3: run]")
		command = ASM_BIN + base
		os.system(command)

	else:
		print("Erro: extensão do arquivo faltando")


def run_joe(input_file):

	command = "./joec " + input_file
	os.system(command)



ls = [x for x in os.scandir()]
names = [x.name for x in ls]
path = os.getcwd()

try:

	if (len(sys.argv) == 1):
		compille()

	elif (sys.argv[1] == "--create"):
		make_directories()

	elif (sys.argv[1].endswith(".asm")):
		compille_assembly(sys.argv[1])

	elif (sys.argv[1] == "--all"):
		idx = sys.argv[2].find(JOE_EXTENSION)
		if (idx == -1):
			print("Extensao de entrada para o Joe incorreta")
			exit(0)

		base = sys.argv[2][:idx]

		compille()
		run_joe(sys.argv[2])
		compille_assembly(base + ".asm")




except IndexError as e:
	print("Erro: verifique os modos de uso")
