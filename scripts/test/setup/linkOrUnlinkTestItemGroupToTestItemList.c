January 12, 2018 14:22:44 Library.fmp12 - linkOrUnlinkTestItemGroupToTestItemList -1-
test: setup: linkOrUnlinkTestItemGroupToTestItemList
#
#
Set Error Capture [ On ]
Allow User Abort [ Off ]
Go to Field [ ]
#
#If subsection is locked stop its test item list
#from being changed, other than added to.
If [ $$lockedMainSubsectionRecord ≠ "" ]
Show Custom Dialog [ Message: "This subsection is locked. Go to the Setup node menu and enter the password for the node —
" & tagCreatorLock::tag & " — to unlock it."; Default Button: “OK”, Commit: “Yes” ]
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
New Window [ Name: "Test Results"; Height: 1; Width: 1; Top: -10000; Left: -10000; Style: Document; Close: “Yes”; Minimize: “Yes”;
Maximize: “Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
// New Window [ Name: "Test Results"; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”;
Resize: “Yes” ]
Enter Find Mode [ ]
Set Field [ tagMenuTestItemGroup::_Lgroup; $group ]
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
#see if any are being used as check-of-the#list
items for the selected general inquiry in
#the Setup window.
Go to Layout [ “testResult0” (testlearn) ]
Enter Find Mode [ ]
Set Field [ testlearn::ktestSubsection; TEMP::ktestSubsection ]
Perform Find [ ]
#
#Go the first record.
Go to Record/Request/Page
[ First ]
#
#Prepare the message window, by clearing all
#records from the last time it was used.
Go to Layout [ “TEMP” (TEMP) ]
Show All Records
Delete All Records
[ No dialog ]
Go to Layout [ “testResult0” (testlearn) ]
#
#The first loop checks for each test item.
Set Variable [ $groupNumber; Value:1 ]
#
#The first loop checks link of test-item group
#to the selected subsection currently using it.
Loop
Set Variable [ $item; Value:GetValue ( $check ; $groupNumber ) ]
#
#Second loop checks if any of the test items in
#the group are used (checked off) for any test
#result records.
Loop
Set Variable [ $number; Value:1 ]
Loop
If [ FilterValues ( GetValue ( testlearn::kctestResultCheckedItems ; $number ) ; $item & ¶ ) = $item & ¶ ]
#
Set Variable [ $addToInUse; Value:$inUse ]
Set Variable [ $inUse; Value:$addToInUse & $item & ¶ ]
#
Set Variable [ $useList; Value:tagTLTestSubject::tag &
" | test/report " &
TextColor( TextStyleAdd ( testlearn::kreportNumber; "" ) ;RGB(0;0;0)) &
¶ &
"section " &
TextColor( TextStyleAdd ( testSectionTemplateName::name; "" ) ;RGB(0;0;0)) &
¶ &
"title " & TextColor( TextStyleAdd ( testlearn::subsectionCustomName; "" ) ;RGB(0;0;0)) ]
Go to Layout [ “TEMP” (TEMP) ]
New Record/Request
Set Field [ TEMP::DeleteMessageInTempWindow1; $useList ]
Go to Layout [ “testResult0” (testlearn) ]
End If
#
#If number was set to exit or if no keys exist, then
#exit loop.
Exit Loop If [ GetValue ( testlearn::kctestResultCheckedItems ; $number ) = "" ]
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
Sort Records [ Keep records in sorted order; Specified Sort Order: TEMP::DeleteMessageInTempWindow1; ascending ]
[ Restore; No dialog ]
View As
[ View as List ]
#
Show/Hide Toolbars
[ Lock; Hide ]
Show/Hide Text Ruler
[ Hide ]
#
#Due to a bug in FM13, window must first be
#moved back into the screen area before the
#calculation of the current screen's
#dimensions can be taken.
Move/Resize Window [ Current Window; Top: 0; Left: 0 ]
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
New Window [ Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
Go to Layout [ “tableTagGroup” (testSubsectionGroup) ]
Enter Find Mode [ ]
Set Field [ testSubsectionGroup::_Lgroup; $group ]
Perform Find [ ]
#
#Capture current list of testList keys.
Set Variable [ $match; Value:testSubsectionGroup::match ]
#
#Remove the key from the list of test-item
#group keys, unless it only belongs to this list,
#in which case tell user that rather than
#unlinking it, the list needs to be deleted
#or linked to another test before unlinking it
#from the current test's list.
If [ TEMP::ktestItemSubsection & "¶" = FilterValues ( $match ; TEMP::ktestItemSubsection & "¶" ) ]
#
#Determine if test-item group belongs to more
#than one test.
If [ ValueCount ( testSubsectionGroup::match ) = 1 ]
Close Window [ Current Window ]
Go to Field [ ]
Show Custom Dialog [ Message: "This group cannot be unlinked because it is only linked to this test-item list and unlinking it
would orphan it. Option 1: delete all items in group to remove it. Option 2: link it to another test and then unlink it from
this test."; Default Button: “OK”, Commit: “No” ]
Set Variable [ $groupHighlight ]
Refresh Window
Exit Script [ ]
Else If [ ValueCount ( testSubsectionGroup::match ) ≠ 1 ]
Set Field [ testSubsectionGroup::match; Substitute ( $match ; TEMP::ktestItemSubsection & "¶" ; "" ) ]
Close Window [ Current Window ]
End If
#
#Add the key to list of test keys, if it is not currently
#part of this list.
Else If [ TEMP::ktestItemSubsection & "¶" ≠ FilterValues ( $match ; TEMP::ktestItemSubsection & "¶" ) ]
Set Field [ testSubsectionGroup::match; TEMP::ktestItemSubsection & ¶ & $match ]
Set Variable [ $newGrouphasBeenAdded; Value:1 ]
Close Window [ Current Window ]
End If
#
#Show newly added group and its test items.
Perform Script [ “menuTestItem” ]
#
#Take user to group added.
If [ $newGrouphasBeenAdded ]
If [ $group = tagMenuTestItemGroup::_Lgroup ]
Set Variable [ $$stopLoadTagRecord ]
Exit Script [ ]
End If
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ $group = tagMenuTestItemGroup::_Lgroup ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
Set Variable [ $$stopLoadTagRecord ]
Perform Script [ “loadTagRecord” ]
End If
#
#
