January 21, 2018 11:49:18 Library.fmp12 - lock -1-
tagMenu: lock
If [ nodeLockTagGroupCreatorLock::orderOrLock = "lock" ]
Go to Field [ ]
Show Custom Dialog [ Message: "Type the following into the box below to unlock all content created by " &
nodeLockTagGroupCreatorLock::tag; Default Button: “OK”, Commit: “Yes”; Button 2: “Cancel”, Commit: “No” ]
Halt Script
End If
