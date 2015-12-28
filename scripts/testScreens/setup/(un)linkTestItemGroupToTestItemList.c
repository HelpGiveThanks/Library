testScreens: setup: (un)linkTestItemGroupToTestItemList
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
Set Error Capture [ On ]
Allow User Abort [ Off ]
Go to Field [ ]
#
#
If [ nodeLockTestTagGroup::orderOrLock ≠ "" ]
Show Custom Dialog [ Message: "This record is locked. Go the node that created it -- " & nodeLockTagMenus::tag & " -- and
enter the password to unlock it."; Buttons: “OK” ]
Exit Script [ ]
End If
#
#Exit script if any of the current groups test items
#are in use. ( At a later date, improve this script
# so it finds the specific records in use and informs
# user of them specficially so user can find
# them and know how many their are. )
#
#find and show all test records that might be using
#any item in this group.
Set Variable [ $$stopLoadTestRecord; Value:1 ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Set Variable [ $$stopDeleteTest; Value:1 ]
Set Variable [ $$stopTest; Value:1 ]
#
#Capture group key to be linked to or unlinked
#from the link pulldown selection the user just made.
Set Variable [ $group; Value:addTestItemGroup::addTestItemGroup ]
Set Variable [ $groupHighlight; Value:addTestItemGroup::addTestItemGroup ]
Set Field [ addTestItemGroup::addTestItemGroup; "" ]
New Window [ Name: "Test Results"; Height: 1; Width: 1; Top: -10000; Left: -10000 ]
// New Window [ Name: "Test Results" ]
Enter Find Mode [ ]
Set Field [ ruleTagMenuTestGroups::_Lgroup; $group ]
Perform Find [ ]
#
#Create a variable keychain of all test items that could
#be used.
Go to Record/Request/Page
[ First ]
Loop
Set Variable [ $addToCheck; Value:$check ]
Set Variable [ $check; Value:tagMenus::_Ltag & ¶ & $addToCheck ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Check each specific inquiry in its group to
#see if any are being used as check-of-the-
#list items for the selected general inquiry in
#the Setup window.
Go to Layout [ “step4_InspectionFinding” (testlearn) ]
Enter Find Mode [ ]
Set Field [ testlearn::ktest; TEMP::ktest ]
Perform Find [ ]
#
Go to Record/Request/Page
[ First ]
#
#
Go to Layout [ “TEMP” (TEMP) ]
Show All Records
Delete All Records
[ No dialog ]
Go to Layout [ “step4_InspectionFinding” (testlearn) ]
#
#The first loop checks for each test item.
Set Variable [ $groupNumber; Value:1 ]
#
#The first loop checks specific inquiry for use
#by the general inquiry record.
Loop
Set Variable [ $item; Value:GetValue ( $check ; $groupNumber ) ]
#
#Second loop checks the selected specific inquiry
#against each key in each test-result record's
#specific inquiry keychain.
Loop
Set Variable [ $number; Value:1 ]
Loop
If [ FilterValues ( GetValue ( testlearn::kctestItem ; $number ) ; $item & ¶ ) = $item & ¶ ]
#
Set Variable [ $addToInUse; Value:$inUse ]
Set Variable [ $inUse; Value:$addToInUse & $item & ¶ ]
#
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
End If
#
#If number was set to exit or if no keys exist, then
#exit loop.
Exit Loop If [ GetValue ( testlearn::kctestItem ; $number ) = "" ]
#
#If variable looked at did not match then raise the number
#to view the next variable.
Set Variable [ $add; Value:$number ]
Set Variable [ $number; Value:$add + 1 ]
End Loop
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#If no more items in group then exit loop.
Exit Loop If [ GetValue ( $check ; $groupNumber ) = "" ]
#
#If variable looked at did not match then raise the number
#to view the next variable.
Set Variable [ $addToGroup; Value:$groupNumber ]
Set Variable [ $groupNumber; Value:$addToGroup + 1 ]
Go to Record/Request/Page
[ First ]
End Loop
#
#
If [ $inUse ≠ "" ]
Select Window [ Name: "Tag Menus"; Current file ]
Refresh Window
Select Window [ Name: "Test Results"; Current file ]
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
Move/Resize Window [ Name: "Test Results"; Current file; Height: Get ( ScreenHeight ); Width: 360; Top: 0; Left: Get
( ScreenWidth ) - ( Get ( ScreenWidth )/2 + 360) ]
Set Field [ TEMP::Message; "To unlink this specific-inquiry group, uncheck the highlighted specific inquires (in the test module)
from the test results below." ]
Pause/Resume Script [ Indefinitely ]
Close Window [ Current Window ]
Set Variable [ $delete ]
Set Variable [ $cannotDelete ]
Set Variable [ $groupHighlight ]
Set Variable [ $$stopLoadTestRecord ]
Set Variable [ $$stopLoadTagRecord ]
Set Variable [ $$stopDeleteTest ]
Set Variable [ $$stopTest ]
Refresh Window
Exit Script [ ]
#
Else
Close Window [ Current Window ]
Set Variable [ $$stopLoadTestRecord ]
Set Variable [ $$stopLoadTagRecord ]
Set Variable [ $$stopDeleteTest ]
Set Variable [ $$stopTest ]
#
End If
#
#
#Open a new window and find this test item group.
New Window [ ]
Go to Layout [ “tableGroupTag” (groupTest) ]
Enter Find Mode [ ]
Set Field [ groupTest::_Lgroup; $group ]
Perform Find [ ]
#
#Capture current list of testList keys.
Set Variable [ $match; Value:groupTest::match ]
#
#Remove the key from the list of test-item
#group keys, unless it only belongs to this list,
#in which case tell user that rather than
#unlinking it, the list needs to be deleted
#or linked to another test before unlinking it
#from the current test's list.
If [ TEMP::ktestItemList & "¶" = FilterValues ( $match ; TEMP::ktestItemList & "¶" ) ]
#
#Determine if test-item group belongs to more
#than one test.
If [ ValueCount ( groupTest::match ) = 1 ]
Close Window [ Current Window ]
Go to Field [ ]
Show Custom Dialog [ Message: "This group cannot be unlinked because it is only linked to this test-item list and unlinking it
would orphan it. Option 1: delete all items in group to remove it. Option 2: link it to another test and then unlink it from
this test."; Buttons: “OK” ]
Exit Script [ ]
Else If [ ValueCount ( groupTest::match ) ≠ 1 ]
Set Field [ groupTest::match; Substitute ( $match ; TEMP::ktestItemList & "¶" ; "" ) ]
Close Window [ Current Window ]
End If
#
#Add the key to list of test keys, if it is not currently
#part of this list.
Else If [ TEMP::ktestItemList & "¶" ≠ FilterValues ( $match ; TEMP::ktestItemList & "¶" ) ]
Set Field [ groupTest::match; TEMP::ktestItemList & ¶ & $match ]
Close Window [ Current Window ]
End If
#
#Show newly added group and its test items.
Perform Script [ “menuTestItem” ]
#
December 27, ଘ౮27 19:29:11 Library.fp7 - (un)linkTestItemGroupToTestItemList -1-
