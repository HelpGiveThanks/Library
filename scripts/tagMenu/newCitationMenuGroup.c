tagMenu: newCitationMenuGroup
Go to Field [ ]
#
#If node is currenlty locked then stop script, inform user.
If [ TEMP::nodeLock ≠ "" ]
Show Custom Dialog [ Message: "The default node selected is locked. Select this node in the setup window and enter the password to unlock it, then you will able to create new records assigned to this node."; Buttons: “OK” ]
Exit Script [ ]
End If
If [ tempSetup::kdefaultNodePrimary = "" and $$stopAddBack ≠ 1 ]
Show Custom Dialog [ Message: "Select yourself (the node responsible) from Tag Menus window OR create a node record for yourself?"; Buttons: “select”, “create” ]
If [ Get ( LastMessageChoice ) = 1 ]
Halt Script
Else
Set Field [ tempSetup::kdefaultNodePrimary; "self" ]
End If
End If
#
If [ tempSetup::ksection = "" ]
Show Custom Dialog [ Message: "First select a section for this category to be created under, then you may create a new category."; Buttons: “OK” ]
Exit Script [ ]
End If
Go to Layout [ “tableGroupTag” (groupTest) ]
#
New Record/Request
Set Field [ groupTest::ksection; TEMP::ksection ]
Set Field [ groupTest::kRecordCreatorNode; TEMP::kdefaultNodePrimary ]
#
If [ $$citationMatch = "otherkey" or
$$citationMatch = "primarykey" ]
Set Field [ groupTest::match; "key" ]
Else If [ $$citationMatch ≠ "otherkey" ]
Set Field [ groupTest::match; $$citationMatch ]
End If
#
Set Field [ groupTest::name; "group" & groupTest::_Lgroup ]
Set Field [ groupTest::nameSpelling; "group" & groupTest::_Lgroup ]
Set Variable [ $group; Value:groupTest::_Lgroup ]
#
If [ $$citationMatch = "sample" ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
End If
#
Go to Layout [ original layout ]
New Record/Request
Set Field [ tagMenus::kGroupOrTest; $group ]
#
#Only test focus tags require section. All other tags
#are linked to groups and then the groups are linked
#to sections.
If [ $$citationMatch = "location" ]
Set Field [ tagMenus::ksection; TEMP::ksection ]
End If
// Set Field [ tagMenus::ksection; TEMP::ksection ]
If [ tempSetup::kdefaultNodePrimary = "self" ]
Set Field [ tagMenus::tag; "MyLastName, MyFirstName" ]
Set Field [ TEMP::kdefaultNodePrimary; tagMenus::_Ltag ]
Set Field [ ruleTagMenuGroups::kRecordCreatorNode; tagMenus::_Ltag ]
Else
Set Field [ tagMenus::kRecordCreatorNode; TEMP::kdefaultNodePrimary ]
End If
If [ $$citationMatch = "key" ]
Set Field [ tagMenus::match; "key" ]
Set Field [ tagMenus::tag; "keyword " & tagMenus::_Ltag ]
Else If [ $$citationMatch = "node" ]
Set Field [ tagMenus::match; "node" ]
Else If [ $$citationMatch ≠ "key" or
$$citationMatch ≠ "node" ]
Set Field [ tagMenus::match; $$citationMatch ]
End If
Sort Records [ Speciﬁed Sort Order: ruleTagMenuGroups::name; ascending
tagMenus::orderOrLock; based on value list: “order”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
If [ $$citationMatch = "sample" ]
Set Variable [ $$stopLoadTagRecord ]
Perform Script [ “loadItemRecordForSampleTagMenu” ]
End If
Go to Field [ tagMenus::tag ]
[ Select/perform ]
January 7, 平成26 16:04:20 Imagination Quality Management.fp7 - newCitationMenuGroup -1-
