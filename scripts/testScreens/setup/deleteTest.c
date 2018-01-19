January 12, 2018 14:10:02 Library.fmp12 - deleteSubsection -1-
test: setup: deleteSubsection
#
#This script is for deleting a test
#subsection template.
#
#
If [ testSectionCreatorLock::orderOrLock ≠ "" ]
Show Custom Dialog [ Message: "This record is locked. Go the node that created it — " & testSectionCreatorLock::tag & " — in
the setup tag window and enter the password to unlock it so that you can delete it."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
#
#Set variables to conditionally format record to
#to be deleted and to supply name for warning
#messages, and to speed up script.
Set Variable [ $delete; Value:testSubsectionTemplate::_LtestSubsection ]
Refresh Window
Set Variable [ $$tagTest; Value:testSubsectionTemplate::_LtestSubsection ]
Set Variable [ $$ID; Value:"ignore" ]
If [ testSubsectionTemplate::name = "" ]
Set Field [ testSubsectionTemplate::name; testSubsectionTemplate::_LtestSubsection ]
End If
Go to Field [ ]
Set Variable [ $$stopLoadTestResultRecord; Value:1 ]
Set Variable [ $$stopLoadTestRecord; Value:1 ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Set Variable [ $$stopDeleteTest; Value:1 ]
Set Variable [ $$stopTest; Value:1 ]
#
#Check if item is in use as test tag on any Report
#records, and if so stop the script.
#
New Window [ Name: " "; Height: 1; Width: 1; Top: -10000; Left: -10000; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize:
“Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
// New Window [ Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
Go to Layout [ “TEMP” (TEMP) ]
Show All Records
Delete All Records
[ No dialog ]
#
Go to Layout [ “reportTestResult” (testlearnReportTags) ]
Enter Find Mode [ ]
Set Field [ testlearnReportTags::ktestSubsection; $delete ]
Set Error Capture [ On ]
Allow User Abort [ Off ]
Perform Find [ ]
Sort Records [ Keep records in sorted order; Specified Sort Order: ReportResultTestSubject::tag; ascending ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ First ]
#
#If records are found using test, then tell the
#user on which reports they where found.
If [ Get (FoundCount) ≠ 0 ]
Loop
Set Variable [ $useList; Value:
TextColor( ReportResultTestSubject::tag &
" | test " & testlearnReportTags::kreportNumber ; RGB(102;102;102)) &
¶ &
testlearnReportTags::countOfONESubsectionsTestResults & " in section " &
TextColor( tagReportTestSubjectSectionNAME::name ; RGB(0;0;0)) ]
Set Variable [ $subSection; Value:testlearnReportTags::subsectionCustomName ]
Go to Layout [ “TEMP” (TEMP) ]
New Record/Request
Set Field [ TEMP::DeleteMessageInTempWindow1; $useList ]
Go to Layout [ “reportTestResult” (testlearnReportTags) ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
Go to Layout [ “TEMP” (TEMP) ]
Sort Records [ Keep records in sorted order; Specified Sort Order: TEMP::DeleteMessageInTempWindow1; ascending ]
[ Restore; No dialog ]
View As
[ View as List ]
#
Move/Resize Window [ Current Window; Top: 0; Left: 0 ]
Move/Resize Window [ Current Window; Height: Get ( ScreenHeight ); Width: 360; Top: 0; Left: Get ( ScreenWidth ) - ( Get
( ScreenWidth )/2 + 360) ]
Set Field [ TEMP::Message; "Test results have been made using the sub-section template " & $subSection & ". To delete it, first
delete the test results made in the test-subject's test-sections below, which use this template." ]
Pause/Resume Script [ Indefinitely ]
Close Window [ Current Window ]
Set Variable [ $delete ]
Set Variable [ $$stopLoadTestResultRecord ]
Set Variable [ $$stopLoadTestRecord ]
Set Variable [ $$stopLoadTagRecord ]
Set Variable [ $$stopDeleteTest ]
Set Variable [ $$stopTest ]
Set Variable [ $$tagTest ]
Set Variable [ $$ID; Value:testSubsectionTemplate::_LtestSubsection ]
Refresh Window
Exit Script [ ]
Else
Set Variable [ $$stopLoadTestResultRecord ]
Set Variable [ $$stopLoadTestRecord ]
Set Variable [ $$stopLoadTagRecord ]
Set Variable [ $$stopDeleteTest ]
Set Variable [ $$stopTest ]
Set Variable [ $$ID; Value:testSubsectionTemplate::_LtestSubsection ]
End If
#
#
#Check if item is in use as test tag on any Learn
#records, and if so stop the script.
Set Variable [ $$stopLoadCitation; Value:1 ]
Go to Layout [ “learn2” (testlearn) ]
#
Set Window Title [ Current Window; New Title: "Learn" ]
#
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ testlearn::filterFind; "main" ]
Set Field [ testlearn::kctestSubsectionInfo; "###" & $$tagTest ]
Perform Find [ ]
Set Variable [ $$stopLoadCitation ]
#
#If records are found using test, then stop script.
If [ Get (FoundCount) ≠ 0 ]
Move/Resize Window [ Current Window; Height: Get ( ScreenHeight ); Width: 360; Top: 0; Left: Get ( ScreenWidth ) - ( Get
( ScreenWidth )/2 + 360) ]
Show Custom Dialog [ Message: "This general inquiry is linked to at least one learn record. To delete it 1) go to the learn
module, 2) click 'test' in its tag-menus window, 3) select it, 4) untag it from all learn records, 5) return to test setup, 6) and
delete it."; Default Button: “OK”, Commit: “Yes” ]
#
Close Window [ Current Window ]
Set Variable [ $delete ]
Set Variable [ $$stopLoadTestRecord ]
Set Variable [ $$stopLoadTagRecord ]
Set Variable [ $$stopDeleteTest ]
Set Variable [ $$stopTest ]
Set Variable [ $$tagTest ]
Set Variable [ $$ID; Value:testSubsectionTemplate::_LtestSubsection ]
Refresh Window
#
Exit Script [ ]
End If
#
Close Window [ Current Window ]
#
#If no records were found using this test, then
#user may delete it. First the record is highlighted
#in red and the user is asked if they really intend
#to delete this record.
Set Variable [ $delete; Value:testSubsectionTemplate::_LtestSubsection ]
Refresh Window
Scroll Window
[ To Selection ]
Go to Field [ ]
Show Custom Dialog [ Message: "Delete " & testSubsectionTemplate::name & "?"; Default Button: “Cancel”, Commit: “Yes”; Button 2:
“Delete”, Commit: “No” ]
#
#If the user cancels the delete, then everything
#goes back to the way it was before the delete
#was started.
If [ Get ( LastMessageChoice ) = 1 ]
Set Variable [ $delete ]
Set Variable [ $$stopLoadTestRecord ]
Set Variable [ $$stopLoadTagRecord ]
Set Variable [ $$stopDeleteTest ]
Set Variable [ $$stopTest ]
Set Variable [ $$tagTest ]
Set Variable [ $$ID; Value:testSubsectionTemplate::_LtestSubsection ]
Refresh Window
Exit Script [ ]
End If
#
#If the user presses 'delete' the system will now
#check if this test is the last test in its test group.
If [ Get ( LastMessageChoice ) = 2 ]
#
Set Variable [ $$stopLoadTestRecord; Value:1 ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Set Variable [ $$stopDeleteTest; Value:1 ]
Set Variable [ $$stopTest; Value:1 ]
#
New Window [ Height: 1; Width: 1; Top: -1000; Left: -1000; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”;
Zoom Control Area: “Yes”; Resize: “Yes” ]
// New Window [ Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
#
#Set variables to find and remove all tests in
#a group and its key from all test items.
Set Variable [ $group; Value:testSubsectionTemplate::ksubsectionGroup ]
Set Variable [ $testSubsection; Value:testSubsectionTemplate::_LtestSubsection ]
#
#Find all tests in this test group.
Go to Layout [ “tableTestSubsectionTemplates” (testSubsectionTemplate) ]
Enter Find Mode [ ]
Set Field [ testSubsectionTemplate::ksubsectionGroup; $group ]
Perform Find [ ]
#
#If the test is the last test, the user is informed
#of this and asked if knowing this they want to
#delete both the test and the test group, since
#a test group cannot exist without at least one test
#in it.
If [ Get (FoundCount) = 1 ]
#
Close Window [ Current Window ]
#
Set Variable [ $deleteGroup; Value:$delete ]
Refresh Window
Show Custom Dialog [ Title: "!"; Message: "If you delete this group's last test, it will also be deleted."; Default Button:
“Cancel”, Commit: “Yes”; Button 2: “Delete”, Commit: “No” ]
#
#If the user cancels the delete, then everything
#goes back to the way it was before the delete
#was started.
If [ Get ( LastMessageChoice ) = 1 ]
Set Variable [ $delete ]
Set Variable [ $deleteGroup ]
Set Variable [ $$stopLoadTestRecord ]
Set Variable [ $$stopLoadTagRecord ]
Set Variable [ $$stopDeleteTest ]
Set Variable [ $$stopTest ]
Set Variable [ $$tagTest ]
Set Variable [ $$ID; Value:testSubsectionTemplate::_LtestSubsection ]
Refresh Window
Exit Script [ ]
End If
#
#If the user pressed delete then first the
#test group is deleted.
#
New Window [ Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
#
Go to Layout [ “tableTagGroup” (testSubsectionGroup) ]
Enter Find Mode [ ]
Set Field [ testSubsectionGroup::_Lgroup; $group ]
Perform Find [ ]
Delete Record/Request
[ No dialog ]
End If
#
End If
#
#Remove test's key from test-items that
#have more than one test's key.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Go to Layout [ “setupTestItem” (tagMenus) ]
Enter Find Mode [ ]
Set Field [ tagMenuTestItemGroup::match; $testSubsection & ¶ ]
Perform Find [ ]
Go to Record/Request/Page
[ First ]
Loop
#If an item has only one test key, do not
#remove it. In the next step these test items
# will be found and deleted along with the
#test-item groups to which they belong.
If [ ValueCount (tagMenuTestItemGroup::match) > 1 ]
Set Variable [ $match; Value:tagMenuTestItemGroup::match ]
Set Field [ tagMenuTestItemGroup::match; Substitute ( $match ; $testSubsection & "¶" ; "" ) ]
End If
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Delete the test items that are only linked
#to this test.
Enter Find Mode [ ]
Set Field [ tagMenuTestItemGroup::match; $testSubsection & ¶ ]
Perform Find [ ]
Delete All Records
[ No dialog ]
#
#Delete the test-item groups that now have no
#test items in them, and are no longer linked
#to any tests.
Go to Layout [ “tableTagGroup” (testSubsectionGroup) ]
Enter Find Mode [ ]
Set Field [ testSubsectionGroup::match; $testSubsection & ¶ ]
Perform Find [ ]
Delete All Records
[ No dialog ]
Set Variable [ $$stopLoadTagRecord ]
#
#Finally, delete the test itself.
Go to Layout [ “tableTestSubsectionTemplates” (testSubsectionTemplate) ]
Enter Find Mode [ ]
Set Field [ testSubsectionTemplate::_LtestSubsection; $testSubsection ]
Perform Find [ ]
Delete Record/Request
[ No dialog ]
Close Window [ Current Window ]
#
#Load current test's information.
Set Variable [ $$stopLoadTestRecord ]
Set Variable [ $$stopLoadTagRecord ]
Set Variable [ $$stopDeleteTest ]
Set Variable [ $$stopTest ]
Set Variable [ $$tagTest ]
Set Variable [ $$ID ]
Perform Script [ “loadSetupTestSubsection (update name change loadSetupTestRecord)” ]
#
