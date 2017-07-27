# Makefile $

MKFILE      = Makefile
GMAKE       = ${MAKE} --no-print-directory
COMPILECPP  = g++ -std=gnu++14 -g -w -O0 -Wall -Wextra -Wold-style-cast
MAKEDEPCPP  = g++ -std=gnu++14 -MM

MODULES     = Add Assign DataType Div Gsc Instruction Jmp Jmpgt Jmpgte Jmplt Jmplte Jmpnz Jmpz Label Mul Out Sleep Ssc Sub Var
CPPHEADER   = ${MODULES:=.h} common.h
CPPSOURCE   = ${MODULES:=.cpp} main.cpp
EXECBIN     = main
OBJECTS     = ${CPPSOURCE:.cpp=.o}


all : ${EXECBIN}

${EXECBIN} : ${OBJECTS}
	${COMPILECPP} -o $@ ${OBJECTS}

%.o : %.cpp
	${COMPILECPP} -c $<

clean :
	- rm ${OBJECTS} ${DEPFILE}

spotless : clean
	- rm ${EXECBIN} 

ifeq (${NEEDINCL}, )
endif
