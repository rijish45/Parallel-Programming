#BHEADER****************************************************************
# (c) 2007   The Regents of the University of California               *
#                                                                      *
# See the file COPYRIGHT_and_DISCLAIMER for a complete copyright       *
# notice and disclaimer.                                               *
#                                                                      *
#EHEADER****************************************************************
CC       = gcc
LDR      = gcc

CFLAGS   = -O3 -pg -fopenmp -c

LDFLAGS  = -O3 -pg -fopenmp -lm

LIBS     =
LIB_DIRS =

PROG     = AMGMk

OBJS     = main.o \
           csr_matrix.o   csr_matvec.o  \
           laplace.o relax.o \
           hypre_error.o hypre_memory.o \
           vector.o

all : $(PROG)

$(PROG) : $(OBJS)
	$(LDR)  $(LDFLAGS) -o $(PROG) $(OBJS) $(LIB_DIRS) $(LIBS) -L. -ltimer


clean :
	rm -f *.o $(PROG) core *~ 


.SUFFIXES : .o  .c

#*****************************************************************
#* Rules for C object file dependencies
#*****************************************************************
.c.o :
	$(CC) $(CFLAGS) $*.c 







