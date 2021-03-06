#include <precomp.h>
#include "plugin.h"
#include "SampleConfigPage.h"
#include "resource.h"
#include <CommCtrl.h>
#include <windowsx.h>
#include "bfc/string/encodedstr.h"

_DECLARE_SERVICETSINGLE(svc_ClipXConfigPage, SampleConfigPage);
void ClipxPluginLog(char *pStr, int iLine);

#define USE_UNICODE_LISTBOX 1

// the name that appears in the config list
const char *SampleConfigPage::getPageTitle()
{
    return "Multiselect";
}

// settings, with default values
int gb_enabled = 1;

int gi_hotkey_vk = 0;
int gi_hotkey_mod = 0;
int gb_newline = 1;
int gb_newfirst = 1;
int gb_quote = 0;
int gb_paste = 1;
int gb_copy = 0;

// temp values
int tb_enabled = 0;

int ti_hotkey_vk = 0;
int ti_hotkey_mod = 0;
int tb_newline = 0;
int tb_newfirst = 0;
int tb_quote = 0;
int tb_paste = 0;
int tb_copy = 0;


INT_PTR CALLBACK MyDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
HWND ghMyDlg = NULL;
int iHotkeyID = 0;

// load settings from ini
void SampleConfigPage::loadSettings(const char *inifile, const char *section)
{
    gb_enabled = GetPrivateProfileInt(section, "multiselect_enabled", gb_enabled, inifile);
    
    gi_hotkey_mod = GetPrivateProfileInt(section, "multiselect_hotkey_mod", gi_hotkey_mod, inifile);
    gi_hotkey_vk = GetPrivateProfileInt(section, "multiselect_hotkey_vk", gi_hotkey_vk, inifile);
    gb_newline = GetPrivateProfileInt(section, "multiselect_newline", gb_newline, inifile);
    gb_newfirst = GetPrivateProfileInt(section, "multiselect_newfirst", gb_newfirst, inifile);
    gb_quote = GetPrivateProfileInt(section, "multiselect_quote", gb_quote, inifile);
    gb_paste = GetPrivateProfileInt(section, "multiselect_paste", gb_paste, inifile);
    gb_copy = GetPrivateProfileInt(section, "multiselect_copy", gb_copy, inifile);

    //unicode ver listbox
#if USE_UNICODE_LISTBOX 
    ghMyDlg = CreateDialogW(the->getOSModuleHandle(), MAKEINTRESOURCEW(IDD_DIALOG_MULTISELECT), NULL, MyDlgProc);
#else
    ghMyDlg = CreateDialog(the->getOSModuleHandle(), MAKEINTRESOURCE(IDD_DIALOG_MULTISELECT), NULL, MyDlgProc);
#endif
    //ShowWindow(ghMyDlg, SW_SHOW);
    g_clipx->hotkey_subclassEditBox(ghMyDlg); 
    iHotkeyID = GlobalAddAtom("mult_select");
    if (gb_enabled)
    {
        RegisterHotKey(ghMyDlg, iHotkeyID, gi_hotkey_mod, gi_hotkey_vk);
    }
}

// save settings to ini
void SampleConfigPage::saveSettings(const char *inifile, const char *section)
{
    WritePrivateProfileString(section, "multiselect_enabled", StringPrintf("%d", gb_enabled), inifile);

    WritePrivateProfileString(section, "multiselect_hotkey_mod", StringPrintf("%d", gi_hotkey_mod), inifile);
    WritePrivateProfileString(section, "multiselect_hotkey_vk", StringPrintf("%d", gi_hotkey_vk), inifile);
    WritePrivateProfileString(section, "multiselect_newline", StringPrintf("%d", gb_newline), inifile);
    WritePrivateProfileString(section, "multiselect_newfirst", StringPrintf("%d", gb_newfirst), inifile);
    WritePrivateProfileString(section, "multiselect_quote", StringPrintf("%d", gb_quote), inifile);
    WritePrivateProfileString(section, "multiselect_paste", StringPrintf("%d", gb_paste), inifile);
    WritePrivateProfileString(section, "multiselect_copy", StringPrintf("%d", gb_copy), inifile);
}

// settings are copied to temporary variables, which the dialog works on, when the clipx config dialog is brought up
void SampleConfigPage::copySettings()
{
    tb_enabled      = gb_enabled;
    
    ti_hotkey_mod   = gi_hotkey_mod;
    ti_hotkey_vk    = gi_hotkey_vk;
    tb_newline      = gb_newline;
    tb_newfirst     = gb_newfirst;
    tb_quote        = gb_quote;
    tb_paste        = gb_paste;
    tb_copy         = gb_copy;
}

// settings are validated when the user clicks ok or apply
void SampleConfigPage::applySettings()
{
    if (gb_enabled && tb_enabled)
    {
        if ((gi_hotkey_mod != ti_hotkey_mod) || (gi_hotkey_vk != ti_hotkey_vk))
        {
            UnregisterHotKey(ghMyDlg, iHotkeyID);
            RegisterHotKey(ghMyDlg, iHotkeyID, ti_hotkey_mod, ti_hotkey_vk);
        }        
    }
    else if (!gb_enabled && tb_enabled)
    {
        RegisterHotKey(ghMyDlg, iHotkeyID, ti_hotkey_mod, ti_hotkey_vk);
    }
    else if (gb_enabled && !tb_enabled)
    {
        UnregisterHotKey(ghMyDlg, iHotkeyID);
    }

    gb_enabled      = tb_enabled;

    gi_hotkey_mod   = ti_hotkey_mod;
    gi_hotkey_vk    = ti_hotkey_vk;
    gb_newline      = tb_newline;
    gb_newfirst     = tb_newfirst;
    gb_quote        = tb_quote;  
    gb_paste        = tb_paste;
    gb_copy         = tb_copy;
}

void updateVisibility(HWND hwndDlg)
{
    EnableWindow(GetDlgItem(hwndDlg, IDC_STATIC_HOTKEY_POPUP), tb_enabled);
    EnableWindow(GetDlgItem(hwndDlg, IDC_HOTKEY_POPUP), tb_enabled);
    EnableWindow(GetDlgItem(hwndDlg, IDC_CHECK_NEWLINE), tb_enabled);
    EnableWindow(GetDlgItem(hwndDlg, IDC_CHECK_NEW_FIRST), tb_enabled);
    EnableWindow(GetDlgItem(hwndDlg, IDC_CHECK_QUOTE), tb_enabled);
    EnableWindow(GetDlgItem(hwndDlg, IDC_STATIC_OUTPUT), tb_enabled);
    EnableWindow(GetDlgItem(hwndDlg, IDC_RADIO_PASTE_TO_BOX), tb_enabled);
    EnableWindow(GetDlgItem(hwndDlg, IDC_RADIO_COPY_TO_CLIP), tb_enabled);
    EnableWindow(GetDlgItem(hwndDlg, IDC_RADIO_PASTE_COPY), tb_enabled);
}

HWND g_last_dlg = NULL;

static const char *CutHeadBlank(const char *pString)
{
    int i;
    
    if (!pString)
    {
        return NULL;
    }
    
    for (i = 0; i < strlen(pString); i++)
    {
        if ((pString[i] != ' ') && (pString[i] != '\t') && (pString[i] != '\r') && (pString[i] != '\n'))
        {
            break;
        }
    }

    return (i == strlen(pString)) ? pString : (pString+i);
}

#define DISP_RECORD_MAX_LEN 300 //????????????????????????
static int iAllRecordTotalSize = 0;
static int FillRecordToListbox(HWND hListCtl)
{
#if 0
    SendMessage(hListCtl, LB_INSERTSTRING, -1, (LPARAM)"test ????0");
    SendMessage(hListCtl, LB_INSERTSTRING, -1, (LPARAM)"test ????1");
    SendMessage(hListCtl, LB_INSERTSTRING, -1, (LPARAM)"test ????2");
    SendMessage(hListCtl, LB_INSERTSTRING, -1, (LPARAM)"test ????3");
#else
    int iItemCnt = g_clipx->history_getNumItems();
    const char *pcText;

    iAllRecordTotalSize = 0;
    
    ListBox_ResetContent(hListCtl);
    for (int i = 0; i < iItemCnt; i++)
    {
        pcText = g_clipx->history_getItemText(i);
        
        if (pcText)
        {
            iAllRecordTotalSize += strlen(pcText);
        }
        
        pcText = CutHeadBlank(pcText);
        if (pcText)
        {
            int iWideCharCnt;
            wchar_t *pwcBuf;
            char czTemp[DISP_RECORD_MAX_LEN+1];

            memset(czTemp, 0, sizeof(czTemp));
            memcpy(czTemp, pcText, (strlen(pcText) > DISP_RECORD_MAX_LEN) ? DISP_RECORD_MAX_LEN : strlen(pcText));
            
            //utf8 to unicode
            iWideCharCnt = MultiByteToWideChar(CP_UTF8, 0, czTemp, -1, NULL, 0);
            pwcBuf = (wchar_t*)calloc(iWideCharCnt + 8 + 1 , sizeof(wchar_t));  //??????+????+??????
            swprintf(pwcBuf, L"(%03d) ", i+1);  //????
            iWideCharCnt = MultiByteToWideChar(CP_UTF8, 0, czTemp, -1, pwcBuf + wcslen(pwcBuf), iWideCharCnt);
            
        #if USE_UNICODE_LISTBOX
            SendMessageW(hListCtl, LB_INSERTSTRING, -1, (LPARAM)(LPCTSTR)pwcBuf);
        #else
            char *pcStr;
            int iLen;
            BOOL bFail;
            
            //unicode to ansi
            iLen = WideCharToMultiByte(CP_ACP, 0, pwcBuf, iWideCharCnt, NULL, 0, "*", &bFail); 
            pcStr = (char*)malloc(iLen);
            iLen = WideCharToMultiByte(CP_ACP, 0, pwcBuf, iWideCharCnt, pcStr, iLen, "*", &bFail); 

            //add to listbox
            ListBox_InsertString(hListCtl, -1, pcStr);
            free(pcStr);
        #endif
        
            free(pwcBuf);
        }
    }
#endif
    return 0;
}

static int CopyTextToClip(char *pcText)
{
    int iRet = 0;
    HGLOBAL hMemory;
    LPTSTR lpMemory;

    int contentSize = strlen(pcText) + 1;

    if (!OpenClipboard(NULL))   // ????????????????????????????????????
    {
        return -1;
    }
    if (!EmptyClipboard())      // ??????????????????????????????????????
    {
        iRet = -2;
        goto _exit;
    }
    if ((hMemory = GlobalAlloc(GMEM_MOVEABLE, contentSize)) == NULL)   // ????????????????
    {
        iRet = -3;
        goto _exit;
    }
    if ((lpMemory = (LPTSTR)GlobalLock(hMemory)) == NULL)            // ??????????????
    {
        iRet = -4;
        goto _exit;
    }
    memcpy_s(lpMemory, contentSize, pcText, contentSize);   // ??????????????????????
    GlobalUnlock(hMemory);                   // ????????????
    if (SetClipboardData(CF_TEXT, hMemory) == NULL)
    {
        iRet = -5;
        goto _exit;
    }

_exit:
    CloseClipboard();

    return iRet;
}

static int CopyUnicodeTextToClip(wchar_t *pText)
{
    int iRet = 0;
    HGLOBAL hMemory;
    LPTSTR lpMemory;

    int contentSize = (wcslen(pText) + 1) * sizeof(wchar_t);

    if (!OpenClipboard(NULL))   // ????????????????????????????????????
    {
        return -1;
    }
    if (!EmptyClipboard())      // ??????????????????????????????????????
    {
        iRet = -2;
        goto _exit;
    }
    if ((hMemory = GlobalAlloc(GMEM_MOVEABLE, contentSize)) == NULL)   // ????????????????
    {
        iRet = -3;
        goto _exit;
    }
    if ((lpMemory = (LPTSTR)GlobalLock(hMemory)) == NULL)            // ??????????????
    {
        iRet = -4;
        goto _exit;
    }
    memcpy_s(lpMemory, contentSize, pText, contentSize);   // ??????????????????????
    GlobalUnlock(hMemory);                   // ????????????
    if (SetClipboardData(CF_UNICODETEXT, hMemory) == NULL)
    {
        iRet = -5;
        goto _exit;
    }

_exit:
    CloseClipboard();

    return iRet;
}


#define TIMER_ID_DEL_RECORD     0x1122
#define TIMER_ID_PASTE_RECORD   0x3344

static int OutputRecordFromListbox(HWND hListCtrl)
{
#if 0
    char czBuf[256];
    int iItemIndex[100];
    int iItemCnt;
    
    iItemCnt = ListBox_GetSelItems(hListCtrl, ARRAYSIZE(iItemIndex), iItemIndex);
    sprintf(czBuf, "sel=%d ", iItemCnt);
    for (int i = 0; i < iItemCnt; i++)
    {
        sprintf(czBuf + strlen(czBuf), " %d ", iItemIndex[i]);
    }
    MessageBox(hListCtrl, czBuf, "debug", MB_ICONINFORMATION | MB_OK);
#elif 0
    int iItemIndex[1000];
    int iItemCnt;
    
    iItemCnt = ListBox_GetSelItems(hListCtrl, ARRAYSIZE(iItemIndex), iItemIndex);
    for (int i = 0; i < iItemCnt; i++)
    {
        if (gb_quote)
        {
            g_clipx->misc_paste("\"");
        }
        g_clipx->misc_pasteHistoryItem(iItemIndex[i]);
        if (gb_quote)
        {
            g_clipx->misc_paste("\"");
        }

        if (gb_newline)
        {
            g_clipx->misc_paste("\r\n");
        }
    }
#else
    int iItemIndex[1000];
    int iItemCnt;
    char *pText;
    int iWideCharCnt;
    wchar_t *pwcText;
    
    iItemCnt = ListBox_GetSelItems(hListCtrl, ARRAYSIZE(iItemIndex), iItemIndex);
    if (iItemCnt <= 0)
    {
        return -1;
    }

    pText = (char*)calloc(iAllRecordTotalSize + 1, sizeof(char));
    if (!pText)
    {
        return -2;
    }

    pText[0] = 0;
    for (int i = 0; i < iItemCnt; i++)
    {
        if (IsDlgButtonChecked(ghMyDlg, IDC_CHECK_QUOTE_DLG))
        {
            strcat(pText, "\"");
        }

        if (IsDlgButtonChecked(ghMyDlg, IDC_CHECK_NEW_FIRST_DLG))
        {
            strcat(pText, g_clipx->history_getItemText(iItemIndex[i]));
        }
        else
        {
            strcat(pText, g_clipx->history_getItemText(iItemIndex[iItemCnt - i - 1]));
        }
        
        if (IsDlgButtonChecked(ghMyDlg, IDC_CHECK_QUOTE_DLG))
        {
            strcat(pText, "\"");
        }
        if (IsDlgButtonChecked(ghMyDlg, IDC_CHECK_NEWLINE_DLG))
        {
            strcat(pText, "\r\n");
        }
    }

    //utf8 to unicode
    iWideCharCnt = MultiByteToWideChar(CP_UTF8, 0, pText, -1, NULL, 0);
    pwcText = (wchar_t*)calloc(iWideCharCnt, sizeof(wchar_t));
    iWideCharCnt = MultiByteToWideChar(CP_UTF8, 0, pText, -1, pwcText, iWideCharCnt);

#if 0
    if (IsDlgButtonChecked(ghMyDlg, IDC_RADIO_PASTE_DLG))
    {
        //paste to box
        g_clipx->misc_paste(pText);
    }
    else if (IsDlgButtonChecked(ghMyDlg, IDC_RADIO_COPY_DLG))
    {
        //copy to clip
        CopyUnicodeTextToClip(pwcText);
    }
    else
    {
        //copy and paste
        CopyUnicodeTextToClip(pwcText);
        g_clipx->misc_paste(pText);
    }
#else
    //copy to clip
    CopyUnicodeTextToClip(pwcText);
    if (IsDlgButtonChecked(ghMyDlg, IDC_RADIO_PASTE_DLG))
    {
        //set paste timer        
        SetTimer(ghMyDlg, TIMER_ID_PASTE_RECORD, 200, NULL);
        //set del timer
        SetTimer(ghMyDlg, TIMER_ID_DEL_RECORD, 300, NULL);
    }
    else if (IsDlgButtonChecked(ghMyDlg, IDC_RADIO_COPY_DLG))
    {
        //nothing
    }
    else
    {
        //set paste timer        
        SetTimer(ghMyDlg, TIMER_ID_PASTE_RECORD, 200, NULL);
    }
#endif
    
    free(pText);
    free(pwcText);
#endif
    return 0;
}

// dialog operates only on temp values, the values are copied from the actual settings prior to running the dialog,
// and copied back to the actual settings when teh user clicks ok or apply
INT_PTR CALLBACK MyDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_INITDIALOG:
            return TRUE;
        case WM_USER+0x100:
        {
            return 0;
        }
            
        case WM_COMMAND:
        {
            int wNotifyCode = HIWORD(wParam);
            int wID = LOWORD(wParam);
            HWND hwndCtl = (HWND) lParam;

            switch (wID)
            {
                case IDOK:
                {
                    ShowWindow(hwndDlg, SW_HIDE);
                    OutputRecordFromListbox(GetDlgItem(hwndDlg, IDC_LIST_RECORD));
                    //EndDialog(hwndDlg, LOWORD(wParam));
                    return TRUE;
                }
                case IDCANCEL:
        		{
        			//EndDialog(hwndDlg, LOWORD(wParam));
        			ShowWindow(hwndDlg, SW_HIDE);
                    return TRUE;
        		}
            }
            break;
        }
        case WM_VKEYTOITEM:
        {
            int iVkey = LOWORD(wParam);
            if (iVkey == VK_RETURN)
            {
                SendMessage(hwndDlg, WM_COMMAND, MAKEWPARAM(IDOK, EN_CHANGE), (LPARAM)GetDlgItem(hwndDlg, IDOK));
            }
//            else if (iVkey == VK_UP)
//            {
//                int iIndex = ListBox_GetCurSel(GetDlgItem(hwndDlg, IDC_LIST_RECORD));
//                ListBox_SetSel(GetDlgItem(hwndDlg, IDC_LIST_RECORD), TRUE, iIndex-1);
//            }
//            else if (iVkey == VK_DOWN)
//            {
//                int iIndex = ListBox_GetCurSel(GetDlgItem(hwndDlg, IDC_LIST_RECORD));
//                ListBox_SetSel(GetDlgItem(hwndDlg, IDC_LIST_RECORD), TRUE, iIndex+1);
//            }
            else
            {
                //??listbox????
                return -1;
            }
            //????????
            return -2;
        }
        case WM_HOTKEY:
        {
            int iHotkeyID = wParam; 
            int iModifiers = LOWORD(lParam); 
            int iVKey = HIWORD(lParam);

            CheckDlgButton(hwndDlg, IDC_CHECK_NEWLINE_DLG, gb_newline ? BST_CHECKED : BST_UNCHECKED);
            CheckDlgButton(hwndDlg, IDC_CHECK_NEW_FIRST_DLG, gb_newfirst ? BST_CHECKED : BST_UNCHECKED);
            CheckDlgButton(hwndDlg, IDC_CHECK_QUOTE_DLG, gb_quote ? BST_CHECKED : BST_UNCHECKED);
            if (gb_paste && !gb_copy)
            {
                CheckRadioButton(hwndDlg, IDC_RADIO_PASTE_DLG, IDC_RADIO_PASTE_COPY_DLG, IDC_RADIO_PASTE_DLG);
            }
            else if (!gb_paste && gb_copy)
            {
                CheckRadioButton(hwndDlg, IDC_RADIO_PASTE_DLG, IDC_RADIO_PASTE_COPY_DLG, IDC_RADIO_COPY_DLG);
            }
            else
            {
                CheckRadioButton(hwndDlg, IDC_RADIO_PASTE_DLG, IDC_RADIO_PASTE_COPY_DLG, IDC_RADIO_PASTE_COPY_DLG);
            }

            FillRecordToListbox(GetDlgItem(hwndDlg, IDC_LIST_RECORD));
            ListBox_SetSel(GetDlgItem(hwndDlg, IDC_LIST_RECORD), TRUE, 0);
            //ListBox_SetHorizontalExtent(GetDlgItem(hwndDlg, IDC_LIST_RECORD), 1000);    //??????????????
            ShowWindow(hwndDlg, SW_SHOW);
            UpdateWindow(hwndDlg);  //????????????
            SetForegroundWindow(hwndDlg);
            SetFocus(GetDlgItem(hwndDlg, IDC_LIST_RECORD));
            break;
        }
        case WM_TIMER:
        {
            int iTimerID = wParam;
            
            if (iTimerID == TIMER_ID_DEL_RECORD)
            {
                g_clipx->history_deleteItem(0);
                KillTimer(ghMyDlg, TIMER_ID_DEL_RECORD);
            }
            else if (iTimerID == TIMER_ID_PASTE_RECORD)
            {
            #if 0
                g_clipx->misc_pasteHistoryItem(0);
            #else
                keybd_event(VK_LCONTROL, 0, 0 ,0);
                keybd_event('V', 0, 0 ,0);
                keybd_event('V', 0, KEYEVENTF_KEYUP,0);
                keybd_event(VK_LCONTROL, 0, KEYEVENTF_KEYUP,0);
                KillTimer(ghMyDlg, TIMER_ID_PASTE_RECORD);
            #endif
            }
            else
            {
                return TRUE;
            }
            return 0;
        }
    
        case WM_CLOSE:
    	{
    		//PostQuitMessage(1);
    		//EndDialog(hwndDlg, LOWORD(wParam));
    		//return TRUE;
    		break;
    	}
        case WM_DESTROY:
            //g_last_dlg = NULL;
            break;
    }
    return 0;
}

//hotkey_encode has problem
static WORD HotkeyCodeExchange(int iVkey, int iModifiers)
{
    int iModTmp = 0;
    if (iModifiers & MOD_CONTROL)
    {
        iModTmp |= HOTKEYF_CONTROL;
    }
    if (iModifiers & MOD_ALT)
    {
        iModTmp |= HOTKEYF_ALT;
    }
    if (iModifiers & MOD_SHIFT)
    {
        iModTmp |= HOTKEYF_SHIFT;
    }
//    if (iModifiers & MOD_WIN)
//    {
//        iModTmp |= HOTKEYF_WIN;
//    }

    return MAKEWORD(iVkey, iModTmp);
}

// dialog operates only on temp values, the values are copied from the actual settings prior to running the dialog,
// and copied back to the actual settings when teh user clicks ok or apply
INT_PTR CALLBACK dlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_INITDIALOG:
        {
            g_last_dlg = hwndDlg;
            CheckDlgButton(hwndDlg, IDC_CHECK_ENABLE, tb_enabled ? BST_CHECKED : BST_UNCHECKED);
        
            // Set rules for invalid key combinations. If the user does not supply a
            // modifier key, use ALT as a modifier. If the user supplies SHIFT as a 
            // modifier key, use SHIFT + ALT instead.
            SendMessage(GetDlgItem(hwndDlg, IDC_HOTKEY_POPUP), 
                        HKM_SETRULES, 
                        (WPARAM) HKCOMB_NONE | HKCOMB_S,   // invalid key combinations 
                        MAKELPARAM(HOTKEYF_ALT, 0));       // add ALT to invalid entries 
            // Set default hot key for this window.
            WORD wHotkey = HotkeyCodeExchange(ti_hotkey_vk, ti_hotkey_mod);
            //WORD wHotkey = MAKEWORD(0x41, HOTKEYF_CONTROL | HOTKEYF_ALT);
            SendMessage(GetDlgItem(hwndDlg, IDC_HOTKEY_POPUP), HKM_SETHOTKEY, wHotkey, 0);

            CheckDlgButton(hwndDlg, IDC_CHECK_NEWLINE, tb_newline ? BST_CHECKED : BST_UNCHECKED);
            CheckDlgButton(hwndDlg, IDC_CHECK_NEW_FIRST, tb_newfirst ? BST_CHECKED : BST_UNCHECKED);
            CheckDlgButton(hwndDlg, IDC_CHECK_QUOTE, tb_quote ? BST_CHECKED : BST_UNCHECKED);
            if (gb_paste && !gb_copy)
            {
                //CheckDlgButton(hwndDlg, IDC_RADIO_PASTE_TO_BOX, BST_CHECKED);
                CheckRadioButton(hwndDlg, IDC_RADIO_PASTE_TO_BOX, IDC_RADIO_PASTE_COPY, IDC_RADIO_PASTE_TO_BOX);
            }
            else if (!gb_paste && gb_copy)
            {
                //CheckDlgButton(hwndDlg, IDC_RADIO_COPY_TO_CLIP, BST_CHECKED);
                CheckRadioButton(hwndDlg, IDC_RADIO_PASTE_TO_BOX, IDC_RADIO_PASTE_COPY, IDC_RADIO_COPY_TO_CLIP);
            }
            else
            {
                //CheckDlgButton(hwndDlg, IDC_RADIO_PASTE_COPY, BST_CHECKED);
                CheckRadioButton(hwndDlg, IDC_RADIO_PASTE_TO_BOX, IDC_RADIO_PASTE_COPY, IDC_RADIO_PASTE_COPY);
            }
            
            updateVisibility(hwndDlg);
            return TRUE;
        }
        case WM_USER+0x100:
            tb_enabled = gb_enabled;
            CheckDlgButton(hwndDlg, IDC_CHECK_ENABLE, tb_enabled ? BST_CHECKED : BST_UNCHECKED);
            updateVisibility(hwndDlg);
            return 0;
        case WM_COMMAND:
        {
            int wNotifyCode = HIWORD(wParam);
            int wID = LOWORD(wParam);
            HWND hwndCtl = (HWND) lParam;
            switch (wID)
            {
                case IDC_CHECK_ENABLE:
                    tb_enabled = IsDlgButtonChecked(hwndDlg, wID);
                    updateVisibility(hwndDlg);
                    g_clipx->config_allowApply();
                    return 0;

                case IDC_CHECK_NEWLINE:
                    tb_newline = IsDlgButtonChecked(hwndDlg, wID);
                    updateVisibility(hwndDlg);
                    g_clipx->config_allowApply();
                    return 0;
                case IDC_CHECK_NEW_FIRST:
                    tb_newfirst = IsDlgButtonChecked(hwndDlg, wID);
                    updateVisibility(hwndDlg);
                    g_clipx->config_allowApply();
                    return 0;
                case IDC_CHECK_QUOTE:
                    tb_quote = IsDlgButtonChecked(hwndDlg, wID);
                    updateVisibility(hwndDlg);
                    g_clipx->config_allowApply();
                    return 0;
                case IDC_RADIO_PASTE_TO_BOX:
                    if (IsDlgButtonChecked(hwndDlg, wID))
                    {
                        tb_paste = 1;
                        tb_copy = 0;
                    }
                    updateVisibility(hwndDlg);
                    g_clipx->config_allowApply();
                    return 0;
                case IDC_RADIO_COPY_TO_CLIP:
                    if (IsDlgButtonChecked(hwndDlg, wID))
                    {
                        tb_paste = 0;
                        tb_copy = 1;
                    }
                    updateVisibility(hwndDlg);
                    g_clipx->config_allowApply();
                    return 0;
                case IDC_RADIO_PASTE_COPY:
                    if (IsDlgButtonChecked(hwndDlg, wID))
                    {
                        tb_paste = 1;
                        tb_copy = 1;
                    }
                    updateVisibility(hwndDlg);
                    g_clipx->config_allowApply();
                    return 0;                   
                    
                case IDC_HOTKEY_POPUP:
                    if (wNotifyCode == EN_CHANGE)
                    {
                        int iModifiers = 0; 
                        int iVKey = 0;
                        WORD wHotkey;  

                        wHotkey = (WORD) SendMessage(GetDlgItem(hwndDlg, IDC_HOTKEY_POPUP), HKM_GETHOTKEY, 0, 0); 
                        g_clipx->hotkey_decode(&iVKey, &iModifiers, wHotkey);
                        ti_hotkey_mod = iModifiers;
                        ti_hotkey_vk = iVKey;
                        g_clipx->config_allowApply();
                    }
                    break;
            }
            break;
        }
        case WM_DESTROY:
            g_last_dlg = NULL;
            break;
    }
    return 0;
}

// create the sub dialog
HWND SampleConfigPage::createPage(HWND parent)
{
    return CreateDialog(the->getOSModuleHandle(), MAKEINTRESOURCE(IDD_CONFIGPAGE), parent, dlgProc);
}

