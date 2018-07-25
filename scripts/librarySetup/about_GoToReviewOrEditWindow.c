July 24, 2018 17:37:06 Library.fmp12 - about_GoToReviewOrEdit… -1-
librarySetup: about_GoToReviewOrEditWindow
#
#
#If user is on the review layout, take them
#to the edit layout.
If [ Get (WindowName) = "About" ]
Go to Layout [ “aboutLibraryEdit” (aboutLibraryMain) ]
Set Window Title [ Of Window: "About"; Current file; New Title: "Edit About" ]
#
#
#If record's creator node is locked, tell the
#user it's locked, but the record can still be
#deleted or edited because it is not locked.
If [ aboutLibraryCreator::orderOrLock ≠ "" ]
Show Custom Dialog [ Message: "The creator node — " & aboutLibraryCreator::tag & " — is locked. HOWEVER, the lock
for these about records are separate from their creator's lock, so you can edit and delete it."; Default Button: “OK”,
Commit: “No” ]
End If
#
#
#If user is on the edit layout, take them
#to the review layout.
Else If [ Get (WindowName) = "Edit About" ]
Go to Layout [ “aboutLibraryReviewUnlocked” (aboutLibraryMain) ]
Set Window Title [ Of Window: "Edit About"; Current file; New Title: "About" ]
End If
#
#
