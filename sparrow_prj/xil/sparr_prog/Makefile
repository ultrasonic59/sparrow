
CFLAGS = -Wall -DLINUX -D_GNU_SOURCE  
 
LFLAGS = -lpthread -lrt -pthread 
LFLAGS += -lm

###CSRCS = ./src/sparrow_app.c ./src/synth.c ./src/udp/o_udp.c ./src/udp/pc_udp_interf.c ./src/udp/Fcs16.c  \
###		./src/ugen_fpga.c ./src/params_ugen.c ./src/sparrow_fpga.c 

CSRCS = ./src/sparrow_app.c ./src/sparrow_fpga.c ./src/udp/o_udp.c ./src/udp/pc_udp_interf.c ./src/udp/Fcs16.c \
		./src/zzz.c ./src/uadc.c ./src/udac.c ./src/sparrow_par.c
		
OBJS = $(CSRCS:.c=.o)

.SUFFIXES:.c.o

all:	sparrow_app

sparrow_app: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LFLAGS)
###	$(CC) $(CFLAGS) $(LFLAGS) -g -o $@ $(OBJS)
	
.c.o:
	$(CC) $(CFLAGS) -g -c -o $@ $<

clean:
	rm -f sparrow_app $(OBJS) 
	rm -f ./src/$(OBJS) 
 ####	find . -type f | xargs -n 5 touch
 ###   rm -rf $(OBJS)
