#include <Vis2>

    file=%a_scriptdir%\image.png

    WinGetActiveTitle, title
    WinGet, hwnd,id,League of Legends
   
    pToken := Gdip_Startup()
    pBitmap := Gdip_BitmapFromHWND(hwnd)
    
    pBitmap2 := Gdip_CloneBitmapArea(pBitmap,1122,23,150,56)

    MsgBox % OCR(pBitmap2,"eng+kor")

    Gdip_SaveBitmapToFile(pBitmap2,file)
    Gdip_DisposeImage(pBitmap)
    Gdip_DisposeImage(pBitmap2)
    Gdip_Shutdown(pToken)


Return

