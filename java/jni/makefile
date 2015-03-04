# Define a variable for classpath
CLASS_PATH = ../bin

# Define a virtual path for .class in the bin directory
vpath %.class $(CLASS_PATH)

all : clean hello.dll TestHookJNI.dll MouseHook.dll


 # del or rm for window/unix
clean :
	del HelloJNI.o hello.dll MouseHook.o MouseHook.dll TestHookJNI.o TestHookJNI.dll
	
	
	
	
# $* matches the target filename without the extension
HelloJNI.h : HelloJNI.class
	javah -classpath $(CLASS_PATH) $*
	
HelloJNI.o : HelloJNI.c HelloJNI.h
	gcc -m64 -I"$(JAVA_HOME)include" -I"$(JAVA_HOME)include\win32" -c $< -o $@
	
hello.dll : HelloJNI.o
	gcc -m64 -Wl,--add-stdcall-alias -shared -o $@ $<	



	

	
MouseHook.h : MouseHook.class
	javah -classpath .;$(CLASS_PATH);bin\ $*	

MouseHook.o : MouseHook.cpp MouseHook.h
	g++ -m64 -I"$(JAVA_HOME)include" -I"$(JAVA_HOME)include\win32" -c $< -o $@  
	
MouseHook.dll : MouseHook.o
	g++ -m64 -Wl,--add-stdcall-alias -shared -o $@ $<





TestHookJNI.h : TestHookJNI.class
	javah -jni -classpath $(CLASS_PATH) $*	

TestHookJNI.o : TestHookJNI.cpp TestHookJNI.h
	g++ -I"$(JAVA_HOME)include" -I"$(JAVA_HOME)include\win32" -c $< -o $@  

TestHookJNI.dll : TestHookJNI.o
	g++ -Wl,--add-stdcall-alias -shared -o $@ $<
	
	
