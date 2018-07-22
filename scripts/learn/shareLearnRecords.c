July 20, 2018 17:23:14 Library.fmp12 - shareLearnRecords -1-
learn: shareLearnRecords
#
#
#
#If in find mode, exit script.
If [ $$findMode ≠ "" ]
Show Custom Dialog [ Message: "Currently in find mode. Click done in the tag menus window to exit find mode, and then click
this button."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
#
#
#
#BEGIN: SHARE DOCUMENT CREATION
# PART 1 >> Admin
# PART 2 >> Find Records
# PART 3 >> What about references?
# PART 4 >> Build shared document
# PART 5 >> Display share document
# PART 6 >> Report any issues
#
#
#
#
#
#PART 1 >> Admin ————————————
#
#
#
#
#
#Admin tasks.
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
#Close Share and Sbare windows, as they may
#be open from the last time the user clicked the
#share button.
Close Window [ Name: "Share"; Current file ]
#Yup, the window is named "Sbare."
Close Window [ Name: "Sbare"; Current file ]
#See explenation below.
#
Set Variable [ $$stopLoadCitation; Value:1 ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
#
#
#Open a new window to find learn records in.
#(For testing, enable the window that is
#not out of sight.)
// New Window [ Name: "Share"; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”; Resize:
“Yes” ]
New Window [ Name: "Share"; Height: 1; Width: 1; Top: 10000; Left: 10000; Style: Document; Close: “Yes”; Minimize: “Yes”;
Maximize: “Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
Go to Layout [ “learnPreviewLayout” (testlearn) ]
#
#
#
#
#
#PART 2 >> Find Records ——————————
#
#
#
#
#
#BEGIN Find brainstorm or test tagged records
#
#If the Tag Menus window is showing the brainstorm
#or inventory menu when the use clicked 'share'
#then find the records tagged with the currently
#selected brainstorm tag = $$brainstorm variable.
If [ $$citationMatch = "brainstorm"
or
$$citationMatch = "test" ]
#
#Find all brainstorm or inventory list records.
Enter Find Mode [ ]
#
#This keychain contain the item's three-digit
#order number followed by the key of the
#brainstorm or inventory list tag record.
If [ $$citationMatch = "brainstorm" ]
Set Field [ testlearn::kcbrainstorm; "***" & $$tagBrainstorm ]
Else If [ $$citationMatch = "test" ]
Set Field [ testlearn::kctestSubsectionInfo; "***" & $$tagTest ]
End If
Perform Find [ ]
If [ TEMP::InventoryLibraryYN = "" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearn::orderTestInformation; based on value list:
“testPulldownListANDsortOrderList”
testlearn::timestamp; descending ]
[ Restore; No dialog ]
Else
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearn::orderInventoryGroupNumber; ascending
testlearn::orderTestInformation; based on value list: “testPulldownListANDsortOrderList”
testlearn::note; ascending ]
[ Restore; No dialog ]
End If
#
#Stop the script if no records are found and
#tell the user why.
If [ Get (FoundCount) = 0 ]
Close Window [ Current Window ]
Select Window [ Name: "Tag Menus"; Current file ]
Set Variable [ $tagName; Value:tagMenus::tag ]
Select Window [ Name: "Learn"; Current file ]
If [ TEMP::InventoryLibraryYN = "" ]
Show Custom Dialog [ Message: "There are no Learn records tagged with — " & $tagName & " — in the Tag Menus
window. Only brainstorm tagged records can be shared when the brainstorm tag menu is active."; Default Button:
“OK”, Commit: “Yes” ]
Else
Show Custom Dialog [ Message: "When an inventory list tag is active in the Tag Menus window, clicking the share
button will show only records tagged with it. Zero records are tagged with " & $tagName & "."; Default Button: “OK”,
Commit: “Yes” ]
End If
#
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
#
Exit Script [ ]
End If
End If
#
#END Find brainstorm or test tagged records
#
#
#
#
#
#BEGIN Find and order non-brainstorm/test
#tagged records
#
#
#Select the Learn window as the background
#for the coming set of questions the user needs
#to answer. It is confusing if the user sees the
#title of learn window changed to 'share' when
#asked these questions.
Select Window [ Name: "Learn"; Current file ]
#
#BEGIN Find out which records to share?
#
If [ $$citationMatch ≠ "brainstorm"
and
$$citationMatch ≠ "test" ]
#
#Used for message below to let user know how
#many records are currently showing that they
#could share.
Set Variable [ $numberOfRecordsBeingViewed; Value:Get (FoundCount) ]
#
#If the current Learn record is linked to other
#Learn note records, do this.
If [ TEMP::InventoryLibraryYN = "" and Filter ( testlearn::kcreference ; "L" ) ≠ ""
 or
TEMP::InventoryLibraryYN = "" and $$LinkedLearnRecords ≠ "" ]
#
#Ask user if they want to share just the linked
#records or share all records being viewed.
If [ TEMP::InventoryLibraryYN = "" ]
Show Custom Dialog [ Message: "Share only this note + " & Length ( Filter ( testlearn::kcreference ; "L" ) ) &
Case ( Length ( Filter ( testlearn::kcreference ; "L" ) ) = 1 ; " note" ; " notes" ) &
" linked to it?" & ¶ & "OR" & ¶ & "Share all notes being viewed? Now viewing " & Get (FoundCount) & ".", Default
Button: "note+" & Length ( Filter ( testlearn::kcreference ; "L" ) ), Commit: “Yes”; Button 2: “all”, Commit: “No”;
Button 3: “cancel”, Commit: “No” ]
End If
#
#Save the user's selection.
If [ Get (LastMessageChoice) = 1 ]
Set Variable [ $show; Value:"self and linked" ]
Else If [ Get (LastMessageChoice) = 2 ]
Set Variable [ $show; Value:"all" ]
End If
#
#Exit script if user clicks cancel.
If [ Get ( LastMessageChoice ) = 3 ]
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
Close Window [ Name: "Share"; Current file ]
Exit Script [ ]
End If
#
#
Else
#If the current Learn record is NOT linked to
#other Learn records, or if this is an inventory
#record do this.
#
#
#Ask user if they want to share the selected
#record, or share all records being viewed.
If [ Get (FoundCount) ≠ 1 ]
If [ TEMP::InventoryLibraryYN = "" ]
#Note record is for an idea.
Show Custom Dialog [ Message: "Share all notes or just this one? " & ¶ & "Now viewing " & Get (FoundCount) &
"."; Default Button: “all”, Commit: “Yes”; Button 2: “one”, Commit: “No”; Button 3: “cancel”, Commit: “No” ]
Else
#Inventory record is for an item.
Show Custom Dialog [ Message: "Share all inventory records being viewed or just this one? " & ¶ & "Now viewing
" & Get (FoundCount) & "."; Default Button: “all”, Commit: “Yes”; Button 2: “one”, Commit: “No”; Button 3:
“cancel”, Commit: “No” ]
End If
#
#Save the user's selection.
If [ Get (LastMessageChoice) = 1 ]
Set Variable [ $show; Value:"all" ]
Else If [ Get (LastMessageChoice) = 2 ]
Set Variable [ $show; Value:"self" ]
End If
#
#Exit script if user clicks cancel.
If [ Get ( LastMessageChoice ) = 3 ]
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
Close Window [ Name: "Share"; Current file ]
Exit Script [ ]
End If
End If
End If
#
#END Find out which records to share?
#
#
#
#BEGIN Ask how to order records being shared
#
If [ TEMP::InventoryLibraryYN = "" and $show ≠ "self" ]
Show Custom Dialog [ Message: "Order notes as seen in the Learn window (newest 1st), or order them in chronoligcal
order (oldest 1st)?"; Default Button: “newest 1st”, Commit: “Yes”; Button 2: “oldest 1st”, Commit: “No”; Button 3: “cancel”,
Commit: “No” ]
End If
#
If [ Get ( LastMessageChoice ) = 2 ]
Set Variable [ $chronologicalSortOrder; Value:1 ]
End If
#
If [ Get ( LastMessageChoice ) = 3 ]
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
Close Window [ Name: "Share"; Current file ]
Exit Script [ ]
End If
#
#END Ask how to order notes being shared
#
#
#
#BEGIN Help user stop share if it takes to long
#
#I commonly click the share button when I do not mean
#click it, so these next two question help the user
#stop this process if it was not intential. They also
#help the user understand that if they proceed how long
#it is likely to take, so they don't become frustrated.
If [ $show = "all" and Get ( FoundCount ) > 500 ]
If [ Get ( FoundCount ) > 999 ]
Show Custom Dialog [ Message: "FYI: It may take a minute or more to process this many records depending on each
record's references and your computer's speed. An old MacBook Pro takes just under 10 minutes to process about
4,000 records."; Default Button: “OK”, Commit: “Yes”; Button 2: “cancel”, Commit: “No” ]
#
Else If [ Get ( FoundCount ) > 500 ]
Show Custom Dialog [ Message: "FYI: It may take more than a minute to process this many records."; Default Button:
“OK”, Commit: “Yes”; Button 2: “cancel”, Commit: “No” ]
End If
#
If [ Get ( LastMessageChoice ) = 2 ]
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
Close Window [ Name: "Share"; Current file ]
Exit Script [ ]
End If
#
Install Menu Set [ “HGT Stop Share” ]
Show Custom Dialog [ Message: "If you get tired of waiting, just click on the 'Help' menu above and select 'Stop Share' to
stop the processing of your records."; Default Button: “OK”, Commit: “Yes” ]
End If
#
#END Help user stop share if it takes to long
#
#
#
#BEGIN Find records user wants to share
#
#Return to the share window.
Select Window [ Name: "Share"; Current file ]
#
#If user elected to show only selected record,
#then only find this record.
If [ $show = "self" ]
Enter Find Mode [ ]
Set Field [ testlearn::_Ltestlearn; $$main ]
Perform Find [ ]
End If
#
#If user elected to show the selected record
#and linked records, then find just these
#records and show them.
If [ $show = "self and linked" ]
#
#Find original record first.
Enter Find Mode [ ]
Set Field [ testlearn::_Ltestlearn; $$main ]
Perform Find [ ]
#
#Get the selected record's linked record IDs.
Set Variable [ $findLinkedLearnRecords; Value:testlearn::_Ltestlearn ]
Loop
Go to Object [ Object Name: "ref2" ]
Exit Loop If [ Get (LastError) = 101 ]
Set Variable [ $findLinkedLearnRecords; Value:refTestLearn::_Ltestlearn & ¶ & $findLinkedLearnRecords ]
Go to Portal Row
[ Select; Next; Exit after last ]
End Loop
#
#Determine how many IDs there are.
Set Variable [ $numberOfKeys; Value:ValueCount ($findLinkedLearnRecords ) ]
#
#Find the 1st ID'ed record.
Enter Find Mode [ ]
Set Field [ testlearn::_Ltestlearn; GetValue ( $findLinkedLearnRecords ; $numberOfKeys ) ]
Extend Found Set [ ]
Set Variable [ $numberOfKeys; Value:$numberOfKeys - 1 ]
#
#Loop thru set of IDs to until all linked records
#have been found.
Loop
#
#Exit the loop when there are no more IDs.
Exit Loop If [ $numberOfKeys = 0 ]
#
#Find next record.
Enter Find Mode [ ]
Set Field [ testlearn::_Ltestlearn; GetValue ( $findLinkedLearnRecords ; $numberOfKeys ) ]
Extend Found Set [ ]
#
#Go the next ID up from the bottom of the list
#of IDs.
Set Variable [ $numberOfKeys; Value:$numberOfKeys - 1 ]
End Loop
#
#Next find all records with links to the
#selected record.
If [ $$LinkedLearnRecords ≠ "" ]
#
Enter Find Mode [ ]
Set Field [ testlearn::kcreference; $$main ]
Extend Found Set [ ]
#
End If
End If
#
#END Find records user wants to share
#
#
#Put all found records in order.
If [ $chronologicalSortOrder = "" ]
If [ TEMP::InventoryLibraryYN = "" ]
#Sort in reverse chronological order.
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearn::date; descending
testlearn::timestamp; descending ]
[ Restore; No dialog ]
Else
#Sort by location and alphabetically by item.
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearn::orderInventoryGroupNumber; ascending
testlearn::note; ascending ]
[ Restore; No dialog ]
End If
Else
#Sort in chronological order.
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearn::date; ascending
testlearn::timestamp; ascending ]
[ Restore; No dialog ]
End If
#
#
End If
#
#END Find and order non-brainstorm/test
#tagged records
#
#
#
#
#
#PART 3 >> What about references? —————
#
#
#
#
#
#BEGIN Ask user what to do with references?
#
If [ TEMP::InventoryLibraryYN = "" and $show ≠ "self" ]
#
#Check if any of the records found have
#references that the user might want
#to display at the end of this share.
Go to Record/Request/Page
[ First ]
Loop
If [ ValueCount ( testlearn::kcreference ) - ( Length ( Filter ( testlearn::kcreference ; "L" ) ) ) > 0 ]
Set Variable [ $thereAreReferences; Value:1 ]
End If
Exit Loop If [ ValueCount ( testlearn::kcreference ) - ( Length ( Filter ( testlearn::kcreference ; "L" ) ) ) > 0 ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#If there are references, ask if the user would
#like to keep them with their notes or display
#them all at the end of the share.
If [ $thereAreReferences ≠ "" ]
Select Window [ Name: "Learn"; Current file ]
If [ $$citationMatch = "brainstorm" ]
Show Custom Dialog [ Message: "Keep brainstorm note references with each note, or put all references in a separate
reference section?"; Default Button: “section”, Commit: “Yes”; Button 2: “note”, Commit: “No”; Button 3: “cancel”,
Commit: “No” ]
Else
Show Custom Dialog [ Message: "Keep note references with each note, or put all references in a separate reference
section?"; Default Button: “section”, Commit: “Yes”; Button 2: “note”, Commit: “No”; Button 3: “cancel”, Commit:
“No” ]
End If
End If
#
#If the user decides to consolidate all notes'
#references to single reference section at
#the end, do the following:
If [ Get (LastMessageChoice) = 1 ]
#
#Note that the user wants an end
#reference section.
Set Variable [ $referencesInSectionAtEnd; Value:1 ]
#
#Ask them what else they might
#like removed from the note.
Show Custom Dialog [ Message: "Keep note numbering (#) and keywords, or just numbers, or remove all (essay format)?";
Default Button: “keepAll”, Commit: “Yes”; Button 2: “keep#”, Commit: “No”; Button 3: “removeAll”, Commit: “No” ]
If [ Get (LastMessageChoice) = 1 ]
#
#Would the to keep just the timestamp or
#only the keywords?
Show Custom Dialog [ Message: "Finally, keep timestamp and keywords, or only timestamp, or only keywords?";
Default Button: “keepBoth”, Commit: “Yes”; Button 2: “KeepTime”, Commit: “No”; Button 3: “keepKey”, Commit:
“No” ]
If [ Get (LastMessageChoice) = 1 ]
Else If [ Get (LastMessageChoice) = 2 ]
Set Variable [ $keepTimestamp; Value:1 ]
Else If [ Get (LastMessageChoice) = 3 ]
Set Variable [ $keepKeywords; Value:1 ]
End If
Else If [ Get (LastMessageChoice) = 2 ]
Set Variable [ $numberOnlyFormat; Value:1 ]
Else If [ Get (LastMessageChoice) = 3 ]
Set Variable [ $essayFormat; Value:1 ]
End If
#
#If the user wants to display them at the end,
#open a new window to gather all learn
#records' references.
New Window [ Name: "Sbare"; Height: 1; Width: 1; Top: 10000; Left: 10000; Style: Document; Close: “Yes”; Minimize: “Yes”;
Maximize: “Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
Go to Layout [ “shareReferencesLast” (TEMP) ]
#
#Show all temp records and
#then delete them to prepare this window for
#the references that will pasted into it below.
Show All Records
Delete All Records
[ No dialog ]
New Record/Request
Set Field [ TEMP::shareReferenceID; "firstRecord" ]
Commit Records/Requests
#
#If the user cancels the script then stop it, but
#do create 1 temporary record to display
#information that is in these fields, like
#the fields on the alldefaults layout.
Else If [ Get (LastMessageChoice) = 3 ]
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
Close Window [ Name: "Share"; Current file ]
Close Window [ Name: "Sbare"; Current file ]
Select Window [ Name: "Learn"; Current file ]
Exit Script [ ]
End If
#
End If
#
#END Ask user what to do with references?
#
#
#
#
#
#PART 4 >> Build shared document —————
#
#
#
#
#
#BEGIN Build note and reference sections
#
#
#Now build a formatted share document,
#numbering each record.
Select Window [ Name: "Share"; Current file ]
Set Variable [ $point; Value:1 ]
Set Variable [ $evidence; Value:1 ]
Go to Record/Request/Page
[ First ]
#
#BEGIN LOOP SECTION Build and format notes
#
Loop
#
If [ TEMP::InventoryLibraryYN = "" ]
#
#BEGIN Build and format idea notes
#
#Assemble the note, order number, author, and
#copyright (if different from default primary
#node), timestamp, and keyword fields.
#
#Show each note found and ...
Set Variable [ $recordReferenceCount; Value:ValueCount ( testlearn::kcreference ) - ( Length ( Filter ( testlearn::
kcreference ; "L" ) ) ) ]
If [ $essayFormat = "" and $numberOnlyFormat = "" ]
If [ $keepKeywords = "" and $keepTimestamp = "" and $referencesInSectionAtEnd = "" ]
#number, timestamp, keywords, references with note.
# (Idenitical to next else if. Was going to
# remove the grey R## from this "with notes"
# option, but for now seems to be useful.)
Set Variable [ $copy; Value://previous records
Case ( $copy = "" ; "" ; $copy & ¶ ) &
//number
TextSize (
Case ( testlearn::brainstormCasePoint = "" ; $point & "." & $evidence ;
$point & ".1" ) &
//R# for number of references
Case ( ValueCount ( testlearn::kcreference ) - ( Length ( Filter ( testlearn::kcreference ; "L" ) ) ) > 0 and
TEMP::InventoryLibraryYN = "" ; " " & TextColor ( ValueCount ( testlearn::kcreference ) - ( Length ( Filter
( testlearn::kcreference ; "L" ) ) ) & "R" ; RGB ( 154 ; 154 ; 154 ) ) ; "" ) ; 11 ) & ¶ &
//main text
TextFont ( testlearn::note ; "Georgia" ) & ¶ &
//grey text
TextColor ( "_______________" ; RGB ( 200 ; 200 ; 200 ) ) & ¶ &
TextSize ( TextColor (
 //node
 Case ( tagTLNodePrimary::_Ltag ≠ TEMP::kdefaultNodePrimary ;
 tagTLNodePrimary::tag &
 Case ( testlearn::NodeOthers = "" ;
 "" ; "; " & testlearn::NodeOthers ) ; "" ) &
 //copyright
 Case ( tagTLNodePrimary::_Ltag ≠ TEMP::kdefaultNodePrimary ;
 ". Copyright " & learnCreatorsCopyright::tag & ¶ ; "" ) &
 //timestamp
 testlearn::timestamp & ¶ &
 //keyword
 Case ( testlearn::OtherKeyWords ≠ "" or testlearn::kKeywordPrimary ≠ "" ;
 Case ( ValueCount ( testlearn::kcKeywordOther ) + ValueCount ( testlearn::kKeywordPrimary ) = 1 ;
 "keyword — " ; "keywords — " ) &
 //primary keyword
 tagTLKeywordPrimary::tag &
 Case ( testlearn::OtherKeyWords = "" ; "" ;
 //other keyword
 Case ( testlearn::kKeywordPrimary ≠ "" ; ", " & testlearn::OtherKeyWords ; testlearn::
OtherKeyWords ) ) ) &
 Case ( testlearn::OtherKeyWords ≠ "" or testlearn::kKeywordPrimary ≠ "" ;
 ¶ ; "" )
//finish text color
; RGB ( 119 ; 119 ; 119 ) ) ; 11 ) ]
Else If [ $keepKeywords = "" and $keepTimestamp = "" and $referencesInSectionAtEnd ≠ "" ]
#number, timestamp, keywords, references at end.
# (Idenitical to above if. Was going to remove
# the grey R## from the above "with notes"
# option, but for now seems to be useful.)
Set Variable [ $copy; Value://previous records
Case ( $copy = "" ; "" ; $copy & ¶ ) &
//number
TextSize (
Case ( testlearn::brainstormCasePoint = "" ; $point & "." & $evidence ;
$point & ".1" ) &
//R# for number of references
Case ( ValueCount ( testlearn::kcreference ) - ( Length ( Filter ( testlearn::kcreference ; "L" ) ) ) > 0 and
TEMP::InventoryLibraryYN = "" ; " " & TextColor ( ValueCount ( testlearn::kcreference ) - ( Length ( Filter
( testlearn::kcreference ; "L" ) ) ) & "R" ; RGB ( 154 ; 154 ; 154 ) ) ; "" ) ; 11 ) & ¶ &
//main text
TextFont ( testlearn::note ; "Georgia" ) & ¶ &
//grey text
TextColor ( "_______________" ; RGB ( 200 ; 200 ; 200 ) ) & ¶ &
TextSize ( TextColor (
 //node
 Case ( tagTLNodePrimary::_Ltag ≠ TEMP::kdefaultNodePrimary ;
 tagTLNodePrimary::tag &
 Case ( testlearn::NodeOthers = "" ;
 "" ; "; " & testlearn::NodeOthers ) ; "" ) &
 //copyright
 Case ( tagTLNodePrimary::_Ltag ≠ TEMP::kdefaultNodePrimary ;
 ". Copyright " & learnCreatorsCopyright::tag & ¶ ; "" ) &
 //timestamp
 testlearn::timestamp & ¶ &
 //keyword
 Case ( testlearn::OtherKeyWords ≠ "" or testlearn::kKeywordPrimary ≠ "" ;
 Case ( ValueCount ( testlearn::kcKeywordOther ) + ValueCount ( testlearn::kKeywordPrimary ) = 1 ;
 "keyword — " ; "keywords — " ) &
 //primary keyword
 tagTLKeywordPrimary::tag &
 Case ( testlearn::OtherKeyWords = "" ; "" ;
 //other keyword
 Case ( testlearn::kKeywordPrimary ≠ "" ; ", " & testlearn::OtherKeyWords ; testlearn::
OtherKeyWords ) ) ) &
 Case ( testlearn::OtherKeyWords ≠ "" or testlearn::kKeywordPrimary ≠ "" ;
 ¶ ; "" )
//finish text color
; RGB ( 119 ; 119 ; 119 ) ) ; 11 ) ]
Else If [ $keepTimestamp ≠ "" ]
#number, timestamp.
Set Variable [ $copy; Value://previous records
Case ( $copy = "" ; "" ; $copy & ¶ ) &
//number
TextSize (
Case ( testlearn::brainstormCasePoint = "" ; $point & "." & $evidence ;
$point & ".1" ) &
//R# for number of references
Case ( ValueCount ( testlearn::kcreference ) - ( Length ( Filter ( testlearn::kcreference ; "L" ) ) ) > 0 and
TEMP::InventoryLibraryYN = "" ; " " & TextColor ( ValueCount ( testlearn::kcreference ) - ( Length ( Filter
( testlearn::kcreference ; "L" ) ) ) & "R" ; RGB ( 154 ; 154 ; 154 ) ) ; "" ) ; 11 ) & ¶ &
//main text
TextFont ( testlearn::note ; "Georgia" ) & ¶ &
//grey text
TextColor ( "_______________" ; RGB ( 200 ; 200 ; 200 ) ) & ¶ &
TextSize ( TextColor (
 //node
 Case ( tagTLNodePrimary::_Ltag ≠ TEMP::kdefaultNodePrimary ;
 tagTLNodePrimary::tag &
 Case ( testlearn::NodeOthers = "" ;
 "" ; "; " & testlearn::NodeOthers ) ; "" ) &
 //copyright
 Case ( tagTLNodePrimary::_Ltag ≠ TEMP::kdefaultNodePrimary ;
 ". Copyright " & learnCreatorsCopyright::tag & ¶ ; "" ) &
 //timestamp
 testlearn::timestamp & ¶
//finish text color
; RGB ( 119 ; 119 ; 119 ) ) ; 11 ) ]
Else If [ $keepKeywords ≠ "" ]
#number, keywords.
Set Variable [ $copy; Value://previous records
Case ( $copy = "" ; "" ; $copy & ¶ ) &
//number
TextSize (
Case ( testlearn::brainstormCasePoint = "" ; $point & "." & $evidence ;
$point & ".1" ) &
//R# for number of references
Case ( ValueCount ( testlearn::kcreference ) - ( Length ( Filter ( testlearn::kcreference ; "L" ) ) ) > 0 and
TEMP::InventoryLibraryYN = "" ; " " & TextColor ( ValueCount ( testlearn::kcreference ) - ( Length ( Filter
( testlearn::kcreference ; "L" ) ) ) & "R" ; RGB ( 154 ; 154 ; 154 ) ) ; "" ) ; 11 ) & ¶ &
//main text
TextFont ( testlearn::note ; "Georgia" ) & ¶ &
//grey text
TextColor ( "_______________" ; RGB ( 200 ; 200 ; 200 ) ) & ¶ &
TextSize ( TextColor (
 //node
 Case ( tagTLNodePrimary::_Ltag ≠ TEMP::kdefaultNodePrimary ;
 tagTLNodePrimary::tag &
 Case ( testlearn::NodeOthers = "" ;
 "" ; "; " & testlearn::NodeOthers ) ; "" ) &
 //copyright
 Case ( tagTLNodePrimary::_Ltag ≠ TEMP::kdefaultNodePrimary ;
 ". Copyright " & learnCreatorsCopyright::tag & ¶ ; "" ) &
 //keyword
 Case ( testlearn::OtherKeyWords ≠ "" or testlearn::kKeywordPrimary ≠ "" ;
 Case ( ValueCount ( testlearn::kcKeywordOther ) + ValueCount ( testlearn::kKeywordPrimary ) = 1 ;
 "keyword — " ; "keywords — " ) &
 //primary keyword
 tagTLKeywordPrimary::tag &
 Case ( testlearn::OtherKeyWords = "" ; "" ;
 //other keyword
 Case ( testlearn::kKeywordPrimary ≠ "" ; ", " & testlearn::OtherKeyWords ; testlearn::
OtherKeyWords ) ) ) &
 Case ( testlearn::OtherKeyWords ≠ "" or testlearn::kKeywordPrimary ≠ "" ;
 ¶ ; "" )
//finish text color
; RGB ( 119 ; 119 ; 119 ) ) ; 11 ) ]
End If
Else If [ $numberOnlyFormat ≠ "" ]
#number.
#BEGIN Number
Set Variable [ $copy; Value://previous records
Case ( $copy = "" ; "" ; $copy & ¶ ) &
//number
TextSize (
Case ( testlearn::brainstormCasePoint = "" ; $point & "." & $evidence ;
$point & ".1" ) &
//R# for number of references
Case ( ValueCount ( testlearn::kcreference ) - ( Length ( Filter ( testlearn::kcreference ; "L" ) ) ) > 0 and TEMP::
InventoryLibraryYN = "" ; " " & TextColor ( ValueCount ( testlearn::kcreference ) - ( Length ( Filter ( testlearn::
kcreference ; "L" ) ) ) & "R" ; RGB ( 154 ; 154 ; 154 ) ) ; "" ) ; 11 ) & ¶ &
//main text
TextFont ( testlearn::note ; "Georgia" ) & ¶ &
 //node other than the primary author
 Case ( tagTLNodePrimary::_Ltag ≠ TEMP::kdefaultNodePrimary ;
//grey text
TextColor ( "_______________" ; RGB ( 200 ; 200 ; 200 ) ) & ¶ &
TextSize ( TextColor (
 //node
 Case ( tagTLNodePrimary::_Ltag ≠ TEMP::kdefaultNodePrimary ;
 tagTLNodePrimary::tag &
 Case ( testlearn::NodeOthers = "" ;
 "" ; "; " & testlearn::NodeOthers ) ; "" ) &
 //copyright
 Case ( tagTLNodePrimary::_Ltag ≠ TEMP::kdefaultNodePrimary ;
 ". Copyright " & learnCreatorsCopyright::tag & ¶ ; "" )
//finish text color
; RGB ( 119 ; 119 ; 119 ) ) ; 11 ) ; "" ) ]
#
#Given that the user has elected to not show
#any information below the note (below the
#grey line), call attention to the user when a
#node's information is shown below a grey line
#because the note is by a node other than the
#one getting credit for the share.
If [ tagTLNodePrimary::_Ltag ≠ TEMP::kdefaultNodePrimary ]
Set Variable [ $nodeOtherThanPrimaryAuthor; Value:1 ]
If [ tagTLNodePrimary::_Ltag ≠ TEMP::kdefaultNodePrimary ]
Set Variable [ $nodeOtherThanPrimaryAuthor; Value:1 ]
End If
End If
#END Number
Else If [ $essayFormat ≠ "" ]
#Show just the note and nothing else.
#BEGIN Essay Format
Set Variable [ $copy; Value://previous records
Case ( $copy = "" ; "" ; $copy & ¶ ) & ¶ &
//main text
TextFont ( testlearn::note ; "Georgia" ) & ¶ &
 //node other than the primary author
 Case ( tagTLNodePrimary::_Ltag ≠ TEMP::kdefaultNodePrimary ;
//grey text
TextColor ( "_______________" ; RGB ( 200 ; 200 ; 200 ) ) & ¶ &
TextSize ( TextColor (
 //node
 Case ( tagTLNodePrimary::_Ltag ≠ TEMP::kdefaultNodePrimary ;
 tagTLNodePrimary::tag &
 Case ( testlearn::NodeOthers = "" ;
 "" ; "; " & testlearn::NodeOthers ) ; "" ) &
 //copyright
 Case ( tagTLNodePrimary::_Ltag ≠ TEMP::kdefaultNodePrimary ;
 ". Copyright " & learnCreatorsCopyright::tag & ¶ ; "" )
//finish text color
; RGB ( 119 ; 119 ; 119 ) ) ; 11 ) ; "" ) ]
#
#Given that the user has elected to not show
#any information below the note (below the
#grey line), call attention to the user when a
#node's information is shown below a grey line
#because the note is by a node other than the
#one getting credit for the share.
If [ tagTLNodePrimary::_Ltag ≠ TEMP::kdefaultNodePrimary ]
Set Variable [ $nodeOtherThanPrimaryAuthor; Value:1 ]
End If
#END Essay Format
#
End If
#
#END Build and format idea notes
#
Else If [ TEMP::InventoryLibraryYN ≠ "" ]
#
#BEGIN Build and format inventory note
#
#Assemble note, order number, timestamp,
#and location fields.
If [ $orderInventoryGroupNumber = "" and $unknownLocation = ""
 or
$orderInventoryGroupNumber ≠ testlearn::orderInventoryGroupNumber ]
If [ $unknownLocation = "" ]
Set Variable [ $copy; Value://previous records
Case ( $copy = "" ; "" ; $copy & ¶ ) &
Case ( $orderInventoryGroupNumber ≠ testlearn::orderInventoryGroupNumber and
$orderInventoryGroupNumber ≠ "" and testlearn::orderInventoryGroupName ≠ "" ;
 TextSize ( ¶ ; 6 ) & "____________________" & ¶ & TextSize ( ¶ ; 14 ) &
 TextSize ( Case ( testlearn::orderInventoryGroupName = "" ; "Unknown Location" ;
testlearn::orderInventoryGroupName ) ; 17 ) ;
 TextSize ( Case ( testlearn::orderInventoryGroupName = "" ; "Unknown Location" ; testlearn::
orderInventoryGroupName ) ; 17 ) )
& ¶ & ¶ &
//main text
TextFont ( testlearn::note ; "Georgia" ) ]
Else
Set Variable [ $copy; Value://previous records
Case ( $copy = "" ; "" ; $copy & ¶ ) &
Case ( $orderInventoryGroupNumber ≠ testlearn::orderInventoryGroupNumber and testlearn::
orderInventoryGroupNumber ≠ "" and testlearn::orderInventoryGroupName ≠ "" ;
 TextSize ( ¶ ; 6 ) & "____________________" & ¶ & TextSize ( ¶ ; 14 ) &
 TextSize ( Case ( testlearn::orderInventoryGroupName = "" ; "Unknown Location" ;
testlearn::orderInventoryGroupName ) ; 17 ) ;
 TextSize ( Case ( testlearn::orderInventoryGroupName = "" ; "Unknown Location" ; testlearn::
orderInventoryGroupName ) ; 17 ) )
& ¶ & ¶ &
//main text
TextFont ( testlearn::note ; "Georgia" ) ]
End If
Set Variable [ $unknownLocation; Value:Case ( testlearn::orderInventoryGroupName = "" ; 1 ; "" ) ]
Set Variable [ $orderInventoryGroupNumber; Value:testlearn::orderInventoryGroupNumber ]
Else
Set Variable [ $copy; Value://previous records
Case ( $copy = "" ; "" ; $copy & ¶ ) &
//grey text
TextColor ( "____________________" ; RGB ( 200 ; 200 ; 200 ) )
& ¶ & ¶ &
//main text
TextFont ( testlearn::note ; "Georgia" ) ]
End If
#
#END Inventory note
#
End If
#
#BEGIN Increase note number
#
#Get note's number before it is updated for
#the next note. This number will be used
#to identify references used by this note in the
#end section.
#
Set Variable [ $noteNumberForItsReferences; Value://number
TextSize (
Case ( testlearn::brainstormCasePoint = "" ; $point & "." & $evidence ;
$point & ".1" ) ; 11 ) ]
#
#Increase note number for next note.
If [ testlearn::brainstormCasePoint = "" ]
Set Variable [ $evidence; Value:$evidence + 1 ]
Else
Set Variable [ $evidence; Value:2 ]
End If
#
#END Increase note number
#
#END LOOP SECTION Build and format notes
#
#
#
#BEGIN LOOP SECTION Build reference
#sections for each note
#
#Print references if a learn record has any.
If [ ValueCount ( testlearn::kcreference ) - ( Length ( Filter ( testlearn::kcreference ; "L" ) ) ) > 0
 and
TEMP::InventoryLibraryYN = "" ]
#
#Print title "Reference," "References,"
#or "Location."
If [ TEMP::InventoryLibraryYN = "" ]
If [ $referencesInSectionAtEnd = "" ]
Set Variable [ $copy; Value:$copy &
TextSize ( ¶ ; 6 ) &
//grey text
TextSize ( TextColor (
//references
Case ( ValueCount ( testlearn::kcreference ) - ( Length ( Filter ( testlearn::kcreference ; "L" ) ) ) = 1 ;
"Reference" ; "References" )
//finish text color
 ; RGB ( 119 ; 119 ; 119 ) ) ; 11 ) ]
End If
Else
Set Variable [ $copy; Value:$copy & ¶ &
Case ( testlearn::kcreference ≠ "" ; ¶ &
 Case ( refTestLearn::concatenateSTUFF = "" ;
 TextColor ( "Location" ; RGB ( 119 ; 119 ; 119 ) ) ; TextColor ( "Location = " ; RGB ( 119 ; 119 ; 119 ) ) &
refTestLearn::concatenateSTUFFcontainer
 // & TextColor ( ", located here:" ; RGB ( 119 ; 119 ; 119 ) )
 )
; "" ) ]
End If
#
#Now get the references. The portal variable
#needs to be reset for each learn record.
Set Variable [ $portal; Value:1 ]
#
#Select portal showing either a scholarly
#reference or inventory items location.
If [ TEMP::InventoryLibraryYN = "" ]
Go to Object [ Object Name: "ref1" ]
Else
If [ refTestLearn::concatenateSTUFF = "" ]
Go to Object [ Object Name: "stuff location" ]
Else
Go to Object [ Object Name: "container location" ]
End If
End If
#
#Now collect each reference's information.
Loop
#If this is the first reference clear the
#$portal variable and select portal's
#first record.
If [ $portal = 1 ]
Go to Portal Row
[ Select; First ]
End If
#
#Print references with the learn record if
#the user has not selected to print all the
#references at the end of this share (after
#all the notes have been printed).
If [ TEMP::InventoryLibraryYN = "" ]
If [ $referencesInSectionAtEnd = "" ]
Set Variable [ $copy; Value:Case ( Right ( $copy ; 9 ) = "Reference" or Right ( $copy ; 10 ) = "References";
$copy & ¶ &
//grey text
TextSize ( TextColor ( refLearn::referenceForLearnShare ; RGB ( 119 ; 119 ; 119 ) ) ; 11 ) ;
$copy & ¶ & TextSize ( ¶ ; 6 ) &
//grey text
TextSize ( TextColor ( refLearn::referenceForLearnShare ; RGB ( 119 ; 119 ; 119 ) ) ; 11 ) ) ]
#
Else
#
#If the user has elected to share the references
#at the end of the share, copy each one and
#store it in a temporary record.
Set Variable [ $shareReferenceID; Value:refLearn::_Lreference ]
Set Variable [ $shareReference; Value:refLearn::referenceForLearnShare ]
#
Go to Object [ Object Name: "shareID" ]
If [ TEMPforShare::shareReferenceID ≠ "firstRecord" ]
Go to Portal Row
[ Select; Last ]
End If
#
Set Field [ TEMPforShare::shareReferenceID; $shareReferenceID ]
Set Field [ TEMPforShare::shareReference; $shareReference ]
Set Field [ TEMPforShare::shareReferenceNoteNumber; $noteNumberForItsReferences ]
End If
#
#
Else
#If this a location, not a reference, then do print
#it with it's learn record = inventory item.
Set Variable [ $copy; Value:Case ( refTestLearn::concatenateSTUFF = "" ;
$copy & ¶ &
refLearn::referenceSTUFF ;
$copy & ¶ &
refContainerLocation::referenceSTUFF4learnOtherContainer ) ]
End If
#
#Select the record's next reference.
#
#Select portal showing either a scholarly
#reference or inventory items location.
If [ TEMP::InventoryLibraryYN = "" ]
Go to Object [ Object Name: "ref1" ]
Else
If [ refTestLearn::concatenateSTUFF = "" ]
Go to Object [ Object Name: "stuff location" ]
Else
Go to Object [ Object Name: "container location" ]
End If
End If
#
Go to Portal Row [ $portal ]
[ No dialog ]
Go to Portal Row
[ Next ]
Exit Loop If [ Get (LastError) = 101 ]
Set Variable [ $portal; Value:$portal + 1 ]
End Loop
#
End If
#
#Go to the next learn record tagged with this
#brainstorm or inventory list tag OR exit loop
#if this is the end of the list.
Go to Record/Request/Page
[ Next; Exit after last ]
Set Variable [ $copy; Value:$copy & Case ( $recordReferenceCount > 0 and $referencesInSectionAtEnd = "" ; ¶ ; "" ) ]
#
#Increase point number if point is different.
If [ testlearn::brainstormCasePoint ≠ "" ]
Set Variable [ $point; Value:$point + 1 ]
End If
#
#
#END LOOP SECTION Build reference
#sections for each note
#
End Loop
#
#
#END Build note and reference sections
#
#
#
#
#
#BEGIN Build reference end section
#
#If the user has elected to share the references
#at the end of the share, go to the temporary
#window and identify any duplicate references,
#and collect and add the note numbers of the
#previous record to the duplicate record. This
#addition will result in the final duplicate record
#containing the numbers of all previous
#duplicates, so each reference will identify all
#the notes referencing it.
If [ $referencesInSectionAtEnd ≠ "" ]
#Exit field in Share window, otherwise the
#field's record will remain in use in this
#window and cause problems for actions
#in the Sbare window.
Go to Field [ ]
Select Window [ Name: "Sbare"; Current file ]
Show All Records
#NOTE: This go to field step is important.
#It keesp the script from failing when
#the sort is performed.
Go to Field [ ]
Sort Records [ Specified Sort Order: TEMP::shareReferenceID; ascending
TEMP::shareReferenceNoteNumber; ascending ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ First ]
Set Variable [ $referenceID; Value:TEMP::shareReferenceID ]
Set Variable [ $noteNumber; Value:TEMP::shareReferenceNoteNumber ]
Loop
Go to Record/Request/Page
[ Next; Exit after last ]
If [ $referenceID = TEMP::shareReferenceID ]
Set Variable [ $noteNumber; Value:$noteNumber & ", " & TEMP::shareReferenceNoteNumber ]
Set Field [ TEMP::shareReferenceID; "duplicate" ]
Set Field [ TEMP::shareReferenceNoteNumber; $noteNumber ]
Else
Set Variable [ $referenceID; Value:TEMP::shareReferenceID ]
Set Variable [ $noteNumber; Value:TEMP::shareReferenceNoteNumber ]
Set Field [ TEMP::shareReferenceNoteNumber; $noteNumber ]
End If
End Loop
#
#Sort the references so the duplicates with all
#the reference note numbers are first. Now
#starting from the top, loop each record and
#select the first reference record for each
#possible duplicated reference record. Create
#a reference with the note numbers on a line
#above them in greyed text.
Go to Field [ ]
Sort Records [ Specified Sort Order: TEMP::shareReference; ascending
TEMP::shareReferenceID; descending
TEMP::shareReferenceNoteNumber; descending ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ First ]
Set Variable [ $reference; Value:TEMP::shareReference ]
Set Variable [ $referenceSection; Value:
TextSize (
Case ( Get ( FoundCount ) = 1 ; "Reference —————" ; "References —————" )
& ¶ ; 12 ) & Case ( $essayFormat = "" ; TextSize ( ¶ ; 4 ) ; TextSize ( ¶ ; 6 ) ) &
Case ( $essayFormat = "" ; TextColor ( TextSize ( TEMP::shareReferenceNoteNumber & ¶ ; 11 ) ; RGB ( 139 ; 139 ; 139 ) ) ;
"" ) &
TextSize ( TEMP::shareReference ; 12 ) ]
Loop
Go to Record/Request/Page
[ Next; Exit after last ]
If [ TEMP::shareReference ≠ $reference ]
Set Variable [ $referenceSection; Value:$referenceSection & ¶ &
Case ( $essayFormat = "" ; TextSize ( ¶ ; 8 ) & TextColor ( TextSize ( TEMP::shareReferenceNoteNumber & ¶ ;
11 ) ; RGB ( 130 ; 130 ; 130 ) ) ; TextSize ( ¶ ; 8 ) ) &
//text size
TextSize ( TEMP::shareReference ; 12 ) ]
End If
Set Variable [ $reference; Value:TEMP::shareReference ]
End Loop
#
#Once the end reference section has been
#created erase the temporary records, and
#then create 1 temporary record to display
#information that is in these fields, like
#the fields on the alldefaults layout.
Select Window [ Name: "Sbare"; Current file ]
Delete All Records
[ No dialog ]
New Record/Request
Close Window [ Name: "Sbare"; Current file ]
Select Window [ Name: "Share"; Current file ]
End If
#
#END Build reference end section
#
#
#
#
#
#BEGIN Build title header for share document
#
#Get primary node's copyright for this share as
#it is the primary node that is sharing these records.
Go to Layout [ “TEMP” (TEMP) ]
Set Variable [ $copyright; Value:defaultCopyrightName::tag ]
#
#
#
#
#Brainstorm or Inventory Header
If [ $$citationMatch = "brainstorm" ]
Select Window [ Name: "Tag Menus"; Current file ]
#
#
If [ TEMP::InventoryLibraryYN = "" ]
#Brainstorm header
#
#If tag and default copyright are different,
#note this so user can be informed.
If [ $copyright ≠ tagsCopyright::tag ]
Set Variable [ $informUserCopyrightNotEqualToDefault; Value:$copyright ]
End If
#
#Get tag's copyright in idea mode.
Set Variable [ $copyright; Value:tagsCopyright::tag ]
Set Variable [ $brainstorm; Value://Title
TEMP::userLibraryName & ": Brainstorm — " & //TextStyleAdd ( tagMenus::tag ; Titlecase )
tagMenus::tag & ¶ &
//author and copyright date
TEMP::DEFAULTNodePrimaryName & " (" & Month ( Get ( CurrentDate ) ) & "/" & Day ( Get ( CurrentDate ) ) & "/" &
Year ( Get ( CurrentDate ) ) & "). Copyright " & $copyright & "." ]
#
Else
#Inventory header
#
Set Variable [ $brainstorm; Value://Title
TEMP::userLibraryName & ": Inventory List — " & //TextStyleAdd ( tagMenus::tag ; Titlecase )
tagMenus::tag & ¶ &
//author and copyright date
TEMP::DEFAULTNodePrimaryName & " (" & Month ( Get ( CurrentDate ) ) & "/" & Day ( Get ( CurrentDate ) ) & "/" &
Year ( Get ( CurrentDate ) ) & "). Copyright " & $copyright & "." ]
End If
#
#
#
#
#Test Header
Else If [ $$citationMatch = "test" ]
Select Window [ Name: "Tag Menus"; Current file ]
#
If [ TEMP::InventoryLibraryYN = "" ]
Set Variable [ $brainstorm; Value://Title
TEMP::userLibraryName & ": Test Subsection — " & //TextStyleAdd ( testSubsectionTemplate::name ; Titlecase )
testSubsectionTemplate::name & ¶ &
//author and copyright date
TEMP::DEFAULTNodePrimaryName & " (" & Month ( Get ( CurrentDate ) ) & "/" & Day ( Get ( CurrentDate ) ) & "/" &
Year ( Get ( CurrentDate ) ) & "). Copyright " & $copyright & "." ]
Else
Set Variable [ $brainstorm; Value://Title
TEMP::userLibraryName & ": Test Subsection — " & //TextStyleAdd ( testSubsectionTemplate::name ; Titlecase )
testSubsectionTemplate::name & ¶ &
//author and copyright date
TEMP::DEFAULTNodePrimaryName & " (" & Month ( Get ( CurrentDate ) ) & "/" & Day ( Get ( CurrentDate ) ) & "/" &
Year ( Get ( CurrentDate ) ) & "). Copyright " & $copyright & "." ]
End If
#
#
#
#
#General idea and inventory share header
Else If [ $$citationMatch ≠ "brainstorm" and $$citationMatch ≠ "test" ]
#
#
#General idea header
If [ TEMP::InventoryLibraryYN = "" ]
#
If [ $show = "all" ]
#Share all records
Set Variable [ $brainstorm; Value://Title
TextStyleAdd ( TEMP::userLibraryName & " Library Notes" ; "bold" ) & ¶ &
//author and copyright date
TEMP::DEFAULTNodePrimaryName & " (" & Month ( Get ( CurrentDate ) ) & "/" & Day ( Get ( CurrentDate ) ) & "/"
& Year ( Get ( CurrentDate ) ) & "). Copyright " & $copyright & "." &
Case ( $chronologicalSortOrder = "" ; ¶ & TextStyleAdd ( "Shown in reverse chronological order." ; Italic ) ; "" ) &
TextSize ( ¶ ; 6 ) &
"_______________" & ¶ &
TextSize ( ¶ ; 10 ) &
"NOTE: This is an unsaved list of " & $numberOfRecordsBeingViewed & " records. Use the Tag Menus'
'brainstorm' option to create custom-ordered, saved, collections of thoughts, ideas, etc." &
TextSize ( ¶ ; 6 ) &
"_______________" ]
#
Else
#Share only linked records
Set Variable [ $brainstorm; Value://Title
TEMP::userLibraryName & " Library Notes" & ¶ &
//author and copyright date
TEMP::DEFAULTNodePrimaryName & " (" & Month ( Get ( CurrentDate ) ) & "/" & Day ( Get ( CurrentDate ) ) & "/"
& Year ( Get ( CurrentDate ) ) & "). Copyright " & $copyright & "." &
Case ( $chronologicalSortOrder = "" ; TextStyleAdd ( ¶ & "Shown in reverse chronological order." ; Italic ) ; "" ) ]
End If
End If
#
#
#General inventory header
If [ TEMP::InventoryLibraryYN ≠ "" ]
#
If [ $show = "all" ]
#Share all records
Set Variable [ $brainstorm; Value://Title
TEMP::userLibraryName & ¶ &
//author and copyright date
TEMP::DEFAULTNodePrimaryName & " (" & Month ( Get ( CurrentDate ) ) & "/" & Day ( Get ( CurrentDate ) ) & "/"
& Year ( Get ( CurrentDate ) ) & "). Copyright " & $copyright & "." &
TextSize ( ¶ ; 6 ) &
"_______________" & ¶ &
TextSize ( ¶ ; 10 ) &
"NOTE: This is an unsaved list of " & $numberOfRecordsBeingViewed & " records. Use the Tag Menus' 'inventory
list' option to create custom-ordered, saved, lists." &
TextSize ( ¶ ; 6 ) &
"_______________" ]
#
Else
#Share only linked records
Set Variable [ $brainstorm; Value://Title
TEMP::userLibraryName & ¶ &
//author and copyright date
TEMP::DEFAULTNodePrimaryName & " (" & Month ( Get ( CurrentDate ) ) & "/" & Day ( Get ( CurrentDate ) ) & "/"
& Year ( Get ( CurrentDate ) ) & "). Copyright " & $copyright & "." ]
End If
End If
End If
Go to Field [ ]
#
#END Build title header for share document
#
#
#
#
#
#PART 5 >> Display share document —————
#
#
#
#
#
#BEGIN Assemble and display share document
#
#Compose the share document.
Set Variable [ $copy; Value://Brainstorm Title and Records and References
$brainstorm & ¶ & ¶ & $copy & ¶ & ¶ & $referenceSection ]
#
#Select Learn window so when the Share
#window is closed it will be selected. Then
#select the Share window to continue
#this script.
Select Window [ Name: "Learn"; Current file ]
Select Window [ Name: "Share"; Current file ]
Go to Layout [ “learnPreviewLayoutView” (testlearn) ]
#
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
#
#Paste the document into the share layout.
Set Field [ TEMP::paste; $copy ]
Go to Field [ ]
#
#All records showing are identical,
#so remove all but one of them.
Go to Record/Request/Page
[ First ]
Omit Multiple Records [ Get (FoundCount) - 1 ]
[ No dialog ]
#
#Display list.
Scroll Window
[ Home ]
Move/Resize Window [ Current Window; Top: 0; Left: 0 ]
Adjust Window
[ Resize to Fit ]
#
#END Assemble and display share document
#
#
#
#
#
#PART 6 >> Report any issues ————————
#
#
#
#
#
#Inform user if one or more record's was
#created by another library node, IF the
#the user elected to not show timestamp
#and keywords.
If [ $nodeOtherThanPrimaryAuthor ≠ "" ]
Show Custom Dialog [ Message: "FYI: This share contains at least one contribution by another author (node). They have been
given credit with their name and copyright under a line, under their contribution."; Default Button: “OK”, Commit: “Yes” ]
End If
#
#Inform user if brainstorm tag's copyright
#is different from user's default copyright.
If [ $informUserCopyrightNotEqualToDefault ≠ "" ]
Show Custom Dialog [ Message: "FYI: This brainstorm's copyright — " & $copyright & " — is NOT the same as your default
copyright = " & $informUserCopyrightNotEqualToDefault & "."; Default Button: “OK”, Commit: “Yes” ]
End If
#
Exit Script [ ]
#
#
#END: SHARE DOCUMENT CREATION
#
#
