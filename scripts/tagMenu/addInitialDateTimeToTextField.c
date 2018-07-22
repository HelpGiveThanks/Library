July 21, 2018 12:55:38 Library.fmp12 - addInitialDateTimeToTextField -1-
tagMenu: addInitialDateTimeToTextField
#
#
#
#On the test-item layout, set this stop check
#or text variable to allows the user to click into
#this field for the purpose of navigating to a
#new record without changing the check or
#text mark status.
If [ $$stopCheckOrTest = 1 ]
Set Variable [ $$stopCheckOrTest ]
Exit Script [ ]
End If
#
#
#
#Stop this script if any of the following are true:
#
#Test subject is locked.
If [ $$testSubjectIsLocked ≠ "" and Get ( LayoutName ) ≠ "defaultTest" and Get ( LayoutName ) ≠ "learnTest" ]
Show Custom Dialog [ Message: "The test subject — " & $$testSubjectIsLocked & " — is locked. To unlock, A) go back to the
setup node tag menu. B) Select this test subject. C) Click 'lock' and enter the password."; Default Button: “OK”, Commit:
“No” ]
Set Variable [ $exit; Value:1 ]
End If
#
#Primary node is locked.
If [ TEMP::primaryNodeIsLocked ≠ "" ]
If [ $exit = "" ]
Show Custom Dialog [ Message: "The default primary node — " & TEMP::DEFAULTNodePrimaryName & " — is locked.
Go to the Default Node Tag Menu and A) click 'lock' to unlock it, B) select an unlocked node for the primary node, or C)
create a new primary node."; Default Button: “OK”, Commit: “No” ]
Else
Show Custom Dialog [ Message: "ALSO, the default primary node — " & TEMP::DEFAULTNodePrimaryName & " — is
locked. Go to the Default Node Tag Menu and A) click 'lock' to unlock it, B) select an unlocked node for the primary
node, or C) create a new primary node."; Default Button: “OK”, Commit: “No” ]
End If
Set Variable [ $exit; Value:1 ]
End If
#
#If any of the above are true, then
#exit this script.
If [ $exit = 1 ]
Exit Script [ ]
End If
#
#
#
#Admin tasks.
Allow User Abort [ Off ]
Set Error Capture [ On ]
Go to Field [ ]
#
#
#
#BEGIN Create the text block to be inserted.
#
#
#Initials
Set Variable [ $initial; Value:TEMP::textDateIntialTime[2] ]
#
#TimeStamp
If [ TEMP::textDateIntialTime = 1 ]
If [ $initial = "" ]
Set Variable [ $time; Value:Left ( DayName ( Get ( CurrentDate ) ) ; 3 ) & " " & Month ( Get ( CurrentDate ) ) & "/" & Day ( Get
( CurrentDate ) ) & "/" & Middle ( Year ( Get ( CurrentDate ) ) ; 3 ; 2 ) & " " & Case ( Right ( Left ( Get ( CurrentTime ) ;
5 ) ; 1 ) = ":" ; Left ( Get ( CurrentTime ) ; 4 ) ; Left ( Get ( CurrentTime ) ; 5 ) ) & " " & Right ( Get ( CurrentTime ) ; 2 ) ]
Else
Set Variable [ $time; Value:" | " & Left ( DayName ( Get ( CurrentDate ) ) ; 3 ) & " " & Month ( Get ( CurrentDate ) ) & "/" &
Day ( Get ( CurrentDate ) ) & "/" & Middle ( Year ( Get ( CurrentDate ) ) ; 3 ; 2 ) & " " & Case ( Right ( Left ( Get
( CurrentTime ) ; 5 ) ; 1 ) = ":" ; Left ( Get ( CurrentTime ) ; 4 ) ; Left ( Get ( CurrentTime ) ; 5 ) ) & " " & Right ( Get
( CurrentTime ) ; 2 ) ]
End If
End If
#
#Time Spent
If [ TEMP::textDateIntialTime[3] ≠ "" ]
Show Custom Dialog [ Message: "Enter time spent."; Default Button: “OK”, Commit: “Yes”; Input #1: TEMP::textDateIntialTime[3],
"hours"; Input #2: TEMP::textDateIntialTime[4], "minutes" ]
If [ $initial = "" and $time = "" ]
Set Variable [ $minutes; Value:Case ( TEMP::textDateIntialTime[3] = "" or TEMP::textDateIntialTime[3] = "0" or TEMP::
textDateIntialTime[3] = "00" ; 0 ; TEMP::textDateIntialTime[3] ) & "h " & TEMP::textDateIntialTime[4] & "m" ]
Else
Set Variable [ $minutes; Value:" | " & Case ( TEMP::textDateIntialTime[3] = "" or TEMP::textDateIntialTime[3] = "0" or TEMP::
textDateIntialTime[3] = "00" ; 0 ; TEMP::textDateIntialTime[3] ) & "h " & TEMP::textDateIntialTime[4] & "m" ]
End If
End If
#
#Combine the text text blocks into one line of text.
Set Variable [ $tag; Value:" " & TextStyleAdd ( TextSize ( TextFont ( TextColor (
Case ( $initial ≠ "" ; $initial ; "" ) &
Case ( $time ≠ "" ; $time ; "" ) &
Case ( $minutes ≠ "" ; $minutes ; "" )
 ;RGB(177 ; 177 ; 177 )) ; "Arial" ) ; 16 ) ; Plain ) & " " ]
#
#If there are no selected items to compose
#a text block, then exit the script.
If [ (TEMP::textDateIntialTime = 1 or TEMP::textDateIntialTime[2] ≠ "" or TEMP::textDateIntialTime[3] ≠ "") = 0 ]
Show Custom Dialog [ Message: "Enter intials or click on the date or time buttons to create a an information text block to insert.";
Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
#
#END Create the text block to be inserted.
#
#
#
#BEGIN Insert text block.
#
#
#See if the user in the test section
#or report section.
Select Window [ Name: "Test"; Current file ]
If [ Get ( LastError )= 112 ]
Select Window [ Name: "Report"; Current file ]
End If
#
#Make sure the cursor is in active field and if
#not tell them to click in one.
If [ Get ( ActiveFieldName ) = "" ]
Show Custom Dialog [ Message: "To insert this text — " & Trim ($tag) & " — 1) click into a field, and then 2) click exactly where
you want it inserted in the field."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
#
#Insert the text block.
Else
If [ Get ( ActiveFieldContents ) = "" ]
Insert Calculated Result [ $tag ]
Else
Insert Calculated Result [ $tag & ¶ ]
End If
End If
#
Exit Script [ ]
#
#
#END Insert text block.
#
#
