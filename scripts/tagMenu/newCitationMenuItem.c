tagMenu: newCitationMenuItem
#
#Exit current field.
Go to Field [ ]
#
#If node is currenlty locked then stop script, inform user.
If [ TEMP::nodeLock ≠ "" ]
Show Custom Dialog [ Message: "The default node selected is locked. Select this node in the setup window and enter the password to unlock it, then you will able to create new records assigned to this node."; Buttons: “OK” ]
Exit Script [ ]
End If
#
#No tag record can be created without an author/node.
If [ tempSetup::kdefaultNodePrimary = "" ]
Show Custom Dialog [ Message: "Select yourself (the node responsible) from Tag Menus window OR create a node record for yourself?"; Buttons: “select”, “create” ]
If [ Get ( LastMessageChoice ) = 1 ]
Halt Script
Else
Set Field [ tempSetup::kdefaultNodePrimary; "self" ]
End If
End If
#
#If no tags exist, then create a group of tags for
#this first tag to belong to. All tags must belong
#to a tag group.
If [ Get (FoundCount) = 0 ]
Perform Script [ “newCitationMenuGroup” ]
Exit Script [ ]
End If
#
#Stop spelling check script.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
#
New Record/Request
#
#Give this new tag the group ID number underwhich
#it was created.
Set Field [ tagMenus::kGroupOrTest; GetNthRecord ( tagMenus::kGroupOrTest ; Get (RecordNumber) - 1 ) ]
#
#Assign the default node/author as the tags creator.
If [ tempSetup::kdefaultNodePrimary = "self" ]
Set Field [ TEMP::kdefaultNodePrimary; tagMenus::_Ltag ]
Set Field [ tagMenus::tag; "MyLastName, MyFirstName" ]
Else
Set Field [ tagMenus::kRecordCreatorNode; TEMP::kdefaultNodePrimary ]
End If
#
#MAY NO LONGER be in use = location. Further,
#testing needed to see if this can be removed.
If [ $$citationMatch = "location" ]
Set Field [ tagMenus::ksection; TEMP::ksection ]
End If
#
#Finish assigning new tag to the current menu item.
If [ $$citationMatch = "key" ]
Set Field [ tagMenus::match; "key" ]
Set Field [ tagMenus::tag; "keyword " & tagMenus::_Ltag ]
Go to Object [ Object Name: "tag" ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Exit Script [ ]
#
Else If [ $$citationMatch = "node" ]
Set Field [ tagMenus::match; "node" ]
#
#WHEN THERE IS TIME the words 'sample' and
#'theory' need to be replaced with 'brainstorm'.
Else If [ $$citationMatch = "sample" ]
#
#Tag is new so it has no learn records tagged with it.
#So, clear this variable.
Set Variable [ $$atLeastOneRecord ]
#
#Set the other three variables that would normally
#be set by the load tag record script.
Set Variable [ $$tagsample; Value:tagMenus::_Ltag ]
Set Field [ TEMP::kcsample; tagMenus::_Ltag ]
Set Variable [ $$SampleOrTestID; Value:Get (RecordID) ]
#
#Refresh conditional formatting in the learn window
#in case the previous tag did have learn records
#tagged with it.
Select Window [ Name: "Learn"; Current file ]
Refresh Window
#
#Sort these learn records in case they where ordered
#for the previous brainstorm tag.
Sort Records [ Specified Sort Order: testlearn::date; descending
testlearn::timestamp; descending ]
[ Restore; No dialog ]
#
Select Window [ Name: "Tag Menus"; Current file ]
Refresh Window
Set Variable [ $$stopLoadTagRecord ]
Exit Script [ ]
#
Else If [ $$citationMatch ≠ "key" or
$$citationMatch ≠ "node" ]
Set Field [ tagMenus::match; $$citationMatch ]
End If
#
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Go to Object [ Object Name: "tag" ]
December 9, ଘ౮27 21:32:09 Library.fp7 - newCitationMenuItem -1-
