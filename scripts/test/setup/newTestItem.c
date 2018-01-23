January 12, 2018 14:13:04 Library.fmp12 - newTestItem -1-
test: setup: newTestItem
#This script is for creating a test item.
#
#If the node that created this group is locked
#prevent new items be created for it even by a
#node that is not locked.
If [ nodeLockTestTagItemGroup::orderOrLock ≠ "" ]
Show Custom Dialog [ Message: "This group is locked. Go the node that created this group — " & nodeLockTestTagItemGroup::
tag & " — in the setup tag window and enter the password to unlock it so that you can create items for it."; Default Button:
“OK”, Commit: “Yes” ]
Exit Script [ ]
End If
#
#If node is currenlty locked then stop script,
#and inform the user.
Perform Script [ “stopNewRecordsBeingCreatedByLockedNode” ]
#
#Stop this script if there are no subsections
#for which to create test items.
If [ TEMP::ktestSubsection = "" ]
Show Custom Dialog [ Message: "All test items must belong to (be linked to) at least one test subsection. Create one now, and
then you can create new test items and test-item groups for it."; Default Button: “OK”, Commit: “No” ]
Exit Script [ ]
End If
#
#If there are no test items, then create a new test
#item group first and then a test for that group.
#All test items belong to test item groups, not
#tests. This allows test item groups to be added
#to other test's test-item lists.
If [ Get (FoundCount) = 0 ]
Perform Script [ “newTestItemGroup” ]
Exit Script [ ]
End If
#
#Capturet he current item's type and style
#to apply to the new item.
Set Variable [ $checkORtextORform; Value:Case ( tagMenus::notesOrCopyright ≠ "" ; tagMenus::notesOrCopyright ; "✓" ) ]
Set Variable [ $style; Value:tagMenus::textStyleOrCreatorNodeFlag ]
#
#Copy current item's style setting.
Set Variable [ $style; Value:tagMenus::textStyleOrCreatorNodeFlag ]
#
#Copy current item's order number.
Set Variable [ $orderNumber; Value:tagMenus::orderOrLock ]
#
#Create an item for this goup of test items.
New Record/Request
Set Field [ tagMenus::match; "testItem" ]
Set Field [ tagMenus::orderOrLock; $orderNumber ]
Set Field [ tagMenus::orderOrLock[2]; $orderNumber ]
Set Field [ tagMenus::textStyleOrCreatorNodeFlag; $style ]
Set Field [ tagMenus::notesOrCopyright; $checkORtextORform ]
Set Field [ tagMenus::kGroupOrTest; GetNthRecord ( tagMenus::kGroupOrTest ; Get (RecordNumber) - 1 ) ]
Set Field [ tagMenus::tag; "test-item" & tagMenus::_Ltag ]
Set Field [ tagMenus::tagSpelling; "test-item" & tagMenus::_Ltag ]
Set Field [ tagMenus::kRecordCreatorNode; TEMP::kdefaultNodePrimary ]
Go to Field [ ]
#
#Apply tag style.
If [ tagMenus::textStyleOrCreatorNodeFlag = "1" ]
Set Field [ tagMenus::tag; Trim (tagMenus::tag) ]
Set Field [ tagMenus::tag; TextFont ( tagMenus::tag ; "Georgia" ) ]
Set Field [ tagMenus::tag; TextColor ( tagMenus::tag ; RGB ( 99 ; 99 ; 99 ) ) ]
Else If [ tagMenus::textStyleOrCreatorNodeFlag = "2" ]
Set Field [ tagMenus::tag; Trim (tagMenus::tag) ]
Set Field [ tagMenus::tag; TextFont ( tagMenus::tag ; "Arial" ) ]
Set Field [ tagMenus::tag; TextColorRemove ( tagMenus::tag ; RGB ( 99 ; 99 ; 99 ) ) ]
Else If [ tagMenus::textStyleOrCreatorNodeFlag = "3" ]
Set Field [ tagMenus::tag; Trim (tagMenus::tag) ]
Set Field [ tagMenus::tag; TextSize ( tagMenus::tag ; 20 ) ]
Set Field [ tagMenus::tag; TextFont ( tagMenus::tag ; "Arial" ) ]
Set Field [ tagMenus::tag; TextStyleAdd ( tagMenus::tag ; Bold ) ]
Set Field [ tagMenus::tag; TextColor ( tagMenus::tag ; RGB ( 99 ; 99 ; 99 ) ) ]
End If
Go to Field [ tagMenus::tag ]
[ Select/perform ]
#
