tagMenu: addTagToMainRecord
#
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
// #Due to the fact that users click the add tag button
// #when they want to find records tagged with a tag,
// #I'm making it so that users can only add tags in edit mode.
// If [ Left (Get (LayoutName) ; 3 ) = "ref" and $$stopAdd ≠ 1 ]
// Show Custom Dialog [ Message: "Click the edit button in the References window (but not in Learn window) to add/change tags. This inconvience was put in place because users kept forgetting to click find before click the P or O buttons."; Buttons: “OK” ]
// Exit Script [ ]
// End If
#
// #Because I keep forgetting to press find mode, this
// #bit of script is to confirm that the user really wants
// #to add or change the tag of the first record instead of
// #finding records with selected tag.
// If [ $$referenceRecordOne = 1 ]
// Show Custom Dialog [ Message: "Did you mean to ADD this tag to the first record or FIND reference records with this tag?"; Buttons: “ADD”, “FIND”, “Cancel” ]
// If [ Get ( LastMessageChoice ) = 2 ]
// #This variable is needed becasue message choice 2
// #gets carried over to the Find Mode Script, which then
// #activates tag instead of reference record find mode.
// Set Variable [ $$ClearMessageChoice; Value:1 ]
// Perform Script [ “FindMode” ]
// Else If [ Get ( LastMessageChoice ) = 3 ]
// Set Variable [ $$referenceRecordOne ]
// Exit Script [ ]
// Else If [ Get ( LastMessageChoice ) = 1 ]
// Set Variable [ $$referenceRecordOne ]
// End If
// End If
#
#
#This script adds tags to main reference or learn
#primary tag fields, and a chunk of it adds section
#keys found in the learn or reference record to
#the keyword or node tag group of the tag just
#added, to insure that this tag shows up in every
#section in which the record it tagged shows up.
#There may be sections where this keyword or
#node tag shows up, and this newly tagged
#reference or learn record does not, which is OK.
#Reference and learn records do not require all
#the section keys the added tag has.
#
#NOTE: Most of these tags except keyword and node
#tags are universal, and so there are no section keys
#to add to them. In the case of sample and test
#tags, because these tags are section specific, there
#is no reason to add keys from other sections to
#them.
#
If [ $$stopAddTagToCitation = 1 ]
Exit Script [ ]
End If
#
#Stop script if user is looking at item/detail tags
#in add mode, as these tags cannot be applied
#to reference records.
If [ $$add = 1 and $$citationMatch = "testSetup" ]
Show Custom Dialog [ Message: "You cannot tag reference records with item tags. So why then are there buttons? The buttons show up because I have not made time to create a separate layout just for item tags. This issue has been logged as a minor irritation."; Buttons: “OK” ]
Exit Script [ ]
End If
#
// #Stop script if user trying to add reference or learn record
// #that has references or citations added to it.
// #In the future this will be possible, but for now I need
// #to focus on other things to get the beta released.
// If [ reference::_Lreference ≠ $$cite ]
// If [ testlearn::kcitation ≠ "" or testlearn::kcreference ≠ "" or reference::kcitation ≠ "" ]
// Show Custom Dialog [ Message: "For now, you cannot use a record that has its own citation or references added to it as a citation or reference for another record. This is a known issue, and in a future release it will be resolved. "; Buttons: “OK” ]
// Exit Script [ ]
// End If
// End If
#
#
#
#If reference or learn record that tag was added
#to belongs to more than one section, then
#add these other sections to the tag's group
#keychain so when this tag record is viewed in
#those sections, the reference or learn record
#just added to it will show up as well.
If [ Get ( LayoutTableName ) = "testlearn" or Get ( LayoutTableName ) = "reference" ]
Perform Script [ “CHUNKaddMainRecordSectionKeysToCiteOrRefSectionKeychain” ]
#
#Check main checkbox if record is not already
#a main record. This is because when going to
#edit cite or reference records, only main records
#are shown by default.
If [ "main" & ¶ ≠ FilterValues ( testlearn::filterFind ; "main" & ¶ ) and Get ( LayoutTableName ) = "testlearn" ]
Set Variable [ $filterFind; Value:testlearn::filterFind ]
Set Field [ testlearn::filterFind; "main" & ¶ & $filterFind ]
Else If [ "main" & ¶ ≠ FilterValues ( reference::filterFind ; "main" & ¶ ) and Get ( LayoutTableName ) = "reference" ]
Set Variable [ $filterFind; Value:reference::filterFind ]
Set Field [ reference::filterFind; "main" & ¶ & $filterFind ]
End If
#
Else If [ 1 = 1 ]
Perform Script [ “CHUNKaddMainSectionKeysToTagRecordKeychain” ]
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
Set Variable [ $tag; Value:test::_Ltest ]
Set Variable [ $tagName; Value:ruleSection::name ]
Else If [ Right ( Get (LayoutName) ; 5 ) = "3cite" ]
Set Variable [ $tag; Value:reference::_Lreference ]
Else If [ Right ( Get (LayoutName) ; 7 ) = "refcite" ]
January 7, 平成26 16:21:34 Imagination Quality Management.fp7 - addTagToMainRecord -1-tagMenu: addTagToMainRecord
Set Variable [ $tag; Value:testlearn::_Ltestlearn ]
Else If [ Right ( Get (LayoutName) ; 8 ) = "sections" ]
Set Variable [ $tag; Value:ruleSection::_Lgroup ]
Set Variable [ $tagName; Value:ruleSection::name ]
#
#Stop check spelling script as this script is triggered
#on section layout by record load trigger, and
#so before user can change the spelling.
Set Variable [ $$stopChangeSectionName; Value:1 ]
Else If [ Right ( Get (LayoutName) ; 4 ) ≠ "cite" ]
Set Variable [ $tag; Value:tagMenus::_Ltag ]
Set Variable [ $lock; Value:tagMenus::orderOrLock ]
End If
#
#Remove focus from field so can see
#conditional formatting.
Go to Field [ ]
#
#If removing a discovery record, the database
#will jump to the next records tag menu selection.
#So to keep the users focus on the tag they orginally
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
Set Variable [ $citeHealth; Value:reference::kHealth ]
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
Set Variable [ $citeHealth; Value:testlearn::kHealth ]
Set Variable [ $citeCopyrightDate; Value:testlearn::copyrightYear ]
Set Variable [ $citekeywordOther; Value:testlearn::kcKeywordOther ]
Set Variable [ $citekeywordOtherWords; Value:testlearn::OtherKeyWords ]
Set Variable [ $citekeywordPrimary; Value:testlearn::kKeywordPrimary ]
End If
#
// New Window [ Name: "Add Tag" ]
#
#Select reference, learn, or setup window.
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Setup"; Current file ]
#
#Check which tag user is looking at and then...
If [ $$citationMatch = "node" ]
#
#If primary node is in use, then remove it.
If [ tempSetup::kdefaultNodePrimary = $tag ]
Set Field [ tempSetup::kdefaultNodePrimary; "" ]
Set Field [ tempSetup::DEFAULTNodePrimaryName; "" ]
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
Set Field [ tempSetup::nodeLock; $lock ]
Set Field [ tempSetup::DEFAULTNodePrimaryName; tagDefaultNodePrimary::tag ]
Set Variable [ $$node; Value:tempSetup::kdefaultNodeOther ]
Set Field [ tempSetup::kdefaultNodeOther; //last item in list has no paragraph mark, so a valuecount test needs to be done and if item is not removed, then the removal calc without the paragraph mark is used
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
Perform Script [ “addORremoveTagFromCitationStep2node” ]
Close Window [ Name: "reorder"; Current file ]
Exit Script [ ]
End If
#
Else If [ $$citationMatch = "health" ]
If [ tempSetup::kdefaultHealth = $tag ]
Set Field [ tempSetup::kdefaultHealth; "" ]
Set Variable [ $$citationItem ]
Set Variable [ $$health ]
Refresh Window
#
#goto Tag Menus window
Select Window [ Name: "Tag Menus"; Current file ]
Refresh Window
Exit Script [ ]
Else If [ testlearn::kHealth ≠ $tag ]
Set Variable [ $$health; Value:tempSetup::kdefaultHealth ]
Set Field [ tempSetup::kdefaultHealth; $tag ]
Refresh Window
#
January 7, 平成26 16:21:34 Imagination Quality Management.fp7 - addTagToMainRecord -2-tagMenu: addTagToMainRecord
#goto Tag Menus window
Select Window [ Name: "Tag Menus"; Current file ]
Refresh Window
Exit Script [ ]
End If
#
#Since sections are required, the deselect script
#steps are not needed. When the user clicks on
#a new record on the section layout this script
#is triggered and that section set as the default
#section.
Else If [ $$citationMatch = "section" ]
Set Field [ tempSetup::ksection; $tag ]
Set Field [ tempSetup::sectionName; $tagName ]
Refresh Window
#
#goto Tag Menus window
Select Window [ Name: "Tag Menus"; Current file ]
Refresh Window
#
#Allow duplicate tag check script to operate.
Set Variable [ $$stopChangeSectionName ]
Exit Script [ ]
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
#
#
#
#
#
Else If [ Get (LastError) ≠ 112 ]
#
#
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
Set Field [ testlearn::kNodeOther; //last item in list has no paragraph mark, so a valuecount test needs to be done and if item is not removed, then the removal calc without the paragraph mark is used
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
Perform Script [ “addORremoveTagFromCitationStep2node” ]
Close Window [ Name: "reorder"; Current file ]
Exit Script [ ]
End If
#
Else If [ $$citationMatch = "medium" ]
If [ testlearn::kmedium = $tag ]
Set Field [ testlearn::kmedium; "" ]
Set Variable [ $$citationItem ]
Set Variable [ $$medium ]
Else If [ testlearn::kmedium ≠ $tag ]
Set Field [ testlearn::kmedium; $tag ]
Set Variable [ $$medium; Value:$tag ]
End If
#
Else If [ $$citationMatch = "ref" ]
If [ testlearn::kcreference= $tag ]
Set Field [ testlearn::kcreference; "" ]
Set Variable [ $$citationItem ]
Set Variable [ $$ref ]
Else If [ testlearn::kcreference ≠ $tag ]
Set Field [ testlearn::kcreference; $tag ]
Set Variable [ $$ref; Value:testlearn::kcreference ]
Perform Script [ “CHUNKaddReferenceNodesAndKeywords” ]
End If
#
Else If [ $$citationMatch = "health" ]
If [ testlearn::kHealth = $tag ]
Set Field [ testlearn::kHealth; "" ]
Set Variable [ $$citationItem ]
Set Variable [ $$health ]
Else If [ testlearn::kHealth ≠ $tag ]
Set Field [ testlearn::kHealth; $tag ]
Set Variable [ $$health; Value:testlearn::kHealth ]
End If
#
Else If [ $$citationMatch = "path" ]
If [ testlearn::kfolderPath = $tag ]
Set Field [ testlearn::kfolderPath; "" ]
January 7, 平成26 16:21:34 Imagination Quality Management.fp7 - addTagToMainRecord -3-tagMenu: addTagToMainRecord
Set Variable [ $$citationItem ]
Set Variable [ $$Path ]
Else If [ testlearn::kfolderPath ≠ $tag ]
Set Field [ testlearn::kfolderPath; $tag ]
Set Variable [ $$Path; Value:testlearn::kfolderPath ]
End If
#
Else If [ $$citationMatch = "cite" ]
If [ Case ( $tableName = "testLearn" ; testlearn::kcitation = $tag & "L" ; testlearn::kcitation = $tag ) ]
Set Field [ testlearn::kcitation; "" ]
#
// #Ask user if OK to remove keywords.
// Show Custom Dialog [ Message: "Use the citation record's keywords? (This will replace this records keywords if there are any.)"; Buttons: “cancel”, “OK” ]
// If [ Get ( LastMessageChoice ) = 2 ]
// End If
// Set Field [ testlearn::kHealth; "" ]
// Set Field [ testlearn::copyrightYear; "" ]
// Set Field [ testlearn::kKeywordPrimary; "" ]
// Set Field [ testlearn::kcKeywordOther; "" ]
// Set Field [ testlearn::OtherKeyWords; "" ]
// #
// Set Field [ testlearn::filename; "" ]
// Set Field [ testlearn::kfileLocation; "" ]
// Set Field [ testlearn::kfolderPath; "" ]
// Set Field [ testlearn::kmedium; "" ]
// Set Field [ testlearn::URL; "" ]
// Set Field [ testlearn::URLPubDate; "" ]
#
Set Variable [ $$citationItem ]
Set Variable [ $$cite ]
// Set Variable [ $citeHealth ]
// Set Variable [ $citeCopyrightYear ]
// Set Variable [ $citekeywordOther ]
// Set Variable [ $citekeywordOtherWords ]
// Set Variable [ $citekeywordPrimary ]
#The 'L' allows system to learn and reference records apart.
Else If [ testlearn::kcitation & "L" ≠ $tag ]
Set Field [ testlearn::kcitation; Case ( $tableName = "testLearn" ; $tag & "L" ; $tag ) ]
Set Variable [ $$cite; Value:Case ( $tableName = "testLearn" ; $tag & "L" ; $tag ) ]
Refresh Window
#
#Ask user if OK to replace keywords.
Select Window [ Name: "Tag Menus"; Current file ]
Show Custom Dialog [ Message: "Use citation record's keywords: " &
//KEYWORDS
Case ( tagKeywordPrimary::tag = "" ; "" ; tagKeywordPrimary::tag ; Bold & ", " ) &
reference::OtherKeyWords &
"? (This will replace keywords for this record, if there are any.)"; Buttons: “no”, “yes” ]
Select Window [ Name: "Learn"; Current file ]
If [ Get ( LastMessageChoice ) = 2 ]
Set Field [ testlearn::kKeywordPrimary; $citekeywordPrimary ]
Set Field [ testlearn::kcKeywordOther; $citekeywordOther ]
Set Field [ testlearn::OtherKeyWords; $citekeywordOtherWords ]
End If
#
#Health should blank and take copyright of cited record.
Set Field [ testlearn::kHealth; "" ]
#
#Decided that user needs to go to tag window to get
#link info, because if changed, it will not change here
#because these items not linked to citation record.
// Set Field [ testlearn::copyrightYear; $citeCopyrightDate ]
// Set Field [ testlearn::filename; $filename ]
// Set Field [ testlearn::kfileLocation; $fileLocation ]
// Set Field [ testlearn::kfolderPath; $folderpath ]
// Set Field [ testlearn::kmedium; $medium ]
// Set Field [ testlearn::URL; $URL ]
// Set Field [ testlearn::URLPubDate; $URLdate ]
Select Window [ Name: "Tag Menus"; Current file ]
Perform Script [ “CHUNKaddReferenceNodesAndKeywords” ]
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
Set Field [ testlearn::kcKeywordOther; //last item in list has no paragraph mark, so a valuecount test needs to be done and if item is not removed, then the removal calc without the paragraph mark is used
If ( ValueCount ( $$key ) ≠ ValueCount ( Substitute ( $$key ; $$citationItem & "¶" ; "" ) ) ;
Substitute ( $$key ; $$citationItem & "¶" ; "" ) ;
Substitute ( $$key ; $$citationItem ; "" )
) ]
Set Variable [ $$key; Value:testlearn::kcKeywordOther ]
Set Variable [ $$skipFirstPartOfScript; Value:1 ]
#
#Record must be committed if user decides to
#perform a script on it right after this one or
#perform a find requiring the newly added key.
Commit Records/Requests
Perform Script [ “addORremoveTagFromCitationStep2keyword” ]
Exit Script [ ]
End If
#
Else If [ $$citationMatch = "test" ]
#
#
#If test item is in use, then remove it.
#
#But first determine if it is a discovery record.
#Because discovery records are created in the
#test module, and then end up here via the
#info check box on the discovery tag menu, these
#records only reason for showing up here in the
#learn module is because of this link. Once
#the user clears this link, the record will be omitted
#and so to not surprise the user with this omission,
January 7, 平成26 16:21:34 Imagination Quality Management.fp7 - addTagToMainRecord -4-tagMenu: addTagToMainRecord
#a warning is given to both inform and allow
#the user to cancel clearing this link.
If [ testlearn::ktest ≠ "" and GetValue ( testlearn::kctest ; 2 ) = "" ]
Show Custom Dialog [ Message: "This discovery record will be removed from this section of your database: learn section. It will still be available in the " & TEMP::sectionName & " test section as a discovery record for " & TEMP::testName & ", report " & testlearn::
kreportNumber & "."; Buttons: “OK”, “Cancel” ]
If [ Get ( LastMessageChoice ) = 2 ]
Select Window [ Name: "Tag Menus"; Current file ]
Refresh Window
Exit Script [ ]
End If
End If
Set Variable [ $number; Value:1 ]
Loop
If [ FilterValues ( Middle ( GetValue ( testlearn::kctest ; $number ) ; 4 ; 42 ) ; $tag & "¶" ) = $tag & ¶ ]
Set Field [ testlearn::kctest; Substitute ( $$test ; GetValue ( testlearn::kctest ; $number ) & "¶" ; "" ) ]
Set Field [ testlearn::orderTest; "" ]
#
#If as discussed above this is a discovery record,
#clear the filterfind field to prevent it from being
#part of the learn record set and then omit it.
If [ testlearn::ktest ≠ "" and testlearn::kctest = "" ]
Set Field [ testlearn::filterFind; "" ]
Omit Record
End If
Set Variable [ $$test; Value:testlearn::kctest ]
Set Variable [ $$citationItem ]
Set Variable [ $number; Value:"exit" ]
End If
Exit Loop If [ GetValue ( testlearn::kctest ; $number ) = "" ]
Exit Loop If [ $number = "" ]
Set Variable [ $add; Value:$number ]
Set Variable [ $number; Value:$add + 1 ]
End Loop
#
#If test item is not in use add it.
If [ $number ≠ "exit" ]
Set Variable [ $number; Value:1 ]
Loop
If [ FilterValues ( Middle ( GetValue ( testlearn::kctest ; $number ) ; 4 ; 42 ) ; $$test & "¶" ) ≠ $tag & ¶ ]
Set Field [ testlearn::kctest; "100" & $tag & ¶ & $$test ]
Set Field [ testlearn::orderTest; "100" ]
Set Variable [ $$test; Value:testlearn::kctest ]
Set Variable [ $number ]
#
#Record must be committed if user decides to
#perform a script on it right after this one or
#perform a find requiring the newly added key.
Commit Records/Requests
End If
Exit Loop If [ FilterValues ( Middle ( GetValue ( testlearn::kctest ; $number ) ; 4 ; 42 ) ; $$test & "¶" ) = "" ]
Exit Loop If [ $number = "" ]
Set Variable [ $add; Value:$number ]
Set Variable [ $number; Value:$add + 1 ]
End Loop
#
#If the system is currently sorting test records
#by order number, then give this newly tagged
#record the number 100, and then sort it the records
#so that it shows up as part of the current tag's
#record set.
Set Field [ testlearn::orderTest; "100" ]
Set Field [ TEMP::TLTestSort; "order" ]
Perform Script [ “SortTLRecordsByOrderNumber” ]
End If
#
Else If [ $$citationMatch = "sample" ]
#
#If sample item is in use, then remove it.
Set Variable [ $number; Value:1 ]
Loop
If [ FilterValues ( Middle ( GetValue ( testlearn::kcsample ; $number ) ; 4 ; 42 ) ; $tag & "¶" ) = $tag & ¶ ]
Set Field [ testlearn::kcsample; Substitute ( $$sample ; GetValue ( testlearn::kcsample ; $number ) & "¶" ; "" ) ]
Set Field [ testlearn::orderTest; "" ]
Set Variable [ $$sample; Value:testlearn::kcsample ]
Set Variable [ $$citationItem ]
Set Variable [ $number; Value:"exit" ]
End If
Exit Loop If [ GetValue ( testlearn::kcsample ; $number ) = "" ]
Exit Loop If [ $number = "" ]
Set Variable [ $add; Value:$number ]
Set Variable [ $number; Value:$add + 1 ]
End Loop
#
If [ $number ≠ "exit" ]
Set Variable [ $number; Value:1 ]
Loop
#If sample item is not in use add it.
If [ FilterValues ( Middle ( GetValue ( testlearn::kcsample ; $number ) ; 4 ; 42 ) ; $tagS & "¶" ) ≠ $tag & ¶ ]
// Set Variable [ $$sample; Value:testlearn::kcsample ]
Set Field [ testlearn::kcsample; "100" & $tag & ¶ & $$sample ]
// Set Field [ testlearn::orderTest; "100" ]
Set Variable [ $$sample; Value:testlearn::kcsample ]
Set Variable [ $number ]
#
#Record must be committed if user decides to
#perform a script on it right after this one or
#perform a find requiring the newly added key.
Commit Records/Requests
End If
Exit Loop If [ FilterValues ( Middle ( GetValue ( testlearn::kcsample ; $number ) ; 4 ; 42 ) ; $tagS & "¶" ) = "" ]
Exit Loop If [ $number = "" ]
Set Variable [ $add; Value:$number ]
Set Variable [ $number; Value:$add + 1 ]
End Loop
#
#If the system is currently sorting test records
#by order number, then give this newly tagged
#record the number 100, and then sort it the records
#so that it shows up as part of the current tag's
#record set.
Set Field [ testlearn::orderTest; "100" ]
Set Field [ TEMP::TLTestSort; "order" ]
Perform Script [ “SortTLRecordsByOrderNumber” ]
End If
End If
#
#Record must be committed if user decides to
January 7, 平成26 16:21:34 Imagination Quality Management.fp7 - addTagToMainRecord -5-tagMenu: addTagToMainRecord
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
#
#
#
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
#Get the keys currently unlocking who is a
#copyright holder.
Set Variable [ $keyChain; Value:reference::kcopyrightHolder ]
#
#Remove key from keychain if it is on
#the copyright holder keychain.
If [ reference::knodeOther = "" and reference::knodePrimary = "" ]
Set Field [ reference::kcopyrightHolder; Substitute ( $keyChain ; "node738fds8ef" & "¶" ; "" ) ]
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
Set Field [ reference::knodeOther; //last item in list has no paragraph mark, so a valuecount test needs to be done and if item is not removed, then the removal calc without the paragraph mark is used
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
Perform Script [ “addORremoveTagFromCitationStep2node” ]
Close Window [ Name: "reorder"; Current file ]
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
Else If [ $$citationMatch = "health" ]
If [ reference::kHealth = $tag ]
Set Field [ reference::kHealth; "" ]
Set Variable [ $$citationItem ]
Set Variable [ $$health ]
Else If [ reference::kHealth ≠ $tag ]
Set Field [ reference::kHealth; $tag ]
Set Variable [ $$health; Value:reference::kHealth ]
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
Perform Script [ “CHUNKaddReferenceNodesAndKeywords” ]
End If
#
Else If [ $$citationMatch = "organ" ]
If [ reference::korgan = $tag ]
Set Field [ reference::korgan; "" ]
#
#Get the keys currently unlocking
#copyright holder.
Set Variable [ $keyChain; Value:reference::kcopyrightHolder ]
#
#Remove key from keychain if it is on
#the copyright holder keychain.
Set Field [ reference::kcopyrightHolder; Substitute ( $keyChain ; $$citationItem & "¶" ; "" ) ]
#Finish removing the key.
Set Variable [ $$citationItem ]
Set Variable [ $$organ ]
#
Else If [ reference::korgan ≠ $tag ]
#
#Get the keys currently unlocking
#copyright holder if on the chain.
January 7, 平成26 16:21:34 Imagination Quality Management.fp7 - addTagToMainRecord -6-tagMenu: addTagToMainRecord
Set Variable [ $oldCopyrightKey; Value:reference::korgan ]
If [ FilterValues ( reference::kcopyrightHolder ; $oldCopyrightKey & ¶ ) = $oldCopyrightKey & ¶ ]
Set Variable [ $keyChain; Value:reference::kcopyrightHolder ]
#
#Remove old key from keychain if it is on
#the copyright holder keychain.
Set Field [ reference::kcopyrightHolder; Substitute ( $keyChain ; $oldCopyrightKey & "¶" ; "" ) ]
#
#Add new key to copyright keychain.
Set Variable [ $keyChain; Value:reference::kcopyrightHolder ]
Set Field [ reference::kcopyrightHolder; $tag & "¶" & $keyChain ]
End If
Set Field [ reference::korgan; $tag ]
Set Variable [ $$organ; Value:reference::korgan ]
End If
#
Else If [ $$citationMatch = "copyist" ]
If [ reference::kcopyist = $tag ]
Set Field [ reference::kcopyist; "" ]
#
#Get the keys currently unlocking
#copyright holder.
Set Variable [ $keyChain; Value:reference::kcopyrightHolder ]
#
#Remove key from keychain if it is on
#the copyright holder keychain.
Set Field [ reference::kcopyrightHolder; Substitute ( $keyChain ; $$citationItem & "¶" ; "" ) ]
#Finish removing the key.
Set Variable [ $$citationItem ]
Set Variable [ $$copyist ]
#
Else If [ reference::kcopyist ≠ $tag ]
#
#Get the keys currently unlocking
#copyright holder if on the chain.
Set Variable [ $oldCopyrightKey; Value:reference::kcopyist ]
If [ FilterValues ( reference::kcopyrightHolder ; $oldCopyrightKey & ¶ ) = $oldCopyrightKey & ¶ ]
Set Variable [ $keyChain; Value:reference::kcopyrightHolder ]
#
#Remove old key from keychain if it is on
#the copyright holder keychain.
Set Field [ reference::kcopyrightHolder; Substitute ( $keyChain ; $oldCopyrightKey & "¶" ; "" ) ]
#
#Add new key to copyright keychain.
Set Variable [ $keyChain; Value:reference::kcopyrightHolder ]
Set Field [ reference::kcopyrightHolder; $tag & "¶" & $keyChain ]
End If
#
Set Field [ reference::kcopyist; $tag ]
Set Variable [ $$copyist; Value:reference::kcopyist ]
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
Set Field [ reference::kkeywordOther; //last item in list has no paragraph mark, so a valuecount test needs to be done and if item is not removed, then the removal calc without the paragraph mark is used
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
Perform Script [ “addORremoveTagFromCitationStep2keyword” ]
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
#Since references can only be tagged in edit mode
#this next part of the script is not needed, and actually
#causes problems.
// #Take user to where record sorts to.
// #will show up.
// Set Variable [ $$stoploadCitation; Value:1 ]
// Set Variable [ $record; Value:reference::_Lreference ]
// If [ $$citationMatch = "node" ]
// Go to Record/Request/Page
[ First ]
// Sort Records [ ]
[ No dialog ]
January 7, 平成26 16:21:34 Imagination Quality Management.fp7 - addTagToMainRecord -7-tagMenu: addTagToMainRecord
// Loop
// Exit Loop If [ reference::_Lreference = $record ]
// Go to Record/Request/Page
[ Next; Exit after last ]
// End Loop
// Else If [ $$citationMatch = "medium" ]
// Go to Record/Request/Page
[ First ]
// Sort Records [ ]
[ No dialog ]
// Loop
// Exit Loop If [ reference::_Lreference = $record ]
// Go to Record/Request/Page
[ Next; Exit after last ]
// End Loop
// Else If [ $$citationMatch = "Path" ]
// Go to Record/Request/Page
[ First ]
// Sort Records [ ]
[ No dialog ]
// Loop
// Exit Loop If [ reference::_Lreference = $record ]
// Go to Record/Request/Page
[ Next; Exit after last ]
// End Loop
// Else If [ $$citationMatch = "key" ]
// Go to Record/Request/Page
[ First ]
// Sort Records [ ]
[ No dialog ]
// Loop
// Exit Loop If [ reference::_Lreference = $record ]
// Go to Record/Request/Page
[ Next; Exit after last ]
// End Loop
// End If
Set Variable [ $$stoploadCitation ]
End If
Select Window [ Name: "Tag Menus"; Current file ]
Go to Record/Request/Page [ $recordNumber ]
[ No dialog ]
#
#Check if any Learn records are tagged with this
#test item (if currently in test mode), and if
#not then sort Learn records by date.
If [ $$citationMatch = "test" and
(FilterValues ( Middle ( GetValue ( $$test ; 1 ) ; 4 ; 42 ) ; test::_Ltest & "¶" ) = test::_Ltest & ¶
 or
FilterValues ( Middle ( GetValue ( $$test ; 2 ) ; 4 ; 42 ) ; test::_Ltest & "¶" ) = test::_Ltest & ¶
 or
FilterValues ( Middle ( GetValue ( $$test ; 3 ) ; 4 ; 42 ) ; test::_Ltest & "¶" ) = test::_Ltest & ¶
 or
FilterValues ( Middle ( GetValue ( $$test ; 4 ) ; 4 ; 42 ) ; test::_Ltest & "¶" ) = test::_Ltest & ¶
 or
FilterValues ( Middle ( GetValue ( $$test ; 5 ) ; 4 ; 42 ) ; test::_Ltest & "¶" ) = test::_Ltest & ¶
 or
FilterValues ( Middle ( GetValue ( $$test ; 6 ) ; 4 ; 42 ) ; test::_Ltest & "¶" ) = test::_Ltest & ¶
 or
FilterValues ( Middle ( GetValue ( $$test ; 7 ) ; 4 ; 42 ) ; test::_Ltest & "¶" ) = test::_Ltest & ¶
 or
FilterValues ( Middle ( GetValue ( $$test ; 8 ) ; 4 ; 42 ) ; test::_Ltest & "¶" ) = test::_Ltest & ¶
 or
FilterValues ( Middle ( GetValue ( $$test ; 9 ) ; 4 ; 42 ) ; test::_Ltest & "¶" ) = test::_Ltest & ¶
 or
FilterValues ( Middle ( GetValue ( $$test ; 10 ) ; 4 ; 42 ) ; test::_Ltest & "¶" ) = test::_Ltest & ¶ )
 = 0 ]
Perform Script [ “loadItemRecordForTestTagMenu” ]
End If
Select Window [ Name: "Tag Menus"; Current file ]
Refresh Window
January 7, 平成26 16:21:34 Imagination Quality Management.fp7 - addTagToMainRecord -8-
