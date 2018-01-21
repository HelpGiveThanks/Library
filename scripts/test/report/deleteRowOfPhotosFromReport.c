January 21, 2018 10:59:02 Library.fmp12 - deleteRowOfPhotosFromReport -1-
test: report: deleteRowOfPhotosFromReport
#
If [ Get (RecordNumber) = 1 ]
Exit Script [ ]
End If
If [ report::kTag1 ≠ "" or
report::kTag2 ≠ "" or
report::kTag3 ≠ "" or
report::kTag4 ≠ "" ]
Show Custom Dialog [ Title: "!"; Message: "You may delete this row only after clearing all photo slots."; Default Button: “OK”,
Commit: “Yes” ]
Halt Script
End If
Set Variable [ $delete; Value:Get (RecordNumber) ]
Refresh Window
Show Custom Dialog [ Message: "Delete this row of photos?"; Default Button: “cancel”, Commit: “Yes”; Button 2: “OK”, Commit: “No” ]
If [ Get ( LastMessageChoice ) = 2 ]
Delete Record/Request
[ No dialog ]
End If
Set Variable [ $delete ]
Refresh Window
#
