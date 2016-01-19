tagMenu: addORremoveCiteOrRefTLTag
#
#Conditionally format field in learn or
#observation window.
Set Variable [ $$refTestLearn; Value:1 ]
#
#If reference or learn record that tag was added
#to belongs to more than one section, then
#add these other sections to the tag's group
#keychain so when this tag record is viewed in
#those sections, the reference or learn record
#just added to it will show up as well.
Perform Script [ “CHUNKaddMainRecordSectionKeysToCiteOrRefSectionKeychain (update)” ]
#
#Check main checkbox if record is not already
#a main record. This is because when going to
#edit cite or reference records, only main records
#are shown by default.
If [ "main" & ¶ ≠ FilterValues ( testlearn::filterFind ; "main" & ¶ ) and Get ( LayoutTableName ) = "testlearn" ]
Set Variable [ $filterFind; Value:testlearn::filterFind ]
Set Field [ testlearn::filterFind; "main" & ¶ & $filterFind ]
End If
#
#Get current record IDs in reference or
#observation window.
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
Set Variable [ $$ref; Value:testlearn::kcreference ]
Else If [ Get (LastError) ≠ 112 ]
Set Variable [ $$ref; Value:reference::lock ]
End If
Select Window [ Name: "Tag Menus"; Current file ]
#
#If tag user clicked has not yet been selected, then add it.
#The 'L' is added to all Tag Menu to conditional format
#the Learn menu button.
If [ testlearn::_Ltestlearn & "L¶" ≠ FilterValues ( $$ref ; testlearn::_Ltestlearn & "L¶" ) ]
#
#If in inventory mode, only allow items
#specified in learn records to be tagged as
#being in one storage location at a time.
If [ TEMP::InventoryLibaryYN ≠ "" and Filter ( $$ref ; "L" ) ≠ "" ]
Show Custom Dialog [ Message: "This item is already tagged as being in a storage location (highlighted green). Untag it
from this storage location before tagging it with a different one."; Buttons: “OK” ]
Set Variable [ $$stopLoadTagRecord ]
Halt Script
End If
#
#Prevent user from tagging storage records
#with other storage tags. I.E., No storage
#inside of storage relationships allowed.
Select Window [ Name: "Learn"; Current file ]
If [ TEMP::InventoryLibaryYN ≠ "" and testlearn::sampleCasePoint ≠ "" ]
Select Window [ Name: "Tag Menus"; Current file ]
Show Custom Dialog [ Message: "This item is storage (box, shelf, etc.). To create a box-within-a-box relationship 1) create
a location record for the pimary box, and 2) tag the secondary box as being in that location."; Buttons: “OK” ]
Halt Script
End If
Select Window [ Name: "Tag Menus"; Current file ]
#
#
Set Variable [ $newRef; Value:testlearn::_Ltestlearn & "L" ]
#
#Set record number so can return user to it when done.
Set Variable [ $recordNumber; Value:Get (RecordNumber) ]
#
#Add reference in reference or observation window.
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
#
#For reference libraries, add reference to list
#of learn record's references.
If [ TEMP::InventoryLibaryYN = "" ]
Set Field [ testlearn::kcreference; $newRef & "¶" & $$ref ]
#
Else
#For inventory libraries, only allow user to
#have location tags for the item or for the
#container the item is in.
If [ $$ref ≠ "" ]
Select Window [ Name: "Tag Menus"; Current file ]
Show Custom Dialog [ Message: "NOTE: Items can either be in a location or in storage: box, shelf, etc. that is in a
location. Adding this storage tag will now delete your item's location tags."; Buttons: “OK”, “cancel” ]
If [ Get ( LastMessageChoice ) = 2 ]
Set Variable [ $$stopLoadTagRecord ]
Halt Script
End If
Select Window [ Name: "Learn"; Current file ]
End If
#
#Set new reference and delete any
#reference-location picture.
Set Field [ testlearn::kcreference; $newRef & "¶" ]
Set Field [ testlearn::kshowReferencedMedia; "" ]
End If
Set Variable [ $$ref; Value:testlearn::kcreference ]
Go to Field [ ]
#
Else If [ Get (LastError) ≠ 112 ]
#If in the reference section, do this...
Set Field [ reference::lock; $newRef & "¶" & $$ref ]
Set Variable [ $$ref; Value:reference::lock ]
Go to Field [ ]
End If
#
Select Window [ Name: "Tag Menus"; Current file ]
Refresh Window
#
#Sort records according to users wishes.
If [ TEMP::InventoryLibaryYN ≠ "" ]
Sort Records [ Specified Sort Order: testlearn::Caption; ascending ]
[ Restore; No dialog ]
Else
Sort Records [ Specified Sort Order: testlearn::date; descending
testlearn::timestamp; descending ]
[ Restore; No dialog ]
End If
#
Set Variable [ $$stopLoadTagRecord ]
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
Go to Record/Request/Page [ $recordNumber ]
[ No dialog ]
Exit Script [ ]
End If
#
#If tag has been selected, then remove it.
Set Variable [ $removeRef; Value:testlearn::_Ltestlearn & "L" ]
#
#Set record number so can return user to it when done.
Set Variable [ $recordNumber; Value:Get (RecordNumber) ]
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
Set Field [ testlearn::kcreference; //last item in list has no paragraph mark, so a valuecount test needs to be done and if item is not
removed, then the removal calc without the paragraph mark is used
If ( ValueCount ( $$ref) ≠ ValueCount ( Substitute ( $$ref ; $removeRef & "¶" ; "" ) ) ;
Substitute ( $$ref ; $removeRef & "¶" ; "" ) ;
Substitute ( $$ref ; $removeRef; "" )
) ]
Set Variable [ $$ref; Value:testlearn::kcreference ]
Go to Field [ ]
Else If [ Get (LastError) ≠ 112 ]
Set Field [ reference::lock; //last item in list has no paragraph mark, so a valuecount test needs to be done and if item is not
removed, then the removal calc without the paragraph mark is used
If ( ValueCount ( $$ref ) ≠ ValueCount ( Substitute ( $$ref ; $removeRef& "¶" ; "" ) ) ;
Substitute ( $$ref ; $removeRef & "¶" ; "" ) ;
Substitute ( $$ref ; $removeRef ; "" )
) ]
Set Variable [ $$ref; Value:reference::lock ]
Go to Field [ ]
End If
#
Select Window [ Name: "Tag Menus"; Current file ]
Refresh Window
#
#Sort records according to users wishes.
If [ TEMP::InventoryLibaryYN ≠ "" ]
Sort Records [ Specified Sort Order: testlearn::Caption; ascending ]
[ Restore; No dialog ]
Else
Sort Records [ Specified Sort Order: testlearn::date; descending
testlearn::timestamp; descending ]
[ Restore; No dialog ]
End If
#
Set Variable [ $$stopLoadTagRecord ]
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
Go to Record/Request/Page [ $recordNumber ]
[ No dialog ]
Set Variable [ $$skipFirstPartOfScript ]
January 18, ଘ౮28 17:35:50 Library.fp7 - addORremoveCiteOrRefTLTag -1-
