OBJ_LIST = hash.obj
CFLAGS = /nologo /W3 /Ihash

DLLNAMES = hash.dll

build: tema1.exe

tema1.exe: main.obj hash_table.obj list.obj
    cl $(CFLAGS) /Fe$@ $** hash.lib
    
main.obj: main.c
    cl $(CFLAGS) /Fo$@ /c $**

hash_table.obj: hash_table.c
    cl $(CFLAGS) /Fo$@ /c $**
    
list.obj: list.c
    cl $(CFLAGS) /Fo$@ /c $**
    
clean: obj_clean
	del tema1.exe
obj_clean : 
	del *.obj

dll_clean : 
	del $(DLLNAMES)