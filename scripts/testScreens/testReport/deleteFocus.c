testScreens: testReport: deleteFocus
#
#
#WHEN TIME PERMITS the vocabuary for scripts,
#variable, fields, layouts, etc. needs to be updated
#to reflect that a 'test' is now a 'test template'
#and a 'focus' is now a test 'template section', etc.
#A complete look at
#the DDR to insure all vocabulary is updated
#everywhere followed by testing for each
#update is required.
#
#
Set Error Capture [ On ]
Allow User Abort [ Off ]
Set Variable [ $focus; Value:tagLocation::_Ltag ]
Set Variable [ $recordNumber; Value:Get (RecordNumber) ]
#
If [ nodeLockTest::orderOrLock ≠ "" ]
Show Custom Dialog [ Message: "This test section is currently locked. Select the node that created it and enter the password to
unlock it, then you will able to start the delete process."; Buttons: “OK” ]
Exit Script [ ]
End If
#
#Highlight section template user is trying to delete.
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
#If section's using this template then inform
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
New Window [ Name: " "; Width: 360; Left: Get ( WindowWidth ) - 360 ]
Go to Layout [ “TEMP” (TEMP) ]
View As
[ View as List ]
#
#Eliminate duplicate template records.
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
#NOTE: omit by default moves focus to the next record
#so to go to the next record after an omission
#script must go to the previous record as
#so when repeating the loop, going to the next
#does not result in skipping the record that comes
#after a omitted record.
Go to Record/Request/Page
[ Previous ]
End If
End Loop
#
Show/Hide Status Area
[ Lock; Hide ]
Show/Hide Text Ruler
[ Hide ]
Set Field [ TEMP::Message; "Before the highlighted test section template can be deleted, the sections created using it (listed
below) must be deleted from the main test window." ]
Pause/Resume Script [ Indefinitely ]
Close Window [ Current Window ]
Set Variable [ $delete ]
Refresh Window
Exit Script [ ]
End If
#
#If the section template is not in use, then
#make sure user really wants to delete it.
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
#
#First remove its key from all test records that
#have it.
New Window [ Height: 1; Width: 1; Top: 10000; Left: 10000 ]
Go to Layout [ “tableTest” (test) ]
Enter Find Mode [ ]
Set Field [ test::kcfocusALL; $delete ]
Perform Find [ ]
Loop
Set Field [ test::kcfocusALL; //last item in list has no paragraph mark, so a valuecount test needs to be done and if item is not
removed, then the removal calc without the paragraph mark is used
If ( ValueCount ( test::kcfocusALL ) ≠ ValueCount ( Substitute ( test::kcfocusALL ; $delete & "¶" ; "" ) ) ;
Substitute ( test::kcfocusALL ; $delete & "¶" ; "" ) ;
Substitute ( test::kcfocusALL ; $delete ; "" )
) ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
Close Window [ Current Window ]
#
#Delete this test section template.
Delete Record/Request
[ No dialog ]
End If
#
#If user cancels delete, then stop the delete process.
Set Variable [ $delete ]
Refresh Window
#
December 21, ଘ౮27 18:25:39 Library.fp7 - deleteFocus -1-
