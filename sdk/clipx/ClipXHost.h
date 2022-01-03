#ifndef CLIPX_HOST_H
#define CLIPX_HOST_H

// CLIPX PLUGIN SDK - DO NOT MODIFY

#include <bfc/dispatch.h>

// {ABAEECFD-1B9E-4c90-973E-3EFE6885ECA8}
static const GUID CLIPX_HOST_GUID = 
{ 0xabaeecfd, 0x1b9e, 0x4c90, { 0x97, 0x3e, 0x3e, 0xfe, 0x68, 0x85, 0xec, 0xa8 } };

class ClipXHost : public Dispatchable {
protected:
  ClipXHost() {}
  virtual ~ClipXHost() {}

public:

  // GENERAL 

  // Get ClipX version string
  const char *getVersion() { return _call(CLIPX_HOST_GETVERSION, (const char *)NULL); }
  // Get beta version flag
  int isBeta() { return _call(CLIPX_HOST_ISBETA, 0); }
  // Get platform id (Win32, Win64)
  const char *getPlatformId() { return _call(CLIPX_HOST_GETPLATFORMID, "Unknown"); }
  // Get architecture id (x86, x64)
  const char *getArchitectureId() { return _call(CLIPX_HOST_GETARCHID, "Unknown"); }
  // Exit ClipX (deferred)
  void exit() { _voidcall(CLIPX_HOST_EXIT); }
  // Get ClipX install path
  const char *getInstallPath() { return _call(CLIPX_HOST_GETINSTALLPATH, (const char *)NULL); }

  // HISTORY

  // Get number of items in clipboard history
  int history_getNumItems() { return _call(CLIPX_HOST_HISTORY_GETNUMITEMS, 0); }
  // Get an item's type (0 = text, 1 = bitmap, 2 = filelist, -1 = invalid index)
  int history_getItemType(int idx) { return _call(CLIPX_HOST_HISTORY_GETITEMTYPE, -1, idx); }
  // Get an item's text (bitmaps return "Bitmap WxH", NULL = invalid index)
  const char *history_getItemText(int idx) { return _call(CLIPX_HOST_HISTORY_GETITEMTEXT, (const char *)NULL, idx); }
  // Get a bitmap item's width (-1 = invalid index, or not a bitmap item)
  int history_getItemBitmapWidth(int idx) { return _call(CLIPX_HOST_HISTORY_GETITEMBITMAPWIDTH, -1, idx); }
  // Get a bitmap item's height (-1 = invalid index, or not a bitmap item)
  int history_getItemBitmapHeight(int idx) { return _call(CLIPX_HOST_HISTORY_GETITEMBITMAPHEIGHT, -1, idx); }
  // Get a pointer to a bitmap item's bits (NULL = invalid index, or not a bitmap item)
  COLORREF *history_getItemBitmapBits(int idx) { return _call(CLIPX_HOST_HISTORY_GETITEMBITMAPBITS, (COLORREF *)NULL, idx); }
  // Get the number of files in a filelist (-1 = invalid index, or not a filelist item)
  int history_getFileListCount(int idx) { return _call(CLIPX_HOST_HISTORY_GETFILELISTCOUNT, 0, idx); }
  // Enumerate the file in a filelist (NULL = invalid file index, or invalid item index)
  const char *history_getFileListFile(int idx, int fileidx) { return _call(CLIPX_HOST_HISTORY_GETFILELISTFILE, (const char *)NULL, idx, fileidx); }
  // Delete an item from the history
  void history_deleteItem(int idx) { _voidcall(CLIPX_HOST_HISTORY_DELETEITEM, idx); }
  // Move an item to another spot (newidx : 0 = first, 1 = second, -1 = last)
  void history_moveItem(int idx, int newidx) { _voidcall(CLIPX_HOST_HISTORY_MOVEITEM, idx, newidx); }
  
  // CONFIG

  // Enable the configuration window's Apply button
  void config_allowApply() { _voidcall(CLIPX_HOST_CONFIG_ALLOWAPPLY); }

  // MISC

  // Navigate to the provided URL, using the user selected method
  void misc_navigate(const char *url) { _voidcall(CLIPX_HOST_MISC_NAVIGATE, url); }
  // Format a block of text into a one line suitable for single line display
  void misc_formatLine(const char *dest, int destlen, const char *source, int doubleands) { _voidcall(CLIPX_HOST_MISC_FORMATLINE, dest, destlen, source, doubleands); }
  // Paste arbitrary text in the currently active application
  void misc_paste(const char *text) { _voidcall(CLIPX_HOST_PASTETEXT, text); }
  // Paste a clipboard history item in the currently active application
  void misc_pasteHistoryItem(int idx) { _voidcall(CLIPX_HOST_PASTEITEM, idx); }

  // HOTKEYS

  // Subclass an edit control and turns it into an extended hotkey control
  void hotkey_subclassEditBox(HWND editBoxWnd) { _voidcall(CLIPX_HOST_HOTKEY_SUBCLASS, editBoxWnd); }
  // Decode a control hotkey code into its RegisterHotkey components
  void hotkey_decode(int *keyCode, int *modifier, WORD controlHotkeyCode) { _voidcall(CLIPX_HOST_HOTKEY_DECODE, keyCode, modifier, controlHotkeyCode, 0); }
  // Encode a control hotkey code from its RegisterHotkey components
  WORD hotkey_encode(int keyCode, int modifier) { return _call(CLIPX_HOST_HOTKEY_ENCODE, keyCode, modifier, 0); }


  enum {
    CLIPX_HOST_GETVERSION                  = 0,
    CLIPX_HOST_EXIT                        = 10,
    CLIPX_HOST_HISTORY_GETNUMITEMS         = 20,
    CLIPX_HOST_HISTORY_GETITEMTYPE         = 30,
    CLIPX_HOST_HISTORY_GETITEMTEXT         = 40,
    CLIPX_HOST_HISTORY_GETITEMBITMAPWIDTH  = 50,
    CLIPX_HOST_HISTORY_GETITEMBITMAPHEIGHT = 60,
    CLIPX_HOST_HISTORY_GETITEMBITMAPBITS   = 70,
    CLIPX_HOST_HISTORY_DELETEITEM          = 80,
    CLIPX_HOST_HISTORY_MOVEITEM            = 90,
    CLIPX_HOST_HISTORY_GETFILELISTCOUNT    = 100,
    CLIPX_HOST_HISTORY_GETFILELISTFILE     = 110,
    CLIPX_HOST_CONFIG_ALLOWAPPLY           = 120,
    CLIPX_HOST_MISC_NAVIGATE               = 130,
    CLIPX_HOST_GETINSTALLPATH              = 140,
    CLIPX_HOST_HOTKEY_SUBCLASS             = 150,
    CLIPX_HOST_HOTKEY_ENCODE               = 160,
    CLIPX_HOST_HOTKEY_DECODE               = 170,
    CLIPX_HOST_MISC_FORMATLINE             = 180,
    CLIPX_HOST_ISBETA                      = 190,
    CLIPX_HOST_GETPLATFORMID               = 200,
    CLIPX_HOST_GETARCHID                   = 210,
    CLIPX_HOST_PASTETEXT                   = 220,
    CLIPX_HOST_PASTEITEM                   = 230,
  };
};


#endif
