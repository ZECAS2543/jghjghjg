cmake_minimum_required(VERSION 4.1)
project(lp_8200352 C)

set(CMAKE_C_STANDARD 90)

add_executable(lp_8200352 main.c
        ativo.c
        ativo.h
        departamentos.c
        departamentos.h
        tecnicos.c
        tecnicos.h
        manutencao.c
        manutencao.h
        comum.h
        relatorios.c
        relatorios.h
        comum.c)
