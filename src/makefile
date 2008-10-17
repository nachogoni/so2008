RM := rm -rf
C_SRCS := libasm.c loader.c libc.c fd.c memory.c strings.c pagination.c ipc.c scheduler.c processes.c sem.c kernel.c io.c ./drivers/video.c ./drivers/tty.c ./drivers/keyboard.c shell.c grubInfo.c ./drivers/serial.c ./app/chat.c ./app/games.c ./app/tron.c ./app/top.c ./app/excep.c ./app/malloccer.c
C_DEPS := libasm.d loader.d libc.d fd.d memory.d strings.d pagination.d ipc.d scheduler.d processes.d sem.d kernel.d io.d ./drivers/video.d ./drivers/tty.d ./drivers/keyboard.d shell.d grubInfo.d ./drivers/serial.d ./app/chat.d ./app/games.d ./app/tron.d ./app/top.d ./app/excep.d ./app/malloccer.d
OBJS := libasm.o loader.o libc.o fd.o memory.o strings.o pagination.o ipc.o scheduler.o processes.o sem.o kernel.o io.o ./drivers/video.o  ./drivers/tty.o ./drivers/keyboard.o shell.o grubInfo.o ./drivers/serial.o ./app/chat.o ./app/games.o ./app/tron.o ./app/top.o ./app/excep.o ./app/malloccer.o
LIBS :=

# All Target
all: kernel.bin

libasm.o: libasm.asm
	@echo 'Building file: $<'
	@echo 'Invoking: NASM Compiler'
	nasm -f aout libasm.asm -o libasm.o
	@echo 'Finished building: $<'
	@echo ' '

loader.o: loader.asm
	@echo 'Building file: $<'
	@echo 'Invoking: NASM Compiler'
	nasm -f aout loader.asm -o loader.o
	@echo 'Finished building: $<'
	@echo ' '

%.o: %.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"../include" -I"../include/drivers" -O0 -g3 -Wall -c -fno-builtin -fno-stack-protector -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
# 	gcc -I"../include" -I"../include/drivers" -O0 -g3 -c -fno-builtin -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

kernel.bin: $(OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C Linker'
	ld -T link.ld -g -o $@ $(OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

clean:
	-$(RM) $(OBJS) $(C_DEPS) kernel.bin *~ ./drivers/*~ ./app/*~
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:
