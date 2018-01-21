January 19, 2018 14:32:45 Library.fmp12 - addORremoveOtherTagStep1 -1-
tagMenu: addORremoveOtherTagStep1
#
#Stop script if user is looking at item/detail tags
#in add mode, as these tags cannot be applied
#to reference records.
If [ $$add = 1 and $$citationMatch = "testItem" ]
Show Custom Dialog [ Message: "You cannot tag reference records with item tags. So why then are there buttons? The buttons
show up because I have not made time to create a separate layout just for item tags. This issue has been logged as a minor
irritation."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
#
#If main record node is currenlty locked then
#stop script and inform the user.
If [ $$citationMatch ≠ "path"
 and
$$citationMatch ≠ "key"
 and
$$citationMatch ≠ "brainstorm"
 and
$$citationMatch ≠ "test" ]
If [ $$lockedMainRefRecord ≠ "" and Left ( Get (LayoutName) ; 1 ) = "r" ]
Show Custom Dialog [ Message: "Tags cannot be added or removed from locked reference records (EXCEPTIONS — Key
P and O tags and Path tags). Select this record's creator node — " & $$lockedMainRefRecord & " — in the setup
window and enter the password to unlock it."; Default Button: “OK”, Commit: “Yes” ]
Halt Script
Else If [ $$lockedMainLearnRecord ≠ "" and Left ( Get (LayoutName) ; 1 ) = "l" ]
Show Custom Dialog [ Message: "Tags cannot be added or removed from locked learn records. EXCEPTIONS — Key (P
and O), Brainstorm, and Test tags. Select this record's creator node — " & $$lockedMainLearnRecord & " — in the
setup window and enter the password to unlock it."; Default Button: “OK”, Commit: “Yes” ]
Halt Script
End If
End If
#
#Reference Section Only
#Because I keep forgetting to press find mode, this
#bit of script is to confirm that the user really wants
#to add or change the tag of the first record instead of
#finding records with selected tag.
If [ Left (Get (LayoutName) ; 3 ) = "ref" and $$stopAdd = "" ]
If [ //Other nodes and keys match
tagMenus::_Ltag & "¶" = FilterValues ( $$key ; tagMenus::_Ltag & "¶" ) and $$citationMatch = "key"
or
tagMenus::_Ltag & "¶" = FilterValues ( $$node ; tagMenus::_Ltag & "¶" ) and $$citationMatch = "node" ]
Show Custom Dialog [ Message: "Remove Tag?" & ¶ &
"OR " & ¶ &
"Find references tagged with it?"; Default Button: “remove”, Commit: “Yes”; Button 2: “find”, Commit: “No”; Button 3:
“cancel”, Commit: “No” ]
Else
Show Custom Dialog [ Message: "Add Tag?" & ¶ &
"OR " & ¶ &
"Find references tagged with it?"; Default Button: “add”, Commit: “Yes”; Button 2: “find”, Commit: “No”; Button 3:
“cancel”, Commit: “No” ]
End If
If [ Get ( LastMessageChoice ) = 2 ]
#This variable is needed because message choice 2
#gets carried over to the Find Mode Script, which then
#activates tag instead of reference record find mode.
Set Variable [ $$ClearMessageChoice; Value:1 ]
Perform Script [ “findMode (update)” ]
Exit Script [ ]
Else If [ Get ( LastMessageChoice ) = 3 ]
Set Variable [ $$referenceRecordOne ]
Exit Script [ ]
Else If [ Get ( LastMessageChoice ) = 1 ]
Set Variable [ $$referenceRecordOne ]
#
#If a primary key is being changed into an
#other key, then user needs to be informed
#that this will change its location in the
#References window.
If [ $$citationItem = tagMenus::_Ltag and $$referenceSort = "" ]
Set Variable [ $removedPrimaryKey; Value:1 ]
End If
End If
End If
#
#
#Turn off the T scripts variable once the
#user selectes or unselects a tag. This variable
#is set when the user navigates to a reference
#field that is blank and triggers a Tag Menu script.
Set Variable [ $$TgotoCitationMenuWithBlankField ]
#
#Leave field so user can see
#conditional formatting.
Go to Field [ ]
#
#Determine if user is looking at nodes or keywords.
If [ $$citationMatch = "key" ]
#
#Create this variable for use in the next script
#addORremoveTagFromCitationStep2, to stop
#resorting of OtherKey tags, which do not
#effect sort order.
Set Variable [ $$otherKeyDoNotLoop; Value:1 ]
#
#Finish key addition or removal.
Perform Script [ “addORremoveOtherTagStep2_keyword (update name addORremoveTagFromCitationStep2keyword)” ]
#
Set Variable [ $$otherKeyDoNotLoop ]
#
#
#
#
If [ $removedPrimaryKey = 1 ]
Show Custom Dialog [ Message: "The reference record will now move to its new subject/keyword location."; Default Button:
“OK”, Commit: “Yes” ]
If [ Get (LastMessageChoice) = 1 ]
Select Window [ Name: "References"; Current file ]
Go to Layout [ “ReferenceStuffScriptLoops” (reference) ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagKeywordPrimary::orderOrLock; based on value
list: “order Pulldown List”
tagKeywordPrimary::tag; ascending
reference::referenceForReferenceWindow; ascending ]
[ Restore; No dialog ]
#
#Go to reference record layout.
If [ TEMP::InventoryLibraryYN ≠ "" ]
Go to Layout [ “ReferenceStuff” (reference) ]
Else
Go to Layout [ “Reference” (reference) ]
End If
Select Window [ Name: "Tag Menus"; Current file ]
End If
End If
#
#
#
#
Else If [ $$citationMatch = "node" ]
Perform Script [ “addORremoveOtherTagStep2_node (update name addORremoveTagFromCitationStep2node)” ]
Close Window [ Name: "reorder"; Current file ]
Set Variable [ $$stopLoadTagRecord ]
#
#Remove author copyright holder if there are
#no authors.
If [ reference::knodeOther = "" and reference::knodePrimary = "" and reference::referenceNodes = "" ]
#Perform removal for items with and without a
#paragraph mark, as the last item in checklist
#has no paragraph mark after it.
If [ Filter ( reference::kcopyrightHolder ; "1" ) = 1 ]
Show Custom Dialog [ Message: "Author is currently checked in the copyright section for this reference as a copyright
holder. Remove this check?"; Default Button: “No”, Commit: “Yes”; Button 2: “Yes”, Commit: “No” ]
If [ Get ( LastMessageChoice ) = 2 ]
Set Field [ reference::kcopyrightHolder; Substitute ( reference::kcopyrightHolder ; "1" & "¶" ; "" ) ]
Set Field [ reference::kcopyrightHolder; Substitute ( reference::kcopyrightHolder ; "1" ; "" ) ]
End If
End If
End If
#
Select Window [ Name: "Tag Menus Change Back When Done"; Current file ]
If [ Get ( WindowName ) = "Tag Menus Change Back When Done" ]
Close Window [ Name: "Tag Menus"; Current file ]
Set Window Title [ Of Window: "Tag Menus Change Back When Done"; Current file; New Title: "Tag Menus" ]
End If
Refresh Window
End If
#
