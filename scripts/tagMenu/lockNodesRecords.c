tagMenu: lockNodesRecords
#
#Capture the password for comparrison and to return
#the password field back to if the user fails to get the
#password right.
Set Variable [ $password; Value:tagMenus::orderOrLock ]
Set Field [ TEMP::nodeLock; "" ]
Go to Field [ ]
#
#If there is a password, ask user to enter it.
If [ tagMenus::orderOrLock ≠ "" ]
Loop
Show Custom Dialog [ Message: "Enter the password to unlock this nodes records."; Buttons: “enter”, “cancel”; Input #1: TEMP::nodeLock, Password ]
If [ Get ( LastMessageChoice ) = 2 ]
Set Field [ TEMP::nodeLock; "" ]
Exit Script [ ]
End If
If [ $password = TEMP::nodeLock ]
Show Custom Dialog [ Message: "unlocked"; Buttons: “OK” ]
Set Field [ tagMenus::orderOrLock; "" ]
Set Field [ TEMP::nodeLock; "" ]
Exit Script [ ]
End If
End Loop
#
#If there is no password, ask user to create one.
Else If [ tagMenus::orderOrLock = "" ]
Set Field [ TEMP::nodeLock; "" ]
Show Custom Dialog [ Message: "Enter a password to lock this node's records. WARNING: If you can't remember this password, your records will remain locked."; Buttons: “enter”, “cancel”; Input #1: tagMenus::orderOrLock, Password, "password"; Input #2: TEMP::nodeLock, Password,
"confirm password" ]
If [ Get ( LastMessageChoice ) = 2 ]
Set Field [ tagMenus::orderOrLock; "" ]
End If
Loop
If [ tagMenus::orderOrLock ≠ TEMP::nodeLock ]
Show Custom Dialog [ Message: "Passwords did not match."; Buttons: “enter”, “cancel”; Input #1: tagMenus::orderOrLock, Password, "password"; Input #2: TEMP::nodeLock, Password, "confirm password" ]
If [ Get ( LastMessageChoice ) = 2 ]
Set Field [ tagMenus::orderOrLock; "" ]
Exit Script [ ]
End If
End If
Exit Loop If [ tagMenus::orderOrLock = TEMP::nodeLock ]
End Loop
End If
January 7, 平成26 16:46:59 Imagination Quality Management.fp7 - lockNodesRecords -1-
