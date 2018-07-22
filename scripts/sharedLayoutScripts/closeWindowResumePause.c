July 21, 2018 12:42:12 Library.fmp12 - closeWindowResumePause -1-
sharedLayoutScripts: closeWindowResumePause
#
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
Close Window [ Current Window ]
#
#Insert the text block.
If [ Length ( $$referenceToInsert ) ≠ 2 ]
Insert Calculated Result [ $$referenceToInsert ]
Show Custom Dialog [ Message: "Your reference was inserted >> " & $$referenceToInsert; Default Button: “OK”, Commit: “Yes” ]
End If
Set Variable [ $$referenceToInsert ]
Refresh Window
#
Pause/Resume Script [ Indefinitely ]
#
#
