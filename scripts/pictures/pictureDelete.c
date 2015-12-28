pictures: pictureDelete
Allow User Abort [ Off ]
Set Error Capture [ On ]
If [ reference::picture ≠ "" and reference::lock = "" or
reference::picture = "" and reference::lock = "" and reference::showMedia ≠ "" and reference::URL ≠ "" ]
Show Custom Dialog [ Message: "Delete current picture?"; Buttons: “Cancel”, “OK” ]
If [ Get ( LastMessageChoice ) = 1 ]
Go to Field [ ]
Exit Script [ ]
Else If [ Get ( LastMessageChoice ) = 2 ]
Set Field [ reference::picture; "" ]
Set Field [ reference::showMedia; "" ]
Close Window [ Current Window ]
Halt Script
End If
Else If [ testlearn::Picture ≠ "" ]
Show Custom Dialog [ Message: "Delete current picture?"; Buttons: “Cancel”, “OK” ]
If [ Get ( LastMessageChoice ) = 1 ]
Go to Field [ ]
Exit Script [ ]
Else If [ Get ( LastMessageChoice ) = 2 ]
Set Field [ testlearn::Picture; "" ]
Close Window [ Current Window ]
Halt Script
End If
Else If [ testlearnReportTags::Picture ≠ "" ]
Show Custom Dialog [ Message: "Delete current picture?"; Buttons: “Cancel”, “OK” ]
If [ Get ( LastMessageChoice ) = 1 ]
Go to Field [ ]
Exit Script [ ]
Else If [ Get ( LastMessageChoice ) = 2 ]
Set Field [ testlearnReportTags::Picture; "" ]
Close Window [ Current Window ]
Halt Script
End If
End If
#
#
December 27, ଘ౮27 19:31:27 Library.fp7 - pictureDelete -1-
