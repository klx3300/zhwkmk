__fake_main__: main

parse_str.o: ./parse_str/strparse.cpp ./parse_str/strparse.h
	@echo "   g++   parse_str.o"
	@g++ -std=c++11 -c -g -o parse_str.o ./parse_str/strparse.cpp
gendest.o: ./gendest/gendest.cpp ./gendest/gendest.h
	@echo "   g++   gendest.o"
	@g++ -std=c++11 -c -g -o gendest.o ./gendest/gendest.cpp
macro_replace.o: ./macro_replace/macro_replace.cpp ./macro_replace/macro_replace.h
	@echo "   g++   macro_replace.o"
	@g++ -std=c++11 -c -g -o macro_replace.o ./macro_replace/macro_replace.cpp
stroper.o: ./stroper/stroper.cpp ./stroper/stroper.h
	@echo "   g++   stroper.o"
	@g++ -std=c++11 -c -g -o stroper.o ./stroper/stroper.cpp
main.o: ./main.cpp
	@echo "   g++   main.o"
	@g++ -std=c++11 -c -g -o main.o ./main.cpp
main: main.o parse_str.o gendest.o macro_replace.o stroper.o 
	@echo "   LD   main"
	@g++ -std=c++11 -o main main.o parse_str.o gendest.o macro_replace.o stroper.o 
clean:
	@echo "  CLEAN   all files."
	-@rm parse_str.o gendest.o macro_replace.o stroper.o main.o main  2>/dev/null >/dev/null || true
