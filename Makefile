bin=trash
cc=g++
src=trash.cc
flag=-std=c++11

$(bin):$(src)
	@$(cc) -o $@ $^ $(flag)
	$(info 编译完成)

.PHONY:clean
clean:
	@/usr/bin/rm -f $(bin)
	$(info 清理完成)
