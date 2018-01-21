January 15, 2018 17:19:27 Library.fmp12 - addORremovePrimaryTag -1-
tagMenu: addORremovePrimaryTag
#
#Admin tasks.
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
#This prevents the system trademark tag (not
#user created) being used improperly.
If [ tagMenuGroup::_Lgroup = "92020171119521809" and $$RecordID = "" ]
Show Custom Dialog [ Message: "Trademark tags can only be added to reference records, and then only if if the reference is for
a trademark, logo, brand, etc."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
#
#Subsection is locked by its creator node.
If [ testSectionCreatorLock::orderOrLock ≠ "" ]
Show Custom Dialog [ Message: "Locked Test tags cannot be added or removed from learn records. Select this record's creator
node — " & testSectionCreatorLock::tag & " — in the setup window and enter the password to unlock it."; Default Button:
“OK”, Commit: “Yes” ]
Exit Script [ ]
End If
#
#Brainstorm tag is locked by its creator node.
If [ tagCreatorLock::orderOrLock ≠ "" and $$citationMatch = "brainstorm" ]
Show Custom Dialog [ Message: "Locked Brainstorm tags cannot be added or removed from learn records. Select this record's
creator node — " & $$lockedMainLearnRecord & " — in the setup window and enter the password to unlock it."; Default
Button: “OK”, Commit: “No” ]
Halt Script
End If
#
#If main record node is currenlty locked then
#stop script and inform the user, unless the
#user altering the key or path tag, which is
#unique to the user's computer, for a locked
#reference or learn record.
If [ $$citationMatch ≠ "path"
 and
$$citationMatch ≠ "key"
 and
$$citationMatch ≠ "brainstorm"
 and
$$citationMatch ≠ "test" ]
If [ $$lockedMainRefRecord ≠ "" and Left ( Get (LayoutName) ; 1 ) = "r" ]
Show Custom Dialog [ Message: "Tags cannot be added or removed from locked reference records (EXCEPTIONS — Key
P and O tags and Path tags). Select this record's creator node — " & $$lockedMainRefRecord & " — in the setup
window and enter the password to unlock it."; Default Button: “OK”, Commit: “Yes” ]
Halt Script
Else If [ $$lockedMainLearnRecord ≠ "" and Left ( Get (LayoutName) ; 1 ) = "l" ]
Show Custom Dialog [ Message: "Tags cannot be added or removed from locked learn records. EXCEPTIONS — Key (P
and O), Brainstorm, and Test tags. Select this record's creator node — " & $$lockedMainLearnRecord & " — in the
setup window and enter the password to unlock it."; Default Button: “OK”, Commit: “Yes” ]
Halt Script
End If
End If
#
#If primary node is currenlty locked then stop
#user from changing the default copyright.
If [ $$citationMatch = "copyright" ]
If [ TEMP::primaryNodeIsLocked ≠ "" ]
Show Custom Dialog [ Message: "The default copyright can be changed once the default primary node — " & TEMP::
DEFAULTNodePrimaryName & " — is unlocked, or an unlocked node is selected as the primary node."; Default Button:
“OK”, Commit: “Yes” ]
Halt Script
Else If [ TEMP::primaryNodesCreatorNodeIsLocked ≠ "" ]
Show Custom Dialog [ Message: "The default copyright can be changed once the creator — " & TEMP::
primaryNodesCreatorNodeIsLocked & " — of the default primary node — " & TEMP::DEFAULTNodePrimaryName & "
— is unlocked, or an unlocked node is selected as the primary node."; Default Button: “OK”, Commit: “Yes” ]
Halt Script
End If
End If
#
#
#Reference Section Only
#Because I keep forgetting to press find mode, this
#bit of script is to confirm that the user really wants
#to add or change the tag of the first record instead of
#finding records with selected tag.
If [ Left (Get (LayoutName) ; 3 ) = "ref" and $$stopAdd ≠ 1 ]
If [ //Primary node and key match
tagMenus::_Ltag = $$citationitem and $$citationMatch = "node"
or
tagMenus::_Ltag = $$citationitem and $$citationMatch = "key"
or
//Other tags match
tagMenus::_Ltag = $$citationitem and $$citationMatch = "copyright"
or
tagMenus::_Ltag = $$citationitem and $$citationMatch = "publication"
or
tagMenus::_Ltag = $$citationitem and $$citationMatch = "path"
or
tagMenus::_Ltag = $$citationitem and $$citationMatch = "publisher" ]
Show Custom Dialog [ Message: "Remove Tag?" & ¶ &
"OR " & ¶ &
"Find references tagged with it?"; Default Button: “remove”, Commit: “Yes”; Button 2: “find”, Commit: “No”; Button 3:
“cancel”, Commit: “No” ]
Else
Show Custom Dialog [ Message: "Add Tag?" & ¶ &
"OR " & ¶ &
"Find references tagged with it?"; Default Button: “add”, Commit: “Yes”; Button 2: “find”, Commit: “No”; Button 3:
“cancel”, Commit: “No” ]
End If
If [ Get ( LastMessageChoice ) = 2 ]
#This variable is needed becasue message choice 2
#gets carried over to the Find Mode Script, which then
#activates tag instead of reference record find mode.
Set Variable [ $$ClearMessageChoice; Value:1 ]
Perform Script [ “findMode (update)” ]
Exit Script [ ]
Else If [ Get ( LastMessageChoice ) = 3 ]
Set Variable [ $$referenceRecordOne ]
Exit Script [ ]
Else If [ Get ( LastMessageChoice ) = 1 ]
Set Variable [ $$referenceRecordOne ]
End If
End If
#
#
If [ $$stopAddTagToCitation = 1 ]
Exit Script [ ]
End If
#
#Stop script if user is looking at item/detail tags
#in add mode, as these tags cannot be applied
#to reference records.
If [ $$add = 1 and $$citationMatch = "testSetup" ]
Show Custom Dialog [ Message: "You cannot tag reference records with item tags. So why then are there buttons? The buttons
show up because I have not made time to create a separate layout just for item tags. This issue has been logged as a minor
irritation."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
#
#
#
#Set key word if need to re-sort after
#editing is completed (used in
#finishReferenceEdit script).
If [ $$citationMatch = "key" ]
Set Variable [ $$primaryKeyWord; Value:$$citationItem ]
End If
#
#
#
#Check main checkbox if record is not already
#a main record. This is because when going to
#edit cite or reference records, only main records
#are shown by default.
If [ Get ( LayoutTableName ) = "testlearn" or Get ( LayoutTableName ) = "reference" ]
If [ "main" & ¶ ≠ FilterValues ( testlearn::filterFind ; "main" & ¶ ) and Get ( LayoutTableName ) = "testlearn" ]
Set Variable [ $filterFind; Value:testlearn::filterFind ]
Set Field [ testlearn::filterFind; "main" & ¶ & $filterFind ]
Else If [ "main" & ¶ ≠ FilterValues ( reference::filterFind ; "main" & ¶ ) and Get ( LayoutTableName ) = "reference" ]
Set Variable [ $filterFind; Value:reference::filterFind ]
Set Field [ reference::filterFind; "main" & ¶ & $filterFind ]
End If
End If
#
#Set variable to note table name in case tag is from
#testLearn table, in which case an 'L' will need to be
#added to the tag to conditionally format the buttons
#for Learn Ref and Learn citations in the Tag Menus window.
Set Variable [ $tableName; Value:Get ( LayoutTableName ) ]
#
#
#Get key for tag that is to be added to record.
If [ Right ( Get (LayoutName) ; 4 ) = "test" ]
Set Variable [ $tag; Value:testSubsectionTemplate::_LtestSubsection ]
Set Variable [ $tagName; Value:testSubsectionTemplate::name ]
Else If [ Right ( Get (LayoutName) ; 5 ) = "3cite" ]
Set Variable [ $tag; Value:reference::_Lreference ]
Else If [ Right ( Get (LayoutName) ; 7 ) = "refcite" ]
Set Variable [ $tag; Value:testlearn::_Ltestlearn ]
Else If [ Right ( Get (LayoutName) ; 8 ) = "sections" ]
Set Variable [ $tag; Value:testSubsectionLibraryName::_Lgroup ]
Set Variable [ $tagName; Value:testSubsectionLibraryName::name ]
#
#Stop check spelling script as this script is triggered
#on section layout by record load trigger, and
#so before user can change the spelling.
Set Variable [ $$stopChangeSectionName; Value:1 ]
Else If [ Right ( Get (LayoutName) ; 4 ) ≠ "cite" ]
Set Variable [ $tag; Value:tagMenus::_Ltag ]
#
#If a node tag is being added in the setup
#window this lock variable will be essential
#below when this primary node is set as the
#default node for the library. Locked nodes set
#as default primary node turn off the users
#ability to create new records with this locked
#node.
If [ $$createNewPrimary ≠ 1 ]
Set Variable [ $lock; Value:tagMenus::orderOrLock ]
End If
#
#Also need to know the node's name to
#populate the primary node name field
#if necessary.
Set Variable [ $nodeName; Value:tagMenus::tag ]
#
#Also need to know the node's creator in case it
#is locked, so this node can also be locked.
Set Variable [ $nodescreatorKey; Value:tagMenus::kRecordCreatorNode ]
Set Variable [ $nodescreatorName; Value:tagCreatorLock::tag ]
End If
#
#Leave field user so can see
#conditional formatting.
Go to Field [ ]
#
#Turn off the T scripts variable once the
#user selects or unselects a tag. This variable
#is set when the user navigates to a reference
#field that is blank and triggers a Tag Menu script.
Set Variable [ $$TgotoCitationMenuWithBlankField ]
#
#If removing a test result record, the database
#will jump to the next record's tag menu selection.
#So to keep the library on the tag orginally
#selected, the system must record this record's
#number now. This will be be used below
#for test records only.
Set Variable [ $recordNumber; Value:Get (RecordNumber) ]
#
#Conditionally format selected tag.
If [ Right ( Get (LayoutName) ; 4 ) ≠ "cite" ]
Set Variable [ $$citationItem; Value:tagMenus::_Ltag ]
Else If [ Right ( Get (LayoutName) ; 5 ) = "3cite" ]
Set Variable [ $$citationItem; Value:reference::_Lreference ]
Set Variable [ $citeCopyright; Value:reference::kCopyright ]
Set Variable [ $citeCopyrightDate; Value:reference::CopyrightYear ]
Set Variable [ $citekeywordOther; Value:reference::kkeywordOther ]
Set Variable [ $citekeywordOtherWords; Value:reference::OtherKeyWords ]
Set Variable [ $citekeywordPrimary; Value:reference::kkeywordPrimary ]
#
Set Variable [ $filename; Value:reference::fileName ]
Set Variable [ $fileLocation; Value:reference::kfileLocation ]
Set Variable [ $folderpath; Value:reference::kfolderpath ]
Set Variable [ $medium; Value:reference::kmedium ]
Set Variable [ $URL; Value:reference::URL ]
Set Variable [ $URLdate; Value:reference::URLdate ]
Else If [ Right ( Get (LayoutName) ; 7 ) = "refcite" ]
Set Variable [ $$citationItem; Value:testlearn::_Ltestlearn ]
Set Variable [ $citeCopyright; Value:testlearn::kcopyright ]
Set Variable [ $citekeywordOther; Value:testlearn::kcKeywordOther ]
Set Variable [ $citekeywordOtherWords; Value:testlearn::OtherKeyWords ]
Set Variable [ $citekeywordPrimary; Value:testlearn::kKeywordPrimary ]
End If
#
// New Window [ Name: "Add Tag"; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”;
Resize: “Yes” ]
#
#Select reference, learn, or setup window.
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
If [ Get (LastError) = 112 ]
#
#
#
#BEGIN — SETUP WINDOW
#
#
#
// Select Window [ Name: "Setup"; Current file ]
#
#Check which tag user is looking at and then...
If [ $$citationMatch = "node" ]
#
#If primary node is in use, then remove it,
#and its creators key.
If [ tempSetup::kdefaultNodePrimary = $tag ]
Set Field [ tempSetup::kdefaultNodePrimary; "" ]
Set Field [ tempSetup::DEFAULTNodePrimaryName; "" ]
Set Field [ tempSetup::kdefaultNodePrimaryCreator; "" ]
Set Field [ tempSetup::primaryNodesCreatorNodeIsLocked; "" ]
#
#Finish removing the key.
Set Variable [ $$citationItem ]
Set Variable [ $$PrimaryNode ]
#
#If primary node is not in use add it and set
#variables to see if it was in the other node
#field so it can be removed from there thus
#preventing the same node showing up twice.
Else If [ tempSetup::kdefaultNodePrimary ≠ $tag ]
Set Field [ tempSetup::kdefaultNodePrimary; $tag ]
Set Field [ tempSetup::DEFAULTNodePrimaryName; $nodeName ]
#
#Also add the key for its creator node, as if it is
#locked, this primary node also needs to be locked.
Set Field [ tempSetup::kdefaultNodePrimaryCreator; $nodescreatorKey ]
If [ primaryNodesCreatorLock::orderOrLock ≠ "" ]
Set Field [ tempSetup::primaryNodesCreatorNodeIsLocked; $nodescreatorName ]
Else
Set Field [ tempSetup::primaryNodesCreatorNodeIsLocked; "" ]
End If
#
#Lock creation of new records if this node is
#locked using the script
#stopNewRecordsBeingCreatedByLockedNode.
If [ $lock ≠ "" ]
Set Field [ tempSetup::primaryNodeIsLocked; $lock ]
Else
Set Field [ tempSetup::primaryNodeIsLocked; "" ]
End If
Set Variable [ $$node; Value:tempSetup::kdefaultNodeOther ]
Set Field [ tempSetup::kdefaultNodeOther; //last item in list has no paragraph mark, so a valuecount test needs to
be done and if item is not removed, then the removal calc without the paragraph mark is used
If ( ValueCount ( $$node ) ≠ ValueCount ( Substitute ( $$node ; $$citationItem & "¶" ; "" ) ) ;
Substitute ( $$node ; $$citationItem & "¶" ; "" ) ;
Substitute ( $$node ; $$citationItem ; "" )
) ]
Set Variable [ $$PrimaryNode; Value:testlearn::kNodePrimary ]
Set Variable [ $$node; Value:tempSetup::kdefaultNodeOther ]
Set Variable [ $$skipFirstPartOfScript; Value:1 ]
#
#Record must be committed if user decides to
#perform a script on it right after this one or
#perform a find requiring the newly added key.
Commit Records/Requests
Perform Script [ “addORremoveOtherTagStep2_node (update name addORremoveTagFromCitationStep2node)” ]
Close Window [ Name: "reorder"; Current file ]
#
Exit Script [ ]
End If
#
Else If [ $$citationMatch = "copyright" ]
If [ tempSetup::kdefaultCopyright = $tag ]
Set Field [ tempSetup::kdefaultCopyright; "" ]
Set Variable [ $$citationItem ]
Set Variable [ $$copyright ]
Refresh Window
#
#goto Tag Menus window
Select Window [ Name: "Tag Menus"; Current file ]
Refresh Window
Exit Script [ ]
Else If [ testlearn::kcopyright ≠ $tag ]
Set Variable [ $$copyright; Value:tempSetup::kdefaultCopyright ]
Set Field [ tempSetup::kdefaultCopyright; $tag ]
Refresh Window
#
#goto Tag Menus window
Select Window [ Name: "Tag Menus"; Current file ]
Refresh Window
#
#Update pimary node with this new copyright
#information, so its test section, subsection,
#and item records will reflect this copyright
#selection. If the primary node is not selected
#that is OK because the copyright tag will be
#added when it is selected.
If [ TEMP::kdefaultNodePrimary ≠ "" ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
New Window [ Height: 1; Width: 1; Top: -10000; Left: -10000; Style: Document; Close: “Yes”; Minimize: “Yes”;
Maximize: “Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
Enter Find Mode [ ]
Set Field [ tagMenus::_Ltag; TEMP::kdefaultNodePrimary ]
Perform Find [ ]
Set Field [ tagMenus::notesOrCopyright; $tag ]
Close Window [ Current Window ]
Set Variable [ $$stopLoadTagRecord ]
End If
Show Custom Dialog [ Message: "The default node's copyright has been updated to match the library's default
copyright."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
End If
#
#Record must be committed if user decides to
#perform a script on it right after this one or
#perform a find requiring the newly added key.
Commit Records/Requests
#
#Refresh the windows so changed conditional formatting
#will show up.
Refresh Window
#
Set Variable [ $$stoploadCitation ]
#
#
#
#END — SETUP WINDOW
#
#
#
#BEGIN — LEARN WINDOW
#
#
#
Else If [ Get (LastError) ≠ 112 ]
#
#
#
#Check which tag user is looking at and then...
If [ $$citationMatch = "node" ]
#
#If primary node is in use, then remove it.
If [ testlearn::kNodePrimary = $tag ]
Set Field [ testlearn::kNodePrimary; "" ]
#
#Finish removing the key.
Set Variable [ $$citationItem ]
Set Variable [ $$PrimaryNode ]
#
#If primary node is not in use add it and set
#variables to see if it was in the other node
#field so it can be removed from there thus
#preventing the same node showing up twice.
Else If [ testlearn::kNodePrimary ≠ $tag ]
Set Field [ testlearn::kNodePrimary; $tag ]
Set Field [ testlearn::kNodeOther; //last item in list has no paragraph mark, so a valuecount test needs to be done
and if item is not removed, then the removal calc without the paragraph mark is used
If ( ValueCount ( $$node ) ≠ ValueCount ( Substitute ( $$node ; $$citationItem & "¶" ; "" ) ) ;
Substitute ( $$node ; $$citationItem & "¶" ; "" ) ;
Substitute ( $$node ; $$citationItem ; "" )
) ]
Set Variable [ $$node; Value:testlearn::kNodeOther ]
Set Variable [ $$PrimaryNode; Value:testlearn::kNodePrimary ]
Set Variable [ $$skipFirstPartOfScript; Value:1 ]
#
#Record must be committed if user decides to
#perform a script on it right after this one or
#perform a find requiring the newly added key.
Commit Records/Requests
Perform Script [ “addORremoveOtherTagStep2_node (update name addORremoveTagFromCitationStep2node)” ]
Close Window [ Name: "reorder"; Current file ]
Set Variable [ $$stopLoadTagRecord ]
#
Exit Script [ ]
End If
#
Else If [ $$citationMatch = "copyright" ]
If [ testlearn::kcopyright = $tag ]
Set Field [ testlearn::kcopyright; "" ]
Set Variable [ $$citationItem ]
Set Variable [ $$copyright ]
Else If [ testlearn::kcopyright ≠ $tag ]
Set Field [ testlearn::kcopyright; $tag ]
Set Variable [ $$copyright; Value:testlearn::kcopyright ]
End If
#
Else If [ $$citationMatch = "key" ]
#
#If primary keyword is in use, then remove it.
If [ testlearn::kKeywordPrimary = $tag ]
Set Field [ testlearn::kKeywordPrimary; "" ]
Set Variable [ $$citationItem ]
Set Variable [ $$PrimaryKey ]
#
#If primary keyword is not in use add it and set
#variables to see if it was in the other keyword
#field so it can be removed from there thus
#preventing the same keyword showing up twice.
Else If [ testlearn::kKeywordPrimary ≠ $tag ]
Set Field [ testlearn::kKeywordPrimary; $tag ]
Set Field [ testlearn::kcKeywordOther; //last item in list has no paragraph mark, so a valuecount test needs to be
done and if item is not removed, then the removal calc without the paragraph mark is used
If ( ValueCount ( $$key ) ≠ ValueCount ( Substitute ( $$key ; $$citationItem & "¶" ; "" ) ) ;
Substitute ( $$key ; $$citationItem & "¶" ; "" ) ;
Substitute ( $$key ; $$citationItem ; "" )
) ]
Set Variable [ $$key; Value:testlearn::kcKeywordOther ]
Set Variable [ $$PrimaryKey; Value:$tag ]
Set Variable [ $$skipFirstPartOfScript; Value:1 ]
#
#Record must be committed if user decides to
#perform a script on it right after this one or
#perform a find requiring the newly added key.
Commit Records/Requests
Perform Script [ “addORremoveOtherTagStep2_keyword (update name
addORremoveTagFromCitationStep2keyword)” ]
#
Exit Script [ ]
End If
#
Else If [ $$citationMatch = "test" ]
#
#If test tag is in use, then remove it.
Set Variable [ $number; Value:1 ]
Loop
If [ Case ( Left ( testlearn::kctestSubsectionInfo ; 2 ) = "00" ;
//If there two zeros in front of the order number, get the key using this calculation:
FilterValues ( Middle ( GetValue ( testlearn::kctestSubsectionInfo ; $number ) ; 4 ; 999 ) ; $tag & "¶" ) = $tag
& ¶ ;
//If there is only one zero in front of the order number, get the key using this calculation:
FilterValues ( Middle ( GetValue ( testlearn::kctestSubsectionInfo ; $number ) ; 3 ; 999 ) ; $tag & "¶" ) = $tag
& ¶
) ]
#
#
#Check if Learn record is in use
#on any reports.
Set Variable [ $$stoploadCitation; Value:1 ]
New Window [ Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”;
Resize: “Yes” ]
Go to Layout [ “tableReport” (report) ]
Set Variable [ $$stoploadCitation ]
#
#See if any picture 1 slots use
#this Learn record,
Enter Find Mode [ ]
Set Field [ report::ktestSubsection; $tag ]
Set Field [ report::kTag1; $$main ]
Perform Find [ ]
#Or picture 2 slots,
Enter Find Mode [ ]
Set Field [ report::ktestSubsection; $tag ]
Set Field [ report::kTag2; $$main ]
Extend Found Set [ ]
#Or picture 3 slots,
Enter Find Mode [ ]
Set Field [ report::ktestSubsection; $tag ]
Set Field [ report::kTag3; $$main ]
Extend Found Set [ ]
#Or picture 4 slots.
Enter Find Mode [ ]
Set Field [ report::ktestSubsection; $tag ]
Set Field [ report::kTag4; $$main ]
Extend Found Set [ ]
#
#If this record is in use on a report, this test
#tag cannot be removed until it is removed
#from these found reports. Tell the user this.
If [ Get (FoundCount) > 0 ]
Go to Layout [ “TEMP” (TEMP) ]
Show All Records
Delete All Records
[ No dialog ]
#
Go to Layout [ “tableReport” (report) ]
Loop
Set Variable [ $useList; Value:ReportTestSubject::tag &
" | report " &
TextColor( TextStyleAdd ( report::kreportNumber; "" ) ;RGB(0;0;0)) &
¶ &
"sub-section >> " & TextColor( TextStyleAdd ( reportSubsection::name; "" ) ;RGB(0;0;0)) ]
Go to Layout [ “TEMP” (TEMP) ]
New Record/Request
Set Field [ TEMP::DeleteMessageInTempWindow1; $useList ]
Go to Layout [ “tableReport” (report) ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
Go to Layout [ “TEMP” (TEMP) ]
Sort Records [ Keep records in sorted order; Specified Sort Order: TEMP::
DeleteMessageInTempWindow1; ascending ]
[ Restore; No dialog ]
View As
[ View as List ]
#
#Due to a bug in FM13, window must first be
#moved back into the screen area before the
#calculation of the current screen's
#dimensions can be taken.
Move/Resize Window [ Current Window; Top: 0; Left: 0 ]
Move/Resize Window [ Current Window; Height: Get ( ScreenHeight ); Width: 360; Top: 0; Left: Get
( ScreenWidth ) - ( Get ( ScreenWidth )/2 + 360) ]
Set Field [ TEMP::Message; "This Learn record is linked to sub-sections on the reports shown below,
and must be unlinked from all them to unlink it from this test tag." ]
Pause/Resume Script [ Indefinitely ]
Close Window [ Current Window ]
#
#
Set Variable [ $number; Value:"exit" ]
#
#Remove tag if Learn record is not in use on
#any reports.
Else
Close Window [ Current Window ]
Set Field [ testlearn::kctestSubsectionInfo; Substitute ( $$test ; GetValue ( testlearn::
kctestSubsectionInfo ; $number ) & "¶" ; "" ) ]
Set Field [ testlearn::orderTestInformation; "" ]
#
#
Set Variable [ $$test; Value:testlearn::kctestSubsectionInfo ]
Set Variable [ $$citationItem ]
Set Variable [ $number; Value:"exit" ]
End If
End If
Exit Loop If [ GetValue ( testlearn::kctestSubsectionInfo ; $number ) = "" //$number = exit will turn up a blank and
so exit this loop. ]
Exit Loop If [ $number = "" ]
Set Variable [ $add; Value:$number ]
Set Variable [ $number; Value:$add + 1 ]
End Loop
#
#If test item is not in use add it.
If [ $number ≠ "exit" ]
Set Variable [ $number; Value:1 ]
Loop
If [ Case ( Left ( testlearn::kctestSubsectionInfo ; 2 ) = "00" ;
//If there two zeros in front of the order number, get the key using this calculation:
FilterValues ( Middle ( GetValue ( testlearn::kctestSubsectionInfo ; $number ) ; 4 ; 999 ) ; $$test & "¶" ) ≠
$tag & ¶ ;
//If there is only one zero in front of the order number, get the key using this calculation:
FilterValues ( Middle ( GetValue ( testlearn::kctestSubsectionInfo ; $number ) ; 3 ; 999 ) ; $$test & "¶" ) ≠
$tag & ¶
) ]
Set Field [ testlearn::kctestSubsectionInfo; "001" & $tag & ¶ & $$test ]
Set Field [ testlearn::orderTestInformation; "001" ]
Set Variable [ $$test; Value:testlearn::kctestSubsectionInfo ]
Set Variable [ $number ]
#
#Record must be committed if user decides to
#perform a script on it right after this one or
#perform a find requiring the newly added key.
Commit Records/Requests
End If
Exit Loop If [ FilterValues ( Middle ( GetValue ( testlearn::kctestSubsectionInfo ; $number ) ; 4 ; 42 ) ; $$test &
"¶" ) = "" ]
Exit Loop If [ $number = "" ]
Set Variable [ $add; Value:$number ]
Set Variable [ $number; Value:$add + 1 ]
End Loop
#
#Give this newly tagged record the order
#number 001, and then sort all records
#so that it shows up as part of the current
#test tag's record set.
Set Field [ testlearn::orderTestInformation; "001" ]
Set Field [ TEMP::TLTestSort; "order" ]
Perform Script [ “sortTestOrBrainstormTaggedLearnRecords (update name change from
sortTLRecordsByOrderNumber)” ]
End If
#
Else If [ $$citationMatch = "brainstorm" ]
#
#If brainstorm item is in use, then remove it.
Set Variable [ $number; Value:1 ]
Loop
If [ FilterValues ( Middle ( GetValue ( testlearn::kcbrainstorm ; $number ) ; 4 ; 42 ) ; $tag & "¶" ) = $tag & ¶ ]
Set Field [ testlearn::kcbrainstorm; Substitute ( $$brainstorm ; GetValue ( testlearn::kcbrainstorm ; $number )
& "¶" ; "" ) ]
Set Field [ testlearn::orderTestInformation; "" ]
Set Variable [ $$brainstorm; Value:testlearn::kcbrainstorm ]
Set Variable [ $$citationItem ]
Set Variable [ $number; Value:"exit" ]
End If
Exit Loop If [ GetValue ( testlearn::kcbrainstorm ; $number ) = "" ]
Exit Loop If [ $number = "" ]
Set Variable [ $add; Value:$number ]
Set Variable [ $number; Value:$add + 1 ]
End Loop
#
If [ $number ≠ "exit" ]
Set Variable [ $number; Value:1 ]
Loop
#If brainstorm item is not in use add it.
If [ FilterValues ( Middle ( GetValue ( testlearn::kcbrainstorm ; $number ) ; 4 ; 42 ) ; $tagS & "¶" ) ≠ $tag & ¶ ]
Set Field [ testlearn::kcbrainstorm; "001" & $tag & ¶ & $$brainstorm ]
Set Variable [ $$brainstorm; Value:testlearn::kcbrainstorm ]
Set Variable [ $number ]
#
#Record must be committed if user decides to
#perform a script on it right after this one or
#perform a find requiring the newly added key.
Commit Records/Requests
End If
Exit Loop If [ FilterValues ( Middle ( GetValue ( testlearn::kcbrainstorm ; $number ) ; 4 ; 42 ) ; $tagS & "¶" ) =
"" ]
Exit Loop If [ $number = "" ]
Set Variable [ $add; Value:$number ]
Set Variable [ $number; Value:$add + 1 ]
End Loop
#
#Give this newly tagged record the order
#number 001, and then sort all records
#so that it shows up as part of the current
#test tag's record set.
Set Field [ testlearn::orderTestInformation; "001" ]
Set Field [ TEMP::TLTestSort; "order" ]
Perform Script [ “sortTestOrBrainstormTaggedLearnRecords (update name change from
sortTLRecordsByOrderNumber)” ]
End If
End If
#
#Record must be committed if user decides to
#perform a script on it right after this one or
#perform a find requiring the newly added key.
Commit Records/Requests
#
#Refresh the windows so changed conditional formatting
#will show up.
Refresh Window
#
Set Variable [ $$stoploadCitation ]
End If
#
#
#
#END — LEARN WINDOW
#
#
#
#BEGIN — REFERENCE WINDOW
#
#
#
Else If [ Get (LastError) ≠ 112 ]
#Check which tag user is looking at and then...
If [ $$citationMatch = "node" ]
#
#If primary node is in use, then remove it.
If [ reference::knodePrimary = $tag ]
Set Field [ reference::knodePrimary; "" ]
#
#Remove author copyright holder if there are
#no authors.
If [ reference::knodeOther = "" and reference::knodePrimary = "" and reference::referenceNodes = "" ]
#Perform removal for items with and without a
#paragraph mark, as the last item in checklist
#has no paragraph mark after it.
If [ Filter ( reference::kcopyrightHolder ; "1" ) = 1 ]
Show Custom Dialog [ Message: "Author is currently checked in the copyright section for this reference as a
copyright holder. Remove this check?"; Default Button: “No”, Commit: “Yes”; Button 2: “Yes”, Commit:
“No” ]
If [ Get ( LastMessageChoice ) = 2 ]
Set Field [ reference::kcopyrightHolder; Substitute ( reference::kcopyrightHolder ; "1" & "¶" ; "" ) ]
Set Field [ reference::kcopyrightHolder; Substitute ( reference::kcopyrightHolder ; "1" ; "" ) ]
End If
End If
End If
#
#Finish removing the key.
Set Variable [ $$citationItem ]
Set Variable [ $$PrimaryNode ]
#
#If primary node is not in use add it and set
#variables to see if it was in the other node
#field so it can be removed from there thus
#preventing the same node showing up twice.
Else If [ reference::knodePrimary ≠ $tag ]
Set Field [ reference::knodePrimary; $tag ]
Set Field [ reference::knodeOther; //last item in list has no paragraph mark, so a valuecount test needs to be done and if
item is not removed, then the removal calc without the paragraph mark is used
If ( ValueCount ( $$node ) ≠ ValueCount ( Substitute ( $$node ; $$citationItem & "¶" ; "" ) ) ;
Substitute ( $$node ; $$citationItem & "¶" ; "" ) ;
Substitute ( $$node ; $$citationItem ; "" )
) ]
Set Variable [ $$node; Value:reference::knodeOther ]
Set Variable [ $$PrimaryNode; Value:reference::knodePrimary ]
Set Variable [ $$skipFirstPartOfScript; Value:1 ]
#
#Record must be committed if user decides to
#perform a script on it right after this one or
#perform a find requiring the newly added key.
Commit Records/Requests
Perform Script [ “addORremoveOtherTagStep2_node (update name addORremoveTagFromCitationStep2node)” ]
Close Window [ Name: "reorder"; Current file ]
#
#If the user is adding a node tag to reference
#record on the main reference layout, then
#inform why they will not see it if the 'open
#authors' field is filled in.
Select Window [ Name: "References"; Current file ]
If [ reference::referenceNodes ≠ "" and Get (LayoutName) = "Reference" ]
Show Custom Dialog [ Message: "Because the open authors field is filled in, this node tag — while added to this
reference — will not show up as a reference author. Click 'edit' to edit the open authors field and see this
reference's node tags."; Default Button: “OK”, Commit: “Yes” ]
#
#Return to the Tag Menus window.
Select Window [ Name: "Tag Menus"; Current file ]
Set Variable [ $$stopLoadTagRecord ]
#
#If the node tag was changed then see if it
#affects the order of the current reference.
Else If [ $$citationMatch = "node" ]
#If this is the reference section and user is
#looking at either author/node or keyword/
#subject ordered records, check to see if this
#order has changed as a result of re-ordering
#the author/node or keyword/subject tags.
Commit Records/Requests
#
#See if the edited record changed position in
#the main reference window as a result of
#alphabetical or order number changing edits.
Set Variable [ $$stoploadCitation; Value:1 ]
Set Variable [ $currentrecord; Value:Get (RecordNumber) ]
New Window [ Name: "CheckDuplicateRecordPosition"; Style: Document; Close: “Yes”; Minimize: “Yes”;
Maximize: “Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
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
reference::referenceForReferenceWindow; ascending ]
[ Restore; No dialog ]
End If
#
#If the edited record moved then note this.
If [ $currentrecord ≠ Get (RecordNumber) ]
Set Variable [ $recordMoved; Value:Get (RecordNumber) ]
End If
Close Window [ Name: "CheckDuplicateRecordPosition"; Current file ]
#
#Re-sort to view edited record if it
#was moved.
If [ $recordMoved ≠ "" ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagKeywordPrimary::orderOrLock;
based on value list: “testPulldownListANDsortOrderList”
tagKeywordPrimary::tag; ascending
reference::publicationYearOrStuffOrderNumber; based on value list:
“testPulldownListANDsortOrderList”
reference::Title; ascending
reference::thoughtsNotesEtc; ascending ]
[ Restore; No dialog ]
Else
Sort Records [ Keep records in sorted order; Specified Sort Order: tagKeywordPrimary::orderOrLock;
based on value list: “order Pulldown List”
tagKeywordPrimary::tag; ascending
reference::referenceForReferenceWindow; ascending ]
[ Restore; No dialog ]
End If
Go to Record/Request/Page [ $recordMoved ]
[ No dialog ]
End If
End If
Set Variable [ $$stoploadCitation ]
Set Variable [ $$stopLoadTagRecord ]
#
#Return to the Tag Menus window.
Select Window [ Name: "Tag Menus"; Current file ]
#
Exit Script [ ]
End If
#
Else If [ $$citationMatch = "medium" ]
If [ reference::kmedium = $tag ]
Set Field [ reference::kmedium; "" ]
Set Variable [ $$citationItem ]
Set Variable [ $$medium ]
Else If [ reference::kmedium ≠ $tag ]
Set Field [ reference::kmedium; $tag ]
Set Variable [ $$medium; Value:reference::kmedium ]
End If
#
Else If [ $$citationMatch = "copyright" ]
If [ reference::kCopyright = $tag ]
Set Field [ reference::kCopyright; "" ]
Set Variable [ $$citationItem ]
Set Variable [ $$copyright ]
Else If [ reference::kCopyright ≠ $tag ]
Set Field [ reference::kCopyright; $tag ]
Set Variable [ $$copyright; Value:reference::kCopyright ]
End If
#
Else If [ $$citationMatch = "cite" ]
If [ reference::kcitation = $tag ]
Set Field [ reference::kcitation; "" ]
Set Variable [ $$citationItem ]
Set Variable [ $$cite ]
Else If [ reference::kcitation ≠ $tag ]
Set Field [ reference::kcitation; $tag ]
Set Variable [ $$cite; Value:reference::kcitation ]
Select Window [ Name: "Tag Menus"; Current file ]
Perform Script [ “CHUNKaddReferenceNodeAndKeywordTagIDs (update name
CHUNKaddReferenceNodesAndKeywords)” ]
End If
#
Else If [ $$citationMatch = "publication" ]
If [ reference::kpublication = $tag ]
Set Field [ reference::kpublication; "" ]
#
#Remove publication copyright holder.
#Perform removal for items with and without a
#paragraph mark, as the last item in checklist
#has no paragraph mark after it.
If [ Filter ( reference::kcopyrightHolder ; "4" ) = 4 ]
Show Custom Dialog [ Message: "Publication is currently checked in the copyright section for this reference as a
copyright holder. Remove this check?"; Default Button: “No”, Commit: “Yes”; Button 2: “Yes”, Commit: “No” ]
If [ Get ( LastMessageChoice ) = 2 ]
Set Field [ reference::kcopyrightHolder; Substitute ( reference::kcopyrightHolder ; "4" & "¶" ; "" ) ]
Set Field [ reference::kcopyrightHolder; Substitute ( reference::kcopyrightHolder ; "4" ; "" ) ]
End If
End If
#
#Finish removing the key.
Set Variable [ $$citationItem ]
Set Variable [ $$publication ]
#
Else If [ reference::kpublication ≠ $tag ]
#
#Add new key to reference.
Set Field [ reference::kpublication; $tag ]
Set Variable [ $$publication; Value:reference::kpublication ]
End If
#
Else If [ $$citationMatch = "publisher" ]
If [ reference::kpublisher = $tag ]
Set Field [ reference::kpublisher; "" ]
#
#Remove publication copyright holder.
#Perform removal for items with and without a
#paragraph mark, as the last item in checklist
#has no paragraph mark after it.
If [ Filter ( reference::kcopyrightHolder ; "5" ) = 5 ]
Show Custom Dialog [ Message: "Publisher is currently checked in the copyright section for this reference as a
copyright holder. Remove this check?"; Default Button: “No”, Commit: “Yes”; Button 2: “Yes”, Commit: “No” ]
If [ Get ( LastMessageChoice ) = 2 ]
Set Field [ reference::kcopyrightHolder; Substitute ( reference::kcopyrightHolder ; "5" & "¶" ; "" ) ]
Set Field [ reference::kcopyrightHolder; Substitute ( reference::kcopyrightHolder ; "5" ; "" ) ]
End If
End If
#
#Finish removing the key.
Set Variable [ $$citationItem ]
Set Variable [ $$publisher ]
#
Else If [ reference::kpublisher ≠ $tag ]
#
#Add key to reference.
Set Field [ reference::kpublisher; $tag ]
Set Variable [ $$publisher; Value:reference::kpublisher ]
End If
#
Else If [ $$citationMatch = "Path" ]
If [ reference::kfolderpath = $tag ]
Set Field [ reference::kfolderpath; "" ]
Set Variable [ $$citationItem ]
Set Variable [ $$Path ]
Else If [ reference::kfolderpath ≠ $tag ]
Set Field [ reference::kfolderpath; $tag ]
Set Variable [ $$Path; Value:reference::kfolderpath ]
End If
#
Else If [ $$citationMatch = "key" ]
#
#If primary keyword is in use, then remove it.
If [ reference::kkeywordPrimary = $tag ]
Set Field [ reference::kkeywordPrimary; "" ]
Set Variable [ $$citationItem ]
Set Variable [ $$PrimaryKey ]
#
#If primary keyword is not in use add it and set
#variables to see if it was in the other keyword
#field so it can be removed from there thus
#preventing the same keyword showing up twice.
Else If [ reference::kkeywordPrimary ≠ $tag ]
Set Field [ reference::kkeywordPrimary; $tag ]
Set Field [ reference::kkeywordOther; //last item in list has no paragraph mark, so a valuecount test needs to be done
and if item is not removed, then the removal calc without the paragraph mark is used
If ( ValueCount ( $$key ) ≠ ValueCount ( Substitute ( $$key ; $$citationItem & "¶" ; "" ) ) ;
Substitute ( $$key ; $$citationItem & "¶" ; "" ) ;
Substitute ( $$key ; $$citationItem ; "" )
) ]
Set Variable [ $$key; Value:reference::kkeywordOther ]
Set Variable [ $$PrimaryKey; Value:reference::kkeywordPrimary ]
Set Variable [ $$skipFirstPartOfScript; Value:1 ]
#
#Record must be committed if user decides to
#perform a script on it right after this one or
#perform a find requiring the newly added key.
Commit Records/Requests
Perform Script [ “addORremoveOtherTagStep2_keyword (update name
addORremoveTagFromCitationStep2keyword)” ]
Exit Script [ ]
End If
#
End If
#
#Record must be committed if user decides to
#perform a script on it right after this one or
#perform a find requiring the newly added key.
Commit Records/Requests
#
#Refresh the windows so changed conditional formatting
#will show up.
Refresh Window
#
Set Variable [ $$stoploadCitation ]
End If
#
#Only need to re-sort if primary key was
#changed or primary author in reference mode.
If [ $$primaryKeyWord ≠ reference::kkeywordPrimary and
$$citationMatch = "key" and
$$stopAdd = "" and
$$referenceSort = "" and
Left ( Get ( LayoutName ) ; 1 ) ≠ "l" ]
Set Variable [ $$primaryKeyWord ]
Show Custom Dialog [ Message: "Record will now move to new keyword location. Scroll window to this location?"; Default
Button: “no”, Commit: “Yes”; Button 2: “yes”, Commit: “No” ]
If [ Get (LastMessageChoice) = 2 ]
Go to Layout [ “ReferenceStuffScriptLoops” (reference) ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagKeywordPrimary::orderOrLock; based on value list:
“order Pulldown List”
tagKeywordPrimary::tag; ascending
reference::referenceForReferenceWindow; ascending ]
[ Restore; No dialog ]
#
#Go to reference record layout.
If [ TEMP::InventoryLibraryYN ≠ "" ]
Go to Layout [ “ReferenceStuff” (reference) ]
Else
Go to Layout [ “Reference” (reference) ]
End If
End If
Else If [ $$citationMatch = "node" and $$referenceSort = ""
or
$$citationMatch = "node" and $$referenceSort = "author" ]
Sort Records [ ]
[ No dialog ]
End If
#
#
#
#END — REFERENCE WINDOW
#
#
#
#Return tag window and refresh to show newly
#added or removed tag selection.
Select Window [ Name: "Tag Menus"; Current file ]
Go to Record/Request/Page [ $recordNumber ]
[ No dialog ]
#
#Check if any Learn records are tagged with a
#test item (if currently in test mode), or a
#brainstorm item (if in brainstorm mode) and sort
#by order and then date and time.
If [ $$citationMatch = "test" ]
Perform Script [ “loadTestTags (update and name change from loadItemRecordForTestTagMenu)” ]
Else If [ $$citationMatch = "brainstorm" ]
Perform Script [ “loadBrainstormTags (update name change loadItemRecordForSampleTagMenu)” ]
End If
Select Window [ Name: "Tag Menus"; Current file ]
Refresh Window
#
