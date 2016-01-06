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
Perform Script [ “CHUNKaddMainRecordSectionKeysToCiteOrRefSectionKeychain” ]
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
#being in one container at a time.
If [ TEMP::InventoryLibaryYN ≠ "" and Filter ( $$ref ; "L" ) ≠ "" ]
Show Custom Dialog [ Message: "This item is already tagged as being in a container (highlighted green). Untag it from this
container before tagging it with a new one."; Buttons: “OK” ]
Set Variable [ $$stopLoadTagRecord ]
Halt Script
End If
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
Show Custom Dialog [ Message: "NOTE: The item in the Learn window is tagged with location tags. Items can be
either in a location or in a container that is in a location. By placing it in a container the item's location tags will
be replaced with the container's location tags."; Buttons: “OK”, “cancel” ]
If [ Get ( LastMessageChoice ) = 2 ]
Set Variable [ $$stopLoadTagRecord ]
Halt Script
End If
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
January 6, ଘ౮28 14:55:06 Library.fp7 - addORremoveCiteOrRefTLTag -1-
