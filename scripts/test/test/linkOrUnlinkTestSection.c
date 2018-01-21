January 15, 2018 15:02:47 Library.fmp12 - linkOrUnlinkTestSection -1-
test: test: linkOrUnlinkTestSection
#
#
#Prevent locked subsection's section links
#from being changed.
If [ $$lockedMainSubsectionRecord ≠ "" ]
Show Custom Dialog [ Message: "Locked subsections cannot have their section links changed. Select its creator node — " & $
$lockedMainSubsectionRecord & " — in setup, and enter the password to unlock it."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
#
#
#If tag has not yet been selected, then link it.
Set Variable [ $sectionTemplate; Value:testSection::_Ltag ]
Go to Field [ ]
Select Window [ Name: "Test Templates"; Current file ]
Set Variable [ $testTemplate; Value:testSubsectionTemplate::_LtestSubsection ]
If [ $sectionTemplate & ¶ ≠ FilterValues ( testSubsectionTemplate::kcsections ; $sectionTemplate & "¶" ) ]
#
Set Variable [ $currentSectionTemplates; Value:testSubsectionTemplate::kcsections ]
Set Field [ testSubsectionTemplate::kcsections; $sectionTemplate & "¶" & $currentSectionTemplates ]
#
#Reset conditional formatting variable for sections.
Set Variable [ $$subsectionSections; Value:testSubsectionTemplate::kcsections ]
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
Set Variable [ $delete; Value:testSection::_Ltag ]
#
#
Set Variable [ $$stopTest; Value:1 ]
Set Variable [ $$ID; Value:"ignore" ]
Set Variable [ $$stopLoadTestRecord; Value:1 ]
New Window [ Name: " "; Width: 360; Left: Get ( WindowWidth ) - 360; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize:
“Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
Go to Layout [ “TEMP” (TEMP) ]
Show All Records
Delete All Records
[ No dialog ]
#
Go to Layout [ “tableTestSectionFromTemplate” (testSectionCreatedFromATemplate) ]
Enter Find Mode [ ]
Set Field [ testSectionCreatedFromATemplate::inUse; "t" ]
Set Field [ testSectionCreatedFromATemplate::ksectionTemplate; $sectionTemplate ]
Perform Find [ ]
#
#For each section found, find its test records, and
#see if any of their test records use the test template
#that you wish to remove this section template.
If [ Get (LastError) ≠ 401 ]
Go to Record/Request/Page
[ First ]
Loop
Set Variable [ $testSection; Value:testSectionCreatedFromATemplate::_LtestSection ]
Set Variable [ $sectionName; Value:testSectionCreatedFromATemplate::name ]
Go to Layout [ “testResult0” (testlearn) ]
Enter Find Mode [ ]
Set Field [ testlearn::ktestSection; $testSection ]
Set Field [ testlearn::ktestSubsection; $testTemplate ]
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
Set Field [ TEMP::DeleteMessageInTempWindow1; $useList ]
End If
Go to Layout [ “tableTestSectionFromTemplate” (testSectionCreatedFromATemplate) ]
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
Sort Records [ Keep records in sorted order; Specified Sort Order: TEMP::DeleteMessageInTempWindow1; ascending ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ First ]
Loop
Set Variable [ $sectionTemplate; Value:TEMP::DeleteMessageInTempWindow1 ]
Go to Record/Request/Page
[ Next; Exit after last ]
If [ TEMP::DeleteMessageInTempWindow1 = $sectionTemplate ]
Omit Record
#
#Omit by default moves to the next record
#in order to test actual next record the database
#must move up one record.
#
Go to Record/Request/Page
[ Previous ]
#then the script can move down to test this record when it repeats
End If
End Loop
#
Show/Hide Toolbars
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
Else
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
Select Window [ Name: "Test Templates"; Current file ]
#
#If tag has been selected, then unlink it.
Set Variable [ $currentSectionTemplates; Value:testSubsectionTemplate::kcsections ]
Set Field [ testSubsectionTemplate::kcsections; //last item in list has no paragraph mark, so a valuecount test needs to be done and if
item is not removed, then the removal calc without the paragraph mark is used
If ( ValueCount ( $currentSectionTemplates ) ≠ ValueCount ( Substitute ( $currentSectionTemplates ; $sectionTemplate & "¶" ;
"" ) ) ;
Substitute ( $currentSectionTemplates ; $sectionTemplate & "¶" ; "" ) ;
""
) ]
#
#Reset conditional formatting variable for sections.
Set Variable [ $$subsectionSections; Value:testSubsectionTemplate::kcsections ]
Go to Field [ ]
#
#Return to Tag Menus window.
Select Window [ Name: "Tag Menus"; Current file ]
Refresh Window
#
