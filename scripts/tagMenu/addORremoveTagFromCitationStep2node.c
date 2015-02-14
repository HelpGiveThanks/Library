tagMenu: addORremoveTagFromCitationStep2node #
Allow User Abort [ Off ]
Set Error Capture [ On ] #
#This script adds tags to main reference or learn
#other tag fields.
If [ $$skipFirstPartOfScript
≠ 1 ]
#
#Get current record IDs in reference or
#learn or setup window. #
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Setup"; Current file ]
Set Variable [ $$node; Value:tempSetup::kdefaultNodeOther ]
Else If [ Get (LastError)
≠ 112 ]
Set Variable [ $$node; Value:testlearn::kNodeOther ]
End If
Else If [ Get (LastError)
≠ 112 ]
Set Variable [ $$node; Value:reference::knodeOther ]
End If #
Select Window [ Name: "Tag Menus"; Current file ] ##
#Create a new window in order to perform the next part
#without moving the focus around on the tag window.
#To do this, as this is being added after the script below
#was written, a hack is needed (so not the best way to
#accomplish this). Rename the current window and then
#call the new window Tag Menus. Then when done undo
#the renaming.
Set Variable [ $currentSelectedTag; Value:tagMenus::_Ltag ]
Set Variable [ $closeWindowWhenDone; Value:1 ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Set Window Title [ Current Window; New Title: "Tag Menus Change Back When Done" ]
New Window [ Name: "Tag Menus"; Height: 1; Width: 1; Top: -1000; Left: -1000 ] #
#Make sure all tags are showing. User may be only
#showing a few of the tags after performing a find.
Enter Find Mode [ ]
Set Field [ tagMenus::match; $$citationMatch ]
Set Field [ ruleTagMenuGroups::ksection; "==" & TEMP::ksection ]
Perform Find [ ] #
#Now loop to user selected tag.
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ $currentSelectedTag = tagMenus::_Ltag ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop ##
#If tag user clicked has not yet been selected, then add it.
If [ tagMenus::_Ltag & "¶"
≠ FilterValues ( $$node ; tagMenus::_Ltag & "¶" ) ]
#
Set Variable [ $newNode; Value:tagMenus::_Ltag ] #
#Set record number so can return user to it when done.
Set Variable [ $recordNumber; Value:Get (RecordNumber) ] ##
#Add node in reference or observation window.
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Setup"; Current file ]
Set Field [ tempSetup::kdefaultNodeOther; $newNode & "¶" & $$Node ]
Set Variable [ $$Node; Value:tempSetup::kdefaultNodeOther ]
If [ tempSetup::kdefaultNodePrimary = $newNode ]
Set Field [ tempSetup::kdefaultNodePrimary; "" ]
Set Variable [ $$citationItem ]
End If
Go to Field [ ]
Else If [ Get (LastError)
≠ 112 ]
Set Field [ testlearn::kNodeOther; $newNode & "¶" & $$Node ]
Set Variable [ $$Node; Value:testlearn::kNodeOther ]
If [ testlearn::kNodePrimary = $newNode ]
Set Field [ testlearn::kNodePrimary; "" ]
Set Variable [ $$citationItem ]
End If
Go to Field [ ]
End If
Else If [ Get (LastError)
≠ 112 ]
Set Field [ reference::knodeOther; $newNode & "¶" & $$Node ]
Set Variable [ $$Node; Value:reference::knodeOther ]
If [ reference::knodePrimary = $newNode ]
Set Field [ reference::knodePrimary; "" ]
Set Variable [ $$citationItem ]
End If
Go to Field [ ]
End If ##
Select Window [ Name: "Tag Menus"; Current file ]
Refresh Window #
#Now re-alphabetize and add new node to citation.
Sort Records [ Specified Sort Order: tagMenus::tag; ascending ]
[ Restore; No dialog ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Go to Record/Request/Page
[ First ]
##
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Setup"; Current file ]
Set Variable [ $otherNodes; Value:tempSetup::DEFAULTNodeOtherNames ]
Else If [ Get (LastError)
≠ 112 ]
Set Variable [ $otherNodes; Value:testlearn::NodeOthers ]
February 13, 平成27 20:59:27 Stuff Library.fp7 - addORremoveTagFromCitationStep2node -1-tagMenu: addORremoveTagFromCitationStep2node
End If
Else If [ Get (LastError)
≠ 112 ]
Set Variable [ $otherNodes; Value:reference::NodeOthers ]
End If ##
#Find and set first value in node list.
#It will not have a comma in front like the other items.
Select Window [ Name: "Tag Menus"; Current file ]
Loop
If [ tagMenus::_Ltag & "¶" = FilterValues ( $$Node ; tagMenus::_Ltag & "¶" ) ]
Set Variable [ $newNode; Value:tagMenus::tag ] ##
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Setup"; Current file ]
Set Field [ tempSetup::DEFAULTNodeOtherNames; $newNode ]
Set Variable [ $otherNodes; Value:tempSetup::DEFAULTNodeOtherNames ]
Else If [ Get (LastError)
≠ 112 ]
Set Field [ testlearn::NodeOthers; $newNode ]
Set Variable [ $otherNodes; Value:testlearn::NodeOthers ]
End If
Else If [ Get (LastError)
≠ 112 ]
Set Field [ reference::NodeOthers; $newNode ]
Set Variable [ $otherNodes; Value:reference::NodeOthers ]
End If
End If ##
Select Window [ Name: "Tag Menus"; Current file ]
Exit Loop If [ tagMenus::_Ltag & "¶" = FilterValues ( $$Node ; tagMenus::_Ltag & "¶" ) ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop #
#Now add remaining nodes to list.
Loop
Go to Record/Request/Page
[ Next; Exit after last ]
If [ tagMenus::_Ltag & "¶" = FilterValues ( $$Node ; tagMenus::_Ltag & "¶" ) ]
Set Variable [ $newNode; Value:tagMenus::tag ] ##
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Setup"; Current file ]
Set Field [ tempSetup::DEFAULTNodeOtherNames; $otherNodes & "; " & $newNode ]
Set Variable [ $otherNodes; Value:tempSetup::DEFAULTNodeOtherNames ]
Set Variable [ $setup; Value:1 ]
Else If [ Get (LastError)
≠ 112 ]
Set Field [ testlearn::NodeOthers; $otherNodes & "; " & $newNode ]
Set Variable [ $otherNodes; Value:testlearn::NodeOthers ]
End If
Else If [ Get (LastError)
≠ 112 ]
Set Field [ reference::NodeOthers; $otherNodes & "; " & $newNode ]
Set Variable [ $otherNodes; Value:reference::NodeOthers ]
End If
End If ##
Select Window [ Name: "Tag Menus"; Current file ]
// Go to Record/Request/Page
[ Next; Exit after last ]
End Loop #
#Commit records so user can change spelling.
#Without commit, the system will not find
#the newly added tag.
Commit Records/Requests
Go to Field [ ]
Select Window [ Name: "Tag Menus"; Current file ] #
// #Sort records according to users wishes.
// #Sort according to current users wishes. By default
// #the sort will be by category which is set by editCitation script.
// If [ TEMP::sortNode = "cat" and Left (Get (LayoutName) ; 11) = "defaultNode"
or
TEMP::sortNode = "" and Left (Get (LayoutName) ; 11) = "defaultNode" ]
// Sort Records [ Specified Sort Order: ruleTagMenuGroups::order; based on value list: “order”
ruleTagMenuGroups::name; ascending
tagMenus::orderOrLock; based on value list: “order”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
// Else If [ TEMP::sortNode = "abc" and Left (Get (LayoutName) ; 11) = "defaultNode" ]
// Sort Records [ Specified Sort Order: tagMenus::tag; ascending ]
[ Restore; No dialog ]
// End If
// If [ TEMP::sortKey = "cat" and Get (LayoutName)
≠ "defaultNode" ]
// Sort Records [ Specified Sort Order: ruleTagMenuGroups::order; based on value list: “order”
ruleTagMenuGroups::name; ascending
tagMenus::orderOrLock; based on value list: “order”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
// Else If [ TEMP::sortKey = "abc" and Get (LayoutName)
≠ "defaultNode" ]
// Sort Records [ Specified Sort Order: tagMenus::tag; ascending ]
[ Restore; No dialog ]
// End If
Set Variable [ $$stopLoadTagRecord ]
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
Go to Record/Request/Page [ $recordNumber ]
[ No dialog ]
#
#If reference or learn record that tag was added
#to belongs to more than one section, then
#add these other sections to the tag's group
#keychain so when this tag record is viewed in
#those sections, the reference or learn record
#just added to it will show up as well.
If [ $setup
≠ 1 ]
Perform Script [ “CHUNKaddMainSectionKeysToTagRecordKeychain” ]
End If #
#Now close working Tag Menus window and rename
#users Tag Menus window to Tag Menus.
Close Window [ Name: "Tag Menus"; Current file ]
February 13, 平成27 20:59:27 Stuff Library.fp7 - addORremoveTagFromCitationStep2node -2-tagMenu: addORremoveTagFromCitationStep2node
Set Window Title [ Of Window: "Tag Menus Change Back When Done"; Current file; New Title: "Tag Menus" ]
Select Window [ Name: "Tag Menus"; Current file ]
Refresh Window
#
Exit Script [ ]
End If
End If
#
#If tag has been selected, then remove it.
Select Window [ Name: "Tag Menus"; Current file ]
Set Variable [ $removeNode; Value:tagMenus::_Ltag ]
#
#Set record number so can return user to it when done.
Set Variable [ $recordNumber; Value:Get (RecordNumber) ]
#
#
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Setup"; Current file ]
Set Variable [ $$Node; Value:tempSetup::kdefaultNodeOther ]
Set Field [ tempSetup::kdefaultNodeOther; //last item in list has no paragraph mark, so a valuecount test needs to be done and if item is not removed, then the removal calc without the paragraph mark is used
If ( ValueCount ( $$Node ) ≠ ValueCount ( Substitute ( $$Node ; $removeNode & "¶" ; "" ) ) ;
Substitute ( $$Node ; $removeNode & "¶" ; "" ) ;
Substitute ( $$Node ; $removeNode ; "" )
) ]
Set Variable [ $$Node; Value:tempSetup::kdefaultNodeOther ]
Go to Field [ ]
Else If [ Get (LastError) ≠ 112 ]
Set Field [ testlearn::kNodeOther; //last item in list has no paragraph mark, so a valuecount test needs to be done and if item is not removed, then the removal calc without the paragraph mark is used
If ( ValueCount ( $$Node ) ≠ ValueCount ( Substitute ( $$Node ; $removeNode & "¶" ; "" ) ) ;
Substitute ( $$Node ; $removeNode & "¶" ; "" ) ;
Substitute ( $$Node ; $removeNode ; "" )
) ]
Set Variable [ $$Node; Value:testlearn::kNodeOther ]
Go to Field [ ]
End If
Else If [ Get (LastError) ≠ 112 ]
Set Field [ reference::knodeOther; //last item in list has no paragraph mark, so a valuecount test needs to be done and if item is not removed, then the removal calc without the paragraph mark is used
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
Select Window [ Name: "Setup"; Current file ]
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
#Now re-alphabetize after removing node.
#
#
#
If [ $$skipFirstPartOfScript = 1 ]
Set Variable [ $$skipFirstPartOfScript ]
#
#
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Setup"; Current file ]
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
February 13, 平成27 20:59:27 Stuff Library.fp7 - addORremoveTagFromCitationStep2node -3-tagMenu: addORremoveTagFromCitationStep2node
Select Window [ Name: "Tag Menus"; Current file ]
New Window [ Name: "reorder"; Height: 1; Width: 1; Top: -1000; Left: -1000 ]
Go to Layout [ “ltagSCRIPTloops” (tagMenus) ]
Sort Records [ Specified Sort Order: tagMenus::tag; ascending ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ First ]
#
#
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Setup"; Current file ]
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
February 13, 平成27 20:59:27 Stuff Library.fp7 - addORremoveTagFromCitationStep2node -4-tagMenu: addORremoveTagFromCitationStep2node
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
// #Sort records according to users wishes.
// #Sort according to current users wishes. By default
// #the sort will be by category which is set by editCitation script.
// If [ TEMP::sortNode = "cat" and Get (LayoutName) = "defaultNode"
or
TEMP::sortNode = "" and Get (LayoutName) = "defaultNode" ]
// Sort Records [ Specified Sort Order: ruleTagMenuGroups::order; based on value list: “order”
ruleTagMenuGroups::name; ascending
tagMenus::orderOrLock; based on value list: “order”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
// Else If [ TEMP::sortNode = "abc" and Get (LayoutName) = "defaultNode" ]
// Sort Records [ Specified Sort Order: tagMenus::tag; ascending ]
[ Restore; No dialog ]
// End If
// If [ TEMP::sortKey = "cat" and Get (LayoutName) ≠ "defaultNode" ]
// Sort Records [ Specified Sort Order: ruleTagMenuGroups::order; based on value list: “order”
ruleTagMenuGroups::name; ascending
tagMenus::orderOrLock; based on value list: “order”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
// Else If [ TEMP::sortKey = "abc" and Get (LayoutName) ≠ "defaultNode" ]
// Sort Records [ Specified Sort Order: tagMenus::tag; ascending ]
[ Restore; No dialog ]
// End If
Set Variable [ $$stopLoadTagRecord ]
// Go to Record/Request/Page
[ First ]
// Scroll Window
[ Home ]
// Go to Record/Request/Page [ $recordNumber ]
[ No dialog ]
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
February 13, 平成27 20:59:27 Stuff Library.fp7 - addORremoveTagFromCitationStep2node -5-
