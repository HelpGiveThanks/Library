tagMenu: addORremoveCiteOrRefTLTag
#
#Conditionally format ﬁeld in learn or
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
If [ "main" & ¶ ≠ FilterValues ( testlearn::ﬁlterFind ; "main" & ¶ ) and Get ( LayoutTableName ) = "testlearn" ]
Set Variable [ $ﬁlterFind; Value:testlearn::ﬁlterFind ]
Set Field [ testlearn::ﬁlterFind; "main" & ¶ & $ﬁlterFind ]
End If
#
#Get current record IDs in reference or
#observation window.
Select Window [ Name: "References"; Current ﬁle ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current ﬁle ]
Set Variable [ $$ref; Value:testlearn::kcreference ]
Else If [ Get (LastError) ≠ 112 ]
Set Variable [ $$ref; Value:reference::lock ]
End If
Select Window [ Name: "Tag Menus"; Current ﬁle ]
#
#If tag user clicked has not yet been selected, then add it.
#The 'L' is added to all Tag Menu to conditional format
#the Learn menu button.
If [ testlearn::_Ltestlearn & "L¶" ≠ FilterValues ( $$ref ; testlearn::_Ltestlearn & "L¶" ) ]
#
Set Variable [ $newRef; Value:testlearn::_Ltestlearn & "L" ]
#
#Set record number so can return user to it when done.
Set Variable [ $recordNumber; Value:Get (RecordNumber) ]
#
#Add reference in reference or observation window.
Select Window [ Name: "References"; Current ﬁle ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current ﬁle ]
Set Field [ testlearn::kcreference; $newRef & "¶" & $$ref ]
Set Variable [ $$ref; Value:testlearn::kcreference ]
Go to Field [ ]
Else If [ Get (LastError) ≠ 112 ]
Set Field [ reference::lock; $newRef & "¶" & $$ref ]
Set Variable [ $$ref; Value:reference::lock ]
Go to Field [ ]
End If
Select Window [ Name: "Tag Menus"; Current ﬁle ]
Refresh Window
#
#Sort records according to users wishes.
Sort Records [ Speciﬁed Sort Order: testlearn::date; descending
testlearn::timestamp; descending ]
[ Restore; No dialog ]
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
Select Window [ Name: "References"; Current ﬁle ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current ﬁle ]
Set Field [ testlearn::kcreference; //last item in list has no paragraph mark, so a valuecount test needs to be done and if item is not removed, then the removal calc without the paragraph mark is used
If ( ValueCount ( $$ref) ≠ ValueCount ( Substitute ( $$ref ; $removeRef & "¶" ; "" ) ) ;
Substitute ( $$ref ; $removeRef & "¶" ; "" ) ;
Substitute ( $$ref ; $removeRef; "" )
) ]
Set Variable [ $$ref; Value:testlearn::kcreference ]
Go to Field [ ]
Else If [ Get (LastError) ≠ 112 ]
Set Field [ reference::lock; //last item in list has no paragraph mark, so a valuecount test needs to be done and if item is not removed, then the removal calc without the paragraph mark is used
If ( ValueCount ( $$ref ) ≠ ValueCount ( Substitute ( $$ref ; $removeRef& "¶" ; "" ) ) ;
Substitute ( $$ref ; $removeRef & "¶" ; "" ) ;
Substitute ( $$ref ; $removeRef ; "" )
) ]
Set Variable [ $$ref; Value:reference::lock ]
Go to Field [ ]
End If
#
Select Window [ Name: "Tag Menus"; Current ﬁle ]
Refresh Window
#Sort records according to users wishes.
Sort Records [ Speciﬁed Sort Order: testlearn::date; descending
testlearn::timestamp; descending ]
[ Restore; No dialog ]
#
Set Variable [ $$stopLoadTagRecord ]
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
Go to Record/Request/Page [ $recordNumber ]
[ No dialog ]
Set Variable [ $$skipFirstPartOfScript ]
January 7, 平成26 16:29:57 Imagination Quality Management.fp7 - addORremoveCiteOrRefTLTag -1-
