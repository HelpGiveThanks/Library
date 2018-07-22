July 21, 2018 13:48:27 Library.fmp12 - addORremoveRefTagStep2_forRefRecord -1-
tagMenu: addORremoveRefTagStep2_forRefRecord
#
#Get current record IDs in reference or
#observation window.
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
#
#Capture tagged location. If this is
#changed while on the Qv layout it will effect
#the record's sort location and require a resort
#for the user to see the record in the Learn window.
If [ TEMP::InventoryLibraryYN ≠ "" ]
Set Variable [ $$QvLocation; Value:testlearn::orderInventoryGroupNumber ]
End If
#
#Decided to not show learn tags, so this
#next block of script makes no sense and
#is disabled.
// #Only allow user to have location tags for the
// #item or for the container the item is in.
// If [ TEMP::InventoryLibraryYN ≠ "" and Filter ( $$ref ; "L" ) ≠ "" ]
// Select Window [ Name: "Tag Menus"; Current file ]
// Show Custom Dialog [ Message: "This item is tagged with an in/on tag. Remove it before applying a location tag. 1)
Click in/on. 2) Deslect the highlighted tag. 3) Click location. 4) Apply the tag."; Default Button: “OK”, Commit: “Yes” ]
// Halt Script
// End If
#
Set Variable [ $$ref; Value:testlearn::kcreference ]
Else If [ Get (LastError) ≠ 112 ]
Set Variable [ $$ref; Value:reference::lock ]
End If
Select Window [ Name: "Tag Menus"; Current file ]
#
#
#
#
#
#If tag user clicked has not yet been selected, then add it.
If [ reference::_Lreference & "¶" ≠ FilterValues ( $$ref ; reference::_Lreference & "¶" ) ]
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
#
#
#
If [ $$QvLocation ≠ testlearn::orderInventoryGroupNumber ]
Set Variable [ $$QvLocation ]
Sort Records [ ]
[ No dialog ]
End If
#
#Ask user if they would like to show the
#reference's media if there is any to show.
If [ $media = 1 and testlearn::picture = "" ]
If [ TEMP::InventoryLibraryYN = "" ]
Show Custom Dialog [ Message: "Display reference's media? Learn layouts with an unused picture area can
display reference media. Click any Learn record's picture-selection button (in QV window) to show/not show
reference media."; Default Button: “no”, Commit: “Yes”; Button 2: “yes”, Commit: “No” ]
Else
Show Custom Dialog [ Message: "Display location's media? Learn layouts with an unused picture area can
display location media. Click any Learn record's picture-selection button (in QV window) to show/not show
location media."; Default Button: “no”, Commit: “Yes”; Button 2: “yes”, Commit: “No” ]
End If
If [ Get (LastMessageChoice) = 2 ]
Set Field [ testlearn::kshowReferencedMedia; $newRef ]
Set Variable [ $$refMediaSelectedToShow; Value:$newRef ]
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
Set Variable [ $$stoploadCitation ]
Set Variable [ $$stopLoadTagRecord ]
Exit Script [ ]
End If
#
#
#
#
#
#If tag has been selected, then remove it.
Set Variable [ $removeRef; Value:reference::_Lreference ]
Set Variable [ $$refMediaSelectedToShow ]
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
#
#
#
#
If [ $$QvLocation ≠ testlearn::orderInventoryGroupNumber ]
Set Variable [ $$QvLocation ]
Sort Records [ ]
[ No dialog ]
End If
#
#
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
// Sort Records [ Keep records in sorted order; Specified Sort Order: tagKeywordPrimary::orderOrLock; ascending
tagKeywordPrimary::tag; ascending
reference::referenceShort; ascending ]
[ Restore; No dialog ]
// Else If [ TEMP::sortRef = "abc" ]
// Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenus::tag; ascending ]
[ Restore; No dialog ]
// End If
Set Variable [ $$stopLoadTagRecord ]
// Go to Record/Request/Page
[ First ]
// Scroll Window
[ Home ]
// Go to Record/Request/Page [ $recordNumber ]
[ No dialog ]
#
#Turn of the skip part script variable.
Set Variable [ $$skipFirstPartOfScript ]
#
