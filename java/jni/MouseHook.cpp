#include <windows.h>
#include <jni.h>
#include "MouseHook.h"

#define DEBUG 1
#ifdef DEBUG
#define DEBUG_PRINT(x) printf x
#else
#define DEBUG_PRINT(x) do {} while (0)
#endif

HINSTANCE hInst = NULL;

JavaVM * jvm = NULL;
DWORD hookThreadId = 0;

jobject mouseHookObject = NULL;
jobject globalMouseListenerObject = NULL;
jmethodID processMouseButtonMethod = NULL;
jmethodID processMouseMoveMethod = NULL;

LONG mouseLocationX = -1, mouseLocationY = -1;

extern "C"
BOOL APIENTRY DllMain(HINSTANCE _hInst, DWORD reason, LPVOID reserved) {
	switch (reason) {
	case DLL_PROCESS_ATTACH:
		DEBUG_PRINT(("NATIVE: DllMain - DLL_PROCESS_ATTACH.n"));
		hInst = _hInst;
		break;
	default:
		break;
	}
	return TRUE;
}

LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
	JNIEnv* env;
	if (jvm->AttachCurrentThread((void **) &env, NULL) >= 0) {
		if (nCode == HC_ACTION) {
			MOUSEHOOKSTRUCT* pStruct = (MOUSEHOOKSTRUCT*) lParam;
			switch (wParam) {
			case WM_LBUTTONDOWN:
			case WM_LBUTTONUP:
			case WM_RBUTTONDOWN:
			case WM_RBUTTONUP:
				env->CallVoidMethod(mouseHookObject, processMouseButtonMethod,
						(jint) wParam, globalMouseListenerObject);
				break;
			case WM_MOUSEMOVE:
				if (pStruct->pt.x != mouseLocationX
						|| pStruct->pt.y != mouseLocationY) {
					env->CallVoidMethod(mouseHookObject, processMouseMoveMethod,
							(jint) pStruct->pt.x, (jint) pStruct->pt.y,
							globalMouseListenerObject);
					mouseLocationX = pStruct->pt.x;
					mouseLocationX = pStruct->pt.y;
				}
				break;
			default:
				break;
			}
		}
	} else
		DEBUG_PRINT(
				("NATIVE: LowLevelMouseProc - Error on the attach current thread.n"));
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

extern "C"
JNIEXPORT void JNICALL Java_MouseHook_registerHook(
		JNIEnv * env, jobject obj, jobject _globalMouseListenerObject) {
	DEBUG_PRINT(
			("NATIVE: Java_MouseHook_registerHook - Hooking started!n"));

	HHOOK hookHandle = SetWindowsHookEx(WH_MOUSE_LL, LowLevelMouseProc, hInst,
			0);
	globalMouseListenerObject = _globalMouseListenerObject;

	if (hookHandle == NULL) {
		DEBUG_PRINT(
				("NATIVE: Java_MouseHook_registerHook - Hook failed!n"));
		return;
	} else
		DEBUG_PRINT(
				("NATIVE: Java_MouseHook_registerHook - Hook successfuln"));

	mouseHookObject = env->NewGlobalRef(obj);
	jclass cls = env->GetObjectClass(mouseHookObject);
	processMouseButtonMethod = env->GetMethodID(cls, "processButton",
			"(ILGlobalMouseListener;)V");
	processMouseMoveMethod = env->GetMethodID(cls, "processMove",
			"(IILGlobalMouseListener;)V");

	env->GetJavaVM(&jvm);
	hookThreadId = GetCurrentThreadId();

	MSG message;
	while (GetMessage(&message, NULL, 0, 0)) {
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	DEBUG_PRINT(
			((!UnhookWindowsHookEx(hookHandle))?("NATIVE: Java_MouseHook_registerHook - Unhook failedn") :"NATIVE: Java_de_ksquared_system_mouse_MouseHook_registerHook - Unhook successfuln"));
}

extern "C"
JNIEXPORT void JNICALL Java_MouseHook_unregisterHook(
		JNIEnv *env, jobject object) {
	if (hookThreadId == 0)
		return;
	DEBUG_PRINT(
			("NATIVE: Java_MouseHook_unregisterHook - call PostThreadMessage.n"));
	PostThreadMessage(hookThreadId, WM_QUIT, 0, 0L);
}
