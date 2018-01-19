reference(citation): changeFileLocationFolder
If [ reference::kfileLocation = TEMP::ReferenceFolder ]
Show Custom Dialog [ Message: "Delete file folder location?"; Buttons: “yes”, “cancel” ]
If [ Get (LastMessageChoice) = 1 ]
Set Field [ reference::kfileLocation; "" ]
End If
End If
Set Field [ TEMP::ReferenceFolder; reference::kfileLocation ]
Go to Field [ ]
August 20, ଘ౮28 14:45:19 Library.fp7 - changeFileLocationFolder -1-
