testScreens: testReport: DeleteInspectionSetupItem
If [ test::_Ltest = "" ]
Halt Script
End If
Set Variable [ $deleteItem; Value:test::_Ltest ]
Set Variable [ $name; Value:test::testName ]
Refresh Window
Show Custom Dialog [ Title: "!"; Message: "Delete " & $name & "?"; Buttons: “Cancel”, “Delete” ]
If [ Get ( LastMessageChoice ) = 2 ]
Delete Portal Row
[ No dialog ]
End If
Set Variable [ $deleteItem ]
Refresh Window
January 7, 平成26 14:22:29 Imagination Quality Management.fp7 - DeleteInspectionSetupItem -1-
