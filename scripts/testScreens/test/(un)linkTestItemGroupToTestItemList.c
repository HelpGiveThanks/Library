testScreens: test: (un)linkTestItemGroupToTestItemList
Set Error Capture [ On ]
Allow User Abort [ Off ]
Go to Field [ ]
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
Set Variable [ $group; Value:ruleTagMenuTestGroups::_Lgroup ]
New Window [ ]
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
#Check each test item against each test discovery record
#for this test item.
Go to Layout [ “step4_InspectionFinding” (testlearn) ]
Enter Find Mode [ ]
Set Field [ testlearn::ktest; $$item ]
Perform Find [ ]
Go to Record/Request/Page
[ First ]
#
#The first loop checks for each test item.
Set Variable [ $groupNumber; Value:1 ]
#
#
#The first loop checks for each test item.
Loop
Set Variable [ $item; Value:GetValue ( $check ; $groupNumber ) ]
#
#Second loop checks the selected test item against each
#key in each discovery record's test item keychain.
Loop
Set Variable [ $number; Value:1 ]
Loop
If [ FilterValues ( GetValue ( testlearn::kctestItem ; $number ) ; $item & ¶ ) = $item & ¶ ]
Set Variable [ $addToInUse; Value:$inUse ]
Set Variable [ $inUse; Value:$addToInUse & $item & ¶ ]
Set Variable [ $number; Value:"exit" ]
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
Set Variable [ $$stopLoadTestRecord ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Close Window [ Current Window ]
#
#If in use the stop script.
If [ $inUse ≠ "" ]
Refresh Window
Show Custom Dialog [ Message: "The highlighed items are currently in use. Uncheck these items from the tests using them and then you will be able to unlink this group of items."; Buttons: “OK” ]
Set Variable [ $inUse ]
Refresh Window
Exit Script [ ]
End If
#
#Capture group key to be linked to or unlinked
#from the current test-item list.
Set Variable [ $addTestItemGroup; Value:addTestItemGroup::addTestItemGroup ]
#
#Open a new window and find this test item group.
New Window [ ]
Go to Layout [ “tableGroupTag” (groupTest) ]
Enter Find Mode [ ]
Set Field [ groupTest::_Lgroup; $addTestItemGroup ]
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
January 7, 平成26 12:20:50 Imagination Quality Management.fp7 - (un)linkTestItemGroupToTestItemList -1-testScreens: test: (un)linkTestItemGroupToTestItemList
#than one test.
If [ ValueCount ( groupTest::match ) = 1 ]
Close Window [ Current Window ]
Go to Field [ ]
Show Custom Dialog [ Message: "This group cannot be unlinked because it is only linked to this test-item list and unlinking it would orphan it. Option 1: delete all items in group to remove it. Option 2: link it to another test and then unlink it from this test."; Buttons: “OK” ]
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
January 7, 平成26 12:20:50 Imagination Quality Management.fp7 - (un)linkTestItemGroupToTestItemList -2-
