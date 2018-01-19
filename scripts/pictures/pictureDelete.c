January 15, 2018 17:42:00 Library.fmp12 - pictureDelete -1-
pictures: pictureDelete
#
#
#Admin tasks.
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
#
#If record is locked (which all default
#copyright symbols used for locked
#copyright tags are), then exit the script.
If [ reference::lock = "lock" ]
Show Custom Dialog [ Message: "This record is used by default copyright tags and so is locked."; Default Button: “OK”, Commit:
“Yes” ]
Exit Script [ ]
End If
#
#
#If the primary node that created this record is
#locked then exit the script.
If [ tagTLNodePrimary::orderOrLock ≠ "" or $$PictureOnReportLayout ≠ "" ]
If [ tagTLNodePrimary::orderOrLock = "0" ]
Show Custom Dialog [ Message: "This Learn record's creator — " & tagTLNodePrimary::tag & " — is locked. To unlock, A)
go back to the setup node tag menu. B) Select this test subject. C) Click 'lock' and enter the password."; Default Button:
“OK”, Commit: “No” ]
Else If [ tagTLReportNodePrimary::orderOrLock = "0" ]
Show Custom Dialog [ Message: "This Learn record's creator — " & tagTLReportNodePrimary::tag & " — is locked. To
unlock, A) go back to the setup node tag menu. B) Select this test subject. C) Click 'lock' and enter the password.";
Default Button: “OK”, Commit: “No” ]
End If
Exit Script [ ]
End If
#
#
#See if reference's media is in use and then
# inform user if it is that they cannot delete it.
Set Variable [ $$pictureDelete; Value:1 ]
If [ Get (LayoutTableName) = "reference" ]
Perform Script [ “CHUNK_checkIfReferencePicIsInUse (new)” ]
End If
#
#If CHUNK_checkIfReferencePicIsInUse finds that the
#reference's media is in use, then stop this delete.
If [ $$pictureDelete = 2 ]
Set Variable [ $$pictureDelete ]
#
#
If [ $$replacePicture = 1 ]
Perform Script [ “pictureReplaceButton (update)” ]
End If
#
#Halt the script if the Media window was just
#closed, so the "continue" button will be
#turned off allowing user to move to other
#windows.
If [ Get (WindowName) = "References" ]
Halt Script
Else
Exit Script [ ]
End If
#
#If not then proceed with the delete.
Else
Set Variable [ $$pictureDelete ]
End If
#
#
#Confirm reference media is free to be deleted,
#and ask user if they want to delete it.
If [ reference::picture ≠ "" and reference::lock = "" ]
Show Custom Dialog [ Message: "Delete current picture?"; Default Button: “Cancel”, Commit: “Yes”; Button 2: “OK”, Commit:
“No” ]
#
#If user cancels delete, exit script.
If [ Get ( LastMessageChoice ) = 1 ]
Go to Field [ ]
Exit Script [ ]
#
#If user decides to delete media, then delete it and
#make sure other media checkboxes are not checked.
Else If [ Get ( LastMessageChoice ) = 2 ]
Set Field [ reference::picture; "" ]
Set Field [ reference::showMedia; "" ]
#
#Close the Media window and halt all running scripts.
Close Window [ Current Window ]
Halt Script
End If
#
#
#Ask user if they want to delete Learn media.
Else If [ testlearn::picture ≠ "" ]
Show Custom Dialog [ Message: "Delete current picture?"; Default Button: “Cancel”, Commit: “No”; Button 2: “OK”, Commit:
“No” ]
#
#If user cancels delete, exit script.
If [ Get ( LastMessageChoice ) = 1 ]
Go to Field [ ]
Exit Script [ ]
End If
#
If [ testlearn::kcInUseOnReportSubsection ≠ "" ]
If [ ValueCount ( testlearn::kcInUseOnReportSubsection ) = 1 ]
Show Custom Dialog [ Message: "This learn records picture and text are in use in the report section " & ValueCount
( testlearn::kcInUseOnReportSubsection ) & " time. (Deleting the picture, like editing the text, will not remove the
link to the report, just change what is on it.)"; Default Button: “Cancel”, Commit: “Yes”; Button 2: “delete”, Commit:
“No” ]
Else
Show Custom Dialog [ Message: "This learn records picture and text are in use in the report section " & ValueCount
( testlearn::kcInUseOnReportSubsection ) & " times? (Deleting the picture, like editing the text, will not remove
links to the report, just change what is on them.)"; Default Button: “cancel”, Commit: “Yes”; Button 2: “delete”,
Commit: “No” ]
End If
End If
#
#If user cancels delete, exit script.
If [ Get ( LastMessageChoice ) = 1 ]
Go to Field [ ]
Exit Script [ ]
#
#If user decides to delete media, then delete it.
Else If [ Get ( LastMessageChoice ) = 2 ]
Set Field [ testlearn::picture; "" ]
#
#Close the Media window and halt all running scripts.
Close Window [ Current Window ]
Halt Script
End If
End If
#
