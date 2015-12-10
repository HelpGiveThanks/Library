testScreens: setup: newTestItem
#This script is for creating a specific inquiry.
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
Show Custom Dialog [ Message: "The default record creation node -- " & TEMP::DEFAULTNodePrimaryName & " -- is locked. Select this node in the setup tag window and enter the password to unlock it so that you can create new records attributed to it."; Buttons: “OK” ]
Exit Script [ ]
End If
#
#If there are no general test inquires, then
#stop this script as there are no general inquires
# to create specific inquires for.
If [ TEMP::ktest = "" ]
Show Custom Dialog [ Message: "There are no tests."; Buttons: “OK” ]
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
#Create an item for this goup of test items.
New Record/Request
Set Field [ tagMenus::match; "testItem" ]
Set Field [ tagMenus::kGroupOrTest; GetNthRecord ( tagMenus::kGroupOrTest ; Get (RecordNumber) - 1 ) ]
Set Field [ tagMenus::ksection; TEMP::ksection ]
Set Field [ tagMenus::tag; "specific_inquiry" & tagMenus::_Ltag ]
Set Field [ tagMenus::tagSpelling; "specific_inquiry" & tagMenus::_Ltag ]
Set Field [ tagMenus::kRecordCreatorNode; TEMP::kdefaultNodePrimary ]
Go to Field [ ]
Go to Field [ tagMenus::tag ]
[ Select/perform ]
December 9, ଘ౮27 19:44:51 Library.fp7 - newTestItem -1-
