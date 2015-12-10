testScreens: setup: deleteTestItem
#
#
#WHEN TIME PERMITS the vocabuary for scripts,
#variable, fields, layouts, etc. needs to be updated
#to reflect that a 'test' is now a 'general inquiry'
#and an 'item' is now a 'specific inquiry' and a 'focus'
#is now a test 'section', etc. A complete look at
#the DDR to insure all vocabulary is updated
#everywhere followed by testing for each
#update is required.
#
#
#If there are no tests, then stop this script as there
#are no test to create things for.
If [ TEMP::ktest = "" ]
Show Custom Dialog [ Message: "There are no tests."; Buttons: “OK” ]
Exit Script [ ]
End If
If [ nodeLockTagMenus::orderOrLock ≠ "" ]
Show Custom Dialog [ Message: "This record is locked. Go the node that created it -- " & nodeLockTagMenus::tag & " -- in the
setup tag window and enter the password to unlock it so that you can delete it."; Buttons: “OK” ]
Exit Script [ ]
End If
If [ Get (FoundCount) = 0 ]
Exit Script [ ]
End If
#
#Get variables needed for delete and delete messages.
Set Variable [ $delete; Value:tagMenus::_Ltag ]
Set Variable [ $group; Value:ruleTagMenuTestGroups::_Lgroup ]
Set Variable [ $groupName; Value:If ( Char ( ruleTagMenuTestGroups::name ) ≤ 20 ; ruleTagMenuTestGroups::name ; Left
( ruleTagMenuTestGroups::name ; 20 ) & "..." ) ]
Set Variable [ $testItemName; Value:If ( Char ( tagMenus::tag ) ≤ 20 ; tagMenus::tag ; Left ( tagMenus::tag ; 20 ) & "..." ) ]
Refresh Window
#
#BEGIN: LEGACY STRATEGY for finding test results
#in use that did not provide enough information.
// #find and show all test records that might be using
// #this item.
// New Window [ Height: 1; Width: 1; Top: -1000; Left: -1000 ]
// Set Variable [ $$stopLoadTestRecord; Value:1 ]
// Go to Layout [ “step4_InspectionFinding” (testlearn) ]
// Set Error Capture [ On ]
// Allow User Abort [ Off ]
// Enter Find Mode [ ]
// Set Field [ testlearn::kctestItem; $delete ]
// Perform Find [ ]
// #
// Sort Records [ Specified Sort Order: testlearn::kreportNumber; ascending ]
[ Restore; No dialog ]
// Go to Record/Request/Page
[ First ]
// #
// #Check if test item is in use by any test result records.
// #Also capture how many results there are using
// #item, and what general inquiries use this specifc inquiry.
// Loop
// Set Variable [ $number; Value:1 ]
// Loop
// If [ FilterValues ( GetValue ( testlearn::kctestItem ; $number ) ; $delete & "¶" ) = $delete & ¶ ]
// Set Variable [ $addToInUse; Value:$inUse ]
// Set Variable [ $inUse; Value:1 + $addToInUse ]
// Set Variable [ $number; Value:"exit" ]
// Set Variable [ $setNumberOfReports; Value:Case (
$report = "" ; 1 ;
$report = testlearn::kreportNumber ; 1 ;
$report ≠ testlearn::kreportNumber and Filter ($report ; testlearn::kreportNumber ) ≠ testlearn::kreportNumber ;
$numberOfReports + 1 ;
Filter ($report ; testlearn::kreportNumber ) = testlearn::kreportNumber ; $numberOfReports ;
"error" ) ]
// Set Variable [ $numberOfReports; Value:$setNumberOfReports ]
// Set Variable [ $setReportNumber; Value:Case (
$report = "" ; testlearn::kreportNumber ;
$report = testlearn::kreportNumber ; testlearn::kreportNumber ;
$report ≠ testlearn::kreportNumber and Filter ($report ; testlearn::kreportNumber ) ≠ testlearn::kreportNumber ;
$report & ", " & testlearn::kreportNumber ;
testlearn::kreportNumber = Filter ($report ; testlearn::kreportNumber ) ; $report ; "error" ) ]
// Set Variable [ $report; Value:$setReportNumber ]
// End If
// #
// #If number was set to exit or if no keys exist, then
// #exit loop.
// Exit Loop If [ GetValue ( testlearn::kctestItem ; $number ) = "" ]
// #
// #If variable looked at did not match then raise the number
// #to view the next variable.
// Set Variable [ $add; Value:$number ]
// Set Variable [ $number; Value:$add + 1 ]
// End Loop
// Go to Record/Request/Page
[ Next; Exit after last ]
// End Loop
// Set Variable [ $report; Value:Case ( Filter ( Right ( $report ; 3 ) ; "," ) = "," ; Replace ( $report; Length ( $report ) - 2 ; 1 ; " and" ) ;
Filter ( Right ( $report ; 4 ) ; "," ) = "," ; Replace ( $report; Length ( $report ) - 3 ; 1 ; " and" ) ;
Filter ( Right ( $report ; 5 ) ; "," ) = "," ; Replace ( $report; Length ( $report ) - 4 ; 1 ; " and" ) ;
$report ) ]
// Set Variable [ $$stopLoadTestRecord ]
// Close Window [ Current Window ]
// #
// #If in use the stop script.
// If [ $inUse ≠ "" ]
// Set Variable [ $cannotDelete; Value:$delete ]
// Refresh Window
// Show Custom Dialog [ Message: If ( $inUse = 1 ; "This specific inquiry is used as a check-off-the-list item for 1 test result in test
" & $report & " in the test module. Uncheck it from this test result to delete it." ;
"This specific inquiry is used as a check-off-the-list item for " & $inUse & " test results" &
If ( $numberOfReports = 1 ; " in test " ; " between tests " ) &
$report &
" in the test module. Uncheck it from all " & $inUse & " results to delete it." ); Buttons: “OK” ]
// Set Variable [ $cannotDelete ]
// Set Variable [ $delete ]
// Refresh Window
// Exit Script [ ]
// End If
#END: LEGACY STRATEGY for finding test results
#in use that did not provide enough information.
#
#
Set Variable [ $$stopLoadTestRecord; Value:1 ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Set Variable [ $$stopDeleteTest; Value:1 ]
Set Variable [ $$stopTest; Value:1 ]
New Window [ Name: " "; Height: 1; Width: 1; Top: -10000; Left: -10000 ]
Go to Layout [ “TEMP” (TEMP) ]
Show All Records
Delete All Records
[ No dialog ]
#
Go to Layout [ “step4_InspectionFinding” (testlearn) ]
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ testlearn::kctestItem; $delete ]
Perform Find [ ]
#
#If this section is found to be in use, then inform
#user of where and prevent its deletion.
If [ Get (LastError) ≠ 401 ]
Loop
Set Variable [ $useList; Value:tagTLTestSubject::tag &
" | test/report " &
TextColor( TextStyleAdd ( testlearn::kreportNumber; "" ) ;RGB(0;0;0)) &
¶ &
"section " &
TextColor( TextStyleAdd ( tagTestResultDefaultSectionName::focusName; "" ) ;RGB(0;0;0)) &
¶ &
"title " & TextColor( TextStyleAdd ( testlearn::Location; "" ) ;RGB(0;0;0)) ]
Go to Layout [ “TEMP” (TEMP) ]
New Record/Request
Set Field [ TEMP::RemoveFocusList; $useList ]
Go to Layout [ “step4_InspectionFinding” (testlearn) ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
Go to Layout [ “TEMP” (TEMP) ]
Sort Records [ Specified Sort Order: TEMP::RemoveFocusList; ascending ]
[ Restore; No dialog ]
View As
[ View as List ]
#
Show/Hide Status Area
[ Lock; Hide ]
Show/Hide Text Ruler
[ Hide ]
Move/Resize Window [ Current Window; Height: Get ( ScreenHeight ); Width: 360; Top: 0; Left: Get ( ScreenWidth ) - ( Get
( ScreenWidth )/2 + 360) ]
Set Field [ TEMP::Message; "Before the highlighted specific inquiry can be deleted, it must unchecked " & ¶ & "(in the test
module) from the test results below." ]
Pause/Resume Script [ Indefinitely ]
Close Window [ Current Window ]
Set Variable [ $delete ]
Set Variable [ $$stopLoadTestRecord ]
Set Variable [ $$stopLoadTagRecord ]
Set Variable [ $$stopDeleteTest ]
Set Variable [ $$stopTest ]
Refresh Window
Exit Script [ ]
Else
Close Window [ Current Window ]
Set Variable [ $$stopLoadTestRecord ]
Set Variable [ $$stopLoadTagRecord ]
Set Variable [ $$stopDeleteTest ]
Set Variable [ $$stopTest ]
End If
#
#
#
#Exit any fields and then contionally format field
#to be deleted by this script.
Go to Field [ ]
Refresh Window
Show Custom Dialog [ Title: "!"; Message: "Delete " & $testItemName & "?"; Buttons: “Cancel”, “Delete” ]
Refresh Window
#
#If the user says yes, first make sure the record
#is not the last record in its group. If it is and
#the system deleted the record without deleting
#the group too, this group would become
#an orphan as only groups that have records
#attached to them show up for the user to add
#more records to them. So the group
#record must also be deleted if this is the last
#test item under it.
If [ Get ( LastMessageChoice ) = 2 ]
New Window [ Name: "delete tag"; Height: 1; Width: 1; Top: -1000; Left: -1000 ]
Go to Layout [ “tableTag” (tagTable) ]
Enter Find Mode [ ]
Set Field [ tagTable::kGroupOrTest; $group ]
Perform Find [ ]
#
#If there are more records under this cateogry
#then the system deletes the current record without
#any more user input.
If [ Get (FoundCount) ≠ 1 ]
Close Window [ Name: "Delete Tag"; Current file ]
Delete Record/Request
[ No dialog ]
Set Variable [ $delete ]
Set Variable [ $group ]
Refresh Window
Exit Script [ ]
#
#BUT if only one record is found user is asked
#if they want to delete the category too.
Else If [ Get (FoundCount) = 1 ]
Select Window [ Name: "Tag Menus"; Current file ]
Set Variable [ $deleteGroup; Value:$group ]
Refresh Window
#
#The records are sorted by category to show
#the user which category is going to be deleted.
If [ TEMP::sortTestItem ≠ "cat" ]
Sort Records [ Specified Sort Order: ruleTagMenuGroups::order; based on value list: “order”
ruleTagMenuGroups::name; ascending
tagMenus::orderOrLock; based on value list: “order”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
End If
#
#Show user warning message dependening on
#whether or not this group is part of other test's
#test-item lists.
If [ ValueCount ( ruleTagMenuTestGroups::match ) > 1 ]
Show Custom Dialog [ Title: "!"; Message: "Deleting " & $testItemName & " will also delete its group: " & $groupName
& ", which is on " & ValueCount ( ruleTagMenuTestGroups::match ) - 1 & " other test-item list(s). Option 1: delete it
from all lists. Option 2: cancel delete. UNLINK this group from this list."; Buttons: “Cancel”, “Delete” ]
Else If [ ValueCount ( ruleTagMenuTestGroups::match ) = 1 ]
Show Custom Dialog [ Title: "!"; Message: "Deleting " & $testItemName & " will also delete its group ' " & $groupName
& "' as it is the last item in this group."; Buttons: “Cancel”, “Delete” ]
End If
#
#If the user says yes, then delete both the tag and
#the category record.
If [ Get ( LastMessageChoice ) = 2 ]
Delete Record/Request
[ No dialog ]
Select Window [ Name: "delete tag"; Current file ]
Go to Layout [ “tableGroupTag” (groupTest) ]
Enter Find Mode [ ]
Set Field [ groupTest::_Lgroup; $group ]
Perform Find [ ]
Delete Record/Request
[ No dialog ]
Close Window [ Name: "Delete Tag"; Current file ]
End If
End If
End If
Set Variable [ $delete ]
Set Variable [ $deleteGroup ]
Refresh Window
December 9, ଘ౮27 19:39:22 Library.fp7 - deleteTestItem -1-
