testScreens: test: returnToStep2
#
#If on test screen, see if any sections have results.
If [ Get (LayoutName) = "step3_InspectionItems" ]
Set Variable [ $testInUseCheck; Value:1 ]
Go to Record/Request/Page
[ First ]
Loop
If [ tlResults::InspectionItemCountLocation ≠ "" ]
Set Variable [ $InUse; Value:1 ]
End If
Exit Loop If [ tlResults::InspectionItemCountLocation ≠ "" ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
End If
#
#
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
#
If [ $InUse = "" and $testInUseCheck = 1 ]
Set Field [ tagTestSubjectLocation::inUse; "" ]
Else If [ $InUse = 1 and $testInUseCheck = 1 ]
Set Field [ tagTestSubjectLocation::inUse; "t" ]
End If
December 15, ଘ౮27 15:14:38 Library.fp7 - returnToStep2 -1-
