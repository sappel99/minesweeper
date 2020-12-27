cmake_minimum_required(VERSION 3.17)
project(130_minesweeper C)

set(CMAKE_C_STANDARD 11)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Wno-unused-parameter")

add_executable(130_minesweeper
        minesweeper.c minesweeper.h prints.c prints.h generatePlayfield.c generatePlayfield.h revealFields.c revealFields.h checkingFunctions.c checkingFunctions.h playerInfo.c playerInfo.h)
