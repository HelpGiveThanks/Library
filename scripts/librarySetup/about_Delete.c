July 24, 2018 17:37:45 Library.fmp12 - about_Delete -1-
librarySetup: about_Delete
#
#
#Stop script if there are no records to lock.
If [ Get (FoundCount) = 0 ]
Exit Script [ ]
End If
#
#
#If there is a password, the delete (x) button
#is invisible, but it can still be clicked, so its
#important to stop this script.
If [ aboutLibraryMain::password[2] ≠ "" ]
Exit Script [ ]
End If
#
#
#If record's creator node is locked, tell the
#user it's locked, but the record can still be
#deleted or edited because it is not locked.
If [ aboutLibraryCreator::orderOrLock ≠ "" ]
Show Custom Dialog [ Message: "The creator node — " & aboutLibraryCreator::tag & " — is locked. HOWEVER, the lock for
these about records are separate from their creator's lock, so you can edit and delete it."; Default Button: “OK”, Commit:
“Yes” ]
End If
#
#
#Make sure the user wants to delete
#the record.
Show Custom Dialog [ Message: "Delete this library about record?"; Default Button: “Cancel”, Commit: “Yes”; Button 2: “OK”, Commit:
“No” ]
#
#
#If user cancels delete, exit script.
If [ Get ( LastMessageChoice ) = 1 ]
Go to Field [ ]
Exit Script [ ]
End If
#
#
#Delete the record.
Delete Record/Request
[ No dialog ]
#
#
#Close the Review Reference window if open.
If [ Get (WindowName) = "About"
 or
Get (WindowName) = "Edit About" ]
Close Window [ Current Window ]
Halt Script
End If
#
#
