all:
	$(MAKE) -C ./src
	mkdir -p bin
	mv ./src/kernel.bin ./bin/kernel.bin

exe:
	$(MAKE) all
	mcopy ./bin/kernel.bin d:boot/ -o
	bochs -qf bochsrc.txt

clean:
	$(MAKE) clean -C src
	rm -rf ./bin/* *~ ./include/*~ ./include/drivers/*~

cexe:
	$(MAKE) clean
	$(MAKE) all
	mcopy ./bin/kernel.bin d:boot/ -o
	$(MAKE) clean
	bochs -qf bochsrc.txt

qemu:
	$(MAKE) clean
	$(MAKE) all	
	mcopy ./bin/kernel.bin d:boot/ -o
	cp bin/kernel.bin bin/kernel.s
	$(MAKE) clean
	qemu -m 32 -fda img/grubTest.img -no-kqemu

cdebug:
	$(MAKE) clean
	$(MAKE) all
	mcopy ./bin/kernel.bin d:boot/ -o
	cp bin/kernel.bin bin/kernel.s
	qemu -s -p 5000 -m 32 -fda img/grubTest.img -no-kqemu &
	sleep 2
	gdb bin/kernel.s --eval-command="target remote localhost:5000" --eval-command="b kmain"  --eval-command="c"

debug:
	$(MAKE) all
	mcopy ./bin/kernel.bin d:boot/ -o
	cp bin/kernel.bin bin/kernel.s
	qemu -s -p 5000 -m 32 -fda img/grubTest.img -no-kqemu &
	sleep 2
	gdb bin/kernel.s --eval-command="target remote localhost:5000" --eval-command="b kmain"  --eval-command="c"
