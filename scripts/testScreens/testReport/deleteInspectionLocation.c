testScreens: testReport: deleteInspectionLocation
If [ tagTestSubjectLocation::_LtestSubjectLocation = "" ]
Halt Script
End If
If [ tagTestSubjectLocation::inUse = "t" ]
Show Custom Dialog [ Message: "Delete all test results made in this test section before deleting it. To do this, click its green test button. Click on each test item. Delete the results you find."; Buttons: “OK” ]
Exit Script [ ]
End If
Set Variable [ $delete; Value:tagTestSubjectLocation::_LtestSubjectLocation ]
Set Variable [ $location; Value:tagTestSubjectLocation::kfocus ]
Go to Field [ ]
Refresh Window
Show Custom Dialog [ Message: "Delete test section " & tagTestSubjectLocation::focusName & " for " & tagTestSubject::tag & "'s test #" & tagTestSubjectLocation::reportNumber & "?"; Buttons: “Cancel”, “Delete” ]
If [ Get ( LastMessageChoice ) = 2 ]
Delete Record/Request
[ No dialog ]
End If
Go to Layout [ original layout ]
Set Variable [ $delete ]
Refresh Window
July 11, 平成27 11:08:18 Library.fp7 - deleteInspectionLocation -1-
