testScreens: testReport: newFocus
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
#Create new focus that any test in this section could be assigned to.
New Record/Request
Set Field [ tagLocation::match; "focus" ]
Set Field [ tagLocation::ksection; TEMP::ksection ]
Set Field [ tagLocation::tag; "test_section" ]
Set Field [ tagLocation::tagSpelling; "test_section" ]
Set Field [ tagLocation::kRecordCreatorNode; TEMP::kdefaultNodePrimary ]
Go to Field [ tagLocation::tag ]
December 9, ଘ౮27 20:59:44 Library.fp7 - newFocus -1-
