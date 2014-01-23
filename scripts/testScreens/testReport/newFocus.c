testScreens: testReport: newFocus
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
Set Field [ tagLocation::ksection; TEMP::ksection ]
Set Field [ tagLocation::match; "focus" ]
Set Field [ tagLocation::kRecordCreatorNode; TEMP::kdefaultNodePrimary ]
Go to Field [ tagLocation::tag ]
January 7, 平成26 14:31:53 Imagination Quality Management.fp7 - newFocus -1-
