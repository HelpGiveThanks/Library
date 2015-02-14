testScreens: setup: newTestItem
#
#If node is currenlty locked then stop script, inform user.
If [ TEMP::nodeLock ≠ "" ]
Show Custom Dialog [ Message: "The default record creation node -- " & TEMP::DEFAULTNodePrimaryName & " -- is locked. Select this node in the setup tag window and enter the password to unlock it so that you can create new records attributed to it."; Buttons: “OK” ]
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
#If there are no test items, then create a new test
#item group first and then a test for that group.
#All test items belong to test item groups, not
#tests. This allows test item groups to be added
#to other test's test item lists.
If [ Get (FoundCount) = 0 ]
Perform Script [ “newTestItemGroup” ]
Exit Script [ ]
End If
#
#Create an item for this goup of test items.
New Record/Request
Set Field [ tagMenus::match; "testItem" ]
Set Field [ tagMenus::kGroupOrTest; GetNthRecord ( tagMenus::kGroupOrTest ; Get (RecordNumber) - 1 ) ]
Set Field [ tagMenus::ksection; TEMP::ksection ]
Set Field [ tagMenus::tag; "item " & tagMenus::_Ltag ]
Set Field [ tagMenus::kRecordCreatorNode; TEMP::kdefaultNodePrimary ]
Go to Field [ ]
Go to Field [ tagMenus::tag ]
[ Select/perform ]
January 7, 平成26 12:18:17 Imagination Quality Management.fp7 - newTestItem -1-
