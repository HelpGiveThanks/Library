January 12, 2018 14:14:19 Library.fmp12 - moveTestItemToNewTestGroupStep1 -1-
test: setup: moveTestItemToNewTestGroupStep1
#
#
#This script is for moving a test item
#to different item group.
#
#
#If there is only one group, exit script.
If [ ValueCount ( ValueListItems ( Get ( FileName ) ; "templateSubsectionGroups" ) ) = 1 ]
Go to Field [ ]
Exit Script [ ]
End If
#
#If node is currenlty locked then stop script, inform user.
If [ testSectionCreatorLock::orderOrLock ≠ "" ]
Go to Field [ ]
Show Custom Dialog [ Message: "This record is locked. Go the node that created it -- " & testSectionCreatorLock::tag & " -- in
the setup tag window and enter the password to unlock it so that you can move it."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
Set Variable [ $$groupOLD; Value:testSubsectionTemplate::ksubsectionGroup ]
Set Variable [ $$moveItem; Value:testSubsectionTemplate::_LtestSubsection ]
Refresh Window
