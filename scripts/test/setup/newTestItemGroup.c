January 12, 2018 14:15:44 Library.fmp12 - newTestItemGroup -1-
test: setup: newTestItemGroup
#
#This script creates test item groups.
#
#
#If node is currenlty locked then stop script,
#and inform the user.
Perform Script [ “stopNewRecordsBeingCreatedByLockedNode” ]
#
#If there are no general test inquires, then
#stop this script as there are no general inquires
# to create specific inquires for.
If [ TEMP::ktestSubsection = "" ]
Show Custom Dialog [ Message: "All test items must belong to (be linked to) at least one test subsection. Create one now, and
then you can create new test items and test-item groups for it."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
#
#Capturet he current item's type and style
#to apply to the new item.
Set Variable [ $checkORtextORform; Value:Case ( tagMenus::notesOrCopyright ≠ "" ; tagMenus::notesOrCopyright ; "✓" ) ]
Set Variable [ $style; Value:tagMenus::textStyleOrCreatorNodeFlag ]
#
#Copy current group's order number.
Set Variable [ $orderNumber; Value:tagMenuTestItemGroup::orderOrLibraryType ]
#
#Create new test item group record.
Go to Layout [ “tableTagGroup” (testSubsectionGroup) ]
New Record/Request
#
#
#BEGIN !!!!!!!!!!!!!!!!!!!!!!!!!!!
#READ CAREFULLY!!! nameSpelling field used differently!!!
#Each test-item group must have a unique name and
#the nameSpellingTestItemGroup field is used when the user
#changes the name to a name already in use at
#which point the nameSpellingTestItemGroup name can revert
#the user back to the former name (as the name
#field contains the duplicate name which is not
#allowed).
Set Field [ testSubsectionGroup::orderOrLibraryType; $orderNumber ]
Set Field [ testSubsectionGroup::orderOrLibraryType[2]; $orderNumber ]
Set Variable [ $group; Value:testSubsectionGroup::_Lgroup ]
Set Field [ testSubsectionGroup::name; "test-item_group" & testSubsectionGroup::_Lgroup ]
Set Field [ testSubsectionGroup::kRecordCreatorNode; TEMP::kdefaultNodePrimary ]
Set Field [ testSubsectionGroup::nameSpellingFORTestItemGroup; "test-item_group" & testSubsectionGroup::_Lgroup ]
#
#
Set Field [ testSubsectionGroup::match; TEMP::ktestSubsection & ¶ ]
#
#NEVER CHANGE!!! This is the key field for the
#link pulldown menu. If you decide to change
#it, you'll have to create a script to change it in
#in older library's group records which will have
#the spelling of the old key and thus not show
#up any longer once the key is changed.
Set Field [ testSubsectionGroup::nameSpellingEXCEPTForTestItemGroup; "testItemGroup" ]
#END !!!!!!!!!!!!!!!!!!!!!!!!!!!
#
#Create a test item for this goup as all groups must
#have at least one item. Item layout is sorted by
#by group and then item and groups are only
#shown as subheaders. So without an item
#even if a group it existed it would not show up.
Go to Layout [ original layout ]
New Record/Request
Set Field [ tagMenus::match; "testItem" ]
Set Field [ tagMenus::notesOrCopyright; $checkORtextORform ]
Set Field [ tagMenus::kGroupOrTest; $group ]
Set Field [ tagMenus::tag; "test-item" & tagMenus::_Ltag ]
Set Field [ tagMenus::textStyleOrCreatorNodeFlag; $style ]
Set Field [ tagMenus::tagSpelling; "test-item" & tagMenus::_Ltag ]
Set Field [ tagMenus::kRecordCreatorNode; TEMP::kdefaultNodePrimary ]
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
#
#Must be sorted to show the group
#for this first test item and when it's
#out of sight.
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenuTestItemGroup::orderOrLibraryType; based on value list:
“order Pulldown List”
tagMenuTestItemGroup::_Lgroup; ascending
tagMenus::orderOrLock; based on value list: “order Pulldown List”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Scroll Window
[ Home ]
#
#Load up all tag variables.
Perform Script [ “loadTagRecord” ]
Go to Field [ tagMenus::tag ]
[ Select/perform ]
#
