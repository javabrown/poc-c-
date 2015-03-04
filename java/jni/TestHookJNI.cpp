#include<jni.h>
#include<iostream>

using namespace std;

extern "C"
JNIEXPORT void JNICALL Java_TestHookJNI_mousePosition (JNIEnv *env, jobject thisObject) {
	cout<<"Hello JNI from C++ to TestHookJNI";
	return;
}
