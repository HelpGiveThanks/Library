July 21, 2018 14:17:00 Library.fmp12 - newTagMenuTag -1-
tagMenu: newTagMenuTag
#
#Admin tasks.
Set Error Capture [ On ]
Allow User Abort [ Off ]
Go to Field [ ]
#
#If the user has not selected a primary node,
#then prevent this script from creating new
#records. All records must be created by the
#primary node.
If [ tempSetup::kdefaultNodePrimary = "" ]
Show Custom Dialog [ Message: "Select yourself (the node responsible for creating and editing records) from the nodes listed
below, OR create a new node record for yourself."; Default Button: “select”, Commit: “Yes”; Button 2: “create”, Commit: “No” ]
If [ Get ( LastMessageChoice ) = 1 ]
Halt Script
Else
Set Field [ tempSetup::kdefaultNodePrimary; "self" ]
End If
End If
#
#
#If no tags exist, then create a group of tags for
#this first tag to belong to. All tags must belong
#to a tag group.
If [ Get (FoundCount) = 0 ]
Perform Script [ “newTagMenuTagGroup (update)” ]
Exit Script [ ]
End If
#
#If node is currenlty locked then stop script,
#and inform the user.
If [ tempSetup::kdefaultNodePrimary ≠ "self" ]
Perform Script [ “stopNewRecordsBeingCreatedByLockedNode (update)” ]
End If
#
#Stop spelling check script.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
#
#
#Create new tag.
New Record/Request
#
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
#
#Give this new tag the group ID number underwhich
#it was created.
Set Field [ tagMenus::kGroupOrTest; GetNthRecord ( tagMenus::kGroupOrTest ; Get (RecordNumber) - 1 ) ]
#
#Get group ID for 'move' button script.
Set Variable [ $$groupOLD; Value:tagMenus::kGroupOrTest ]
#
#Capture recordID to conditionally format current record.
Set Variable [ $$tagRecordID; Value:Get (RecordID) ]
#
#
#Setup as the new primary node.
If [ tempSetup::kdefaultNodePrimary = "self" or $$createNewPrimary = 1 ]
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
Go to Field [ tagMenus::tag ]
Set Variable [ $$stopLoadTagRecord ]
Exit Script [ ]
#
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
#
Go to Field [ tagMenus::tag ]
#
Else If [ $$citationMatch = "brainstorm" ]
#
Set Field [ tagMenus::match; "brainstorm" ]
#
#Tag is new so it has no learn records tagged with it.
#So, clear this variable.
Set Variable [ $$atLeastOneRecord ]
#
#Set default copyright for tag.
Set Field [ tagMenus::notesOrCopyright; TEMP::kdefaultCopyright ]
#
#Set the other three variables that would normally
#be set by the load tag record script.
Set Variable [ $$tagBrainstorm; Value:tagMenus::_Ltag ]
Set Field [ TEMP::kcbrainstorm; tagMenus::_Ltag ]
Set Variable [ $$BrainstormOrTestID; Value:Get (RecordID) ]
#
#Refresh conditional formatting in the learn window
#in case the previous tag did have learn records
#tagged with it.
Select Window [ Name: "Learn"; Current file ]
Refresh Window
#
#Sort these learn records in case they where ordered
#for the previous brainstorm tag.
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearn::date; descending
testlearn::timestamp; descending ]
[ Restore; No dialog ]
#
Select Window [ Name: "Tag Menus"; Current file ]
Refresh Window
Go to Field [ tagMenus::tag ]
Set Variable [ $$stopLoadTagRecord ]
Exit Script [ ]
#
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
Go to Field [ tagMenus::tag ]
End If
#
Set Variable [ $$stopLoadTagRecord ]
#
#If this is a new copyright tag then open up
#the edit copyright tag window.
If [ $$citationMatch = "copyright" ]
Set Field [ tagMenus::tag; "Copyright Abbreviation — Full copyright name or brief description" ]
Set Field [ tagMenus::tagSpelling; "Copyright Abbreviation — Full copyright name or brief description" ]
Set Field [ tagMenus::notesOrCopyright; TextSize ( TextFont ( "[NOTE: Click the 'web' button above to view the most current and
complete source of the text below, copied on " & MonthName ( Get ( CurrentDate ) ) & " " & Day ( Get ( CurrentDate ) ) & ", " &
Year ( Get ( CurrentDate ) ) & " from https://website.org for your convenience.]" ; "Arial" ) & ¶ ; 16 ) &
TextSize ( ¶ &
"Description of copyright from the webpage you copied it from (copy and paste it here)."
& ¶ & ¶ &
"Create a reference record for this copyright that includes the web address."
& ¶ & ¶ &
"Use the add button to add the reference with the website link to this copyright record and a copyright image, which you may
pick from those included in this library." ; 18 ) ]
Commit Records/Requests
[ Skip data entry validation; No dialog ]
Perform Script [ “reviewCopyright (update)” ]
Go to Field [ tagMenus::tag ]
End If
#
#Run primary node script if user is creating a
#new primary node.
If [ $$createNewPrimary = 1 ]
Perform Script [ “addORremovePrimaryTag (update)” ]
Set Variable [ $$createNewPrimary ]
Go to Field [ tagMenus::tag ]
[ Select/perform ]
End If
#
#
