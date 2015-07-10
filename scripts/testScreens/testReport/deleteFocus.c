testScreens: testReport: deleteFocus
#
#WHEN TIME PERMITS for testing, change "focus"
#to "section" everywhere it currently exists.
#
#
Set Error Capture [ On ]
Allow User Abort [ Off ]
Set Variable [ $focus; Value:tagLocation::_Ltag ]
Set Variable [ $recordNumber; Value:Get (RecordNumber) ]
#
If [ nodeLockTest::orderOrLock ≠ "" ]
Show Custom Dialog [ Message: "This record is currently locked. Select the node that created it and enter the password to unlock it, then you will able to start the delete process."; Buttons: “OK” ]
Exit Script [ ]
End If
#
#Highlight section user is trying to delete.
Set Variable [ $delete; Value:tagLocation::_Ltag ]
#
Go to Layout [ “TEMP” (TEMP) ]
Show All Records
Delete All Records
[ No dialog ]
#
Go to Layout [ “tableTestSubjectFocus” (tagTestSubjectLocation) ]
Enter Find Mode [ ]
Set Field [ tagTestSubjectLocation::kfocus; $focus ]
Perform Find [ ]
#
#If this section is found to be in use, then inform
#user of where and prevent its deletion.
If [ Get (LastError) ≠ 401 ]
Loop
Set Variable [ $useList; Value:"test subject " &
tagTestSubject::tag &
¶ &
"test/report " &
TextColor( TextStyleAdd ( tagTestSubjectLocation::reportNumber; "" ) ;RGB(0;0;0)) &
" | section " &
TextColor( TextStyleAdd ( tagTestSubjectLocation::focusName; "" ) ;RGB(0;0;0)) ]
Go to Layout [ “TEMP” (TEMP) ]
New Record/Request
Set Field [ TEMP::RemoveFocusList; $useList ]
Go to Layout [ “tableTestSubjectFocus” (tagTestSubjectLocation) ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
Go to Layout [ original layout ]
New Window [ Name: " "; Width: 350; Left: Get ( WindowWidth ) - 350 ]
Go to Layout [ “TEMP” (TEMP) ]
View As
[ View as List ]
#
#eliminate duplicate location records
Sort Records [ Specified Sort Order: TEMP::RemoveFocusList; ascending ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ First ]
Loop
Set Variable [ $focus; Value:TEMP::RemoveFocusList ]
Go to Record/Request/Page
[ Next; Exit after last ]
If [ TEMP::RemoveFocusList = $focus ]
Omit Record
#
#omit by default moves focus to the next record
#in order to test this next record the focus must move up one record
#
Go to Record/Request/Page
[ Previous ]
#then the script can move down to test this record when it repeats
End If
End Loop
#
Show/Hide Status Area
[ Lock; Hide ]
Show/Hide Text Ruler
[ Hide ]
Pause/Resume Script [ Indefinitely ]
Close Window [ Current Window ]
Exit Script [ ]
End If
#
#If the section is not in use, then make sure
#user really wants to delete it.
Go to Layout [ original layout ]
Go to Field [ ]
Go to Record/Request/Page [ $recordNumber ]
[ No dialog ]
Set Variable [ $delete; Value:tagLocation::_Ltag ]
Set Variable [ $name; Value:tagLocation::tag ]
Refresh Window
Show Custom Dialog [ Title: "!"; Message: "Delete " & $name & "?"; Buttons: “Cancel”, “Delete” ]
#
#If user decides to delete it then do so.
If [ Get ( LastMessageChoice ) = 2 ]
If [ tagLocation::_Ltag & "¶" = FilterValues ( test::kcfocusALL ; tagLocation::_Ltag & "¶" ) ]
#
#Remove it from the list of inUse focuses.
Set Variable [ $focus; Value:test::kcfocusALL ]
Set Field [ test::kcfocusALL; //last item in list has no paragraph mark, so a valuecount test needs to be done and if item is not removed, then the removal calc without the paragraph mark is used
If ( ValueCount ( test::kcfocusALL ) ≠ ValueCount ( Substitute ( test::kcfocusALL ; tagLocation::_Ltag & "¶" ; "" ) ) ;
Substitute ( test::kcfocusALL ; tagLocation::_Ltag & "¶" ; "" ) ;
Substitute ( test::kcfocusALL ; tagLocation::_Ltag ; "" )
) ]
End If
#
Delete Record/Request
[ No dialog ]
#
End If
#
#If user cancels delete, then stop the delete process.
Set Variable [ $delete ]
Refresh Window
#
July 10, 平成27 15:46:11 Library.fp7 - deleteFocus -1-
