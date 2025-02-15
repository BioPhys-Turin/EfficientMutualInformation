.DEFAULT_GOAL := hk

WSL_G++_PATH = /home/linuxbrew/.linuxbrew/bin/
MACOS_G++_PATH = /opt/homebrew/bin/
G++_PATH = $(WSL_G++_PATH)

PATH := $(PATH):./local/bin/


hk: ./local/src/main.cpp
	$(G++_PATH)g++-14 -fopenmp -o ./local/bin/hk ./local/src/main.cpp -std=c++17 -O3 -Wall -Wextra -Wpedantic -Werror
