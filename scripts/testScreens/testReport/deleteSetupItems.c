January 15, 2018 16:02:05 Library.fmp12 - deleteSetupItems -1-
test: report: probablyNotInUse: deleteSetupItems
Go to Object [ Object Name: "item" ]
If [ testSubsectionTemplate::_LtestSubsection ≠ "" ]
Show Custom Dialog [ Title: "!"; Message: "You can delete this record only after you delete all items assigned to this subsection
in these sections."; Default Button: “OK”, Commit: “Yes” ]
Go to Field [ ]
Halt Script
End If
Go to Field [ ]
Delete Record/Request
