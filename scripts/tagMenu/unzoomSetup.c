tagMenu: unzoomSetup
Move/Resize Window [ Current Window; Height: Get (ScreenHeight); Width: 700; Top: 0; Left: 0 ]
Set Variable [ $left; Value:Get ( WindowLeft ) ]
Set Variable [ $width; Value:Get ( WindowWidth) ]
Set Zoom Level
[ 100% ]
Select Window [ Name: "Tag Menus"; Current file ]
If [ Get (LastError) = 112 ]
New Window [ Name: "Tag Menus"; Width: 333; Left: 0 ]
Go to Layout [ “setupTestFocus” (tagLocation) ]
End If
Set Zoom Level
[ 100% ]
Move/Resize Window [ Current Window; Height: Get (ScreenHeight); Width: 333; Top: 0; Left: If ( $left + $width + 333 > Get ( ScreenWidth ) ; Get ( ScreenWidth ) - 333 ; $left + $width ) ]
Select Window [ Name: "Setup"; Current file ]
January 7, 平成26 15:37:44 Imagination Quality Management.fp7 - unzoomSetup -1-
