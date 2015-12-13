testScreens: test: linkTestFocusOrUnlinkTestFocus (UPDATE fix not unlinking)
#
#
#WHEN TIME PERMITS the vocabuary for scripts,
#variable, fields, layouts, etc. needs to be updated
#to reflect that a 'test' is now a 'test template'
#and a 'focus'
#is now a test 'section', etc. A complete look at
#the DDR to insure all vocabulary is updated
#everywhere followed by testing for each
#update is required.
#
#
If [ nodeLockTest::orderOrLock ≠ "" ]
Show Custom Dialog [ Message: "This test-section template is currently locked. Select the node that created it and enter the
password to unlock it, then you will able to start the delete process."; Buttons: “OK” ]
Exit Script [ ]
End If
#
#
#If tag has not yet been selected, then link it.
Set Variable [ $sectionTemplate; Value:tagLocation::_Ltag ]
Go to Field [ ]
Select Window [ Name: "Setup"; Current file ]
Set Variable [ $testTemplate; Value:test::_Ltest ]
If [ $sectionTemplate & ¶ ≠ FilterValues ( test::kcfocusALL ; $sectionTemplate & "¶" ) ]
#
Set Variable [ $currentSectionTemplates; Value:test::kcfocusALL ]
Set Field [ test::kcfocusALL; $sectionTemplate & "¶" & $currentSectionTemplates ]
#
#Reset conditional formatting variable for focuses.
Set Variable [ $$focuses; Value:test::kcfocusALL ]
Go to Field [ ]
Select Window [ Name: "Tag Menus"; Current file ]
Refresh Window
Exit Script [ ]
End If
#
#
#
#Find all sections that use this section template.
Select Window [ Name: "Tag Menus"; Current file ]
#
Set Error Capture [ On ]
Allow User Abort [ Off ]
Set Variable [ $recordNumber; Value:Get (RecordNumber) ]
#
#Highlight section user is trying to delete.
Set Variable [ $delete; Value:tagLocation::_Ltag ]
#
#
Set Variable [ $$stopTest; Value:1 ]
Set Variable [ $$ID; Value:"ignore" ]
Set Variable [ $$stopLoadTestRecord; Value:1 ]
New Window [ Name: " "; Width: 360; Left: Get ( WindowWidth ) - 360 ]
Go to Layout [ “TEMP” (TEMP) ]
Show All Records
Delete All Records
[ No dialog ]
#
Go to Layout [ “tableTestSubjectFocus” (tagTestSubjectLocation) ]
Enter Find Mode [ ]
Set Field [ tagTestSubjectLocation::inUse; "t" ]
Set Field [ tagTestSubjectLocation::kfocus; $sectionTemplate ]
Perform Find [ ]
#
#For each section found, find its test records, and
#see if any of their test records use the test template
#that you wish to remove this section template.
If [ Get (LastError) ≠ 401 ]
Go to Record/Request/Page
[ First ]
Loop
Set Variable [ $testSection; Value:tagTestSubjectLocation::_LtestSubjectLocation ]
Set Variable [ $sectionName; Value:tagTestSubjectLocation::focusName ]
Go to Layout [ “step4_InspectionFinding” (testlearn) ]
Enter Find Mode [ ]
Set Field [ testlearn::kaudienceLocation; $testSection ]
Set Field [ testlearn::ktest; $testTemplate ]
Perform Find [ ]
If [ Get (LastError) ≠ 401 ]
Set Variable [ $useList; Value:"test subject " &
tagTLTestSubject::tag &
¶ &
"test " &
TextColor( TextStyleAdd ( testlearn::kreportNumber; "" ) ;RGB(0;0;0)) &
" | section " &
TextColor( TextStyleAdd ( $sectionName; "" ) ;RGB(0;0;0)) ]
Go to Layout [ “TEMP” (TEMP) ]
New Record/Request
Set Field [ TEMP::RemoveFocusList; $useList ]
End If
Go to Layout [ “tableTestSubjectFocus” (tagTestSubjectLocation) ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
If [ $useList ≠ "" ]
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
Set Variable [ $sectionTemplate; Value:TEMP::RemoveFocusList ]
Go to Record/Request/Page
[ Next; Exit after last ]
If [ TEMP::RemoveFocusList = $sectionTemplate ]
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
Set Field [ TEMP::Message; "Before the highlighted test section-template can be unlinked, the test records in the test
sections created using it (listed below) must be deleted from the testing window." ]
Pause/Resume Script [ Indefinitely ]
Close Window [ Current Window ]
Set Variable [ $delete ]
Set Variable [ $$stopTest ]
Set Variable [ $$ID; Value:$testTemplate ]
Set Variable [ $$stopLoadTestRecord ]
Refresh Window
Exit Script [ ]
End If
Close Window [ Current Window ]
End If
Set Variable [ $delete ]
Set Variable [ $$stopTest ]
Set Variable [ $$ID; Value:$testTemplate ]
Set Variable [ $$stopLoadTestRecord ]
Refresh Window
#
#
#
Select Window [ Name: "Setup"; Current file ]
#
#If tag has been selected, then unlink it.
Set Variable [ $currentSectionTemplates; Value:test::kcfocusALL ]
Set Field [ test::kcfocusALL; //last item in list has no paragraph mark, so a valuecount test needs to be done and if item is not removed,
then the removal calc without the paragraph mark is used
If ( ValueCount ( $currentSectionTemplates ) ≠ ValueCount ( Substitute ( $currentSectionTemplates ; $sectionTemplate & "¶" ;
"" ) ) ;
Substitute ( $currentSectionTemplates ; $sectionTemplate & "¶" ; "" ) ;
Substitute ( $currentfocuses ; $focus ; "" )
) ]
#
#Reset conditional formatting variable for focuses.
Set Variable [ $$focuses; Value:test::kcfocusALL ]
Go to Field [ ]
#
Select Window [ Name: "Tag Menus"; Current file ]
Refresh Window
December 13, ଘ౮27 4:31:08 Library.fp7 - linkTestFocusOrUnlinkTestFocus (UPDATE fix not unlinking) -1-
