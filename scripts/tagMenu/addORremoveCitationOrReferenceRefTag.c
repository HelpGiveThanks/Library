tagMenu: addORremoveCitationOrReferenceRefTag
#
#Get current record IDs in reference or
#observation window.
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
#
#Only allow user to have location tags for the
#item or for the container the item is in.
If [ TEMP::InventoryLibaryYN ≠ "" and Filter ( $$ref ; "L" ) ≠ "" ]
Show Custom Dialog [ Message: "This item is tagged with a container tag. Remove this tag (click 'containers') before
tagging it with its own location tags. Items can be either in a location or in a container that is in a location."; Buttons:
“OK” ]
Select Window [ Name: "Tag Menus"; Current file ]
Halt Script
End If
#
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
#If the reference has media, then prepare to
#ask user if they would like to show it.
Set Variable [ $newRef; Value:reference::_Lreference ]
If [ //There is a picture to show if...
reference::picture ≠ "" or
reference::showMedia ≠ "" and reference::URL ≠ "" or
reference::kfileLocation ≠ "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "jpg"
or reference::kfileLocation ≠ "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "gif"
or reference::kfileLocation ≠ "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "eps"
or reference::kfileLocation ≠ "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "jp2"
or reference::kfileLocation ≠ "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "psd"
or reference::kfileLocation ≠ "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "png"
or reference::kfileLocation ≠ "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "pct"
or reference::kfileLocation ≠ "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "pcs"
or reference::kfileLocation ≠ "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = ".qt"
or reference::kfileLocation ≠ "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "sgi"
or reference::kfileLocation ≠ "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "tga"
or reference::kfileLocation ≠ "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "tif"
or reference::kfileLocation ≠ "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "bmp"
or reference::kfileLocation ≠ "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "wmf"
or reference::kfileLocation ≠ "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "emf" or
reference::URL ≠ "" and Right ( reference::URL ; 3 )= "jpg"
or reference::URL ≠ "" and Right ( reference::URL ; 3 )= "gif"
or reference::URL ≠ "" and Right ( reference::URL ; 3 )= "eps"
or reference::URL ≠ "" and Right ( reference::URL ; 3 )= "jp2"
or reference::URL ≠ "" and Right ( reference::URL ; 3 )= "psd"
or reference::URL ≠ "" and Right ( reference::URL ; 3 )= "png"
or reference::URL ≠ "" and Right ( reference::URL ; 3 )= "pct"
or reference::URL ≠ "" and Right ( reference::URL ; 3 )= "pcs"
or reference::URL ≠ "" and Right ( reference::URL ; 3 )= ".qt"
or reference::URL ≠ "" and Right ( reference::URL ; 3 )= "sgi"
or reference::URL ≠ "" and Right ( reference::URL ; 3 )= "tga"
or reference::URL ≠ "" and Right ( reference::URL ; 3 )= "tif"
or reference::URL ≠ "" and Right ( reference::URL ; 3 )= "bmp"
or reference::URL ≠ "" and Right ( reference::URL ; 3 )= "wmf"
or reference::URL ≠ "" and Right ( reference::URL ; 3 )= "emf" ]
Set Variable [ $media; Value:1 ]
End If
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
#
#Ask user if they would like to show the
#reference's media if there is any to show.
If [ $media = 1 and testlearn::Picture = "" ]
Show Custom Dialog [ Message: "Display reference's media? Learn layouts with an unused picture area can display
reference media. Click any reference's picture-selection button (QV layout) to toggle showing/not showing its
media."; Buttons: “no”, “yes” ]
If [ Get (LastMessageChoice) = 2 ]
Set Field [ testlearn::kshowReferencedMedia; $newRef ]
End If
End If
#
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
#
#Make sure the reference being removed also
#gets its picture removed from this learn
#record if it is being used.
If [ $removeRef = testlearn::kshowReferencedMedia ]
Set Field [ testlearn::kshowReferencedMedia; "" ]
End If
#
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
#seems to work fine without them.
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
January 6, ଘ౮28 14:56:37 Library.fp7 - addORremoveCitationOrReferenceRefTag -1-
