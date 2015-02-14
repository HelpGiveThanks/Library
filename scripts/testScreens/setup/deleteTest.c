testScreens: setup: deleteTest
#
If [ nodeLockTest::orderOrLock ≠ "" ]
Show Custom Dialog [ Message: "This record is locked. Go the node that created it -- " & nodeLockTest::tag & " -- in the setup tag window and enter the password to unlock it so that you can delete it."; Buttons: “OK” ]
Exit Script [ ]
End If
#
#Set variables to conditionally format record to
#to be deleted and to supply name for warning
#messages, and to speed up script.
Set Variable [ $delete; Value:test::_Ltest ]
Set Variable [ $$tagTest; Value:test::_Ltest ]
Set Variable [ $$ID; Value:"ignore" ]
If [ test::testName = "" ]
Set Field [ test::testName; test::_Ltest ]
End If
Go to Field [ ]
#
#Check if item is in use as test tag on any Report
#records, and if so stop the script.
#
New Window [ Name: "Report: Discovery Records"; Height: 4; Width: 4 ]
#
Go to Layout [ “reportTagDiscovery” (testlearnReportTags) ]
Enter Find Mode [ ]
Set Field [ testlearnReportTags::ktest; $delete ]
Set Error Capture [ On ]
Allow User Abort [ Off ]
Perform Find [ ]
#
#If records are found using test, then stop script.
If [ Get (FoundCount) ≠ 0 ]
Move/Resize Window [ Current Window; Height: Get ( ScreenHeight ); Width: 333; Top: 0 ]
Show Custom Dialog [ Title: "!"; Message: "Discoveries where made for this test (shown). Delete all these discovery records and then this test can be deleted."; Buttons: “OK” ]
#
Close Window [ Current Window ]
Set Variable [ $$ID; Value:test::_Ltest ]
#
Exit Script [ ]
End If
#
#Check if item is in use as test tag on any Learn
#records, and if so stop the script.
Set Variable [ $$stopLoadCitation; Value:1 ]
Go to Layout [ “learn1” (testlearn) ]
#
Set Window Title [ Current Window; New Title: "Learn" ]
#
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ testlearn::kcsection; TEMP::ksection ]
Set Field [ testlearn::filterFind; "main" ]
Set Field [ testlearn::kctest; "###" & $$tagTest ]
Perform Find [ ]
Set Variable [ $$stopLoadCitation ]
#
#If records are found using test, then stop script.
If [ Get (FoundCount) ≠ 0 ]
Move/Resize Window [ Current Window; Height: Get ( ScreenHeight ); Width: 333; Top: 0 ]
Show Custom Dialog [ Title: "!"; Message: "This test is linked to at least one Learn record. You can delete this test after removing these links (created in the Learn module)."; Buttons: “OK” ]
#
Close Window [ Current Window ]
Set Variable [ $$ID; Value:test::_Ltest ]
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
Refresh Window
Go to Field [ test::testName ]
[ Select/perform ]
Scroll Window
[ To Selection ]
Go to Field [ ]
Show Custom Dialog [ Title: "!"; Message: "Delete " & test::testName & "?"; Buttons: “Cancel”, “Delete” ]
#
#If the user cancels the delete, then everything
#goes back to the way it was before the delete
#was started.
If [ Get ( LastMessageChoice ) = 1 ]
Set Variable [ $delete ]
Set Variable [ $$ID; Value:test::_Ltest ]
Refresh Window
Exit Script [ ]
End If
#
#If the user presses 'delete' the system will now
#check if this test is the last test in its test group.
If [ Get ( LastMessageChoice ) = 2 ]
#
New Window [ Height: 1; Width: 1; Top: -1000; Left: -1000 ]
#
Set Variable [ $section; Value:test::ksection ]
#( a test group field is neccessary because a section
# may have more than one test group, and so trying
# to find a test group using the section key and
# the testGroup match field would find all groups
# when we need the system to find one group. )
Set Variable [ $group; Value:test::ktestGroup ]
Set Variable [ $test; Value:test::_Ltest ]
#
#Find all tests in this test group.
Go to Layout [ “tableTest” (test) ]
Enter Find Mode [ ]
Set Field [ test::ktestGroup; $group ]
Perform Find [ ]
#
#If the test is the last test, the user is informed
#of this and asked if knowing this they want to
#delete both the test and the test group, since
#a test group cannot exist without at least one test
#in it.
If [ Get (FoundCount) = 1 ]
January 7, 平成26 12:17:15 Imagination Quality Management.fp7 - deleteTest -1-testScreens: setup: deleteTest
#
Close Window [ Current Window ]
#
Set Variable [ $deleteGroup; Value:$delete ]
Refresh Window
Show Custom Dialog [ Title: "!"; Message: "If you delete this group's last test, it will also be deleted."; Buttons: “Cancel”, “Delete” ]
#
#If the user cancels the delete, then everything
#goes back to the way it was before the delete
#was started.
If [ Get ( LastMessageChoice ) = 1 ]
Set Variable [ $delete ]
Set Variable [ $deleteGroup ]
Refresh Window
Set Variable [ $$ID; Value:test::_Ltest ]
Exit Script [ ]
End If
#
#If the user pressed delete then first the
#test group is deleted.
#
New Window [ ]
#
Go to Layout [ “tableGroupTag” (groupTest) ]
Enter Find Mode [ ]
Set Field [ groupTest::_Lgroup; $group ]
Perform Find [ ]
Delete Record/Request
[ No dialog ]
End If
#
End If
#
#Remove test's key from test-item groups that
#have it plus other keys.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Go to Layout [ “setupTestItem” (tagMenus) ]
Enter Find Mode [ ]
Set Field [ ruleTagMenuTestGroups::match; $test & ¶ ]
Perform Find [ ]
Go to Record/Request/Page
[ First ]
Loop
If [ ValueCount (ruleTagMenuTestGroups::match) > 1 ]
Set Variable [ $match; Value:ruleTagMenuTestGroups::match ]
Set Field [ ruleTagMenuTestGroups::match; Substitute ( $match ; $test & "¶" ; "" ) ]
End If
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Delete the test's test items that are only linked
#to this one test.
Enter Find Mode [ ]
Set Field [ ruleTagMenuTestGroups::match; $test & ¶ ]
Perform Find [ ]
Delete All Records
[ No dialog ]
Set Variable [ $$stopLoadTagRecord ]
#
#Finally, the test itself is deleted.
Go to Layout [ “tableTest” (test) ]
Enter Find Mode [ ]
Set Field [ test::_Ltest; $test ]
Perform Find [ ]
Delete Record/Request
[ No dialog ]
Close Window [ Current Window ]
#
#If this was the last test and there are no more
#tests, then the test focuses and attributes for
#this test section will also be deleted (as
#without any tests there is no need for a test
#focus or attribute).
If [ Get (FoundCount) = 0 ]
#
Set Field [ TEMP::ktestListtTestName; "" ]
Set Field [ TEMP::ktestItemListOLD; "" ]
Set Field [ TEMP::ktestItemList; "" ]
Set Field [ TEMP::kcfocuses; "" ]
Set Field [ TEMP::kfocus; "" ]
Set Field [ TEMP::ktest; "" ]
#
New Window [ ]
#
Go to Layout [ “setupTestFocus” (tagLocation) ]
Enter Find Mode [ ]
Set Field [ tagLocation::ksection; TEMP::ksection ]
Set Field [ tagLocation::match; "focus" ]
Perform Find [ ]
Delete All Records
[ No dialog ]
#
Enter Find Mode [ ]
Set Field [ tagLocation::ksection; TEMP::ksection ]
Set Field [ tagLocation::match; "attribute" ]
Perform Find [ ]
Delete All Records
#
Close Window [ Current Window ]
End If
#
#Load current test's information.
Set Variable [ $$ID ]
Perform Script [ “loadSetupTestRecord” ]
January 7, 平成26 12:17:15 Imagination Quality Management.fp7 - deleteTest -2-
