January 19, 2018 14:35:43 Library.fmp12 - addORremoveOtherTagStep2_node -1-
tagMenu: addORremoveOtherTagStep2_node
#
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
#This script adds tags to main reference or learn
#other tag fields.
If [ $$skipFirstPartOfScript ≠ 1 ]
#
#Get current record IDs in reference or
#learn or setup window.
#
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
If [ Get (LastError) = 112 ]
// Select Window [ Name: "Setup"; Current file ]
Set Variable [ $$node; Value:tempSetup::kdefaultNodeOther ]
Else If [ Get (LastError) ≠ 112 ]
Set Variable [ $$node; Value:testlearn::kNodeOther ]
End If
Else If [ Get (LastError) ≠ 112 ]
Set Variable [ $$node; Value:reference::knodeOther ]
End If
#
Select Window [ Name: "Tag Menus"; Current file ]
#
#
#Create a new window in order to perform the next part
#without moving from the selected tag.
#To do this, as this is being added after the script below
#was written, a hack is needed (so not the best way to
#accomplish this). Rename the current window and then
#call the new window Tag Menus. Then when done undo
#the renaming.
Set Variable [ $currentSelectedTag; Value:tagMenus::_Ltag ]
Set Variable [ $closeWindowWhenDone; Value:1 ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Set Window Title [ Current Window; New Title: "Tag Menus Change Back When Done" ]
New Window [ Name: "Tag Menus"; Height: 1; Width: 1; Top: -10000; Left: -10000; Style: Document; Close: “Yes”; Minimize:
“Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
#
#Make sure all tags are showing. User may be only
#showing a few of the tags after performing a find.
Enter Find Mode [ ]
Set Field [ tagMenus::match; $$citationMatch ]
Perform Find [ ]
#
#Now loop to user selected tag.
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ $currentSelectedTag = tagMenus::_Ltag ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#
#If tag user clicked has not yet been selected, then add it.
If [ tagMenus::_Ltag & "¶" ≠ FilterValues ( $$node ; tagMenus::_Ltag & "¶" ) ]
#
Set Variable [ $newNode; Value:tagMenus::_Ltag ]
#
#Set record number so can return user to it when done.
Set Variable [ $recordNumber; Value:Get (RecordNumber) ]
#
#
#Add node in reference or observation window.
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
If [ Get (LastError) = 112 ]
// Select Window [ Name: "Setup"; Current file ]
Set Field [ tempSetup::kdefaultNodeOther; $newNode & "¶" & $$Node ]
Set Variable [ $$Node; Value:tempSetup::kdefaultNodeOther ]
If [ tempSetup::kdefaultNodePrimary = $newNode ]
Set Field [ tempSetup::kdefaultNodePrimary; "" ]
Set Variable [ $$citationItem ]
End If
Go to Field [ ]
Else If [ Get (LastError) ≠ 112 ]
Set Field [ testlearn::kNodeOther; $newNode & "¶" & $$Node ]
Set Variable [ $$Node; Value:testlearn::kNodeOther ]
If [ testlearn::kNodePrimary = $newNode ]
Set Field [ testlearn::kNodePrimary; "" ]
Set Variable [ $$citationItem ]
End If
Go to Field [ ]
End If
Else If [ Get (LastError) ≠ 112 ]
Set Field [ reference::knodeOther; $newNode & "¶" & $$Node ]
Set Variable [ $$Node; Value:reference::knodeOther ]
If [ reference::knodePrimary = $newNode ]
Set Field [ reference::knodePrimary; "" ]
Set Variable [ $$citationItem ]
End If
Go to Field [ ]
End If
#
#
Select Window [ Name: "Tag Menus"; Current file ]
Refresh Window
#
#Now re-alphabetize and add new node to citation.
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenus::tag; ascending ]
[ Restore; No dialog ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Go to Record/Request/Page
[ First ]
#
#
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
If [ Get (LastError) = 112 ]
// Select Window [ Name: "Setup"; Current file ]
Set Variable [ $otherNodes; Value:tempSetup::DEFAULTNodeOtherNames ]
Else If [ Get (LastError) ≠ 112 ]
Set Variable [ $otherNodes; Value:testlearn::NodeOthers ]
End If
Else If [ Get (LastError) ≠ 112 ]
Set Variable [ $otherNodes; Value:reference::NodeOthers ]
End If
#
#
#Find and set first value in node list.
#It will not have a comma in front like the other items.
Select Window [ Name: "Tag Menus"; Current file ]
Loop
If [ tagMenus::_Ltag & "¶" = FilterValues ( $$Node ; tagMenus::_Ltag & "¶" ) ]
Set Variable [ $newNode; Value:tagMenus::tag ]
#
#
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
If [ Get (LastError) = 112 ]
// Select Window [ Name: "Setup"; Current file ]
Set Field [ tempSetup::DEFAULTNodeOtherNames; $newNode ]
Set Variable [ $otherNodes; Value:tempSetup::DEFAULTNodeOtherNames ]
Else If [ Get (LastError) ≠ 112 ]
Set Field [ testlearn::NodeOthers; $newNode ]
Set Variable [ $otherNodes; Value:testlearn::NodeOthers ]
End If
Else If [ Get (LastError) ≠ 112 ]
Set Field [ reference::NodeOthers; $newNode ]
Set Variable [ $otherNodes; Value:reference::NodeOthers ]
#
#If the user is adding a node tag to reference
#record on the main reference layout, then
#inform why they will not see it if the 'open
#authors' field is filled in.
If [ reference::referenceNodes ≠ "" and Get (LayoutName) = "Reference" ]
Show Custom Dialog [ Message: "Because the open authors field is filled in, this node tag — while
added to this reference — will not show up as a reference author. Click 'edit' to edit the open
authors field and see this reference's node tags."; Default Button: “OK”, Commit: “Yes” ]
End If
End If
End If
#
#
Select Window [ Name: "Tag Menus"; Current file ]
Exit Loop If [ tagMenus::_Ltag & "¶" = FilterValues ( $$Node ; tagMenus::_Ltag & "¶" ) ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Now add remaining nodes to list.
Loop
Go to Record/Request/Page
[ Next; Exit after last ]
If [ tagMenus::_Ltag & "¶" = FilterValues ( $$Node ; tagMenus::_Ltag & "¶" ) ]
Set Variable [ $newNode; Value:tagMenus::tag ]
#
#
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
If [ Get (LastError) = 112 ]
// Select Window [ Name: "Setup"; Current file ]
Set Field [ tempSetup::DEFAULTNodeOtherNames; $otherNodes & "; " & $newNode ]
Set Variable [ $otherNodes; Value:tempSetup::DEFAULTNodeOtherNames ]
Set Variable [ $setup; Value:1 ]
Else If [ Get (LastError) ≠ 112 ]
Set Field [ testlearn::NodeOthers; $otherNodes & "; " & $newNode ]
Set Variable [ $otherNodes; Value:testlearn::NodeOthers ]
End If
Else If [ Get (LastError) ≠ 112 ]
Set Field [ reference::NodeOthers; $otherNodes & "; " & $newNode ]
Set Variable [ $otherNodes; Value:reference::NodeOthers ]
End If
End If
#
#
Select Window [ Name: "Tag Menus"; Current file ]
// Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Commit records so user can change spelling.
#Without commit, the system will not find
#the newly added tag.
Commit Records/Requests
Go to Field [ ]
Select Window [ Name: "Tag Menus"; Current file ]
#
Set Variable [ $$stopLoadTagRecord ]
Set Variable [ $$doNotHaltOtherScripts; Value:1 ]
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
Go to Record/Request/Page [ $recordNumber ]
[ No dialog ]
#
#Now close working Tag Menus window and rename
#users Tag Menus window to Tag Menus.
Close Window [ Name: "Tag Menus"; Current file ]
Set Window Title [ Of Window: "Tag Menus Change Back When Done"; Current file; New Title: "Tag Menus" ]
Select Window [ Name: "Tag Menus"; Current file ]
Refresh Window
#
#Select the default copyright for this node if blank.
If [ tagMenus::notesOrCopyright = "" ]
Set Field [ tagMenus::notesOrCopyright; TEMP::kdefaultCopyright ]
Show Custom Dialog [ Message: "Because this node's copyright was blank it was given the library's default copyright.";
Default Button: “OK”, Commit: “No” ]
End If
#
Set Variable [ $$doNotHaltOtherScripts ]
Exit Script [ ]
End If
End If
#
#
#Give primary node the current copyright tag
#for use when this node creates new test
#sections, subsections, and items. It's OK if
#the copyright has not yet been selected as
#when first setting up a library. It will be
#assigned to the primary node when the user
#selects the default copyright or changes it.
Select Window [ Name: "Tag Menus"; Current file ]
If [ tagMenus::notesOrCopyright = "" ]
Set Field [ tagMenus::notesOrCopyright; TEMP::kdefaultCopyright ]
Refresh Window
Show Custom Dialog [ Message: "This node's copyright has been updated to match the library's default copyright."; Default
Button: “OK”, Commit: “Yes” ]
Else If [ tagMenus::notesOrCopyright ≠ "" and tagMenus::notesOrCopyright ≠ tempSetup::kdefaultCopyright and tagMenus::_Ltag =
tempSetup::kdefaultNodePrimary ]
Set Variable [ $$copyright; Value:tagMenus::notesOrCopyright ]
Set Field [ tempSetup::kdefaultCopyright; tagMenus::notesOrCopyright ]
Refresh Window
Show Custom Dialog [ Message: "The library's default copyright has been updated to match the default node's copyright.";
Default Button: “OK”, Commit: “Yes” ]
End If
#
#
#If tag has been selected, then remove it from
#the other node field if is there.
Set Variable [ $removeNode; Value:tagMenus::_Ltag ]
#
#Set record number so can return user to it
#when done checking the other node fields
#containing other node names and keys.
Set Variable [ $recordNumber; Value:Get (RecordNumber) ]
#
#
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
If [ Get (LastError) = 112 ]
// Select Window [ Name: "Setup"; Current file ]
Set Variable [ $$Node; Value:tempSetup::kdefaultNodeOther ]
Set Field [ tempSetup::kdefaultNodeOther; //last item in list has no paragraph mark, so a valuecount test needs to be done
and if item is not removed, then the removal calc without the paragraph mark is used
If ( ValueCount ( $$Node ) ≠ ValueCount ( Substitute ( $$Node ; $removeNode & "¶" ; "" ) ) ;
Substitute ( $$Node ; $removeNode & "¶" ; "" ) ;
Substitute ( $$Node ; $removeNode ; "" )
) ]
Set Variable [ $$Node; Value:tempSetup::kdefaultNodeOther ]
Go to Field [ ]
Else If [ Get (LastError) ≠ 112 ]
Set Field [ testlearn::kNodeOther; //last item in list has no paragraph mark, so a valuecount test needs to be done and if item
is not removed, then the removal calc without the paragraph mark is used
If ( ValueCount ( $$Node ) ≠ ValueCount ( Substitute ( $$Node ; $removeNode & "¶" ; "" ) ) ;
Substitute ( $$Node ; $removeNode & "¶" ; "" ) ;
Substitute ( $$Node ; $removeNode ; "" )
) ]
Set Variable [ $$Node; Value:testlearn::kNodeOther ]
Go to Field [ ]
End If
Else If [ Get (LastError) ≠ 112 ]
Set Field [ reference::knodeOther; //last item in list has no paragraph mark, so a valuecount test needs to be done and if item is
not removed, then the removal calc without the paragraph mark is used
If ( ValueCount ( $$Node ) ≠ ValueCount ( Substitute ( $$Node ; $removeNode & "¶" ; "" ) ) ;
Substitute ( $$Node ; $removeNode & "¶" ; "" ) ;
Substitute ( $$Node ; $removeNode ; "" )
) ]
Set Variable [ $$Node; Value:reference::knodeOther ]
Go to Field [ ]
End If
#
#
#
#
#
#
#
#This next part of the script checks to see if
#the otherNode field was affected.
If [ $$skipFirstPartOfScript = 1 ]
#
#
#
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
If [ Get (LastError) = 112 ]
// Select Window [ Name: "Setup"; Current file ]
Set Variable [ $removeNode; Value:tempSetup::kdefaultNodePrimary ]
Else If [ Get (LastError) ≠ 112 ]
Set Variable [ $removeNode; Value:testlearn::kNodePrimary ]
End If
Else If [ Get (LastError) ≠ 112 ]
Set Variable [ $removeNode; Value:reference::knodePrimary ]
End If
Select Window [ Name: "Tag Menus"; Current file ]
Set Variable [ $recordNumber; Value:Get (RecordNumber) ]
Else If [ $$skipFirstPartOfScript ≠ 1 ]
Select Window [ Name: "Tag Menus"; Current file ]
Set Variable [ $removeNode; Value:tagMenus::tag ]
End If
Refresh Window
#
#
#
#
#Now re-alphabetize after removing node.
If [ $$skipFirstPartOfScript = 1 ]
Set Variable [ $$skipFirstPartOfScript ]
#
#
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
If [ Get (LastError) = 112 ]
// Select Window [ Name: "Setup"; Current file ]
Set Variable [ $removeNode; Value:tempSetup::kdefaultNodePrimary ]
Else If [ Get (LastError) ≠ 112 ]
Set Variable [ $removeNode; Value:testlearn::kNodePrimary ]
End If
Else If [ Get (LastError) ≠ 112 ]
Set Variable [ $removeNode; Value:reference::knodePrimary ]
End If
#
#
End If
#
#
#Order list alphabetically to re-construct otherNode
#field belonging to the citation record.
// Sort Records [ ]
[ No dialog ]
// Set Variable [ $$stopLoadTagRecord; Value:1 ]
// Go to Record/Request/Page
[ First ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Select Window [ Name: "Tag Menus"; Current file ]
New Window [ Name: "reorder"; Height: 1; Width: 1; Top: -1000; Left: -1000; Style: Document; Close: “Yes”; Minimize: “Yes”;
Maximize: “Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
Go to Layout [ “ltagSCRIPTloops” (tagMenus) ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenus::tag; ascending ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ First ]
#
#
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
If [ Get (LastError) = 112 ]
// Select Window [ Name: "Setup"; Current file ]
Set Variable [ $otherNodes; Value:tempSetup::DEFAULTNodeOtherNames ]
#
#Clear the field now in case all tags have been de-selected.
Set Field [ tempSetup::DEFAULTNodeOtherNames; "" ]
Else If [ Get (LastError) ≠ 112 ]
Set Variable [ $otherNodes; Value:testlearn::NodeOthers ]
#
#Clear the field now in case all tags have been de-selected.
Set Field [ testlearn::NodeOthers; "" ]
End If
Else If [ Get (LastError) ≠ 112 ]
Set Variable [ $otherNodes; Value:reference::NodeOthers ]
#
#Clear the field now in case all tags have been de-selected.
Set Field [ reference::NodeOthers; "" ]
End If
#
#
#Find and set first value in node list.
#It will not have a comma in front like the other items.
// Select Window [ Name: "Tag Menus"; Current file ]
Select Window [ Name: "reorder"; Current file ]
Go to Record/Request/Page
[ First ]
Loop
If [ tagMenus::_Ltag & "¶" = FilterValues ( $$Node ; tagMenus::_Ltag & "¶" )
and
tagMenus::tag ≠ $removeNode ]
Set Variable [ $newNode; Value:tagMenus::tag ]
#
#
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Setup"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
// Go to Layout [ “learnSCRIPTloops” (testlearn) ]
Set Field [ testlearn::NodeOthers; $newNode ]
Set Variable [ $otherNodes; Value:testlearn::NodeOthers ]
Else If [ Get (LastError) ≠ 112 ]
Set Field [ tempSetup::DEFAULTNodeOtherNames; $newNode ]
Set Variable [ $otherNodes; Value:tempSetup::DEFAULTNodeOtherNames ]
End If
Else If [ Get (LastError) ≠ 112 ]
Set Field [ reference::NodeOthers; $newNode ]
Set Variable [ $otherNodes; Value:reference::NodeOthers ]
End If
End If
#
#
// Select Window [ Name: "Tag Menus"; Current file ]
Select Window [ Name: "reorder"; Current file ]
Exit Loop If [ tagMenus::_Ltag & "¶" = FilterValues ( $$Node ; tagMenus::_Ltag & "¶" )
and
tagMenus::tag ≠ $removeNode ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Now add remaining nodes to alphabetical list.
Go to Layout [ “ltagSCRIPTloops” (tagMenus) ]
If [ Get (LastError) ≠ 101 ]
Go to Record/Request/Page
[ Next; Exit after last ]
If [ Get (LastError) = 101 ]
Set Variable [ $$stopLoadTagRecord ]
Set Variable [ $$doNotHaltOtherScripts; Value:1 ]
Close Window [ Name: "reorder"; Current file ]
Set Variable [ $$skipFirstPartOfScript ]
#
#Now close working Tag Menus window and rename
#users Tag Menus window to Tag Menus.
If [ $closeWindowWhenDone = 1 ]
Close Window [ Name: "Tag Menus"; Current file ]
Set Window Title [ Of Window: "Tag Menus Change Back When Done"; Current file; New Title: "Tag Menus" ]
End If
Select Window [ Name: "Tag Menus"; Current file ]
Refresh Window
Set Variable [ $$doNotHaltOtherScripts ]
Exit Script [ ]
End If
Loop
If [ tagMenus::_Ltag & "¶" = FilterValues ( $$Node ; tagMenus::_Ltag & "¶" )
and
tagMenus::tag ≠ $removeNode ]
Set Variable [ $newNode; Value:tagMenus::tag ]
#
#
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Setup"; Current file ]
Set Field [ tempSetup::DEFAULTNodeOtherNames; $otherNodes & "; " & $newNode ]
Set Variable [ $otherNodes; Value:tempSetup::DEFAULTNodeOtherNames ]
Else If [ Get (LastError) ≠ 112 ]
// Go to Layout [ “learnSCRIPTloops” (testlearn) ]
Set Field [ testlearn::NodeOthers; $otherNodes & "; " & $newNode ]
Set Variable [ $otherNodes; Value:testlearn::NodeOthers ]
End If
Else If [ Get (LastError) ≠ 112 ]
Set Field [ reference::NodeOthers; $otherNodes & "; " & $newNode ]
Set Variable [ $otherNodes; Value:reference::NodeOthers ]
End If
End If
#
#
// Select Window [ Name: "Tag Menus"; Current file ]
Select Window [ Name: "reorder"; Current file ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
End If
#
Close Window [ Name: "reorder"; Current file ]
Set Variable [ $$skipFirstPartOfScript ]
#
#Now close working Tag Menus window and rename
#users Tag Menus window to Tag Menus.
If [ $closeWindowWhenDone = 1 ]
Close Window [ Name: "Tag Menus"; Current file ]
Set Window Title [ Of Window: "Tag Menus Change Back When Done"; Current file; New Title: "Tag Menus" ]
End If
Select Window [ Name: "Tag Menus"; Current file ]
Set Variable [ $$stopLoadTagRecord ]
Refresh Window
#
