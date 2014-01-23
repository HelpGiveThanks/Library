tagMenu: zoomSetup
Move/Resize Window [ Current Window; Height: Get (ScreenHeight); Width: 700; Top: 0; Left: 0 ]
Set Variable [ $left; Value:Get ( WindowLeft ) ]
Set Variable [ $width; Value:Get ( WindowWidth) ]
Set Zoom Level
[ 150% ]
Select Window [ Name: "Tag Menus"; Current ﬁle ]
If [ Get (LastError) = 112 ]
New Window [ Name: "Tag Menus" ]
Go to Layout [ “setupTestFocus” (tagLocation) ]
End If
Set Zoom Level
[ 150% ]
Move/Resize Window [ Current Window; Height: Get (ScreenHeight); Width: 490; Top: 0; Left: If ( $left + $width > Get ( ScreenWidth ) - 490; Get ( ScreenWidth ) - 490 ; $left + $width ) ]
Select Window [ Name: "Setup"; Current ﬁle ]
January 7, 平成26 15:55:23 Imagination Quality Management.fp7 - zoomSetup -1-
