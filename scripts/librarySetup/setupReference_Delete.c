January 25, 2018 10:23:17 CODELibrary.fmp12 - setupReference_Delete -1-
librarySetup: setupReference_Delete
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
If [ librarySetupReferenceMain::password[2] ≠ "" ]
Exit Script [ ]
End If
#
#
#If record's creator node is locked, tell the
#user it's locked, but the record can still be
#deleted or edited because it is not locked.
If [ librarySetupCreator::orderOrLock ≠ "" ]
Show Custom Dialog [ Message: "This library setup-reference's creator node — " & librarySetupCreator::tag & " — is locked.
HOWEVER, the lock for these setup-reference records are separate from their creator's lock, so you can edit and delete it.";
Default Button: “OK”, Commit: “Yes” ]
End If
#
#
#Make sure the user wants to delete
#the record.
Show Custom Dialog [ Message: "Delete this library setup-reference?"; Default Button: “Cancel”, Commit: “Yes”; Button 2: “OK”,
Commit: “No” ]
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
If [ Get (WindowName) = "Review Reference"
 or
Get (WindowName) = "Edit Reference" ]
Close Window [ Current Window ]
Halt Script
End If
#
#
