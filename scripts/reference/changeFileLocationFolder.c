January 21, 2018 12:10:47 Library.fmp12 - changeFileLocationFolder -1-
reference: changeFileLocationFolder
If [ reference::kfileLocation = TEMP::ReferenceFolder ]
Show Custom Dialog [ Message: "Delete file folder location?"; Default Button: “yes”, Commit: “Yes”; Button 2: “cancel”, Commit:
“No” ]
If [ Get (LastMessageChoice) = 1 ]
Set Field [ reference::kfileLocation; "" ]
End If
End If
Set Field [ TEMP::ReferenceFolder; reference::kfileLocation ]
Go to Field [ ]
