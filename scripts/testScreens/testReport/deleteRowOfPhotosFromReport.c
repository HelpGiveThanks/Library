testScreens: testReport: DeleteRowOfPhotosFromReport
#
If [ Get (RecordNumber) = 1 ]
Exit Script [ ]
End If
If [ report::_kfPhoto ≠ "" or
report::_kfPhoto2 ≠ "" or
report::_kfPhoto3 ≠ "" or
report::_kfPhoto4 ≠ "" ]
Show Custom Dialog [ Title: "!"; Message: "You may delete this row only after clearing all photo slots."; Buttons: “OK” ]
Halt Script
End If
Set Variable [ $delete; Value:Get (RecordNumber) ]
Refresh Window
Show Custom Dialog [ Message: "Delete this row of photos?"; Buttons: “cancel”, “OK” ]
If [ Get ( LastMessageChoice ) = 2 ]
Delete Record/Request
[ No dialog ]
End If
Set Variable [ $delete ]
Refresh Window
#
January 7, 平成26 14:29:48 Imagination Quality Management.fp7 - DeleteRowOfPhotosFromReport -1-
