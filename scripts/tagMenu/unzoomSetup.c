January 21, 2018 11:56:40 Library.fmp12 - unzoomSetup -1-
tagMenu: unzoomSetup
Move/Resize Window [ Current Window; Height: Get (ScreenHeight); Width: 700; Top: 0; Left: 0 ]
Set Variable [ $left; Value:Get ( WindowLeft ) ]
Set Variable [ $width; Value:Get ( WindowWidth) ]
Set Zoom Level [ 100%; Camera: Back; Resolution: Full ]
Select Window [ Name: "Tag Menus"; Current file ]
If [ Get (LastError) = 112 ]
New Window [ Name: "Tag Menus"; Width: 333; Left: 0; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom
Control Area: “Yes”; Resize: “Yes” ]
Go to Layout [ “setupTestSection” (testSection) ]
End If
Set Zoom Level [ 100%; Camera: Back; Resolution: Full ]
Move/Resize Window [ Current Window; Height: Get (ScreenHeight); Width: 333; Top: 0; Left: If ( $left + $width + 333 > Get
( ScreenWidth ) ; Get ( ScreenWidth ) - 333 ; $left + $width ) ]
Select Window [ Name: "Setup"; Current file ]
