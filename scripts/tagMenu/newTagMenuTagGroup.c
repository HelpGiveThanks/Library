July 21, 2018 14:17:17 Library.fmp12 - newTagMenuTagGroup -1-
tagMenu: newTagMenuTagGroup
#
#Admin tasks.
Allow User Abort [ Off ]
Set Error Capture [ On ]
Go to Field [ ]
#
#Users need to use existing copyright groups.
If [ $$citationMatch = "copyright" ]
Exit Script [ ]
End If
#
#If node is currenlty locked then stop script,
#and inform the user.
Perform Script [ “stopNewRecordsBeingCreatedByLockedNode” ]
#
#If the user has not selected a primary node,
#then prevent this script from creating new
#records. All records must be created by the
#primary node.
If [ tempSetup::kdefaultNodePrimary = "" and $$stopAddBack ≠ 1 ]
#Make sure all creator nodes are showing
#before asking the user to select one or
#create one.
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ tagMenus::match; $$citationMatch ]
Set Field [ tagMenus::textStyleOrCreatorNodeFlag; 123456789 ]
Perform Find [ ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenuGroup::orderOrLibraryType; based on value list:
“order Pulldown List”
tagMenuGroup::name; ascending
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Show Custom Dialog [ Message: "Select yourself (the node responsible for creating and editing records) from the nodes listed
below, OR create a new node record for yourself."; Default Button: “select”, Commit: “Yes”; Button 2: “create”, Commit: “No” ]
If [ Get ( LastMessageChoice ) = 1 ]
Halt Script
Else
Set Field [ tempSetup::kdefaultNodePrimary; "self" ]
End If
End If
#
#Create new tag group.
Go to Layout [ “tableTagGroup” (testSubsectionGroup) ]
New Record/Request
Set Field [ testSubsectionGroup::kRecordCreatorNode; TEMP::kdefaultNodePrimary ]
#
#Note the type of tag this group is for.
If [ $$citationMatch = "otherkey" or
$$citationMatch = "primarykey" ]
Set Field [ testSubsectionGroup::match; "key" ]
Else If [ $$citationMatch ≠ "otherkey" ]
Set Field [ testSubsectionGroup::match; $$citationMatch ]
End If
#
#Set the groups identification fields.
Set Field [ testSubsectionGroup::name; "group" & testSubsectionGroup::_Lgroup ]
Set Field [ testSubsectionGroup::nameSpellingEXCEPTForTestItemGroup; "group" & testSubsectionGroup::_Lgroup ]
Set Variable [ $group; Value:testSubsectionGroup::_Lgroup ]
#(Further testing required. This group is
#created by the new library script, so it does
#not need to be created here.)
// If [ tempSetup::kdefaultNodePrimary = "self" ]
// Set Field [ testSubsectionGroup::orderOrLibraryType; "001" ]
// End If
#
#
#Create new tag for this group so it will show up.
If [ $$citationMatch = "brainstorm" ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Else
Set Variable [ $$doNotHaltOtherScripts; Value:1 ]
End If
Go to Layout [ original layout ]
New Record/Request
#
#In Learn and Setup sections make node tag
#into a creator node = a node that can create
#and edit library records.
If [ $$citationMatch = "node" and Left (Get (LayoutName) ; 1) = "l"
 or
$$citationMatch = "node" and Left (Get (LayoutName) ; 1) = "d" ]
Set Field [ tagMenus::kRecordCreatorNode; tagMenus::_Ltag ]
Set Field [ tagMenus::textStyleOrCreatorNodeFlag; 123456789 ]
#
#
#For all other tags, and for Reference Section
#node tags, assign the default node/author as
#the tag's creator.
Else
Set Field [ tagMenus::kRecordCreatorNode; TEMP::kdefaultNodePrimary ]
End If
#
#Give this new tag the group ID number underwhich
#it was created.
Set Field [ tagMenus::kGroupOrTest; $group ]
#
#Setup as the new primary node.
If [ tempSetup::kdefaultNodePrimary = "self" ]
Set Field [ TEMP::kdefaultNodePrimary; tagMenus::_Ltag ]
Set Field [ tagMenus::tag; "LastName, FirstName" ]
Set Field [ tagMenus::tagSpelling; "LastName, FirstName" ]
Set Variable [ $$createNewPrimary; Value:1 ]
Set Field [ tempSetup::kdefaultNodePrimary; "" ]
Set Field [ tempSetup::DEFAULTNodePrimaryName; "" ]
Set Field [ tempSetup::kdefaultNodePrimaryCreator; "" ]
Set Field [ tempSetup::primaryNodesCreatorNodeIsLocked; "" ]
End If
#
#Finish assigning new tag to the current menu item.
If [ $$citationMatch = "key" ]
Set Field [ tagMenus::match; "key" ]
#
#Leave key name field blank so user can enter
#a new name into a blank field, but create a
#tagSpelling unique name should the user
#leave this field blank, which will then become
#the record's unique name upon leaving the
#record, as key and node records cannot be
#blank records.
Set Field [ tagMenus::tagSpelling; "keyword " & tagMenus::_Ltag ]
Else If [ $$citationMatch = "node" ]
Set Field [ tagMenus::match; "node" ]
#
#Set default copyright for tag.
Set Field [ tagMenus::notesOrCopyright; TEMP::kdefaultCopyright ]
#
#Leave key name field blank so user can enter
#a new name into a blank field, but create a
#tagSpelling unique name should the user
#leave this field blank, which will then become
#the record's unique name upon leaving the
#record, as key and node records cannot be
#blank records.
Set Field [ tagMenus::tagSpelling; "node " & tagMenus::_Ltag ]
Else If [ $$citationMatch ≠ "key" or
$$citationMatch ≠ "node" ]
Set Field [ tagMenus::match; $$citationMatch ]
#
#If a path tag, ask user if this path is to a shelf.
If [ $$citationMatch = "path" ]
Show Custom Dialog [ Message: "Is this computer path OR a path to a real place (example: living room bookcase)?";
Default Button: “computer”, Commit: “Yes”; Button 2: “real place”, Commit: “No” ]
If [ Get ( LastMessageChoice ) = 2 ]
Set Field [ tagMenus::kfileORkTestItemCreatorNode; 1 ]
End If
End If
#
End If
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenuGroup::orderOrLibraryType; based on value list: “order
Pulldown List”
tagMenuGroup::name; ascending
tagMenus::tag; ascending ]
[ Restore; No dialog ]
If [ $$citationMatch = "brainstorm" ]
#
#Set default copyright for tag.
Set Field [ tagMenus::notesOrCopyright; TEMP::kdefaultCopyright ]
Perform Script [ “loadBrainstormTags (udpate)” ]
Else
Set Variable [ $$doNotHaltOtherScripts ]
End If
#
#Capture recordID to conditionally format current record.
Set Variable [ $$tagRecordID; Value:Get (RecordID) ]
#
#Get group ID for 'move' button script.
Set Variable [ $$groupOLD; Value:tagMenus::kGroupOrTest ]
#
If [ $$citationMatch = "copyright" ]
Set Field [ tagMenus::tag; "Copyright Abbreviation — Full copyright name or brief description" ]
Set Field [ tagMenus::tagSpelling; "Copyright Abbreviation — Full copyright name or brief description" ]
Set Field [ tagMenus::notesOrCopyright; TextFont ( "[NOTE: Click the 'web' button above to view the most current and complete
source of the text excerpts below, copied on " & MonthName ( Get ( CurrentDate ) ) & " " & Day ( Get ( CurrentDate ) ) & ", " &
Year ( Get ( CurrentDate ) ) & " from https://website.org for your convenience.]" ; "Arial" ) & ¶ & ¶ &
"Description of copyright from the webpage you copied it from (copy and paste it here)."
& ¶ & ¶ &
"Create a reference record for this copyright that includes the web address."
& ¶ & ¶ &
"Use the add button to add the reference with the website link to this copyright record and a copyright image, which you may
pick from those included in this library." ]
Commit Records/Requests
[ Skip data entry validation; No dialog ]
Perform Script [ “reviewCopyright” ]
Go to Field [ tagMenus::tag ]
[ Select/perform ]
End If
#
#Run primary node script if user is creating a
#new primary node.
If [ $$createNewPrimary = 1 ]
Perform Script [ “addORremovePrimaryTag” ]
Set Variable [ $$createNewPrimary ]
Go to Field [ tagMenus::tag ]
[ Select/perform ]
End If
#
#If not already in the field, then go to it now.
Go to Field [ tagMenus::tag ]
#
