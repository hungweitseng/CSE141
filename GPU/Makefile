OPENCLC=/System/Library/Frameworks/OpenCL.framework/Libraries/openclc
BUILD_DIR=./build
EXECUTABLE=gpumm 
.SUFFIXES:
KERNEL_ARCH=i386 x86_64 gpu_32 gpu_64
BITCODES=$(patsubst %, gpumm_kernel.cl.%.bc, $(KERNEL_ARCH))

$(EXECUTABLE): $(BUILD_DIR)/gpumm_kernel.cl.o $(BUILD_DIR)/gpumm.o $(BITCODES) blockmm
	clang -framework OpenCL -o $@ $(BUILD_DIR)/gpumm_kernel.cl.o $(BUILD_DIR)/gpumm.o
	
$(BUILD_DIR)/gpumm_kernel.cl.o: gpumm_kernel.cl.c
	mkdir -p $(BUILD_DIR)
	clang -c -Os -Wall -arch x86_64 -o $@ -c gpumm_kernel.cl.c
			
$(BUILD_DIR)/gpumm.o: gpumm.c gpumm_kernel.cl.h
	mkdir -p $(BUILD_DIR)
	clang -c -Os -Wall -arch x86_64 -o $@ -c $<
					
gpumm_kernel.cl.c gpumm_kernel.cl.h: gpumm_kernel.cl
	$(OPENCLC) -x cl -cl-std=CL1.1 -cl-auto-vectorize-enable -emit-gcl $<

gpumm_kernel.cl.%.bc: gpumm_kernel.cl
	$(OPENCLC) -x cl -cl-std=CL1.1 -Os -arch $* -emit-llvm -o $@ -c $<
	
blockmm: blockmm.c
	clang -O3 -o blockmm blockmm.c

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) gpumm_kernel.cl.h gpumm_kernel.cl.c $(EXECUTABLE) *.bc blockmm
	