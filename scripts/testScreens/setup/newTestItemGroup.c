testScreens: setup: newTestItemGroup
#
#If node is currenlty locked then stop script, inform user.
If [ TEMP::nodeLock ≠ "" ]
Show Custom Dialog [ Message: "The default record creation node -- " & TEMP::DEFAULTNodePrimaryName & " -- is locked. Select this node in the setuptag window and enter the password to unlock it so that you can create new records attributed to it."; Buttons: “OK” ]
Exit Script [ ]
End If
#
#If there are no tests, then stop this script as there
#are no test to create things for.
If [ TEMP::ktest = "" ]
Show Custom Dialog [ Message: "There are no tests."; Buttons: “OK” ]
Exit Script [ ]
End If
#
Go to Layout [ “tableGroupTag” (groupTest) ]
#
New Record/Request
Set Field [ groupTest::ksection; TEMP::ksection ]
#
#Each test-item group must have a unique name and
#the nameSpelling field is used when the user
#changes the name to a name already in use at
#which point the nameSpelling name can revert
#the user back to the former name (as the name
#field contains the duplicate name which is not
#allowed).
Set Field [ groupTest::name; "test item group " & groupTest::_Lgroup ]
Set Field [ groupTest::kRecordCreatorNode; TEMP::kdefaultNodePrimary ]
Set Field [ groupTest::nameSpelling; "testItemGroup" ]
Set Field [ groupTest::match; TEMP::ktest & ¶ ]
Set Variable [ $group; Value:groupTest::_Lgroup ]
#
#Create an item for this goup as all groups must
#have at least one item. Item layout is sorted by
#by group and then item and groups are only
#shown as subheaders. So without an item
#even if a group it existed it would not show up.
Go to Layout [ original layout ]
New Record/Request
Set Field [ tagMenus::match; "testItem" ]
Set Field [ tagMenus::kGroupOrTest; $group ]
Set Field [ tagMenus::ksection; TEMP::ksection ]
Set Field [ tagMenus::tag; "item " & tagMenus::_Ltag ]
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
January 7, 平成26 12:19:15 Imagination Quality Management.fp7 - newTestItemGroup -1-
