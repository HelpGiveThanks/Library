July 24, 2018 16:31:38 Library.fmp12 - about_GoToReviewOrEditWindow -1-
librarySetup: about_GoToReviewOrEditWindow
#
#
#If user is on the review layout, take them
#to the edit layout.
If [ Get (WindowName) = "About" ]
Go to Layout [ “defaultSetupViewAndEdit” (librarySetupReferenceMain) ]
Set Window Title [ Of Window: "About"; Current file; New Title: "Edit About" ]
#
#
#If record's creator node is locked, tell the
#user it's locked, but the record can still be
#deleted or edited because it is not locked.
If [ librarySetupCreator::orderOrLock ≠ "" ]
Show Custom Dialog [ Message: "The creator node — " & librarySetupCreator::tag & " — is locked. HOWEVER, the lock for
these about records are separate from their creator's lock, so you can edit and delete it."; Default Button: “OK”, Commit:
“No” ]
End If
#
#
#If user is on the edit layout, take them
#to the review layout.
Else If [ Get (WindowName) = "Edit About" ]
Go to Layout [ “setupReferenceViewUnlocked” (librarySetupReferenceMain) ]
Set Window Title [ Of Window: "Edit About"; Current file; New Title: "About" ]
End If
#
#
