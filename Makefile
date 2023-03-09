bin=trash
cc=g++
src=trash.cc
flag=-std=c++11

$(bin):$(src)
	$(cc) -o $@ $^ $(flag)

.PHONY:clean
clean:
	/usr/bin/rm -f $(bin)
