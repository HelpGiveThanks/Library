January 11, 2018 19:12:19 Library.fmp12 - setupReference_GoToReviewOrEditWindow -1-
librarySetup: setupReference_GoToReviewOrEditWindow
#
#
#If user is on the review layout, take them
#to the edit layout.
If [ Get (WindowName) = "Review Reference" ]
Go to Layout [ “defaultSetupViewAndEdit” (librarySetupReferenceMain) ]
Set Window Title [ Of Window: "Review Reference"; Current file; New Title: "Edit Reference" ]
#
#
#If record's creator node is locked, tell the
#user it's locked, but the record can still be
#deleted or edited because it is not locked.
If [ librarySetupCreator::orderOrLock ≠ "" ]
Show Custom Dialog [ Message: "This library setup-reference's creator node — " & librarySetupCreator::tag & " — is
locked. HOWEVER, the lock for these setup-reference records are separate from their creator's lock, so you can edit
and delete it."; Default Button: “OK”, Commit: “No” ]
End If
#
#
#If user is on the edit layout, take them
#to the review layout.
Else If [ Get (WindowName) = "Edit Reference" ]
Go to Layout [ “setupReferenceViewUnlocked” (librarySetupReferenceMain) ]
Set Window Title [ Of Window: "Edit Reference"; Current file; New Title: "Review Reference" ]
End If
#
#
