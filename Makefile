ifeq ($(OS), Windows_NT)
    PLATFORM := windows
    MINGW32 := C:/MinGW-W64/mingw32/bin/
    MINGW64 := C:/MinGW-W64/mingw64/bin/
	addIcon32 := addIcon-x32.res
	addIcon64 := addIcon-x64.res
    resMaking := $(MINGW32)windres addIcon.rc -O coff -F pe-i386 -o $(addIcon32) && \
                 $(MINGW64)windres addIcon.rc -O coff -o $(addIcon64)
    Compress := C:/Program Files/7-Zip/7z.exe a -t7z -mx9
    EXE := .exe
	Archive := .7z
    RM := del /Q
else
    PLATFORM := linux
    Compress := tar -cJvf
	Archive := .tar.xz
    RM := rm -f
endif

CPP := main.cpp functions.cpp 
fileName := Snake

$(PLATFORM)-build:
	@echo Building for $(PLATFORM)
	$(resMaking)
	$(MINGW32)g++ -static -m32 -o $(fileName)-x32 $(CPP) $(addIcon32)
	$(MINGW64)g++ -static -o $(fileName)-x64 $(CPP) $(addIcon64)

	$(Compress) $(PLATFORM)-x32$(Archive) $(fileName)-x32$(EXE)
	$(Compress) $(PLATFORM)-x64$(Archive) $(fileName)-x64$(EXE)

clean:
	$(RM) $(fileName)-x32$(EXE) $(fileName)-x64$(EXE) addIcon-x32.res addIcon-x64.res *$(Archive)