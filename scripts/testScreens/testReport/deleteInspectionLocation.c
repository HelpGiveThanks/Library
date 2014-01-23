testScreens: testReport: DeleteInspectionLocation
If [ tagTestSubjectLocation::_LtestSubjectLocation = "" ]
Halt Script
End If
If [ tagTestSubjectLocation::inUse = "t" ]
Show Custom Dialog [ Title: "!"; Message: "Deleting this set of test items is allowed after you delete all discoveries made during testing."; Buttons: “OK” ]
Exit Script [ ]
End If
Set Variable [ $delete; Value:tagTestSubjectLocation::_LtestSubjectLocation ]
Set Variable [ $location; Value:tagTestSubjectLocation::kfocus ]
Go to Field [ ]
Refresh Window
Show Custom Dialog [ Title: "!"; Message: "Delete " & tagTestSubject::tag & "'s " & "test number " & tagTestSubjectLocation::reportNumber & " of " & tagTestSubjectLocation::focusName & "?"; Buttons: “Cancel”, “Delete” ]
If [ Get ( LastMessageChoice ) = 2 ]
Delete Record/Request
[ No dialog ]
End If
Go to Layout [ original layout ]
Set Variable [ $delete ]
Refresh Window
January 7, 平成26 14:16:54 Imagination Quality Management.fp7 - DeleteInspectionLocation -1-
