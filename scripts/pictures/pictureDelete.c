pictures: pictureDelete
Allow User Abort [ Off ]
Set Error Capture [ On ]
If [ reference::picture ≠ "" and reference::lock = "" ]
Show Custom Dialog [ Message: "Delete current picture?"; Buttons: “Cancel”, “OK” ]
If [ Get ( LastMessageChoice ) = 1 ]
Go to Field [ ]
Exit Script [ ]
Else If [ Get ( LastMessageChoice ) = 2 ]
Set Field [ reference::picture; "" ]
// Close Window [ Current Window ]
// Exit Script [ ]
// Halt Script
End If
Else If [ testlearn::Picture ≠ "" ]
Show Custom Dialog [ Message: "Delete current picture?"; Buttons: “Cancel”, “OK” ]
If [ Get ( LastMessageChoice ) = 1 ]
Go to Field [ ]
Exit Script [ ]
Else If [ Get ( LastMessageChoice ) = 2 ]
Set Field [ testlearn::Picture; "" ]
// Close Window [ Current Window ]
// Exit Script [ ]
// Halt Script
End If
Else If [ testlearnReportTags::Picture ≠ "" ]
Show Custom Dialog [ Message: "Delete current picture?"; Buttons: “Cancel”, “OK” ]
If [ Get ( LastMessageChoice ) = 1 ]
Go to Field [ ]
Exit Script [ ]
Else If [ Get ( LastMessageChoice ) = 2 ]
Set Field [ testlearnReportTags::Picture; "" ]
// Close Window [ Current Window ]
// Exit Script [ ]
// Halt Script
End If
End If
#
#
January 7, 平成26 17:05:41 Imagination Quality Management.fp7 - pictureDelete -1-
