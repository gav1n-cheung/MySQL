src=$(wildcard ./*.c)
objs=$(patsubst %.c,%.o,$(src))
target=app
$(target):$(objs)
	$(CC) $^ -o $@
%.o:%.c
	$(CC) -c $< -o $@
#生成伪目标，避免与外部文件对比
.PHONY:clean
clean:
	rm $(objs) -f
