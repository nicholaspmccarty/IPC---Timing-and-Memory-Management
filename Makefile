CXX=g++-12
RM=rm -f
CPPFLAGS=--std=c++2b -Werror -Wall -Wextra -Wconversion -Wsign-conversion -Wpedantic -Wnull-dereference -Wold-style-cast -Wdouble-promotion -Wshadow

SRCS_PIPE=send_pipe.cpp
SRCS_SEND_SHM=send_shm.cpp
SRCS_RCV_SHM=rcv_shm.cpp
SRCS_SEND_MSG=send_msg.cpp
SRCS_RCV_MSG=rcv_msg.cpp

OBJS_PIPE=$(subst .cpp,.o,$(SRCS_PIPE))
OBJS_SEND_SHM=$(subst .cpp,.o,$(SRCS_SEND_SHM))
OBJS_RCV_SHM=$(subst .cpp,.o,$(SRCS_RCV_SHM))
OBJS_SEND_MSG=$(subst .cpp,.o,$(SRCS_SEND_MSG))
OBJS_RCV_MSG=$(subst .cpp,.o,$(SRCS_RCV_MSG))

all: send_pipe send_shm rcv_shm send_msg rcv_msg

send_pipe: $(OBJS_PIPE)
	$(CXX) $(CPPFLAGS) -o send_pipe $(OBJS_PIPE)

send_shm: $(OBJS_SEND_SHM)
	$(CXX) $(CPPFLAGS) -o send_shm $(OBJS_SEND_SHM)
	
rcv_shm: $(OBJS_RCV_SHM)
	$(CXX) $(CPPFLAGS) -o rcv_shm $(OBJS_RCV_SHM)

send_msg: $(OBJS_SEND_MSG)
	$(CXX) $(CPPFLAGS) -o send_msg $(OBJS_SEND_MSG)

rcv_msg: $(OBJS_RCV_MSG)
	$(CXX) $(CPPFLAGS) -o rcv_msg $(OBJS_RCV_MSG)


# Build all C++ files
depend: .depend

.depend: $(SRCS)
	$(RM) ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend

# Clean compiled C++ files
clean:
	$(RM) *.o $(OBJS_PIPE) $(OBJS_RCV_SHM) $(OBJS_SEND_SHM) $(OBJS_RCV_MSG) $(OBJS_SEND_MSG)*~ .depend lab send_pipe send_shm send_msg rcv_msg rcv_shm
 

include .depend