tagMenu: addORremoveTagFromCitationStep2keyword
#
Set Error Capture [ On ]
Allow User Abort [ Off ]
#
#This script adds tags to main reference or learn
#other tag fields.
If [ $$skipFirstPartOfScript ≠ 1 ]
#
#Get current reference or learn record key.
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
Set Variable [ $$key; Value:testlearn::kcKeywordOther ]
Else If [ Get (LastError) ≠ 112 ]
Set Variable [ $$key; Value:reference::kkeywordOther ]
End If
#
Select Window [ Name: "Tag Menus" ]
#
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
New Window [ Name: "Tag Menus"; Height: 1; Width: 1; Top: -1000; Left: -1000 ]
#
#Make sure all tags are showing. User may be only
#showing a few of the tags after performing a find.
Enter Find Mode [ ]
Set Field [ tagMenus::match; $$citationMatch ]
Set Field [ ruleTagMenuGroups::ksection; "==" & TEMP::ksection ]
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
#If tag user clicked has not been added, then add it.
If [ tagMenus::_Ltag & "¶" ≠ FilterValues ( $$key ; tagMenus::_Ltag & "¶" ) ]
#
#
#Check for duplicates, prior to adding to a record.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Set Variable [ $tagName; Value:tagMenus::tag ]
Set Variable [ $tagKey; Value:tagMenus::_Ltag ]
New Window [ ]
Enter Find Mode [ Specified Find Requests: Find Records; Criteria: tagMenus::match: “key” AND ruleTagMenuGroups::
ksection: “==7052011234235374” ]
[ Restore ]
Set Field [ tagMenus::tag; "==" & $tagName ]
Set Field [ TEMP::ksection ]
Perform Find [ ]
Go to Record/Request/Page
[ First ]
If [ Get ( FoundCount ) > 1 ]
Loop
Exit Loop If [ tagMenus::_Ltag = $tagKey ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
Set Field [ tagMenus::tag; $tagName & tagMenus::_Ltag ]
Set Field [ tagMenus::tagSpelling; $tagName & tagMenus::_Ltag ]
#
Close Window [ Current Window ]
Show Custom Dialog [ Message: "Keywords must have different spellings in each section. The ID number has been
added to this keyword to make it different from its duplicate. Please do change it to something meaningful.";
Buttons: “OK” ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Else If [ Get ( FoundCount ) ≤ 1 ]
Close Window [ Current Window ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
End If
#
#
#
Set Variable [ $newKey; Value:tagMenus::_Ltag ]
#
#Set record number so can return user to it when done.
Set Variable [ $recordNumber; Value:Get (RecordNumber) ]
#
#Add keyword in reference or observation window.
#
#
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
Set Field [ testlearn::kcKeywordOther; $newKey & "¶" & $$key ]
Set Variable [ $$key; Value:testlearn::kcKeywordOther ]
If [ testlearn::kKeywordPrimary = $newKey ]
Set Field [ testlearn::kKeywordPrimary; "" ]
Set Variable [ $$citationItem ]
End If
Go to Field [ ]
Else If [ Get (LastError) ≠ 112 ]
Set Field [ reference::kkeywordOther; $newKey & "¶" & $$key ]
Set Variable [ $$key; Value:reference::kkeywordOther ]
If [ reference::kkeywordPrimary = $newKey ]
Set Field [ reference::kkeywordPrimary; "" ]
Set Variable [ $$citationItem ]
End If
Go to Field [ ]
End If
#
#
Select Window [ Name: "Tag Menus"; Current file ]
Refresh Window
#
#Now re-alphabetize and add new keyword to citation.
Sort Records [ Specified Sort Order: tagMenus::tag; ascending ]
[ Restore; No dialog ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Go to Record/Request/Page
[ First ]
#
#
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
Set Variable [ $otherKeys; Value:testlearn::OtherKeyWords ]
Else If [ Get (LastError) ≠ 112 ]
Set Variable [ $otherKeys; Value:reference::OtherKeyWords ]
End If
#
#
#Find and set first value in keyword list.
#It will not have a comma in front like the other items.
Select Window [ Name: "Tag Menus"; Current file ]
Loop
If [ tagMenus::_Ltag & "¶" = FilterValues ( $$key ; tagMenus::_Ltag & "¶" ) ]
Set Variable [ $newKey; Value:tagMenus::tag ]
#
#
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
Set Field [ testlearn::OtherKeyWords; $newKey ]
Set Variable [ $otherKeys; Value:testlearn::OtherKeyWords ]
Else If [ Get (LastError) ≠ 112 ]
Set Field [ reference::OtherKeyWords; $newKey ]
Set Variable [ $otherKeys; Value:reference::OtherKeyWords ]
End If
End If
#
#
Select Window [ Name: "Tag Menus"; Current file ]
Exit Loop If [ tagMenus::_Ltag & "¶" = FilterValues ( $$key ; tagMenus::_Ltag & "¶" ) ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Now add remaining keywords to list.
Loop
Go to Record/Request/Page
[ Next; Exit after last ]
If [ tagMenus::_Ltag & "¶" = FilterValues ( $$key ; tagMenus::_Ltag & "¶" ) ]
Set Variable [ $newKey; Value:tagMenus::tag ]
#
#
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
Set Field [ testlearn::OtherKeyWords; $otherKeys & ", " & $newKey ]
Set Variable [ $otherKeys; Value:testlearn::OtherKeyWords ]
Else If [ Get (LastError) ≠ 112 ]
Set Field [ reference::OtherKeyWords; $otherKeys & ", " & $newKey ]
Set Variable [ $otherKeys; Value:reference::OtherKeyWords ]
End If
End If
#
#
Select Window [ Name: "Tag Menus"; Current file ]
End Loop
#
#Commit records so user can change spelling.
#Without commit records the system will not find
#the newly added tag.
Commit Records/Requests
Go to Field [ ]
#
#Sort records according to users wishes.
If [ TEMP::sortKey = "cat" ]
Sort Records [ Specified Sort Order: ruleTagMenuGroups::order; based on value list: “order”
ruleTagMenuGroups::name; ascending
tagMenus::orderOrLock; based on value list: “order”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Else If [ TEMP::sortKey = "abc" ]
Sort Records [ Specified Sort Order: tagMenus::tag; ascending ]
[ Restore; No dialog ]
End If
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
Perform Script [ “CHUNKaddMainSectionKeysToTagRecordKeychain” ]
#
#Now close working Tag Menus window and rename
#users Tag Menus window to Tag Menus.
Close Window [ Name: "Tag Menus"; Current file ]
Set Window Title [ Of Window: "Tag Menus Change Back When Done"; Current file; New Title: "Tag Menus" ]
Select Window [ Name: "Tag Menus"; Current file ]
Refresh Window
Exit Script [ ]
End If
#
#
#
#
#If tag has been selected, then remove it.
Set Variable [ $removeKey; Value:tagMenus::_Ltag ]
#
#Set record number so can return user to it when done.
Set Variable [ $recordNumber; Value:Get (RecordNumber) ]
#
#
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
Set Field [ testlearn::kcKeywordOther; //last item in list has no paragraph mark, so a valuecount test needs to be done and if
item is not removed, then the removal calc without the paragraph mark is used
If ( ValueCount ( $$key ) ≠ ValueCount ( Substitute ( $$key ; $removekey & "¶" ; "" ) ) ;
Substitute ( $$key ; $removekey & "¶" ; "" ) ;
Substitute ( $$key ; $removekey ; "" )
) ]
Set Variable [ $$key; Value:testlearn::kcKeywordOther ]
Go to Field [ ]
Else If [ Get (LastError) ≠ 112 ]
Set Field [ reference::kkeywordOther; //last item in list has no paragraph mark, so a valuecount test needs to be done and if
item is not removed, then the removal calc without the paragraph mark is used
If ( ValueCount ( $$key ) ≠ ValueCount ( Substitute ( $$key ; $removekey & "¶" ; "" ) ) ;
Substitute ( $$key ; $removekey & "¶" ; "" ) ;
Substitute ( $$key ; $removekey ; "" )
) ]
Set Variable [ $$key; Value:reference::kkeywordOther ]
Go to Field [ ]
End If
End If
#
#
#
#
#This next part of the script checks to see if
#the otherKey field was affected.
#
If [ $$skipFirstPartOfScript = 1 ]
#
#
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
Set Variable [ $removeKey; Value:testlearn::kKeywordPrimary ]
Else If [ Get (LastError) ≠ 112 ]
Set Variable [ $removeKey; Value:reference::kkeywordPrimary ]
End If
#
#
Select Window [ Name: "Tag Menus"; Current file ]
Set Variable [ $recordNumber; Value:Get (RecordNumber) ]
Else If [ $$skipFirstPartOfScript ≠ 1 ]
Select Window [ Name: "Tag Menus"; Current file ]
Set Variable [ $removeKey; Value:tagMenus::tag ]
End If
Refresh Window
#
#Now re-alphabetize after removing keyword.
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
Set Variable [ $removeKey; Value:testlearn::kKeywordPrimary ]
Else If [ Get (LastError) ≠ 112 ]
Set Variable [ $removeKey; Value:reference::kkeywordPrimary ]
End If
#
#
Select Window [ Name: "Tag Menus"; Current file ]
End If
#
#
#
#Order list alphabetically to re-construct otherKey
#field belonging to the citation record.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
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
Set Variable [ $otherKeys; Value:testlearn::OtherKeyWords ]
Set Variable [ $testLearnRecordKey; Value:testlearn::_Ltestlearn ]
#
#Clear the field now in case all tags have been de-selected.
Set Field [ testlearn::OtherKeyWords; "" ]
Go to Field [ ]
Else If [ Get (LastError) ≠ 112 ]
Set Variable [ $otherKeys; Value:reference::OtherKeyWords ]
#
#Clear the field now in case all tags have been de-selected.
Set Field [ reference::OtherKeyWords; "" ]
#
#Re-sort records so focus is back on selected record.
If [ $$primaryKeyWord ≠ reference::kkeywordPrimary and $$citationMatch ≠ "cite" and $$stopAdd = "" and $$otherKeyDoNotLoop
= "" and $$referenceSort = "" ]
Set Variable [ $$primaryKeyWord ]
Show Custom Dialog [ Message: "Record will now move to new keyword location. Scroll window to this location?"; Buttons:
“no”, “yes” ]
If [ Get (LastMessageChoice) = 2 ]
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
End If
End If
End If
#
#
#Find and set first value in keyword list.
#It will not have a comma in front like the other items.
Select Window [ Name: "reorder"; Current file ]
Loop
If [ tagMenus::_Ltag & "¶" = FilterValues ( $$key ; tagMenus::_Ltag & "¶" )
and
tagMenus::tag ≠ $removeKey ]
Set Variable [ $newKey; Value:tagMenus::tag ]
#
#
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
// Select Window [ Name: "Learn"; Current file ]
Go to Layout [ “learnSCRIPTloops” (testlearn) ]
If [ $testLearnRecordKey ≠ testlearn::_Ltestlearn ]
Enter Find Mode [ ]
Set Field [ testlearn::_Ltestlearn; $testLearnRecordKey ]
Perform Find [ ]
End If
Set Field [ testlearn::OtherKeyWords; $newKey ]
Set Variable [ $otherKeys; Value:testlearn::OtherKeyWords ]
Else If [ Get (LastError) ≠ 112 ]
Set Field [ reference::OtherKeyWords; $newKey ]
Set Variable [ $otherKeys; Value:reference::OtherKeyWords ]
End If
End If
#
#
Select Window [ Name: "reorder"; Current file ]
Exit Loop If [ tagMenus::_Ltag & "¶" = FilterValues ( $$key ; tagMenus::_Ltag & "¶" )
and
tagMenus::tag ≠ $removeKey ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Now add remaining keys to list.
Go to Layout [ “ltagSCRIPTloops” (tagMenus) ]
If [ Get (LastError) ≠ 101 ]
Go to Record/Request/Page
[ Next ]
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
If [ tagMenus::_Ltag & "¶" = FilterValues ( $$key ; tagMenus::_Ltag & "¶" )
and
tagMenus::tag ≠ $removeKey ]
Set Variable [ $newKey; Value:tagMenus::tag ]
#
#
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
// Select Window [ Name: "Learn"; Current file ]
Go to Layout [ “learnSCRIPTloops” (testlearn) ]
Set Field [ testlearn::OtherKeyWords; $otherKeys & ", " & $newKey ]
Set Variable [ $otherKeys; Value:testlearn::OtherKeyWords ]
Go to Layout [ “ltagSCRIPTloops” (tagMenus) ]
Else If [ Get (LastError) ≠ 112 ]
Set Field [ reference::OtherKeyWords; $otherKeys & ", " & $newKey ]
Set Variable [ $otherKeys; Value:reference::OtherKeyWords ]
End If
End If
#
#
Select Window [ Name: "reorder"; Current file ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
End If
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
August 19, ଘ౮28 19:55:09 Library.fp7 - addORremoveTagFromCitationStep2keyword -1-
