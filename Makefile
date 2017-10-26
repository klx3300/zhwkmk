__fake_main__: main

parse_str.o: parse_str/strparse.cpp
	@echo "   g++   parse_str.o"
	@g++ -c  -o parse_str.o parse_str/strparse.cpp
gendest.o: gendest/gendest.cpp
	@echo "   g++   gendest.o"
	@g++ -c  -o gendest.o gendest/gendest.cpp
macro_replace.o: macro_replace/macro_replace.cpp
	@echo "   g++   macro_replace.o"
	@g++ -c  -o macro_replace.o macro_replace/macro_replace.cpp
stroper.o: stroper/stroper.cpp
	@echo "   g++   stroper.o"
	@g++ -c  -o stroper.o stroper/stroper.cpp
main.o: main.cpp
	@echo "   g++   main.o"
	@g++ -c  -o main.o main.cpp
main: main.o parse_str.o gendest.o macro_replace.o stroper.o 
	@echo "   LD   main"
	@g++  -o main main.o parse_str.o gendest.o macro_replace.o stroper.o 
clean:
	@echo "  CLEAN   all files."
	-@rm parse_str.o gendest.o macro_replace.o stroper.o main.o main  || true
