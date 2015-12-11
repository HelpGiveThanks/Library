testScreens: test: probablyNotInUse: returnToStep2
Go to Layout [ “defaultSetup” (tempSetup) ]
Set Window Title [ Current Window; New Title: "Setup" ]
#
#Make sure window to fills half of the screen.
Move/Resize Window [ Current Window; Height: Get (ScreenHeight); Width: Get (ScreenWidth) / 2; Top: 0; Left: 0 ]
#
#goto Tag Menus window
Select Window [ Name: "Tag Menus"; Current file ]
If [ Get (LastError) = 112 ]
New Window [ Name: "Tag Menus"; Height: Get (ScreenHeight); Width: Get (ScreenWidth) / 2; Top: 0; Left: Get (ScreenWidth) /
2 ]
End If
#
#Make sure window to fills half of the screen.
Move/Resize Window [ Current Window; Height: Get (ScreenHeight); Width: Get (ScreenWidth) / 2; Top: 0; Left: Get (ScreenWidth) /
2 ]
#
Go to Layout [ “defaultTest” (tagTestSubjectLocation) ]
Perform Script [ “defaultTestLocationMenu” ]
#
Go to Record/Request/Page [ $$TSRecordNumber ]
[ No dialog ]
Set Variable [ $$TSRecordNumber ]
December 11, ଘ౮27 1:32:32 Library.fp7 - returnToStep2 -1-
