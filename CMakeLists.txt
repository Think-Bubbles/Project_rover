cmake_minimum_required(VERSION 3.27)
project(Project_rover C)

set(CMAKE_C_STANDARD 11)

add_executable(Project_rover main.c
        loc.c
        loc.h
        moves.c
        moves.h
        map.c
        map.h
        queue.c
        queue.h
        stack.c
        stack.h
        CardPicker.c
        CardPicker.h
        tree.h
        tree.c
        paths.c
        paths.h
        times.c
        times.h
)

