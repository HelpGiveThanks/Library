tagMenu: newCitationMenuItem
Go to Field [ ]
#
#If node is currenlty locked then stop script, inform user.
If [ TEMP::nodeLock ≠ "" ]
Show Custom Dialog [ Message: "The default node selected is locked. Select this node in the setup window and enter the password to unlock it, then you will able to create new records assigned to this node."; Buttons: “OK” ]
Exit Script [ ]
End If
If [ tempSetup::kdefaultNodePrimary = "" ]
Show Custom Dialog [ Message: "Select yourself (the node responsible) from Tag Menus window OR create a node record for yourself?"; Buttons: “select”, “create” ]
If [ Get ( LastMessageChoice ) = 1 ]
Halt Script
Else
Set Field [ tempSetup::kdefaultNodePrimary; "self" ]
End If
End If
If [ Get (FoundCount) = 0 ]
Perform Script [ “newCitationMenuGroup” ]
Exit Script [ ]
End If
#
#Stop spelling check script.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
New Record/Request
Set Field [ tagMenus::kGroupOrTest; GetNthRecord ( tagMenus::kGroupOrTest ; Get (RecordNumber) - 1 ) ]
If [ tempSetup::kdefaultNodePrimary = "self" ]
Set Field [ TEMP::kdefaultNodePrimary; tagMenus::_Ltag ]
Set Field [ tagMenus::tag; "MyLastName, MyFirstName" ]
Else
Set Field [ tagMenus::kRecordCreatorNode; TEMP::kdefaultNodePrimary ]
End If
#
#Only test focus tags require section. All other tags
#are linked to groups and then the groups are linked
#to sections.
If [ $$citationMatch = "location" ]
Set Field [ tagMenus::ksection; TEMP::ksection ]
End If
// Set Field [ tagMenus::ksection; TEMP::ksection ]
If [ $$citationMatch = "key" ]
Set Field [ tagMenus::match; "key" ]
Set Field [ tagMenus::tag; "keyword " & tagMenus::_Ltag ]
Go to Field [ tagMenus::tag ]
[ Select/perform ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Exit Script [ ]
Else If [ $$citationMatch = "node" ]
Set Field [ tagMenus::match; "node" ]
Else If [ $$citationMatch ≠ "key" or
$$citationMatch ≠ "node" ]
Set Field [ tagMenus::match; $$citationMatch ]
End If
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Go to Object [ Object Name: "tag" ]
January 7, 平成26 16:04:49 Imagination Quality Management.fp7 - newCitationMenuItem -1-
