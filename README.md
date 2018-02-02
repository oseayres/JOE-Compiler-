# JOE-Compiler

JOE-Compiler é um compilador de uma linguagem de programação estruturada simplificada, utilizando *flex* e *bison*. O compilador produz código em assembly para processadores intel da família x86_64.

### Como usar

Para gerar o executável do compilador a apartir do código fonte:
```sh
$ python3 make.py
```

Para executar o compilador:
```sh
$ ./joec arquivo_entrada.txt [-o arquivo_saida.asm]
```

Para compilar, montar e executar o arquivo .asm:
```sh
$ python3 make.py arquivo.asm
```

Para executar os 3 comandos anteriores de uma vez só:
```sh
$ python3 make.py --all arquivo_entrada.txt
```

