reference(citation): addORremoveCitationOrReferenceRefTag
#
#Get current record IDs in reference or
#observation window.
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
If [ testlearn::kcitation ≠ "" ]
Show Custom Dialog [ Message: "References can be added after the citation is removed. (Cite the source of an unchanged
copy, clip, quote, etc. from one source. Reference the sources of your rewording/remixing of one or more texts, movies,
etc.)"; Buttons: “OK” ]
Select Window [ Name: "Tag Menus"; Current file ]
Halt Script
End If
Set Variable [ $$ref; Value:testlearn::kcreference ]
Else If [ Get (LastError) ≠ 112 ]
Set Variable [ $$ref; Value:reference::lock ]
End If
Select Window [ Name: "Tag Menus"; Current file ]
#
#If tag user clicked has not yet been selected, then add it.
If [ reference::_Lreference & "¶" ≠ FilterValues ( $$ref ; reference::_Lreference & "¶" ) ]
Freeze Window
Perform Script [ “CHUNKaddMainRecordSectionKeysToCiteOrRefSectionKeychain” ]
// #
// #Stop script if user trying to add reference or learn record
// #that has references or citations added to it.
// #In the future this will be possible, but for now I need
// #to focus on other things to get the beta released.
// If [ testlearn::kcitation ≠ "" or testlearn::kcreference ≠ "" or reference::kcitation ≠ "" ]
// Show Custom Dialog [ Message: "For now, you cannot use a record that has its own citation or references added to it as a
citation or reference for another record. This is a known issue, and in a future release it will be resolved. "; Buttons:
“OK” ]
// Exit Script [ ]
// End If
#
Set Variable [ $newRef; Value:reference::_Lreference ]
#
#Set record number so can return user to it when done.
Set Variable [ $recordNumber; Value:Get (RecordNumber) ]
#
#Add reference in reference or observation window.
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
Set Field [ testlearn::kcreference; $newRef & "¶" & $$ref ]
Set Variable [ $$ref; Value:testlearn::kcreference ]
Go to Field [ ]
Else If [ Get (LastError) ≠ 112 ]
Set Field [ reference::lock; $newRef & "¶" & $$ref ]
Set Variable [ $$ref; Value:reference::lock ]
Go to Field [ ]
End If
Select Window [ Name: "Tag Menus"; Current file ]
Refresh Window
#
// #Sort records according to users wishes.
// If [ TEMP::sortKey = "cat" ]
// Sort Records [ Specified Sort Order: ruleTagMenuGroups::order; based on value list: “order”
ruleTagMenuGroups::name; ascending
tagMenus::orderOrLock; based on value list: “order”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
// Else If [ TEMP::sortKey = "abc" ]
// Sort Records [ Specified Sort Order: tagMenus::tag; ascending ]
[ Restore; No dialog ]
// End If
// Set Variable [ $$stopLoadTagRecord ]
// Go to Record/Request/Page
[ First ]
// Scroll Window
[ Home ]
Freeze Window
Go to Record/Request/Page [ $recordNumber ]
[ No dialog ]
#
#Check main checkbox if record is not already
#a main record. This is because when going to
#edit cite or reference records, only main records
#are shown by default.
If [ "main" & ¶ ≠ FilterValues ( reference::filterFind ; "main" & ¶ ) and Get ( LayoutTableName ) = "reference" ]
Set Variable [ $filterFind; Value:reference::filterFind ]
Set Field [ reference::filterFind; "main" & ¶ & $filterFind ]
End If
#
#NOTE: Library used to consist of multilbe
#sections and now it consists of only one, so
#these next steps are no longer neccessary.
#I'll leave them until the next version in case further testing reveals a need for them after all.
#I'll leave them until the next version in case
#further testing reveals a need for them after all.
#
// #If reference or learn record that tag was added
// #to belongs to more than one section, then
// #add these other sections to the tag's group
// #keychain so when this tag record is viewed in
// #those sections, the reference or learn record
// #just added to it will show up as well.
// Perform Script [ “CHUNKaddReferenceNodesAndKeywords” ]
// #Sort records according to users wishes.
// Freeze Window
// If [ TEMP::sortRef = "cat" ]
// Sort Records [ Specified Sort Order: tagKeywordPrimary::orderOrLock; ascending
tagKeywordPrimary::tag; ascending
reference::referenceShort; ascending ]
[ Restore; No dialog ]
// Else If [ TEMP::sortRef = "abc" ]
// Sort Records [ Specified Sort Order: tagMenus::tag; ascending ]
[ Restore; No dialog ]
// End If
// Set Variable [ $$stoploadCitation; Value:1 ]
// Set Variable [ $$stopLoadTagRecord; Value:1 ]
// #
// #Go to citation record's current selection or to first record.
// Go to Record/Request/Page
[ First ]
// Scroll Window
[ Home ]
// Loop
// Exit Loop If [ FilterValues ( $$ref ; reference::_Lreference ) = reference::_Lreference & ¶ ]
// Go to Record/Request/Page
[ Next; Exit after last ]
// End Loop
// If [ FilterValues ( $$ref ; reference::_Lreference ) ≠ reference::_Lreference & ¶ ]
// Scroll Window
[ Home ]
// Go to Record/Request/Page
[ First ]
// End If
#
Set Variable [ $$stoploadCitation ]
Set Variable [ $$stopLoadTagRecord ]
Exit Script [ ]
End If
#
#If tag has been selected, then remove it.
Set Variable [ $removeRef; Value:reference::_Lreference ]
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
#NOTE: Further testing will reveal if these next
#steps are necessary, but right now everything
#works fine without them.
// #Sort records according to users wishes.
// If [ TEMP::sortRef = "cat" ]
// Sort Records [ Specified Sort Order: tagKeywordPrimary::orderOrLock; ascending
tagKeywordPrimary::tag; ascending
reference::referenceShort; ascending ]
[ Restore; No dialog ]
// Else If [ TEMP::sortRef = "abc" ]
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
Set Variable [ $$skipFirstPartOfScript ]
December 29, ଘ౮27 10:20:33 Library.fp7 - addORremoveCitationOrReferenceRefTag -1-
