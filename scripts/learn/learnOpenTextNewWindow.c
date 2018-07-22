July 20, 2018 17:20:54 Library.fmp12 - learnOpenTextNewWindow -1-
learn: learnOpenTextNewWindow
If [ Get ( WindowMode ) = 1 ]
Go to Field [ testlearn::note ]
Exit Script [ ]
End If
#
#Stop script if user clicked in the note field to
#navigate to this record, not to open the text
#edit window.
If [ $$stopOpenNewTextWindow = 1 ]
Set Variable [ $$stopOpenNewTextWindow ]
Exit Script [ ]
End If
Go to Field [ ]
#
#Set variable so when user closes this edit
#window a test can be performed to see if
#record was changed and so Learn window
#needs to be resorted for inventory tags only.
If [ TEMP::InventoryLibraryYN ≠ "" ]
Set Variable [ $$copyNoteForSortCheck; Value:testlearn::note ]
End If
#
Set Variable [ $record; Value:testlearn::_Ltestlearn ]
Set Variable [ $$stopLoadCitation; Value:1 ]
Close Window [ Name: "Edit"; Current file ]
New Window [ Name: "Edit"; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”; Resize:
“Yes” ]
If [ tagTLNodePrimary::orderOrLock = "" ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
#
#If the user in on an iDevice...
If [ Get ( SystemPlatform ) = 3 ]
Go to Layout [ “LearnTextWindowStuff_iDevice” (testlearn) ]
Else
Go to Layout [ “LearnTextWindowStuff” (testlearn) ]
End If
Else
#
#If the user in on an iDevice...
If [ Get ( SystemPlatform ) = 3 ]
Go to Layout [ “LearnTextWindow_iDevice” (testlearn) ]
Else
Go to Layout [ “LearnTextWindow” (testlearn) ]
End If
End If
Go to Field [ testlearn::note ]
Else If [ tagTLNodePrimary::orderOrLock ≠ "" ]
#
#If the user in on an iDevice...
If [ Get ( SystemPlatform ) = 3 ]
Go to Layout [ “LearnTextWindowLocked_iDevice” (testlearn) ]
Else
Go to Layout [ “LearnTextWindowLocked” (testlearn) ]
End If
End If
Enter Find Mode [ ]
Set Field [ testlearn::_Ltestlearn; $record ]
Perform Find [ ]
Set Variable [ $$stopLoadCitation ]
If [ $$duplicateRecord = 1 ]
Set Variable [ $$duplicateRecord ]
Go to Field [ testlearn::note ]
[ Select/perform ]
Else
Go to Field [ testlearn::note ]
End If
#
#If the user in on an iDevice...
If [ Get ( SystemPlatform ) = 3 ]
Show Custom Dialog [ Message: "Use two-finger pinch-and-zoom gesture to make text easier to see and edit."; Default Button:
“OK”, Commit: “Yes” ]
End If
Pause/Resume Script [ Indefinitely ]
#
#
