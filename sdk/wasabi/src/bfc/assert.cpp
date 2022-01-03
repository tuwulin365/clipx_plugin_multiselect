#include <precomp.h>
#ifdef WIN32
#include <windows.h>
#endif

#include "assert.h"

#ifdef ASSERTS_ENABLED

static int in_assert = 0;

// we try to use wsprintf because it can make for a smaller .exe
#ifdef WIN32
#define ASSERT_SPRINTF wsprintf
#elif defined(LINUX)
#define ASSERT_SPRINTF sprintf
#else
#error port me!
#endif

#ifdef WIN32
static int isDebuggerPresent() {
  HINSTANCE kernel32 = LoadLibrary("kernel32.dll");
  if (kernel32 == NULL) return 0;
  BOOL (WINAPI *IsDebuggerPresent)() = NULL;
  IsDebuggerPresent = (BOOL (WINAPI *)())GetProcAddress(kernel32, "IsDebuggerPresent");
  if (IsDebuggerPresent == NULL) return 0;
  int ret = (*IsDebuggerPresent)();
  FreeLibrary(kernel32);
  return ret;
}
#endif

void _assert_handler(const char *reason, const char *file, int line) {
  char msg[4096];
  ASSERT_SPRINTF(msg, "Expression: %s\nFile: %s\nLine: %d\n", reason, file, line);
  OutputDebugString(msg);
#ifdef WIN32
#ifdef _WIN64
  if (in_assert) __debugbreak();
#else
  if (in_assert) __asm { int 3 };
#endif
  in_assert = 1;

  ATOM a = AddAtom("BYPASS_DEACTIVATE_MGR"); // so we don't need to call api->appdeactivation_setbypass

  if (isDebuggerPresent() || MessageBox(NULL, msg, "Assertion failed", MB_OKCANCEL|MB_TASKMODAL) == IDCANCEL) {
#ifdef _WIN64
	__debugbreak();
#else
	__asm { int 0x3 };
#endif
  } else
    ExitProcess(0);
  DeleteAtom(a);
#elif defined(LINUX)
  kill(getpid(), SIGSEGV );
#else
#error port me!
#endif
  in_assert = 0;
}

void _assert_handler_str(const char *string, const char *reason, const char *file, int line) {
  char msg[4096];
  ASSERT_SPRINTF(msg, "\"%s\"\nExpression: %s\nFile: %s\nLine: %d\n", string, reason ? reason : "", file, line);
  OutputDebugString(msg);

#ifdef WIN32
#ifdef _WIN64
  if (in_assert) __debugbreak();
#else
  if (in_assert) __asm { int 3 };
#endif
  in_assert = 1;

  ATOM a = AddAtom("BYPASS_DEACTIVATE_MGR");
  if (isDebuggerPresent() || MessageBox(NULL, msg, "Assertion failed", MB_OKCANCEL|MB_TASKMODAL) == IDCANCEL) {
#ifdef _WIN64
	__debugbreak();
#else
	__asm { int 0x3 };
#endif
  } else
    ExitProcess(0);
  DeleteAtom(a);
#elif defined(LINUX)
  kill(getpid(), SIGSEGV );
#else
#error port me!
#endif
  in_assert = 0;
}

#endif
