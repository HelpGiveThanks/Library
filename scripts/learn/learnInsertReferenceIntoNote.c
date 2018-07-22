July 21, 2018 14:45:39 Library.fmp12 - learnInsertReferenceIntoNote -1-
test: test: learnInsertReferenceIntoNote
#
#
#Admin tasks.
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
#If the record has no references, then insert a
#generic reference template and let user know
#the benefits of tag references and then
#clicking the insertRef button.
If [ testlearn::kcreference = ""
 or
ValueCount ( testlearn::kcreference ) - Length ( Filter ( testlearn::kcreference ; "L" ) ) = 0 ]
Show Custom Dialog [ Message: "If you add references to a record like this one, this button will give you a list of pre-formatted
references to insert including the author's name and date of publication."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
#
#Make sure the cursor is in active field and if
#not tell them to click in one.
If [ Get ( ActiveFieldName ) = ""
or
Get ( ActiveFieldName ) ≠ "note" ]
Show Custom Dialog [ Message: "Click into the text field, and then click exactly where you want — " & Trim ($tag) & " —
inserted."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
#
#Make sure the user has not selected any text.
If [ Get ( ActiveFieldName ) = ""
or
Get ( ActiveFieldName ) ≠ "note" ]
Show Custom Dialog [ Message: "Click into the text field, and then click exactly where you want — " & Trim ($tag) & " —
inserted."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
#
#Remind the user that the inserted reference
#is going to go where they have placed
#their cursor.
Show Custom Dialog [ Message: "Is your cursor where you want to insert a reference? WARNING: Selected text will be erased
during insert." &
"" & ¶ &
"(You can also click 'yes' just to see this note's references.)"; Default Button: “yes”, Commit: “Yes”; Button 2: “cancel”, Commit:
“No” ]
If [ Get (LastMessageChoice) = 2 ]
Exit Script [ ]
End If
#
#Hide controls so user knows to close the
#Insert Reference window before they can
#continue editing their note.
Set Variable [ $$hideEditNoteControls; Value:1 ]
Refresh Window
#
#Capture the keys of the references load.
Set Variable [ $references; Value:testlearn::kcreference ]
#
#Determine how many references there are.
Set Variable [ $numberOfReferences; Value:ValueCount ( testlearn::kcreference ) ]
#
#Prevent loading up records.
Set Variable [ $$STOPloadReferenceForInsertIntoText; Value:1 ]
#
#In the test section, go the Reference window
#or open one up if neccessary.
If [ Get ( SystemPlatform ) = - 2 ]
New Window [ Name: "Insert Reference"; Height: Get (WindowDesktopHeight) - 21; Width: Get (ScreenWidth) / 2; Top: 0; Left:
Get (ScreenWidth) / 2; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”; Resize:
“Yes” ]
Else
New Window [ Name: "Insert Reference"; Height: Get (ScreenHeight); Width: Get (ScreenWidth) / 2; Top: 0; Left: Get
(ScreenWidth) / 2; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”; Resize:
“Yes” ]
End If
#
#Go the insert references layout.
Go to Layout [ “learnMenu3CitePickAReference” (reference) ]
#
#Find the first reference. NOTE: It may be this
#first reference is a learn reference, and so no
#records will be found, but this is OK. This first
#find clears out any records that may have
#been found previously, and replaces them with
#the outcome of this first find, which if none is,
#again, OK. Then next find step expands on
#this find, so to speed things up, it will not look
#for learn references, BUT if this step did not
#look for learn records, the script would in
#effect skip this first find and so leave in place
#the records found previously. Very Bad!
#NOTE: I've had a lot of caffeine.
Enter Find Mode [ ]
Set Field [ reference::_Lreference; GetValue ( $references ; $numberOfReferences ) ]
Perform Find [ ]
#
#If there is more than one reference, then load
#find them one-at-time until all have been found.
Loop
Set Variable [ $numberOfReferences; Value:$numberOfReferences - 1 ]
#
#Exit find loop once all references have
#been found.
Exit Loop If [ $numberOfReferences = 0 ]
#
#Only find references from the Reference section.
If [ Right ( GetValue ( $references ; $numberOfReferences ) ; 1 ) ≠ "L" ]
Enter Find Mode [ ]
Set Field [ reference::_Lreference; GetValue ( $references ; $numberOfReferences ) ]
Extend Found Set [ ]
End If
#
End Loop
#
#Sort according the user's preference.
If [ TEMP::sortInsertRef = "cat" or TEMP::sortInsertRef = "" ]
Set Field [ TEMP::sortInsertRef; "abc" ]
Else If [ TEMP::sortInsertRef = "abc" ]
Set Field [ TEMP::sortInsertRef; "cat" ]
End If
Perform Script [ “sortTags” ]
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
#
#Resize the window.
Move/Resize Window [ Name: "Test"; Current file; Width: Get ( ScreenWidth ) / 3; Left: 0 ]
#
#Turn back on info record record's load script.
Set Variable [ $$STOPloadReferenceForInsertIntoText ]
Perform Script [ “loadReferenceForInsertIntoText” ]
#
#Pause the script so the user cannot do
#anything until they either insert a reference
#or close this window.
Pause/Resume Script [ Indefinitely ]
#
#
