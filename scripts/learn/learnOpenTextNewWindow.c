September 20, 2018 17:53:34 Library.fmp12 - learnOpenTextNew… -1-
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
Set Variable [ $duplicateRecord; Value:1 ]
Go to Field [ testlearn::note ]
[ Select/perform ]
Else
Go to Field [ testlearn::note ]
End If
#
#If the user in on an iDevice...
#AND is just opening this window for the first time ...
If [ Get ( SystemPlatform ) = 3 and $$showPinchAndZoommessageOnlyOnce = "" ]
Show Custom Dialog [ Message: "NOTE: The following help messages are shown once per session."; Default Button: “OK”,
Commit: “Yes” ]
Show Custom Dialog [ Message: "Scroll up to view all buttons — back, [Ref] (to add a reference), etc. — and the date and time
field."; Default Button: “OK”, Commit: “Yes” ]
Show Custom Dialog [ Message: "Use the two-finger pinch-and-zoom gesture to enlarge everything for easier viewing."; Default
Button: “OK”, Commit: “Yes” ]
#
#These next steps are necessary to get the edit
#interface buttons to show and not scroll into
#hidding. This is important to insure the user
#understands where the buttons are for this
#interface and how to access them. Without
#these next steps, the interface never reveals
#the buttons and fills the entire screen on iOS
#device with just the textbox.
If [ $duplicateRecord = 1 ]
Pause/Resume Script [ Duration (seconds): 2 ]
Scroll Window
[ Home ]
Pause/Resume Script [ Duration (seconds): 1.5 ]
Scroll Window
[ Home ]
Else
Pause/Resume Script [ Duration (seconds): 1.5 ]
Scroll Window
[ Home ]
End If
Set Variable [ $$showPinchAndZoommessageOnlyOnce; Value:1 ]
#
#
#AND is opening this window after the first time ...
Else If [ Get ( SystemPlatform ) = 3 and $$showPinchAndZoommessageOnlyOnce ≠ "" ]
#
#These next steps are necessary to get the edit
#interface buttons to show and not scroll into
#hidding. This is important to insure the user
#understands where the buttons are for this
#interface and how to access them. Without
#these next steps, the interface never reveals
#the buttons and fills the entire screen on iOS
#device with just the textbox.
Refresh Window
If [ $duplicateRecord = 1 ]
Pause/Resume Script [ Duration (seconds): 2 ]
Scroll Window
[ Home ]
Pause/Resume Script [ Duration (seconds): 1.5 ]
Scroll Window
[ Home ]
Else
Pause/Resume Script [ Duration (seconds): 1.5 ]
Scroll Window
[ Home ]
End If
End If
Pause/Resume Script [ Indefinitely ]
#
#
