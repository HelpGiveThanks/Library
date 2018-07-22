July 21, 2018 12:56:41 Library.fmp12 - insertReferenceToReference -1-
tagMenu: insertReferenceToReference
#
#
#Admin tasks.
Allow User Abort [ Off ]
Set Error Capture [ On ]
Go to Field [ ]
#
#Figure out which template the user wants
#to insert.
If [ $$referenceToInsert = "" ]
Set Variable [ $$referenceToInsert; Value:Case ( $$andPageNumber ≠ "" ;
TEMP::referenceInsertAndPage ;
Case ( $$andTime ≠ "" ;
TEMP::referenceInsertAndTime ;
TEMP::referenceInsert ) ) ]
Else
Set Variable [ $referenceToAddToInsert; Value:Case ( $$andPageNumber ≠ "" ;
TEMP::referenceInsertAndPage ;
Case ( $$andTime ≠ "" ;
TEMP::referenceInsertAndTime ;
TEMP::referenceInsert ) ) ]
Set Variable [ $$referenceToInsert; Value:$$referenceToInsert & "; " & $referenceToAddToInsert ]
End If
Set Variable [ $$andPageNumber ]
Set Variable [ $$andTime ]
#
#Ask user if they would like to continue adding
#refernces or close the window to continue
#working on their note if there is more than one
#record.
If [ Get (FoundCount) ≠ 1 ]
Show Custom Dialog [ Message: "Your reference so far >> " &
Case (
TEMP::referenceInsertBeforeOrAfterPeriod = 1
 or
TEMP::referenceInsertBeforeOrAfterPeriod = "" ;
"(" & $$referenceToInsert & ")" ;
"[" & $$referenceToInsert & "]" ); Default Button: “OK”, Commit: “Yes” ]
Show Custom Dialog [ Message: "Close this window and insert it?" & ¶ & " or" & ¶ & "Add more references to it?"; Default Button:
“close”, Commit: “Yes”; Button 2: “more”, Commit: “No”; Button 3: “cancel”, Commit: “No” ]
If [ Get (LastMessageChoice) = 2
or
Get (LastMessageChoice) = 3 ]
Pause/Resume Script [ Indefinitely ]
Exit Script [ ]
End If
End If
#
#Clear this variable to reveal the edit note controls.
Set Variable [ $$hideEditNoteControls ]
#
#Determine if punctuation for reference.
If [ TEMP::referenceInsertBeforeOrAfterPeriod = 1
 or
TEMP::referenceInsertBeforeOrAfterPeriod = "" ]
Set Variable [ $$referenceToInsert; Value:"(" & $$referenceToInsert & ")" ]
Else
Set Variable [ $$referenceToInsert; Value:"[" & $$referenceToInsert & "]" ]
End If
#
#Close window and restart the pause, so the
#user cannot leave the selected window until
#they are finished using it.
Close Window [ Name: "Insert Reference"; Current file ]
#
#Insert the text block.
If [ Length ( $$referenceToInsert ) ≠ 2 ]
Insert Calculated Result [ $$referenceToInsert ]
End If
Set Variable [ $$referenceToInsert ]
Refresh Window
#
Pause/Resume Script [ Indefinitely ]
#
#
