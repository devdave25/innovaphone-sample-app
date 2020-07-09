#----------------------------------------------------------------------------
# makefile
# copyright (c) innovaphone 2013
#----------------------------------------------------------------------------

default: x86_64 arm copy-to-builddir

native: SampleApp

#Native compiling
SampleApp:
	make -j5 -f SampleApp.mak native

#Cross-compiling: x86_64, all sub-projects
x86_64:	
	export PATH=$$PATH_GCC_X86_64_BIN; make -j5 -f SampleApp.mak $@

#Cross-compiling: arm, all sub-projects
arm:
	export PATH=$$PATH_GCC_ARM_BIN; make -j5 -f SampleApp.mak $@
	
copy-to-builddir:
	mksxcopy "x86_64/SampleApp/*"; mksxcopy "arm/SampleApp/*"; mksxcopy SampleApp_files;

clean:
	make -j5 -f SampleApp.mak $@ TARGET=$@

