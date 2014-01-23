probablyNotInUse: testScreens: testReport: DeleteInspectionComplement
If [ test::_Ltest = "" ]
Halt Script
End If
Set Variable [ $deleteComp; Value:<Table Missing>::<Field Missing> ]
Set Variable [ $name; Value:<Table Missing>::<Field Missing> ]
Refresh Window
Show Custom Dialog [ Title: "!"; Message: "Delete " & $name & "?"; Buttons: “Cancel”, “Delete” ]
If [ Get ( LastMessageChoice ) = 2 ]
Delete Portal Row
[ No dialog ]
End If
Set Variable [ $deleteComp ]
Refresh Window
January 7, 平成26 14:22:57 Imagination Quality Management.fp7 - DeleteInspectionComplement -1-
