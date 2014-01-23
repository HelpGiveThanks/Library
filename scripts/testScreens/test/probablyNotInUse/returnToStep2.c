testScreens: test: probablyNotInUse: returnToStep2
Go to Layout [ “defaultSetup” (tempSetup) ]
Set Window Title [ Current Window; New Title: "Setup" ]
Move/Resize Window [ Current Window; Height: Get (ScreenHeight); Width: Get (ScreenWidth) / 2; Top: 0; Left: 0 ]
#
#goto Tag Menus window
Select Window [ Name: "Tag Menus"; Current ﬁle ]
If [ Get (LastError) = 112 ]
New Window [ Name: "Tag Menus"; Height: Get (ScreenHeight); Width: Get (ScreenWidth) / 2; Top: 0; Left: Get (ScreenWidth) / 2 ]
End If
#
Go to Layout [ “defaultTest” (tagTestSubjectLocation) ]
Perform Script [ “defaultTestLocationMenu” ]
#
Go to Record/Request/Page [ $$TSRecordNumber ]
[ No dialog ]
Set Variable [ $$TSRecordNumber ]
January 7, 平成26 12:32:16 Imagination Quality Management.fp7 - returnToStep2 -1-
