tagMenu: moveTagToNewGroupStep1
#
#If node is currenlty locked then stop script, inform user.
If [ nodeLockTagMenus::orderOrLock ≠ "" ]
Go to Field [ ]
Show Custom Dialog [ Message: "This record is locked. Go the node that created it -- " & nodeLockTagMenus::tag & " -- in the setup tag window and enter the password to unlock it so that you can move it."; Buttons: “OK” ]
Exit Script [ ]
End If
If [ tagMenus::orderOrLock = "lock" ]
Go to Field [ ]
Exit Script [ ]
End If
If [ ValueCount ( ruleTagMenuGroups::ksection ) > 1 ]
#
#If group user is moving tag from is in more than
#one section of the database, then stop the move.
#The problem is that if this tag is in use, and the
#user moves it to a section that does not exist
#in one of the sections using it, then in that section
#the user will not be able to ﬁnd by this tag or
#or remove it. The remedy would be to add
#the group being moved to to all the sections using
#the tag. I leaving this remedy for another day.
Go to Field [ ]
Show Custom Dialog [ Title: "!"; Message: tagMenus::tag & " cannot be moved because its group belongs to more than one section. Tags can be moved as long as the groups they are being moved from belong to only one section."; Buttons: “OK” ]
Exit Script [ ]
End If
Set Variable [ $$groupOLD; Value:tagMenus::kGroupOrTest ]
Set Variable [ $$moveItem; Value:tagMenus::_Ltag ]
Refresh Window
January 7, 平成26 16:09:21 Imagination Quality Management.fp7 - moveTagToNewGroupStep1 -1-
