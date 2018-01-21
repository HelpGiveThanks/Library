January 18, 2018 16:00:19 Library.fmp12 - stopLockedRecordsFromBeingDeleted -1-
sharedLayoutScripts: stopLockedRecordsFromBeingDeleted
#
#If node is currenlty locked then stop script,
#and inform the user.
If [ tagCreatorLock::orderOrLock ≠ "" ]
Show Custom Dialog [ Message: "This record is locked. Go the node that created it — " & tagCreatorLock::tag & " — in the
setup tag window and enter the password to unlock it."; Default Button: “OK”, Commit: “Yes” ]
Halt Script
End If
#
