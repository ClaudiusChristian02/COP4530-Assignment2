all: proj2

proj2: test_list.cpp List.cpp
	g++ test_list.cpp -o proj2.exe -std=c++11

clean:
	rm -f proj2.exe
