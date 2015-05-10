tagMenu: changeSpellingOfKeywordOrNodeTag
#
Allow User Abort [ Off ]
#
If [ $$stopTest = 1
//or $$citationMatch = "key"
//or $$citationMatch = "node"
//or $$citationMatch = "health"
or $$citationMatch = "path" ]
Exit Script [ ]
End If
#
#First turn back any spelling changes made by dragging
#text into field.
Set Variable [ $$tag; Value:tagMenus::_Ltag ]
Set Variable [ $tagSpelling; Value:tagMenus::tagSpelling ]
Perform Script [ “insureEqualityOfSpellFields” ]
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
Set Field [ tagMenus::tag; "keyword" & tagMenus::_Ltag ]
Else If [ $$citationMatch = "node" ]
Set Field [ tagMenus::tag; "node" & tagMenus::_Ltag ]
End If
Show Custom Dialog [ Message: "Blank tag records are not allowed."; Buttons: “OK” ]
End If
#
Perform Script [ “removeTextFormattingAndCommas” ]
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
#Commit changes to the spellling.
Commit Records/Requests
Set Variable [ $newSpelling; Value:tagMenus::tag ]
#
#Get library name for use in comment below.
Set Variable [ $libraryName; Value:TEMP::sectionName ]
#
#
#
#
#
#
#BEGIN A - Check if a tag with this spelling
#already exists in this section of the library.
Loop
New Window [ ]
Enter Find Mode [ ]
Set Field [ tagMenus::tag; "==" & $newSpelling ]
// Set Field [ tagMenus::ksection; TEMP::ksection ]
Set Field [ ruleTagMenuGroups::ksection; TEMP::ksection ]
Set Field [ tagMenus::match; $$citationMatch ]
Perform Find [ ]
Exit Loop If [ Get (FoundCount) ≤ 1 ]
If [ Get (FoundCount) > 1 ]
Close Window [ Current Window ]
Set Variable [ $turnRed; Value:$newSpelling ]
Refresh Window
#
#If change was made to a new tag do this:
If [ tagMenus::tagSpelling = "" ]
If [ $$citationMatch = "node" ]
Show Custom Dialog [ Message: "A node with this exact spelling already exists. The system allows this, though for your sake add an initial and a picture to help you tell these nodes apart."; Buttons: “OK” ]
Else If [ $$citationMatch = "key" ]
Show Custom Dialog [ Message: "Every tag in this library section must have a unique name. Change the spelling of the newly created tag or delete it."; Buttons: “change”, “delete”; Input #1: tagMenus::tag, "change spelling" ]
End If
#
#If change was made to an old tag do this:
Else If [ tagMenus::tagSpelling ≠ "" ]
If [ $$citationMatch = "node" ]
Show Custom Dialog [ Message: "A node with this exact spelling already exists."; Buttons: “OK” ]
Else If [ $$citationMatch = "key" ]
Show Custom Dialog [ Message: "Every tag in this library section must have a unique name. Change the spelling of current tag to something new or revert to its old spelling."; Buttons: “change”, “revert”; Input #1: tagMenus::tag, "change spelling" ]
Commit Records/Requests
End If
End If
Set Variable [ $turnRed ]
#
#Choice 2
If [ Get ( LastMessageChoice ) = 2 ]
#
#Choice 2: node
If [ $$citationMatch = "node" ]
#If new tag, user has been informed and we can exit.
If [ tagMenus::tagSpelling = "" ]
Set Field [ tagMenus::tagSpelling; tagMenus::tag ]
Refresh Window
Exit Script [ ]
#
#If change is made to an existing tag, then go
#to part B.
Else If [ tagMenus::tagSpelling ≠ "" ]
Set Variable [ $exit; Value:1 ]
End If
#
#Choice 2: key
Else If [ $$citationMatch = "key" ]
If [ tagMenus::tagSpelling = "" ]
#If user decided to delete new tag then delete it.
Delete Record/Request
[ No dialog ]
Refresh Window
Exit Script [ ]
#
May 10, 平成27 12:52:41 Library.fp7 - changeSpellingOfKeywordOrNodeTag -1-
tagMenu: changeSpellingOfKeywordOrNodeTag
#If change is made to an existing tag, then go
#to part B.
Else If [ tagMenus::tagSpelling ≠ "" ]
Set Field [ tagMenus::tag; tagMenus::tagSpelling ]
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
Perform Script [ “changeSpellingOfKeywordOrNodeTag” ]
Exit Script [ ]
#
End If
End If
End If
Exit Loop If [ $exit = 1 ]
End Loop
#
#END A - Check if a tag with this spelling
#already exists in this section of the library.
#
#
#
#
#
#
#BEGIN B - Check if a tag with this spelling
#already exists in the library.
If [ $exit ≠ 1 ]
Go to Layout [ “ReferenceMenu2keywordOrNodeSpellCheck” (tagMenus) ]
#
Enter Find Mode [ ]
Set Field [ tagMenus::tag; "==" & $newSpelling ]
Set Field [ tagMenus::match; $$citationMatch ]
Perform Find [ ]
#
#If duplicates exists ask user what they want to do.
If [ Get (FoundCount) > 1 ]
#
#Show tags under their categories.
Sort Records [ Specified Sort Order: ruleTagSectionName::name; ascending
ruleTagMenuGroups::order; based on value list: “order”
ruleTagMenuGroups::name; ascending
tagMenus::orderOrLock; based on value list: “order”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
#
#Go to tag in question.
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ $$key = tagMenus::_Ltag ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
// #Filemake has bug where if this commit records
// #is not here, the comment box that comes up next
// #will not allow the user to select option 2 until
// #a few seconds after box appears. With commmit
// #this hang up does not happen.
// Commit Records/Requests
#
#Ask question.
Show Custom Dialog [ Message: "'" & $newSpelling & "' already exists in library. Keep the new copy of it 1) under light grey category, or 2) remove it from there and add the dark grey category including its copy of '" & $newSpelling & "' to current library section, or"; Buttons: “3”, “2”, “1”;
Input #1: tagMenus::tag, "3) Change spelling to make it unique." ]
#
#Choice 3, user wants to keep duplicate.
If [ Get ( LastMessageChoice ) = 3 ]
#Go on to Part C.
#
#
#Choice 2, user wants to add orginal tag to
#current library section and delete the
#duplicate tag.
Else If [ Get ( LastMessageChoice ) = 2 ]
#
#Make key being replaced the old key.
Set Variable [ $$keyOLD; Value:$$key ]
#
#If there is more than one duplicate exit the scirpt
#to allow the user to choose which duplicate to
#to add to the current library.
If [ Get (FoundCount) > 2 ]
Pause/Resume Script [ Indefinitely ]
Set Variable [ $$key; Value:tagMenus::_Ltag ]
#
#If user decided to use light grey category (the
#category the new tag was created under instead
#of using one of the old tags instead under one
#of the dark grey categories) close window and
#and exit the script.
If [ $$key = $$keyOLD ]
#
Close Window [ Current Window ]
#
#Update spelling of word in case of future changes
#to its spelling that would then trigger the first
May 10, 平成27 12:52:41 Library.fp7 - changeSpellingOfKeywordOrNodeTag -2-
tagMenu: changeSpellingOfKeywordOrNodeTag
#part of this scirpt to udpate the spelling in the
#tag list.
Set Field [ tagMenus::tagSpelling; $newSpelling ]
Set Variable [ $$key ]
Set Variable [ $$keyOLD ]
Exit Script [ ]
End If #
#Add category to current library section, which
#of course includes the tag of interest.
Set Field [ ruleTagMenuGroups::ksection; TEMP::ksection & ¶ & ruleTagMenuGroups::ksection ] #
#Go to duplicate and delete it.
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ $$keyOLD = tagMenus::_Ltag ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
Delete Record/Request
[ No dialog ]
Else If [ Get (FoundCount) = 2 ]
#Go to new key and copy it.
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ $$key
≠ tagMenus::_Ltag ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
Set Variable [ $$key; Value:tagMenus::_Ltag ] #
#Add category to current library section, which
#of course includes the tag/sujbect of interest.
Set Field [ ruleTagMenuGroups::ksection; TEMP::ksection & ¶ & ruleTagMenuGroups::ksection ] #
#Go to duplicate and delete it.
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ $$keyOLD = tagMenus::_Ltag ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
Delete Record/Request
[ No dialog ]
End If #
#Turn off recordLoad script and go to EDIT layout
#to change keys in records tagged with old key.
Set Variable [ $$stoploadCitation; Value:1 ]
Go to Layout [ “Reference” (reference) ] #
#Remove focus from other window so don't get
#error 301: record in use, which prevents key from
#being replaced.
Set Variable [ $windowName; Value:Get (WindowName) ]
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Setup"; Current file ]
#The field selected does not matter. It serves
#only to remove the focus.
Go to Field [ tempSetup::kuserLocation ]
Go to Field [ ]
Else If [ Get (LastError)
≠ 112 ]
#The field selected does not matter. It serves
#only to remove the focus.
Go to Field [ testlearn::_Number ]
Go to Field [ ]
End If
Else If [ Get (LastError)
≠ 112 ]
#The field selected does not matter. It serves
#only to remove the focus.
Go to Field [ reference::_Number ]
Go to Field [ ]
End If
Select Window [ Name: $windowName; Current file ] #
#If user is consolidating a keyword.
If [ $$citationMatch = "key" ] #
#Replace old key with selected key to consolidate
#primary records under one key.
Allow User Abort [ Off ]
Set Error Capture [ On ]
Enter Find Mode [ ]
Set Field [ reference::kkeywordPrimary; $$keyOLD ]
Perform Find [ ]
If [ Get (LastError)
≠ 401 ]
Go to Record/Request/Page
[ First ]
Loop
Set Field [ reference::kkeywordPrimary; $$key ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
End If
Commit Records/Requests #
#Replace old key with selected key to consolidate
#other records under one key. Since the spelling
#is the same only the key needs to be replaced.
Enter Find Mode [ ]
Set Field [ reference::kkeywordOther; $$keyOLD ]
Perform Find [ ]
If [ Get (LastError)
≠ 401 ]
Go to Record/Request/Page
[ First ]
Loop
Set Field [ reference::kkeywordOther; $$key ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
End If #
#If user is consolidating a node.
Else If [ $$citationMatch = "node" ] #
May 10, 平成27 12:52:41 Library.fp7 - changeSpellingOfKeywordOrNodeTag -3-
tagMenu: changeSpellingOfKeywordOrNodeTag
#Replace old key with selected key to consolidate
#primary records under one key.
Allow User Abort [ Off ]
Set Error Capture [ On ]
Enter Find Mode [ ]
Set Field [ reference::knodePrimary; $$keyOLD ]
Perform Find [ ]
If [ Get (LastError)
≠ 401 ]
Go to Record/Request/Page
[ First ]
Loop
Set Field [ reference::knodePrimary; $$key ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
End If #
#Replace old key with selected key to consolidate
#other records under one key. Since the spelling
#is the same only the key needs to be replaced.
Enter Find Mode [ ]
Set Field [ reference::knodeOther; $$keyOLD ]
Perform Find [ ]
If [ Get (LastError)
≠ 401 ]
Go to Record/Request/Page
[ First ]
Loop
Set Field [ reference::knodeOther; $$key ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
End If
End If #
#Return to original layout.
Set Variable [ $$stoploadCitation ] #
#Show added category to user with tag under it.
Close Window [ Current Window ]
#If earlier script took user to another window
#to prevent 301 error, then closing the window
#will put the focus on that window which is not
#the correct window, thus this next step.
Select Window [ Name: "Tag Menus"; Current file ]
Set Variable [ $$stoploadCitation; Value:1 ]
Enter Find Mode [ ]
Set Field [ ruleTagMenuGroups::ksection; TEMP::ksection ]
Set Field [ tagMenus::match; $$citationMatch ]
Perform Find [ ] #
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
End If #
#Go to newly added tag.
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ $$key = tagMenus::_Ltag ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop #
#Highlight changes.
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Setup"; Current file ]
If [ $$citationMatch = "node" ]
Set Variable [ $$citationItem; Value:tempSetup::kdefaultNodePrimary ]
Set Variable [ $$key; Value:testlearn::kNodeOther ]
End If
Else If [ Get (LastError)
≠ 112 ]
If [ $$citationMatch = "key" ]
Set Variable [ $$citationItem; Value:testlearn::kKeywordPrimary ]
Set Variable [ $$node; Value:testlearn::kcKeywordOther ]
Else If [ $$citationMatch = "node" ]
Set Variable [ $$citationItem; Value:testlearn::kNodePrimary ]
Set Variable [ $$key; Value:testlearn::kNodeOther ]
End If
End If
Else If [ Get (LastError)
≠ 112 ]
If [ $$citationMatch = "key" ]
Set Variable [ $$citationItem; Value:reference::kkeywordPrimary ]
Set Variable [ $$node; Value:reference::kkeywordOther ]
Else If [ $$citationMatch = "node" ]
Set Variable [ $$citationItem; Value:reference::knodePrimary ]
Set Variable [ $$key; Value:reference::knodeOther ]
End If
End If
Refresh Window
Select Window [ Name: "Tag Menus" ]
Refresh Window #
#Clear variables only needed for this script.
Set Variable [ $$stoploadCitation ]
Set Variable [ $$key ]
Set Variable [ $$keyOLD ]
Set Variable [ $$keyOLD ] #
#This halt step was placed after discovering when
#adding a new group because it contains a tag that
#is spelled the same as a tag already in this section,
#the spell/duplicate check script ends with no field
#selected, but then after the exit step was used the
#the system would enter the field, even though no
#scripts tell the system to take any further action after
#the exit, and on scripts are waiting to finish after
#the spell/duclicate check script finishes. This halt
#script step takes care of the problem the exit does not.
Go to Field [ ]
Halt Script
May 10, 平成27 12:52:41 Library.fp7 - changeSpellingOfKeywordOrNodeTag -4-
tagMenu: changeSpellingOfKeywordOrNodeTag
Halt Script
#
#Choice 1, user wants to change spelling.
Else If [ Get ( LastMessageChoice ) = 1 ]
Set Variable [ $newSpelling ]
Close Window [ Current Window ]
Perform Script [ “changeSpellingOfKeywordOrNodeTag” ]
Exit Script [ ]
End If
End If
#
#END B - Check if a tag with this spelling
#already exists in the library.
#
#
#
#
#
#
#BEGIN C - Change spelling of uniquely spelled tag.
#
Close Window [ Current Window ]
#
#If Part B was skipped due to spelling of node
#clear the exit variable which is needed in Part C.
End If
Set Variable [ $exit ]
#
#
Set Variable [ $recordNumber; Value:Get (RecordNumber) ]
#
#If the spellling of the tag has changed or if tag
#is new do the following.
If [ tagMenus::tag ≠ tagMenus::tagSpelling and tagMenus::tagSpelling ≠ "" ]
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
End If
Else If [ Get (LastError) ≠ 112 ]
Commit Records/Requests
End If
Select Window [ Name: "Tag Menus"; Current file ]
#
#Replace the old spelling with the new one.
Set Variable [ $$stoploadCitation; Value:1 ]
Set Variable [ $oldSpelling; Value:tagMenus::tagSpelling ]
Set Variable [ $$key; Value:tagMenus::_Ltag ]
#Update spelling of word in case of future changes
Set Field [ tagMenus::tagSpelling; $newSpelling ]
#
#Replace in Reference table.
Go to Layout [ “Reference” (reference) ]
#
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
Set Variable [ $tags; Value:reference::OtherKeyWords ]
Set Field [ reference::OtherKeyWords; ", ,, " & $tags & ", ,, " ]
Set Variable [ $tags; Value:reference::OtherKeyWords ]
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
Set Field [ reference::OtherKeyWords; Substitute ( $tags ; ", " & $oldSpelling & ", " ; ", " & $newSpelling & ", " ) ]
Else If [ $$citationMatch = "node" ]
#
#Change spelling of one node. If two or more
May 10, 平成27 12:52:41 Library.fp7 - changeSpellingOfKeywordOrNodeTag -5-
tagMenu: changeSpellingOfKeywordOrNodeTag
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
Set Variable [ $exit ] #
#Sort list alphabetically and recreate otherNode
#field from list.
Sort Records [ Specified Sort Order: TEMP::tempListNode; ascending ]
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
End Loop #
#Now create one temp record. This is done because
#the Setup window shows one temp record that
#contains the current global default node, section, etc.
#information. The system just deleted all temp
#records, so unless one is now created, the user
#will see a blank setup screen.
New Record/Request #
#Set the nodeOther field with new alphabetized list.
Go to Layout [ “Reference” (reference) ]
Set Field [ reference::NodeOthers; $tags ]
End If #
#Remove comma from front and back of list so it
#looks nice.
If [ $$citationMatch = "key" ]
Set Variable [ $otherKeys; Value:reference::OtherKeyWords ]
Set Field [ reference::OtherKeyWords; Substitute ( $otherKeys ; ", ,, " ; "" ) ]
End If
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop #
#Replace in TestLearn table.
Go to Layout [ “learn4” (testlearn) ] ##
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
Loop#
#Add comma to last item and before first item
#in list for spelling changes script which has
#to find words separated by commas.
If [ $$citationMatch = "key" ]
Set Variable [ $tags; Value:testlearn::OtherKeyWords ]
Set Field [ testlearn::OtherKeyWords; ", ,, " & $tags & ", ,, " ]
Set Variable [ $tags; Value:testlearn::OtherKeyWords ]
Else If [ $$citationMatch = "node" ] #
#Create list of values.
Set Variable [ $tags; Value:testlearn::NodeOthers ]
Set Field [ testlearn::NodeOthers; Substitute ( $tags ; "; " ; "¶" ) ]
Set Variable [ $tags; Value:testlearn::NodeOthers ] #
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
End If #
#Change spelling.
If [ $$citationMatch = "key" ]
Set Field [ testlearn::OtherKeyWords; Substitute ( $tags ; ", " & $oldSpelling & ", " ; ", " & $newSpelling & ", " ) ]
Else If [ $$citationMatch = "node" ] #
#Change spelling of one node. If two or more
#nodes spelling is identical leave others alone.
#Reason: nodes can have same spelling and when
#change spelling of one need to leave others alone
#until user specfically changes their spelling too.
Go to Record/Request/Page
[ First ]
May 10, 平成27 12:52:41 Library.fp7 - changeSpellingOfKeywordOrNodeTag -6-
tagMenu: changeSpellingOfKeywordOrNodeTag
Loop
If [ TEMP::tempListNode = $oldSpelling ]
Set Field [ TEMP::tempListNode; $newSpelling ]
Set Variable [ $exit; Value:1 ]
End If
Exit Loop If [ $exit = 1 ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
Set Variable [ $exit ] #
#Sort list alphabetically and recreate otherNode
#field from list.
Sort Records [ Specified Sort Order: TEMP::tempListNode; ascending ]
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
End Loop #
#Now create one temp record. This is done because
#the Setup window shows one temp record that
#contains the current global default node, section, etc.
#information. The system just deleted all temp
#records, so unless one is now created, the user
#will see a blank setup screen.
New Record/Request #
#Set the nodeOther field with new alphabetized list.
Go to Layout [ “learn4” (testlearn) ]
Set Field [ testlearn::NodeOthers; $tags ]
End If #
#Remove comma from front and back of list so it
#looks nice.
If [ $$citationMatch = "key" ]
Set Variable [ $otherKeys; Value:testlearn::OtherKeyWords ]
Set Field [ testlearn::OtherKeyWords; Substitute ( $otherKeys ; ", ,, " ; "" ) ]
End If
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
Go to Layout [ original layout ]
#Decided not to re-alaphabetize list as would
#bog down system. User can do so by taking item
#away and adding at back using the O button on
#the Tag Menus window.
// #Set record number so can return user to it when done.
// Set Variable [ $recordNumber; Value:Get (RecordNumber) ]
// #Now re-alphabetize and add new keyword to citation.
// Sort Records [ Specified Sort Order: tagMenus::tag; ascending ]
[ Restore; No dialog ]
// Go to Record/Request/Page
[ First ]
// Select Window [ Name: "References"; Current file ]
// If [ Get (LastError) = 112 ]
// Select Window [ Name: "Learn"; Current file ]
// Set Variable [ $otherKeys; Value:testlearn::OtherKeyWords ]
// Else If [ Get (LastError)
≠ 112 ]
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
// Else If [ Get (LastError)
≠ 112 ]
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
// Else If [ Get (LastError)
≠ 112 ]
// Set Field [ reference::OtherKeyWords; $otherKeys & ", " & $newKey ]
// Set Variable [ $otherKeys; Value:reference::OtherKeyWords ]
// End If
// End If
// #
// Select Window [ Name: "Tag Menus"; Current file ]
// Go to Record/Request/Page
[ Next; Exit after last ]
// End Loop #
#Not sure why this update fails at this point.
#The variable is correct, but the field fails to take
#it, so I moved this this step up to right after old
#spelling variable is created from tagSpelling field.
// #Update spelling of word in case of future changes
May 10, 平成27 12:52:41 Library.fp7 - changeSpellingOfKeywordOrNodeTag -7-
tagMenu: changeSpellingOfKeywordOrNodeTag
// #to its spelling that would then trigger the first
// #part of this scirpt to udpate the spelling in the
// #tag list.
// Go to Record/Request/Page [ $recordNumber ]
[ No dialog ]
// Set Field [ tagMenus::tagSpelling; $newSpelling ]
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
Set Variable [ $$stoploadCitation ]
Exit Script [ ]
#
End If
#
#Update spelling of word in case of future changes
#to its spelling that would then trigger the first
#part of this scirpt to udpate the spelling in the
#tag list.
Set Field [ tagMenus::tagSpelling; $newSpelling ]
#
#END C - Change spelling of uniquely spelled tag.
May 10, 平成27 12:52:41 Library.fp7 - changeSpellingOfKeywordOrNodeTag -8-
