testScreens: setup: newTestItemGroup
#This script is for creating a specific inquiry group.
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
#If node is currenlty locked then stop script, inform user.
If [ TEMP::nodeLock ≠ "" ]
Show Custom Dialog [ Message: "The default record creation node -- " & TEMP::DEFAULTNodePrimaryName & " -- is locked. Select this node in the setuptag window and enter the password to unlock it so that you can create new records attributed to it."; Buttons: “OK” ]
Exit Script [ ]
End If
#
#If there are no general test inquires, then
#stop this script as there are no general inquires
# to create specific inquires for.
If [ TEMP::ktest = "" ]
Show Custom Dialog [ Message: "To create a specific inquiry there must be general test inquiry to assign it to."; Buttons: “OK” ]
Exit Script [ ]
End If
#
Go to Layout [ “tableGroupTag” (groupTest) ]
#
New Record/Request
Set Field [ groupTest::ksection; TEMP::ksection ]
#
#BEGIN !!!!!!!!!!!!!!!!!!!!!!!!!!!
#READ CAREFULLY!!! nameSpelling field used differently!!!
#Each general-test-inquiry group must have a unique name and
#the defaultSectionInfo field is used when the user
#changes the name to a name already in use at
#which point the defaultSectionInfo name can revert
#the user back to the former name (as the name
#field contains the duplicate name which is not
#allowed).
Set Field [ groupTest::name; "specific-inquiry_group" & groupTest::_Lgroup ]
Set Field [ groupTest::defaultSectionInfo; "specific-inquiry_group" & groupTest::_Lgroup ]
Set Field [ groupTest::kRecordCreatorNode; TEMP::kdefaultNodePrimary ]
Set Variable [ $group; Value:groupTest::_Lgroup ]
#
#
Set Field [ groupTest::match; TEMP::ktest & ¶ ]
#
#NEVER CHANGE!!! This is the key field for the
#link pulldown menu. If you decide to change
#it, you'll have to create a script to change it in
#in older library's group records which will have
#the spelling of the old key and thus not show
#up any longer once the key is changed.
Set Field [ groupTest::nameSpelling; "testItemGroup" ]
#END !!!!!!!!!!!!!!!!!!!!!!!!!!!
#
#Create a general inquiry for this goup as all groups must
#have at least one item. Item layout is sorted by
#by group and then item and groups are only
#shown as subheaders. So without an item
#even if a group it existed it would not show up.
Go to Layout [ original layout ]
New Record/Request
Set Field [ tagMenus::tag; "specific_inquiry" & tagMenus::_Ltag ]
Set Field [ tagMenus::tagSpelling; "specific_inquiry" & tagMenus::_Ltag ]
Set Field [ tagMenus::match; "testItem" ]
Set Field [ tagMenus::kGroupOrTest; $group ]
Set Field [ tagMenus::ksection; TEMP::ksection ]
Set Field [ tagMenus::kRecordCreatorNode; TEMP::kdefaultNodePrimary ]
Go to Field [ ]
Go to Field [ tagMenus::tag ]
[ Select/perform ]
#
#If this is the first record to be created the layout
#must be sorted to get it to show the group for
#this first test item.
If [ Get (FoundCount) = 1 ]
Sort Records [ Specified Sort Order: ruleTagMenuTestGroups::order; based on value list: “order”
ruleTagMenuTestGroups::_Lgroup; ascending
tagMenus::orderOrLock; based on value list: “order”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
End If
December 9, ଘ౮27 19:54:04 Library.fp7 - newTestItemGroup -1-
