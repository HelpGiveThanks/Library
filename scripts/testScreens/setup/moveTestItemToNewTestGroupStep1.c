testScreens: setup: moveTestItemToNewTestGroupStep1
#
#This script is for moving a general inquiry to different group.
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
If [ nodeLockTest::orderOrLock ≠ "" ]
Go to Field [ ]
Show Custom Dialog [ Message: "This record is locked. Go the node that created it -- " & nodeLockTest::tag & " -- in the setup tag window and enter the password to unlock it so that you can move it."; Buttons: “OK” ]
Exit Script [ ]
End If
Set Variable [ $$groupOLD; Value:test::ktestGroup ]
Set Variable [ $$moveItem; Value:test::_Ltest ]
Refresh Window
December 9, ଘ౮27 19:49:51 Library.fp7 - moveTestItemToNewTestGroupStep1 -1-
