July 21, 2018 13:49:00 Library.fmp12 - checkKeyANDNodeTagNames -1-
tagMenu: checkKeyANDNodeTagNames
#
#
#Admin task.
Allow User Abort [ Off ]
#
#Stop script if this script will slow down
#other scripts.
If [ $$stopTest = 1
//or $$citationMatch = "key"
//or $$citationMatch = "node"
//or $$citationMatch = "copyright"
or $$citationMatch = "path"
or $$citationMatch = "brainstorm" ]
Exit Script [ ]
End If
#
#First turn back any spelling changes made by dragging
#text into other records.
If [ Get ( ActiveFieldName ) = "tag" ]
#
#Set this tag variable to keep any changes
#user made to the current record, so it can be
#checked for duplication later in this script.
Set Variable [ $$tag; Value:tagMenus::_Ltag ]
End If
Set Variable [ $tagSpelling; Value:tagMenus::tagSpelling ]
Perform Script [ “CHUNK_checkForDraggedPasteChanges” ]
Set Variable [ $$tag ]
Set Field [ tagMenus::tagSpelling; $tagSpelling ]
#
#If user approved spelling for this tag and no
#changes have been made then cancel the script.
If [ tagMenus::tag = tagMenus::tagSpelling and tagMenus::tag ≠ "" ]
Exit Script [ ]
End If
#
#If blank, put in ID number.
If [ tagMenus::tag = "" ]
If [ $$citationMatch = "key" ]
#
#If spelling field is blank, put in ID number.
If [ tagMenus::tagSpelling = "" ]
Set Field [ tagMenus::tagSpelling; "keyword" & tagMenus::_Ltag ]
Set Field [ tagMenus::tag; "keyword" & tagMenus::_Ltag ]
Else
Set Field [ tagMenus::tag; tagMenus::tagSpelling ]
End If
#
#
Else If [ $$citationMatch = "node" ]
#
#If spelling field is blank, put in ID number.
If [ tagMenus::tagSpelling = "" ]
Set Field [ tagMenus::tagSpelling; "node" & tagMenus::_Ltag ]
Set Field [ tagMenus::tag; "node" & tagMenus::_Ltag ]
Else
Set Field [ tagMenus::tag; tagMenus::tagSpelling ]
End If
End If
#
Show Custom Dialog [ Message: "Blank tag records are not allowed."; Default Button: “OK”, Commit: “Yes” ]
End If
#
Perform Script [ “removeTextFormattingAndCommas” ]
#
#The $$key variable is set by main record load
#scripts, so remember it, and change it back
#to this setting when script is done.
Set Variable [ $RememberKey; Value:$$Key ]
#
#Get the key for this record for later in script
#when it will be used to change the spelling in
#any records tagged with this key, but of course
#showing the old spelling of the tag. The spellling
#unlike the key is belongs to the tagged record
#not the tag, and so the spelling must be changed
#in every record tagged.
Set Variable [ $$key; Value:tagMenus::_Ltag ]
#
#
#Commit changes to the spellling.
Commit Records/Requests
Set Variable [ $newSpelling; Value:tagMenus::tag ]
#
#If the this node is the primary node, then
#update the temp field with the name change.
If [ tagMenus::_Ltag = TEMP::kdefaultNodePrimary ]
Set Field [ TEMP::DEFAULTNodePrimaryName; tagMenus::tag ]
End If
#
#If the this node is the test subject node, then
#update the temp field with the name change.
If [ tagMenus::_Ltag = TEMP::kdefaultNodeTestSubject ]
Set Field [ TEMP::DEFAULTNodeTestSubjectName; tagMenus::tag ]
End If
#
#If the this node is an other node, then
#inform user that they need to remove and
#add it back to see the change take place.
If [ FilterValues ( TEMP::kdefaultNodeOther ; tagMenus::_Ltag & "¶" ) ]
Show Custom Dialog [ Message: "On the Setup's Node Tag Menus' window, click the O button twice: 1) to remove and then 2) to
add it back. This forces an update of its spelling in all temporary fields."; Default Button: “OK”, Commit: “Yes” ]
Show Custom Dialog [ Message: "This manual requirement is on the list for automation in a future version of the library app.";
Default Button: “OK”, Commit: “Yes” ]
End If
#
#Get library name for use in comment below.
Set Variable [ $libraryName; Value:TEMP::userLibraryName ]
#
#
#
#
#
#
#BEGIN A - Check if a tag with this spelling
#already exists in this library.
#
#
#This loop will first identitfy any duplicate
#tags. If the user changes the spelling, it will
#then repeat to see if the changed spelling is
#a duplicate, and so on, until the user either
#creates a unique tag, reverts the tag in
#question back to its original spelling, OR if
#this a node tag, the loop will end after telling
#the user that duplicate nodes spellings are
#OK, but can create problems.
Loop
#Stop tag record load script.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
#
#Open a new window find any duplicate tags.
#This keeps the current window's scroll
#position static for the user.
New Window [ Name: "Duplicate Check"; Height: 1; Width: 1; Top: -10000; Left: -10000; Style: Document; Close: “Yes”; Minimize:
“Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
Enter Find Mode [ ]
Set Field [ tagMenus::tag; "==" & $newSpelling ]
Set Field [ tagMenus::match; $$citationMatch ]
Perform Find [ ]
#
#Turn on tag record load script.
Set Variable [ $$stopLoadTagRecord ]
#
#If a tag with this spelling is found,
#inform the user.
Exit Loop If [ Get (FoundCount) ≤ 1 ]
If [ Get (FoundCount) > 1 ]
#
#Close the duplicate check window, and
#highlight the duplicates and orginal tag.
Close Window [ Current Window ]
Set Variable [ $turnRed; Value:$newSpelling ]
Refresh Window
#
#This first 'if...' I don't think is in use, as a
#blank tag field is always filled in by an above
#section of this script that must have been
#added later, and then I failed to see that this
#check was no longer necessary? Anyway,
#leaving this check in for now, until I've got
#more brain resources to feel confident that it
#can be removed!
If [ tagMenus::tagSpelling = "" ]
If [ $$citationMatch = "node" ]
Show Custom Dialog [ Message: "A node with this exact spelling already exists (FYI: it may only show up in the
Reference section). Nodes can have the same name, though for your sake, add an initial, number, or a
picture to help you tell these nodes apart."; Default Button: “OK”, Commit: “Yes” ]
Else If [ $$citationMatch = "key" ]
Show Custom Dialog [ Message: "Every keyword in this library must have a unique name. Change the spelling of
this duplicate keyword or delete it."; Default Button: “change”, Commit: “Yes”; Button 2: “delete”, Commit: “No”;
Input #1: tagMenus::tag, "change spelling" ]
End If
#
#On the first time thru the loop where a
#duplicate is found, and all future times thru
#this loop where a duplicate is found, inform
#the user like this...
Else If [ tagMenus::tagSpelling ≠ "" ]
If [ $$citationMatch = "node" ]
Show Custom Dialog [ Message: "A node with this exact spelling already exists (FYI: it may only show up in the
Reference section). Nodes can have the same name, though for your sake, add an initial, number, or a
picture to help you tell these nodes apart."; Default Button: “OK”, Commit: “Yes” ]
Else If [ $$citationMatch = "key" ]
Show Custom Dialog [ Message: "Every keyword in this library must have a unique name. Change this keyword's
spelling or revert it back to its old spelling = " & tagMenus::tagSpelling & "."; Default Button: “change”, Commit:
“Yes”; Button 2: “revert”, Commit: “No”; Input #1: tagMenus::tag, "change spelling" ]
Commit Records/Requests
End If
End If
Set Variable [ $turnRed ]
#
#Choice 2 (only applies to key tags)
If [ Get ( LastMessageChoice ) = 2 ]
#
#Choice 2: key
If [ $$citationMatch = "key" ]
#
#If user decided to delete new tag then delete it.
If [ tagMenus::tagSpelling = "" ]
Delete Record/Request
[ No dialog ]
#
#Reset $$key variable.
Set Variable [ $$Key; Value:$RememberKey ]
Refresh Window
Exit Script [ ]
#
#If change is made to an existing tag, then go
#to part B.
Else If [ tagMenus::tagSpelling ≠ "" ]
Set Field [ tagMenus::tag; tagMenus::tagSpelling ]
#
#Reset $$key variable.
Set Variable [ $$Key; Value:$RememberKey ]
Refresh Window
Exit Script [ ]
End If
End If
#
#Choice 1
Else If [ Get ( LastMessageChoice ) = 1 ]
#
If [ $$citationMatch = "node" ]
#
#If new tag, user has been informed and we can exit.
If [ tagMenus::tagSpelling = "" ]
Set Field [ tagMenus::tagSpelling; tagMenus::tag ]
#
#Reset $$key variable.
Set Variable [ $$Key; Value:$RememberKey ]
Refresh Window
Exit Script [ ]
#
#If change is made to an existing tag, then go
#to part B.
Else If [ tagMenus::tagSpelling ≠ "" ]
Set Variable [ $exit; Value:1 ]
End If
#
Else If [ $$citationMatch = "key" ]
#If change was made to a new tag check if spelling
#is already in use.
Set Variable [ $newSpelling; Value:tagMenus::tag ]
Refresh Window
#
#Set this tag variable to keep any changes
#user made to the current record, so it can be
#checked for duplication when this script is
#run all over again right now.
Set Variable [ $$tag; Value:tagMenus::_Ltag ]
Perform Script [ “checkKeyANDNodeTagNames (update)” ]
#
#Reset $$key variable.
Set Variable [ $$Key; Value:$RememberKey ]
Refresh Window
Exit Script [ ]
#
End If
End If
End If
Exit Loop If [ $exit = 1 ]
End Loop
#
#Close the duplicate check window of still
#open, and clear the exit variable in
#preparation for part B.
Close Window [ Name: "Duplicate Check"; Current file ]
Set Variable [ $exit ]
#
#
#
#END A - Check if a tag with this spelling
#already exists in this section of the library.
#
#
#
#
#
#
#BEGIN B - Complete spelling change or adding of new tag.
#
#
#
#
Set Variable [ $recordNumber; Value:Get (RecordNumber) ]
#
#If the spellling of the tag has changed or if tag
#is new do the following.
If [ tagMenus::tag ≠ tagMenus::tagSpelling and tagMenus::tagSpelling ≠ "" ]
#
#(See disabled code not below.)
// Set Variable [ $$key; Value:tagMenus::_Ltag ]
#
#Commit records so user can change spelling.
#Without commit records the system will not find
#a newly added tag during the find part script.
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Setup"; Current file ]
Commit Records/Requests
Else If [ Get (LastError) ≠ 112 ]
Commit Records/Requests
#
#
#This block of code is the unfinished start of
#informing the user when they change the
#spelling of a keyword that is in use as a
#reference header that its alphabetical position
#might be altered. I thought this is important
#information for keyword order number
#changes, which can actually un-alphabetize
#the order the reference group headers.
#However, I thought such information would be
#pointing-out-the-obvious when it comes to
#spelling changes changing the alphabetical
#position, and, so, stopped work on this code
#and disabled it.
Set Variable [ $$stoploadCitation; Value:1 ]
// New Window [ Name: "CheckDuplicateRecordPosition"; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize:
“Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
// Go to Layout [ “ReferenceScriptLoops” (reference) ]
// Enter Find Mode [ ]
// Set Field [ tagKeywordPrimary::_Ltag; $$key ]
// Perform Find [ ]
// #
// #If the edited record moved then note this.
// If [ Get ( FoundCount ) ≠ 0 ]
// Show Custom Dialog [ Message: "lkjlk"; Default Button: “OK”, Commit: “Yes” ]
// End If
// Close Window [ Current Window ]
#
End If
Else If [ Get (LastError) ≠ 112 ]
Commit Records/Requests
#
#
#See if the edited record changed position in
#the main reference window as a result of
#alphabetical changing edits.
Set Variable [ $$stoploadCitation; Value:1 ]
Set Variable [ $currentrecord; Value:Get (RecordNumber) ]
New Window [ Name: "CheckDuplicateRecordPosition"; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”;
Zoom Control Area: “Yes”; Resize: “Yes” ]
If [ $$citationMatch = "key" and $$referenceSort = "" ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagKeywordPrimary::orderOrLock; based on
value list: “testPulldownListANDsortOrderList”
tagKeywordPrimary::tag; ascending
reference::publicationYearOrStuffOrderNumber; based on value list: “testPulldownListANDsortOrderList”
reference::Title; ascending
reference::thoughtsNotesEtc; ascending ]
[ Restore; No dialog ]
Else
Sort Records [ Keep records in sorted order; Specified Sort Order: tagKeywordPrimary::orderOrLock; based on
value list: “order Pulldown List”
tagKeywordPrimary::tag; ascending
reference::referenceShort; ascending ]
[ Restore; No dialog ]
End If
Else If [ $$citationMatch = "node" and $$referenceSort = "author" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: reference::sortByAuthor; ascending
reference::referenceForReferenceWindow; ascending ]
[ Restore; No dialog ]
End If
#
#If the edited record move then note this.
If [ $currentrecord ≠ Get (RecordNumber) ]
Set Variable [ $recordMoved; Value:Get (RecordNumber) ]
#
#
Else
#This block of code is the unfinished start of
#informing the user when they change the
#spelling of a keyword that is in use as a
#reference header that its alphabetical position
#might be altered. I thought this is important
#information for keyword order number
#changes, which can actually un-alphabetize
#the order the reference group headers.
#However, I thought such information would be
#pointing-out-the-obvious when it comes to
#spelling changes changing the alphabetical
#position, and, so, stopped work on this code
#and disabled it.
// Set Variable [ $$stoploadCitation; Value:1 ]
// New Window [ Name: "CheckDuplicateRecordPosition"; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize:
“Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
// Go to Layout [ “ReferenceScriptLoops” (reference) ]
// Enter Find Mode [ ]
// Set Field [ tagKeywordPrimary::_Ltag; $$key ]
// Perform Find [ ]
// #
// #If the edited record moved then note this.
// If [ Get ( FoundCount ) ≠ 0 ]
// Show Custom Dialog [ Message: "lkjlk"; Default Button: “OK”, Commit: “Yes” ]
// Set Variable [ ]
// End If
// Close Window [ Current Window ]
End If
#
Close Window [ Name: "CheckDuplicateRecordPosition"; Current file ]
#
#
#Re-sort and return to edited record if it
#was moved.
If [ $recordMoved ≠ "" ]
If [ $$citationMatch = "key" and $$referenceSort = "" ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagKeywordPrimary::orderOrLock; based
on value list: “testPulldownListANDsortOrderList”
tagKeywordPrimary::tag; ascending
reference::publicationYearOrStuffOrderNumber; based on value list: “testPulldownListANDsortOrderList”
reference::Title; ascending
reference::thoughtsNotesEtc; ascending ]
[ Restore; No dialog ]
Else
Sort Records [ Keep records in sorted order; Specified Sort Order: tagKeywordPrimary::orderOrLock; based
on value list: “order Pulldown List”
tagKeywordPrimary::tag; ascending
reference::referenceShort; ascending ]
[ Restore; No dialog ]
End If
Else If [ $$citationMatch = "node" and $$referenceSort = "author" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: reference::sortByAuthor; ascending
reference::referenceForReferenceWindow; ascending ]
[ Restore; No dialog ]
End If
Go to Record/Request/Page [ $recordMoved ]
[ No dialog ]
End If
#
#
#
End If
#
#Replace the old spelling with the new one.
Select Window [ Name: "Tag Menus"; Current file ]
Set Variable [ $oldSpelling; Value:tagMenus::tagSpelling ]
Set Variable [ $$key; Value:tagMenus::_Ltag ]
#
#Update spelling of word in case of future changes
Set Field [ tagMenus::tagSpelling; $newSpelling ]
#
#Replace in Reference table.
#
#Turn off reference load script.
Set Variable [ $$stoploadCitation; Value:1 ]
Go to Layout [ “Reference” (reference) ]
#
#Error notification needs to be turned off in case
#a tag that has never been used has its spelling
#changed, in which case this unused tag will
#will not be found and give the user a notification
#to that effect.
Allow User Abort [ Off ]
Set Error Capture [ On ]
Enter Find Mode [ ]
If [ $$citationMatch = "key" ]
Set Field [ reference::kkeywordOther; $$key & ¶ ]
Else If [ $$citationMatch = "node" ]
Set Field [ reference::knodeOther; $$key & ¶ ]
End If
Perform Find [ ]
Loop
#
#Add comma to last item and before first item
#in list for spelling changes script which has
#to find words separated by commas.
If [ $$citationMatch = "key" ]
#
#Replace changed spelling of other key words
#but do not re-alphabatize.
// Set Variable [ $tags; Value:reference::OtherKeyWords ]
// Set Field [ reference::OtherKeyWords; ", ,, " & $tags & ", ,, " ]
// Set Variable [ $tags; Value:reference::OtherKeyWords ]
#
#Replace changed spelling of other key words
#and re-alphabatize.
#
#Create list of values.
Set Variable [ $tags; Value:reference::OtherKeyWords ]
Set Field [ reference::OtherKeyWords; Substitute ( $tags ; ", " ; "¶" ) ]
Set Variable [ $tags; Value:reference::OtherKeyWords ]
#
#Transfer list from variable to temporary list of records.
#This list will be used next to change the spelling
#of only one item. If there are two or more items
#in this list with the same spelling, these other
#items will not be affected. The user after all
#only changed the spellling of one tag, not all the
#tags spelled the same way.
Go to Layout [ “TEMPnodeList” (TEMP) ]
Set Variable [ $numberOfNodes; Value:ValueCount ( $tags ) ]
Delete All Records
[ No dialog ]
Loop
Exit Loop If [ $numberOfNodes = 0 ]
New Record/Request
Set Field [ TEMP::tempListNode; GetValue ( $tags ; $numberOfNodes ) ]
Set Variable [ $numberOfNodes; Value:$numberOfNodes - 1 ]
End Loop
#
Else If [ $$citationMatch = "node" ]
#
#Create list of values.
Set Variable [ $tags; Value:reference::NodeOthers ]
Set Field [ reference::NodeOthers; Substitute ( $tags ; "; " ; "¶" ) ]
Set Variable [ $tags; Value:reference::NodeOthers ]
#
#Transfer list from variable to temporary list of records.
#This list will be used next to change the spelling
#of only one item. If there are two or more items
#in this list with the same spelling, these other
#items will not be affected. The user after all
#only changed the spellling of one tag, not all the
#tags spelled the same way.
Go to Layout [ “TEMPnodeList” (TEMP) ]
Set Variable [ $numberOfNodes; Value:ValueCount ( $tags ) ]
Delete All Records
[ No dialog ]
Loop
Exit Loop If [ $numberOfNodes = 0 ]
New Record/Request
Set Field [ TEMP::tempListNode; GetValue ( $tags ; $numberOfNodes ) ]
Set Variable [ $numberOfNodes; Value:$numberOfNodes - 1 ]
End Loop
End If
#
#Change spelling of only one tag.
If [ $$citationMatch = "key" ]
#
#OLD
// Set Field [ reference::OtherKeyWords; Substitute ( $tags ; ", " & $oldSpelling & ", " ; ", " & $newSpelling & ", " ) ]
#
#New
#
#Change spelling of one node. If two or more
#nodes' spelling is identical leave others alone.
#Reason: nodes can have same spelling and when
#change spelling of one need to leave others alone
#until user specfically changes their spelling too.
Go to Record/Request/Page
[ First ]
Loop
If [ TEMP::tempListNode = $oldSpelling ]
Set Field [ TEMP::tempListNode; $newSpelling ]
Set Variable [ $exit; Value:1 ]
End If
Exit Loop If [ $exit = 1 ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
Set Variable [ $exit ]
#
#Sort list alphabetically and recreate otherNode
#field from list.
Sort Records [ Keep records in sorted order; Specified Sort Order: TEMP::tempListNode; ascending ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ Last ]
Set Variable [ $tags; Value:TEMP::tempListNode ]
Loop
Delete Record/Request
[ No dialog ]
Exit Loop If [ Get ( FoundCount ) = 0 ]
Set Variable [ $list; Value:$tags ]
Set Variable [ $tags; Value:TEMP::tempListNode & ", " & $list ]
End Loop
#
#Now create one temp record. This is done because
#the Setup window shows one temp record that
#contains the current global default node, section, etc.
#information. The system just deleted all temp
#records, so unless one is now created, the user
#will see a blank setup screen.
New Record/Request
#
#Set the nodeOther field with new alphabetized list.
Go to Layout [ “Reference” (reference) ]
Set Field [ reference::OtherKeyWords; $tags ]
#
Else If [ $$citationMatch = "node" ]
#
#Change spelling of one node. If two or more
#nodes' spelling is identical leave others alone.
#Reason: nodes can have same spelling and when
#change spelling of one need to leave others alone
#until user specfically changes their spelling too.
Go to Record/Request/Page
[ First ]
Loop
If [ TEMP::tempListNode = $oldSpelling ]
Set Field [ TEMP::tempListNode; $newSpelling ]
Set Variable [ $exit; Value:1 ]
End If
Exit Loop If [ $exit = 1 ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
Set Variable [ $exit ]
#
#Sort list alphabetically and recreate otherNode
#field from list.
Sort Records [ Keep records in sorted order; Specified Sort Order: TEMP::tempListNode; ascending ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ Last ]
Set Variable [ $tags; Value:TEMP::tempListNode ]
Loop
Delete Record/Request
[ No dialog ]
Exit Loop If [ Get ( FoundCount ) = 0 ]
Set Variable [ $list; Value:$tags ]
Set Variable [ $tags; Value:TEMP::tempListNode & "; " & $list ]
End Loop
#
#Now create one temp record. This is done because
#the Setup window shows one temp record that
#contains the current global default node, section, etc.
#information. The system just deleted all temp
#records, so unless one is now created, the user
#will see a blank setup screen.
New Record/Request
#
#Set the nodeOther field with new alphabetized list.
Go to Layout [ “Reference” (reference) ]
Set Field [ reference::NodeOthers; $tags ]
End If
#
#Remove comma from front and back of list so it
#looks nice.
If [ $$citationMatch = "key" ]
Set Variable [ $otherKeys; Value:reference::OtherKeyWords ]
Set Field [ reference::OtherKeyWords; Substitute ( $otherKeys ; ", ,, " ; "" ) ]
End If
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Turn on reference load script.
Set Variable [ $$stoploadCitation ]
#
#
#Replace in TestLearn table, but turn off Learn
#record load script before looping thru them.
Set Variable [ $$stoploadCitation; Value:1 ]
Go to Layout [ “learn4” (testlearn) ]
#
#Error notification needs to be turned off in case
#a tag that has never been used has its spelling
#changed, in which case this unused tag will
#will not be found and give the user a notification
#to that effect.
Allow User Abort [ Off ]
Set Error Capture [ On ]
Enter Find Mode [ ]
If [ $$citationMatch = "key" ]
Set Field [ testlearn::kcKeywordOther; $$key & ¶ ]
Else If [ $$citationMatch = "node" ]
Set Field [ testlearn::kNodeOther; $$key & ¶ ]
End If
Perform Find [ ]
Loop
#
#Add comma to last item and before first item
#in list for spelling changes script which has
#to find words separated by commas.
If [ $$citationMatch = "key" ]
Set Variable [ $tags; Value:testlearn::OtherKeyWords ]
Set Field [ testlearn::OtherKeyWords; ", ,, " & $tags & ", ,, " ]
Set Variable [ $tags; Value:testlearn::OtherKeyWords ]
Else If [ $$citationMatch = "node" ]
#
#Create list of values.
Set Variable [ $tags; Value:testlearn::NodeOthers ]
Set Field [ testlearn::NodeOthers; Substitute ( $tags ; "; " ; "¶" ) ]
Set Variable [ $tags; Value:testlearn::NodeOthers ]
#
#Transfer list from variable to temporary list of records.
#This list will be used next to change the spelling
#of only one item. If there are two or more items
#in this list with the same spelling, these other
#items will not be affected. The user after all
#only changed the spellling of one tag, not all the
#tags spelled the same way.
Go to Layout [ “TEMPnodeList” (TEMP) ]
Set Variable [ $numberOfNodes; Value:ValueCount ( $tags ) ]
Delete All Records
[ No dialog ]
Loop
Exit Loop If [ $numberOfNodes = 0 ]
New Record/Request
Set Field [ TEMP::tempListNode; GetValue ( $tags ; $numberOfNodes ) ]
Set Variable [ $numberOfNodes; Value:$numberOfNodes - 1 ]
End Loop
End If
#
#Change spelling.
If [ $$citationMatch = "key" ]
Set Field [ testlearn::OtherKeyWords; Substitute ( $tags ; ", " & $oldSpelling & ", " ; ", " & $newSpelling & ", " ) ]
Else If [ $$citationMatch = "node" ]
#
#Change spelling of one node. If two or more
#nodes spelling is identical leave others alone.
#Reason: nodes can have same spelling and when
#change spelling of one need to leave others alone
#until user specfically changes their spelling too.
Go to Record/Request/Page
[ First ]
Loop
If [ TEMP::tempListNode = $oldSpelling ]
Set Field [ TEMP::tempListNode; $newSpelling ]
Set Variable [ $exit; Value:1 ]
End If
Exit Loop If [ $exit = 1 ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
Set Variable [ $exit ]
#
#Sort list alphabetically and recreate otherNode
#field from list.
Sort Records [ Keep records in sorted order; Specified Sort Order: TEMP::tempListNode; ascending ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ Last ]
Set Variable [ $tags; Value:TEMP::tempListNode ]
Loop
Delete Record/Request
[ No dialog ]
Exit Loop If [ Get ( FoundCount ) = 0 ]
Set Variable [ $list; Value:$tags ]
Set Variable [ $tags; Value:TEMP::tempListNode & "; " & $list ]
End Loop
#
#Now create one temp record. This is done because
#the Setup window shows one temp record that
#contains the current global default node, section, etc.
#information. The system just deleted all temp
#records, so unless one is now created, the user
#will see a blank setup screen.
New Record/Request
#
#Set the nodeOther field with new alphabetized list.
Go to Layout [ “learn4” (testlearn) ]
Set Field [ testlearn::NodeOthers; $tags ]
End If
#
#Remove comma from front and back of list so it
#looks nice.
If [ $$citationMatch = "key" ]
Set Variable [ $otherKeys; Value:testlearn::OtherKeyWords ]
Set Field [ testlearn::OtherKeyWords; Substitute ( $otherKeys ; ", ,, " ; "" ) ]
End If
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Prevent halting in loadTagRecord script.
Set Variable [ $$doNotHaltOtherScripts; Value:1 ]
Go to Layout [ original layout ]
Set Variable [ $$doNotHaltOtherScripts ]
#
#Turn back on Learn record load script.
Set Variable [ $$stoploadCitation ]
#
#
#Decided not to re-alaphabetize list as would
#bog down system. User can do so by taking item
#away and adding it back using the O button on
#the Tag Menus window.
// #Set record number so can return user to it when done.
// Set Variable [ $recordNumber; Value:Get (RecordNumber) ]
// #Now re-alphabetize and add new keyword to citation.
// Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenus::tag; ascending ]
[ Restore; No dialog ]
// Go to Record/Request/Page
[ First ]
// Select Window [ Name: "References"; Current file ]
// If [ Get (LastError) = 112 ]
// Select Window [ Name: "Learn"; Current file ]
// Set Variable [ $otherKeys; Value:testlearn::OtherKeyWords ]
// Else If [ Get (LastError) ≠ 112 ]
// Set Variable [ $otherKeys; Value:reference::OtherKeyWords ]
// End If
// #
// #Find and set first value in keyword list.
// #It will not have a comma in front like the other items.
// Select Window [ Name: "Tag Menus"; Current file ]
// Loop
// If [ tagMenus::_Ltag & "¶" = FilterValues ( $$key ; tagMenus::_Ltag & "¶" ) ]
// Set Variable [ $newKey; Value:tagMenus::tag ]
// #
// Select Window [ Name: "References"; Current file ]
// If [ Get (LastError) = 112 ]
// Select Window [ Name: "Learn"; Current file ]
// Set Field [ testlearn::OtherKeyWords; $newKey ]
// Set Variable [ $otherKeys; Value:testlearn::OtherKeyWords ]
// Else If [ Get (LastError) ≠ 112 ]
// Set Field [ reference::OtherKeyWords; $newKey ]
// Set Variable [ $otherKeys; Value:reference::OtherKeyWords ]
// End If
// End If
// #
// Select Window [ Name: "Tag Menus"; Current file ]
// Exit Loop If [ tagMenus::_Ltag & "¶" = FilterValues ( $$key ; tagMenus::_Ltag & "¶" ) ]
// Go to Record/Request/Page
[ Next; Exit after last ]
// End Loop
// #
// #Now add remaining keywords to list.
// Go to Record/Request/Page
[ Next; Exit after last ]
// Loop
// If [ tagMenus::_Ltag & "¶" = FilterValues ( $$key ; tagMenus::_Ltag & "¶" ) ]
// Set Variable [ $newKey; Value:tagMenus::tag ]
// #
Select Window [ Name: "References"; Current file ]
// If [ Get (LastError) = 112 ]
// Select Window [ Name: "Learn"; Current file ]
// Set Field [ testlearn::OtherKeyWords; $otherKeys & ", " & $newKey ]
// Set Variable [ $otherKeys; Value:testlearn::OtherKeyWords ]
// Else If [ Get (LastError) ≠ 112 ]
// Set Field [ reference::OtherKeyWords; $otherKeys & ", " & $newKey ]
// Set Variable [ $otherKeys; Value:reference::OtherKeyWords ]
// End If
// End If
// #
// Select Window [ Name: "Tag Menus"; Current file ]
// Go to Record/Request/Page
[ Next; Exit after last ]
// End Loop
#
#Not sure why this update fails at this point.
#The variable is correct, but the field fails to take
#it, so I moved this step up to right after old
#spelling variable is created from tagSpelling field.
// #Update spelling of word in case of future changes
// #to its spelling that would then trigger the first
// #part of this scirpt to udpate the spelling in the
// #tag list.
// Go to Record/Request/Page [ $recordNumber ]
[ No dialog ]
// Set Field [ tagMenus::tagSpelling; $newSpelling ]
#
#Return to Tag Menus window and sort records
#according to users wishes.
Select Window [ Name: "Tag Menus"; Current file ]
If [ $$citationMatch = "key" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenuGroup::orderOrLibraryType; based on value list:
“order Pulldown List”
tagMenuGroup::name; ascending
tagMenus::orderOrLock; based on value list: “order Pulldown List”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Else
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenuGroup::orderOrLibraryType; based on value list:
“order Pulldown List”
tagMenuGroup::name; ascending
tagMenus::tag; ascending ]
[ Restore; No dialog ]
End If
Set Variable [ $$stoploadCitation ]
#
#Reset $$key variable.
Set Variable [ $$Key; Value:$RememberKey ]
#
End If
#
#END B - Complete spelling change or adding of new tag.
#
#
