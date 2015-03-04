#include<stdio.h>
#include<windows.h>
#include<jni.h>
#include "HelloJNI.h"

JNIEXPORT void JNICALL Java_HelloJNI_sayHello(JNIEnv *env, jobject thisObject){
	printf("Hello JNI From Raja Khan\n");
	return;
}

JNIEXPORT void JNICALL Java_HelloJNI_mousePosition (JNIEnv *env, jobject thisObject){
	printf("Hello JNI1 win32 call start\n");
	MessageBox(0,"Hello, Windows","MinGW Test Program",MB_OK);

	POINT cursorPos;
	GetCursorPos( &cursorPos );
	int x = (int) cursorPos.x;
	int y = (int) cursorPos.y;

	printf("Mouse Position [ x=%d, y=%d ] \n", &x, &y);

	printf("\nHello JNI1 win32 call end.\n");

	return;
}
