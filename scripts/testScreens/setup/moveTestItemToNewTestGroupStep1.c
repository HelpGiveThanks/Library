testScreens: setup: moveTestItemToNewTestGroupStep1
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
January 7, 平成26 12:18:46 Imagination Quality Management.fp7 - moveTestItemToNewTestGroupStep1 -1-
