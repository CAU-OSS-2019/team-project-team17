#include <Vis2>
#Include Search_img.ahk
#Include Gdip_ImageSearch.ahk

    file=%a_scriptdir%\image.png

    WinGetActiveTitle, title
    WinGet, hwnd,id,League of Legends
   


controlclick,x1174 y97,League of Legends

sleep,500

controlclick,x459 y238,League of Legends

sleep,500


N:=(97*65536)+1174
postmessage,0x200,0,%N%,Chrome_RenderWidgetHostHWND1,League of Legends

postmessage,0x201,1,%N%,Chrome_RenderWidgetHostHWND1,League of Legends

postmessage,0x202,0,%N%,Chrome_RenderWidgetHostHWND1,League of Legends

sleep,500

N:=(238*65536)+459
postmessage,0x200,0,%N%,Chrome_RenderWidgetHostHWND1,League of Legends

postmessage,0x201,1,%N%,Chrome_RenderWidgetHostHWND1,League of Legends

postmessage,0x202,0,%N%,Chrome_RenderWidgetHostHWND1,League of Legends

sleep,500

Send,^v


N:=(239*65536)+875
postmessage,0x200,0,%N%,Chrome_RenderWidgetHostHWND1,League of Legends

postmessage,0x201,1,%N%,Chrome_RenderWidgetHostHWND1,League of Legends

postmessage,0x202,0,%N%,Chrome_RenderWidgetHostHWND1,League of Legends

sleep,500

N:=(603*65536)+639
postmessage,0x200,0,%N%,Chrome_RenderWidgetHostHWND1,League of Legends

postmessage,0x201,1,%N%,Chrome_RenderWidgetHostHWND1,League of Legends

postmessage,0x202,0,%N%,Chrome_RenderWidgetHostHWND1,League of Legends

sleep,500