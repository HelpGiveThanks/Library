tagMenu: Lock
If [ nodeLockTagGroup::orderOrLock = "lock" ]
Go to Field [ ]
Show Custom Dialog [ Message: "Type the following into the box below to unlock all content created by " & nodeLockTagGroup::tag; Buttons: “OK”, “Cancel” ]
Halt Script
End If
January 7, 平成26 16:45:29 Imagination Quality Management.fp7 - Lock -1-
