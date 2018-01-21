January 21, 2018 11:57:24 Library.fmp12 - zoomSetup -1-
tagMenu: zoomSetup
Move/Resize Window [ Current Window; Height: Get (ScreenHeight); Width: 700; Top: 0; Left: 0 ]
Set Variable [ $left; Value:Get ( WindowLeft ) ]
Set Variable [ $width; Value:Get ( WindowWidth) ]
Set Zoom Level [ 150% ]
Select Window [ Name: "Tag Menus"; Current file ]
If [ Get (LastError) = 112 ]
New Window [ Name: "Tag Menus"; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”;
Resize: “Yes” ]
Go to Layout [ “setupTestSection” (testSection) ]
End If
Set Zoom Level [ 150% ]
Move/Resize Window [ Current Window; Height: Get (ScreenHeight); Width: 490; Top: 0; Left: If ( $left + $width > Get ( ScreenWidth )
- 490; Get ( ScreenWidth ) - 490 ; $left + $width ) ]
Select Window [ Name: "Setup"; Current file ]
