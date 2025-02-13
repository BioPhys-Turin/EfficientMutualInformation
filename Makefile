

hk: main.cpp
	/opt/homebrew/bin/g++-14 -fopenmp -o hk main.cpp -std=c++17 -O3 -Wall -Wextra -Wpedantic -Werror

clean:
	rm -f hk *.o