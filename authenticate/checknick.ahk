#include <Vis2>

    file=%a_scriptdir%\image.png

    WinGetActiveTitle, title
    WinGet, hwnd,id,League of Legends
   
    pToken := Gdip_Startup()
    pBitmap := Gdip_BitmapFromHWND(hwnd)
    
    pBitmap2 := Gdip_CloneBitmapArea(pBitmap,1122,23,140,26)

    string := OCR(pBitmap2,"eng+kor")
    FileDelete,%A_ScriptDir%\nick.txt
    FileAppend,%string%,%A_ScriptDir%\nick.txt

    Gdip_SaveBitmapToFile(pBitmap2,file)
    Gdip_DisposeImage(pBitmap)
    Gdip_DisposeImage(pBitmap2)
    Gdip_Shutdown(pToken)

exitapp
Return

