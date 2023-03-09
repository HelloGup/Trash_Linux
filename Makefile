bin=trash
cc=g++
src=trash.cc

$(bin):$(src)
	$(cc) -o $@ $^

.PHONY:clean
clean:
	/usr/bin/rm -f $(bin)
