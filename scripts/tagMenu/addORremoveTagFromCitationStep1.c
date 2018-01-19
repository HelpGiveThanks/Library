tagMenu: addORremoveTagFromCitationStep1
#
#Stop script if user is looking at item/detail tags
#in add mode, as these tags cannot be applied
#to reference records.
If [ $$add = 1 and $$citationMatch = "testItem" ]
Show Custom Dialog [ Message: "You cannot tag reference records with item tags. So why then are there buttons? The buttons
show up because I have not made time to create a separate layout just for item tags. This issue has been logged as a minor
irritation."; Buttons: “OK” ]
Exit Script [ ]
End If
#
#Reference Section Only
#Because I keep forgetting to press find mode, this
#bit of script is to confirm that the user really wants
#to add or change the tag of the first record instead of
#finding records with selected tag.
If [ Left (Get (LayoutName) ; 3 ) = "ref" and $$stopAdd = "" ]
Show Custom Dialog [ Message: "Change tag OR find references with this tag?"; Buttons: “change”, “find”, “cancel” ]
If [ Get ( LastMessageChoice ) = 2 ]
#This variable is needed becasue message choice 2
#gets carried over to the Find Mode Script, which then
#activates tag instead of reference record find mode.
Set Variable [ $$ClearMessageChoice; Value:1 ]
Perform Script [ “findMode” ]
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
If [ $$citationItem = $$PrimaryKey and $$referenceSort = "" ]
Set Variable [ $removedPrimaryKey; Value:1 ]
End If
End If
End If
#
#
#Remove focus from field so can see
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
Perform Script [ “addORremoveTagFromCitationStep2keyword (update)” ]
#
Set Variable [ $$otherKeyDoNotLoop ]
#
#
#
#
If [ $removedPrimaryKey = 1 ]
Show Custom Dialog [ Message: "Record will now move to new keyword location. Scroll window to this location?"; Buttons:
“no”, “yes” ]
If [ Get (LastMessageChoice) = 2 ]
Select Window [ Name: "References"; Current file ]
Go to Layout [ “ReferenceStuffScriptLoops” (reference) ]
Sort Records [ Specified Sort Order: tagKeywordPrimary::orderOrLock; based on value list: “order”
tagKeywordPrimary::tag; ascending
reference::referenceForReferenceWindow; ascending ]
[ Restore; No dialog ]
#
#Go to reference record layout.
If [ TEMP::InventoryLibaryYN ≠ "" ]
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
Perform Script [ “addORremoveTagFromCitationStep2node” ]
Close Window [ Name: "reorder"; Current file ]
Set Variable [ $$stopLoadTagRecord ]
#
#Get the keys currently unlocking who is a
#copyright holder.
Set Variable [ $keyChain; Value:reference::kcopyrightHolder ]
#
#Remove key from keychain if it is on
#the copyright holder keychain.
If [ reference::knodeOther = "" and reference::knodePrimary = "" ]
Set Field [ reference::kcopyrightHolder; Substitute ( $keyChain ; "node738fds8ef" & "¶" ; "" ) ]
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
August 19, ଘ౮28 19:53:46 Library.fp7 - addORremoveTagFromCitationStep1 -1-
