January 16, 2018 17:48:36 Library.fmp12 - shareLearnRecords -1-
learn: shareLearnRecords
#
#If in find mode, exit script.
If [ $$findMode ≠ "" ]
Show Custom Dialog [ Message: "Exit find mode in the Tag Menus window, then click this button."; Default Button: “OK”,
Commit: “No” ]
Exit Script [ ]
End If
#
#
#Admin tasks.
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
Close Window [ Name: "Share"; Current file ]
#
Set Variable [ $$stopLoadCitation; Value:1 ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Set Variable [ $layoutName; Value:Get ( LayoutName ) ]
#
#
#BEGIN: SHARE Brainstorm/Inventory or Test Tagged Records
#
#If the Tag Menus window is showing the brainstorm
#or inventory menu when the use clicked 'share'
#then find the records tagged with the currently
#selected brainstorm tag = $$brainstorm variable.
If [ $$citationMatch = "brainstorm" and $layoutName ≠ "learn4EDIT" and $layoutName ≠ "learn4EDITstuff"
or
$$citationMatch = "test" and $layoutName ≠ "learn4EDIT" and $layoutName ≠ "learn4EDITstuff" ]
#
// New Window [ Name: "Share"; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”;
Resize: “Yes” ]
New Window [ Name: "Share"; Height: 1; Width: 1; Top: 10000; Left: 10000; Style: Document; Close: “Yes”; Minimize: “Yes”;
Maximize: “Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
Go to Layout [ “learnPreviewLayout” (testlearn) ]
#
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
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearn::orderTestInformation; based on value list:
“testPulldownListANDsortOrderList”
testlearn::timestamp; descending ]
[ Restore; No dialog ]
#
#
#Stop the script if no records are found and
#tell the user why.
If [ Get (FoundCount) = 0 ]
Close Window [ Current Window ]
Select Window [ Name: "Tag Menus"; Current file ]
Set Variable [ $tagName; Value:tagMenus::tag ]
Select Window [ Name: "Learn"; Current file ]
If [ TEMP::InventoryLibraryYN = "" ]
Show Custom Dialog [ Message: "When a brainstorm tag is active in the Tag Menus window, clicking the share button
will show all records tagged with it. Zero records are tagged with " & $tagName & "."; Default Button: “OK”,
Commit: “Yes” ]
Else
Show Custom Dialog [ Message: "When an inventory list tag is active in the Tag Menus window, clicking the share
button will show all records tagged with it. Zero records are tagged with " & $tagName & "."; Default Button: “OK”,
Commit: “Yes” ]
End If
#
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
#
Exit Script [ ]
End If
#
#
#Now add references linked to all records.
Set Variable [ $point; Value:1 ]
Set Variable [ $evidence; Value:1 ]
Go to Record/Request/Page
[ First ]
#
#Print order number, author, record date, text
#of learn record, and keywords.
Loop
If [ TEMP::InventoryLibraryYN = "" ]
#Set copyright.
Set Variable [ $copy; Value://previous records
Case ( $copy = "" ; "" ; $copy & ¶ & ¶) &
//text
Case ( testlearn::brainstormCasePoint = "" ; $point & "." & $evidence ;
$point & ".1" ) &
//node
TextColor ( " [" & tagTLNodePrimary::tag &
Case ( testlearn::NodeOthers = "" ; "" ; "; " & testlearn::NodeOthers ) &
//timestamp
" (" & testlearn::timestamp & ")." &
//copyright
" Copyright " & learnCreatorsCopyright::tag & ".]"
 ; RGB ( 119 ; 119 ; 119 ) ) & ¶ & ¶ &
//main text
TextFont ( testlearn::note ; "Georgia" ) & ¶ &
//grey remain text
TextColor (
//keyword
Case ( testlearn::OtherKeyWords ≠ "" or testlearn::kKeywordPrimary ≠ "" ; ¶ &
"keywords — " &
//primary keyword
tagTLKeywordPrimary::tag &
Case ( testlearn::OtherKeyWords = "" ; "" ;
//other keyword
Case ( testlearn::kKeywordPrimary ≠ "" ; ", " & testlearn::OtherKeyWords ; testlearn::OtherKeyWords ) ) )
//finsih text color
 ; RGB ( 119 ; 119 ; 119 ) ) ]
Else
Set Variable [ $copy; Value://previous records
Case ( $copy = "" ; "" ; $copy & ¶ & ¶) &
//number
Case ( testlearn::brainstormCasePoint = "" ; $point & "." & $evidence ;
$point & ".1" ) &
//node
TextColor ( " [" & tagTLNodePrimary::tag &
Case ( testlearn::NodeOthers = "" ; "" ; "; " & testlearn::NodeOthers ) &
//timestamp
" " & testlearn::timestamp & "]"
 ; RGB ( 119 ; 119 ; 119 ) ) & ¶ & ¶ &
//main text
TextFont ( testlearn::note ; "Georgia" ) & ¶ &
//grey remain text
TextColor (
//keyword
Case ( testlearn::OtherKeyWords ≠ "" or testlearn::kKeywordPrimary ≠ "" ; ¶ &
"Attibutes = " &
//primary keyword
tagTLKeywordPrimary::tag &
Case ( testlearn::OtherKeyWords = "" ; "" ;
//other keyword
Case ( testlearn::kKeywordPrimary ≠ "" ; ", " & testlearn::OtherKeyWords ; testlearn::OtherKeyWords ) ) )
//finsih text color
 ; RGB ( 119 ; 119 ; 119 ) ) ]
End If
#
#Increase evidence number if point is required.
If [ testlearn::brainstormCasePoint = "" ]
Set Variable [ $evidence; Value:$evidence + 1 ]
Else
Set Variable [ $evidence; Value:2 ]
End If
#
#Print references if a learn record has any.
If [ testlearn::kcreference ≠ "" ]
If [ refLearn::referenceForReferenceWindow ≠ "" or
TEMP::InventoryLibraryYN ≠ "" and refContainerLocation::referenceForReferenceWindow ≠ "" ]
#
#Name reference or inventory location section.
If [ TEMP::InventoryLibraryYN = "" ]
Set Variable [ $copy; Value:$copy & ¶ &
//grey text
TextColor (
//references
Case ( testlearn::kcreference ≠ "" ; ¶ & "References" ; "" )
//finsih text color
 ; RGB ( 119 ; 119 ; 119 ) ) ]
Else
Set Variable [ $copy; Value:$copy & ¶ &
Case ( testlearn::kcreference ≠ "" ; ¶ &
 Case ( refTestLearn::concatenateSTUFF = "" ;
 TextColor ( "Location" ; RGB ( 119 ; 119 ; 119 ) ) ; TextColor ( "Location = " ; RGB ( 119 ; 119 ;
119 ) ) & refTestLearn::concatenateSTUFFcontainer
 // & TextColor ( ", located here:" ; RGB ( 119 ; 119 ; 119 ) )
 )
; "" ) ]
End If
#
#Start with the first reference. This needs to
#be set at the start of each loop.
Set Variable [ $portal; Value:1 ]
#
Loop
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
#If this is the first reference clear the
#$portal variable and select portal's first record.
If [ $portal = 1 ]
Set Variable [ $portal ]
Go to Portal Row
[ Select; First ]
End If
#
#Print references.
If [ TEMP::InventoryLibraryYN = "" ]
Set Variable [ $copy; Value:Case ( Right ( $copy ; 10 ) = "References" ;
$copy & ¶ &
//grey text
TextColor ( refLearn::referenceForReferenceWindow ; RGB ( 119 ; 119 ; 119 ) ) ;
$copy & ¶ & ¶ &
//grey text
TextColor ( refLearn::referenceForReferenceWindow ; RGB ( 119 ; 119 ; 119 ) ) ) ]
Else
Set Variable [ $copy; Value:Case ( refTestLearn::concatenateSTUFF = "" ;
$copy & ¶ &
refLearn::referenceSTUFF ;
$copy & ¶ &
refContainerLocation::referenceSTUFF4learnOtherContainer ) ]
End If
#
#Go to the learn records next reference.
Go to Portal Row
[ Select; Next; Exit after last ]
Exit Loop If [ Get (LastError) = 101 ]
End Loop
#
End If
End If
#
#Go to the next learn record tagged with this
#brainstorm or inventory list tag OR exit loop
#if this is the end of the list.
Go to Record/Request/Page
[ Next; Exit after last ]
Set Variable [ $copy; Value:$copy & ¶ &
//grey text
TextColor ( "_______________________________________________" ; RGB ( 119 ; 119 ; 119 ) ) ]
#
#Increase point number if point is different.
If [ testlearn::brainstormCasePoint ≠ "" ]
Set Variable [ $point; Value:$point + 1 ]
End If
End Loop
#
#
#Get primary node's copyright for this share as
#it is the primary node that is sharing these records.
Go to Layout [ “TEMP” (TEMP) ]
Set Variable [ $copyright; Value:defaultCopyrightName::tag ]
Go to Layout [ “learnPreviewLayout” (testlearn) ]
#
#
#Get brainstorm or inventory list tag's title and
#use as the title for this shared list.
If [ $$citationMatch = "brainstorm" or $$citationMatch = "test" ]
Select Window [ Name: "Tag Menus"; Current file ]
If [ $$citationMatch = "brainstorm" ]
If [ TEMP::InventoryLibraryYN = "" ]
#Set copyright.
Set Variable [ $copyright; Value:tagsCopyright::tag ]
Set Variable [ $brainstorm; Value://Title
TEMP::userLibraryName & " Brainstorm — " & TextStyleAdd ( tagMenus::tag ; Titlecase ) & ¶ &
//author and copyright date
TEMP::DEFAULTNodePrimaryName & " (" & Month ( Get ( CurrentDate ) ) & "/" & Day ( Get ( CurrentDate ) )
& "/" & Year ( Get ( CurrentDate ) ) & "). Brainstorm Copyright " & $copyright & "." ]
Else
#Set copyright.
Set Variable [ $copyright; Value:tagsCopyright::tag ]
Set Variable [ $brainstorm; Value://Title
TEMP::userLibraryName & " Inventory List — " & TextStyleAdd ( tagMenus::tag ; Titlecase ) & ¶ &
//author and copyright date
TEMP::DEFAULTNodePrimaryName & " (" & Month ( Get ( CurrentDate ) ) & "/" & Day ( Get ( CurrentDate ) )
& "/" & Year ( Get ( CurrentDate ) ) & "). Inventory List Copyright " & $copyright & "." ]
End If
Else If [ $$citationMatch = "test" ]
If [ TEMP::InventoryLibraryYN = "" ]
#Set copyright.
Set Variable [ $brainstorm; Value://Title
TEMP::userLibraryName & " Test Subsection — " & TextStyleAdd ( testSubsectionTemplate::name ;
Titlecase ) & ¶ &
//author and copyright date
TEMP::DEFAULTNodePrimaryName & " (" & Month ( Get ( CurrentDate ) ) & "/" & Day ( Get ( CurrentDate ) )
& "/" & Year ( Get ( CurrentDate ) ) & "). Copyright " & $copyright & "." ]
Else
#Set copyright.
Set Variable [ $brainstorm; Value://Title
TEMP::userLibraryName & " Test Subsection — " & TextStyleAdd ( testSubsectionTemplate::name ;
Titlecase ) & ¶ &
//author and copyright date
TEMP::DEFAULTNodePrimaryName & " (" & Month ( Get ( CurrentDate ) ) & "/" & Day ( Get ( CurrentDate ) )
& "/" & Year ( Get ( CurrentDate ) ) & "). Copyright " & $copyright & "." ]
End If
End If
Go to Field [ ]
Set Variable [ $copy; Value://Brainstorm Title and History
$brainstorm & ¶ & ¶ & $copy ]
#
#Select Learn window so when the Share
#window is closed it will be selected. Then
#select the Share window to continue
#this script.
Select Window [ Name: "Learn"; Current file ]
Select Window [ Name: "Share"; Current file ]
Go to Layout [ “learnPreviewLayoutView” (testlearn) ]
End If
#
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
#
#Set font size.
Set Field [ TEMP::paste; TextSize ( $copy ; 12 ) ]
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
Move/Resize Window [ Current Window; Height: Get (ScreenHeight); Width: Get (ScreenWidth) / 2; Top: 0; Left: 0 ]
Adjust Window
[ Resize to Fit ]
#
Exit Script [ ]
#
#END: SHARE Brainstorm/Inventory or Test Tagged Records
#
#
#
#
#
Else
#
#
#
#
#
#
#BEGIN: SHARE Non-Brainstorm and Inventory Records
#
#BEGIN: Find out if the user wants to show the
#selected record, linked records too, or all
#records being viewed.
#
#Use for header message on printed list.
Set Variable [ $numberOfRecordsBeingViewed; Value:Get (FoundCount) ]
#
#Check if the current Learn record
#references other Learn records or is
#referenced by other Learn records.
If [ Filter ( testlearn::kcreference ; "L" ) ≠ "" or $$LinkedLearnRecords ≠ "" ]
#
#If it does reference other Learn records ask
#the user what they would like to see?
If [ $layoutName = "learn4EDIT" or
$layoutName = "learn4EDITStuff" ]
#
#On QV layouts ask about viewing just the
#selected record or all linked records.
If [ TEMP::InventoryLibraryYN = "" ]
Show Custom Dialog [ Message: "This record is linked to other learn records (text areas highlighted purple).
Share linked or just this one record?"; Default Button: “linked”, Commit: “Yes”; Button 2: “one”, Commit: “No”;
Button 3: “cancel”, Commit: “No” ]
Else
#
#Determine if inventory record is for a container.
If [ testlearn::brainstormCasePoint = "" ]
Show Custom Dialog [ Message: "This record is linked to other inventory records. Show them too or just this
one record?"; Default Button: “linked”, Commit: “Yes”; Button 2: “one”, Commit: “No”; Button 3: “cancel”,
Commit: “No” ]
Else
Show Custom Dialog [ Message: "This holder (box, shelf, etc) is linked to other inventory records. Show
them too or just this one record?"; Default Button: “linked”, Commit: “Yes”; Button 2: “one”, Commit: “No”;
Button 3: “cancel”, Commit: “No” ]
End If
#
End If
If [ Get (LastMessageChoice) = 1 ]
Set Variable [ $show; Value:"self and referenced" ]
Else If [ Get (LastMessageChoice) = 2 ]
Set Variable [ $show; Value:"self" ]
End If
#
Else
#On main learn layouts ask about viewing
#selected or all records.
If [ TEMP::InventoryLibraryYN = "" ]
Show Custom Dialog [ Message: "Share only linked learn records (text areas highlighted purple)?" & ¶ & "OR" &
¶ & "Share all records being viewed? Now viewing " & Get (FoundCount) & "."; Default Button: “linked”,
Commit: “Yes”; Button 2: “all”, Commit: “No”; Button 3: “cancel”, Commit: “No” ]
Else
If [ testlearn::brainstormCasePoint = "" ]
Show Custom Dialog [ Message: "Share this inventory record and all records to which it's linked?" & ¶ &
"OR" & ¶ & "Share all inventory records being viewed? Now viewing " & Get (FoundCount) & "."; Default
Button: “linked”, Commit: “Yes”; Button 2: “all”, Commit: “No”; Button 3: “cancel”, Commit: “No” ]
Else
Show Custom Dialog [ Message: "Share this storage record and inventory records linked to it?" & ¶ & "OR"
& ¶ & "Share all records being viewed? Now viewing " & Get (FoundCount) & "."; Default Button: “linked”,
Commit: “Yes”; Button 2: “all”, Commit: “No”; Button 3: “cancel”, Commit: “No” ]
End If
End If
If [ Get (LastMessageChoice) = 1 ]
Set Variable [ $show; Value:"self and referenced" ]
#
Else If [ Get (LastMessageChoice) = 2 ]
Set Variable [ $show; Value:"all" ]
#
End If
End If
#
#Exit script if user clicks cancel.
If [ Get ( LastMessageChoice ) = 3 ]
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
Exit Script [ ]
End If
#
#
Else
#
#
#If it has no references to other Learn records
#on QV layouts set to just show this one record.
If [ $layoutName = "learn4EDIT" or
$layoutName = "learn4EDITStuff" ]
Set Variable [ $show; Value:"self" ]
End If
#
#If record is on main layout (not QV) and has no
#references, see if user wants view just the
#selected record or all records being viewed.
If [ Get (FoundCount) ≠ 1 and $layoutName ≠ "learn4EDIT" and $layoutName ≠ "learn4EDITStuff" ]
If [ TEMP::InventoryLibraryYN = "" ]
Show Custom Dialog [ Message: "Share all or just this one record? Now viewing " & Get (FoundCount) & ".";
Default Button: “all”, Commit: “Yes”; Button 2: “one”, Commit: “No”; Button 3: “cancel”, Commit: “No” ]
Else
#
#Determine if inventory record is for a container.
If [ testlearn::brainstormCasePoint = "" ]
Show Custom Dialog [ Message: "Share all inventory records being viewed or just this one record? Now
viewing " & Get (FoundCount) & "."; Default Button: “all”, Commit: “Yes”; Button 2: “one”, Commit: “No”;
Button 3: “cancel”, Commit: “No” ]
Else
Show Custom Dialog [ Message: "Share all inventory records being viewed or just this one storage area,
holder, etc. record? Now viewing " & Get (FoundCount) & "."; Default Button: “all”, Commit: “Yes”; Button
2: “one”, Commit: “No”; Button 3: “cancel”, Commit: “No” ]
End If
End If
#
If [ Get (LastMessageChoice) = 1 ]
Set Variable [ $show; Value:"all" ]
#
Else If [ Get (LastMessageChoice) = 2 ]
Set Variable [ $show; Value:"self" ]
End If
#
#Exit script if user clicks cancel.
If [ Get ( LastMessageChoice ) = 3 ]
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
Exit Script [ ]
End If
End If
End If
End If
#
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
Show Custom Dialog [ Message: "FYI: It may take more than a minute to process this many records."; Default Button: “OK”,
Commit: “Yes”; Button 2: “cancel”, Commit: “No” ]
End If
#
If [ Get ( LastMessageChoice ) = 2 ]
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
Exit Script [ ]
End If
#
Install Menu Set [ “HGT Stop Share” ]
Show Custom Dialog [ Message: "If you get tired of waiting, just click on the 'Help' menu above and select 'Stop Share' to stop
the processing of your records."; Default Button: “OK”, Commit: “Yes” ]
End If
#
#
#END: Find out if the user wants to show the
#selected record, linked records too, or all
#records being viewed.
#
#
#Begin process of showing user selected
#records.
// New Window [ Name: "Share"; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”; Resize:
“Yes” ]
New Window [ Name: "Share"; Height: 1; Width: 1; Top: 10000; Left: 10000; Style: Document; Close: “Yes”; Minimize: “Yes”;
Maximize: “Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
Go to Layout [ “learnPreviewLayout” (testlearn) ]
Install Menu Set [ “HGT Stop Share” ]
#
#If user elected to show only selected record,
#then only this record.
If [ $show = "self" ]
Enter Find Mode [ ]
Set Field [ testlearn::_Ltestlearn; $$main ]
Perform Find [ ]
End If
#
#
#If user elected to show the selected record
#and linked records, then find just these
#records and show them.
If [ $show = "self and referenced" ]
#
#Find original record first.
Enter Find Mode [ ]
Set Field [ testlearn::_Ltestlearn; $$main ]
Perform Find [ ]
#
#Determine if record has references to show.
If [ Filter ( testlearn::kcreference ; "L" ) ≠ "" ]
#
#Set $showReferences variable.
Set Variable [ $showReferences; Value:1 ]
End If
#
#If there are records it has links to
#AND records with links to it ask user if they
#want to see the first type or both types.
If [ $showReferences ≠ ""
and
$$LinkedLearnRecords ≠ "" ]
#
Select Window [ Name: "Learn"; Current file ]
If [ TEMP::InventoryLibraryYN = "" ]
Show Custom Dialog [ Message: "This record 1) references and is 2) referenced by other Learn records. Show 1 =
Refs or 1 and 2 = Refs+?"; Default Button: “Refs +”, Commit: “Yes”; Button 2: “Refs”, Commit: “No”; Button 3:
“cancel”, Commit: “No” ]
Else
If [ testlearn::brainstormCasePoint = "" ]
Show Custom Dialog [ Message: "This record 1) references and is 2) referenced by other Learn records. Show 1
= Refs or 1 and 2 = Refs+?"; Default Button: “Refs +”, Commit: “Yes”; Button 2: “Refs”, Commit: “No”; Button
3: “cancel”, Commit: “No” ]
Else
Set Variable [ $showReferencesReferencingMe; Value:1 ]
End If
End If
If [ Get (LastMessageChoice) = 1 ]
Set Variable [ $showReferencesReferencingMe; Value:1 ]
End If
Select Window [ Name: "Share"; Current file ]
End If
#
#
#Exit script if user clicks cancel.
If [ Get ( LastMessageChoice ) = 3 ]
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
Close Window [ Current Window ]
Exit Script [ ]
End If
End If
#
#
#BEGIN: Get all learn records the selected record
#has links to (it references these records).
If [ $showReferences ≠ "" ]
#
#First get the linked records' IDs.
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
#Find 1st record.
Enter Find Mode [ ]
Set Field [ testlearn::_Ltestlearn; GetValue ( $findLinkedLearnRecords ; $numberOfKeys ) ]
Extend Found Set [ ]
Set Variable [ $numberOfKeys; Value:$numberOfKeys - 1 ]
#
#Loop set of IDs to expand found records until
#all linked records have been found.
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
End If
#END: Get all learn records the selected record
#has links to (it references these records).
#
#
#Find all records with links to selected record
#if the user wants to see them, I.E., the user
#clicked a 'linked' button.
If [ $show ≠ "self" ]
If [ $show ≠ "all" ]
If [ //There are only learn records referencing this record to show
$showReferences = "" and $$LinkedLearnRecords ≠ ""
or
//There are learn records this record references and records referencing it that the user wants to show.
$showReferences ≠ "" and $showReferencesReferencingMe ≠ "" ]
#
Enter Find Mode [ ]
Set Field [ testlearn::kcreference; $$main ]
Extend Found Set [ ]
#
End If
End If
End If
#
#Put all found records in order.
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearn::date; descending
testlearn::timestamp; descending ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ First ]
#
#
#Now add references for the found learn records.
Set Variable [ $point; Value:1 ]
Set Variable [ $evidence; Value:1 ]
Go to Record/Request/Page
[ First ]
#
Loop
#Print order number, author, record date, text
#of learn record, and keywords.
If [ TEMP::InventoryLibraryYN = "" ]
#Set copyright.
Set Variable [ $copy; Value://previous records
Case ( $copy = "" ; "" ; $copy & ¶ & ¶) &
//text
Case ( testlearn::brainstormCasePoint = "" ; $point & "." & $evidence ;
$point & ".1" ) &
//node
TextColor ( " [" & tagTLNodePrimary::tag &
Case ( testlearn::NodeOthers = "" ; "" ; "; " & testlearn::NodeOthers ) &
//timestamp
" (" & testlearn::timestamp & ")." &
//copyright
" Copyright " & learnCreatorsCopyright::tag & ".]"
 ; RGB ( 119 ; 119 ; 119 ) ) & ¶ & ¶ &
//main text
TextFont ( testlearn::note ; "Georgia" ) & ¶ &
//grey remain text
TextColor (
//keyword
Case ( testlearn::OtherKeyWords ≠ "" or testlearn::kKeywordPrimary ≠ "" ; ¶ &
"keywords — " &
//primary keyword
tagTLKeywordPrimary::tag &
Case ( testlearn::OtherKeyWords = "" ; "" ;
//other keyword
Case ( testlearn::kKeywordPrimary ≠ "" ; ", " & testlearn::OtherKeyWords ; testlearn::OtherKeyWords ) ) )
//finish text color
 ; RGB ( 119 ; 119 ; 119 ) ) ]
Else
Set Variable [ $copy; Value://previous records
Case ( $copy = "" ; "" ; $copy & ¶ & ¶) &
//number
Case ( testlearn::brainstormCasePoint = "" ; $point & "." & $evidence ;
$point & ".1" ) &
//node
TextColor ( " [" & tagTLNodePrimary::tag &
Case ( testlearn::NodeOthers = "" ; "" ; "; " & testlearn::NodeOthers ) &
//timestamp
" " & testlearn::timestamp & "]"
 ; RGB ( 119 ; 119 ; 119 ) ) & ¶ & ¶ &
//main text
TextFont ( testlearn::note ; "Georgia" ) & ¶ &
//grey remain text
TextColor (
//keyword
Case ( testlearn::OtherKeyWords ≠ "" or testlearn::kKeywordPrimary ≠ "" ; ¶ &
"Attibutes = " &
//primary keyword
tagTLKeywordPrimary::tag &
Case ( testlearn::OtherKeyWords = "" ; "" ;
//other keyword
Case ( testlearn::kKeywordPrimary ≠ "" ; ", " & testlearn::OtherKeyWords ; testlearn::OtherKeyWords ) ) )
//finish text color
 ; RGB ( 119 ; 119 ; 119 ) ) ]
End If
#
If [ testlearn::kcreference ≠ "" ]
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
#Print references if this learn record has any.
If [ testlearn::kcreference ≠ "" ]
#
#Name reference or inventory location section.
#Apply only if references are found.
If [ TEMP::InventoryLibraryYN = "" and Get (LastError) ≠ 101 ]
Set Variable [ $copy; Value:$copy & ¶ &
//Add a paragraph space between kewords and references if both exist.
Case ( testlearn::kcreference ≠ "" and testlearn::kKeywordPrimary = "" and testlearn::OtherKeyWords = "" ;
"" ; ¶ ) &
//grey text
TextColor (
//references
Case ( testlearn::kcreference ≠ "" ; "References" ; "" )
//finsih text color
 ; RGB ( 119 ; 119 ; 119 ) ) ]
Else If [ Get (LastError) ≠ 101 ]
Set Variable [ $copy; Value:$copy & ¶ &
Case ( testlearn::kcreference ≠ "" ; ¶ &
 Case ( refTestLearn::concatenateSTUFF = "" ;
 TextColor ( "Location" ; RGB ( 119 ; 119 ; 119 ) ) ; TextColor ( "Location = " ; RGB ( 119 ; 119 ; 119 ) )
& refTestLearn::concatenateSTUFFcontainer
 // & TextColor ( ", located here:" ; RGB ( 119 ; 119 ; 119 ) )
 )
; "" ) ]
End If
#
#Start with the first reference. This needs to
#be set at the start of each loop.
Set Variable [ $portal; Value:1 ]
#
Loop
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
#Exit the loop if there are no records.
Exit Loop If [ Get (LastError) = 101 ]
#
#If this is the first reference clear the
#$portal variable and select portal's first record.
If [ $portal = 1 ]
Set Variable [ $portal ]
Go to Portal Row
[ Select; First ]
End If
#
#Print references.
If [ TEMP::InventoryLibraryYN = "" ]
Set Variable [ $copy; Value:Case ( Right ( $copy ; 10 ) = "References" ;
$copy & ¶ &
//grey text
TextColor ( refLearn::referenceForReferenceWindow ; RGB ( 119 ; 119 ; 119 ) ) ;
$copy & ¶ & ¶ &
//grey text
TextColor ( refLearn::referenceForReferenceWindow ; RGB ( 119 ; 119 ; 119 ) ) ) ]
Else
Set Variable [ $copy; Value:Case ( refTestLearn::concatenateSTUFF = "" ;
$copy & ¶ &
refLearn::referenceSTUFF ;
$copy & ¶ &
refContainerLocation::referenceSTUFF4learnOtherContainer ) ]
End If
#
#Go to the learn records next reference.
Go to Portal Row
[ Select; Next; Exit after last ]
Exit Loop If [ Get (LastError) = 101 ]
End Loop
End If
End If
#
#Go to the next learn record tagged with this
#brainstorm or inventory list tag OR exit loop
#if this is the end of the list.
Go to Record/Request/Page
[ Next; Exit after last ]
Set Variable [ $copy; Value:$copy & ¶ &
//grey text
TextColor ( "_______________________________________________" ; RGB ( 119 ; 119 ; 119 ) ) ]
#
#Increase 'main point' number if required.
If [ testlearn::brainstormCasePoint ≠ "" ]
Set Variable [ $point; Value:$point + 1 ]
End If
#
#Increase secondary point if it is different.
If [ testlearn::brainstormCasePoint = "" ]
Set Variable [ $evidence; Value:$evidence + 1 ]
Else
Set Variable [ $evidence; Value:1 ]
End If
End Loop
#
#
#Get default copyright for all lists below.
Go to Layout [ “TEMP” (TEMP) ]
Set Variable [ $copyright; Value:defaultCopyrightName::tag ]
Go to Layout [ “learnPreviewLayout” (testlearn) ]
#
#
#Attach user name, date and time and a note
#about how to create saved lists using
#brainstorm or inventory list tags if needed.
If [ TEMP::InventoryLibraryYN = "" ]
#
#Reference Title
#
#All records being viewed.
If [ $show = "all" ]
#Set copyright.
Set Variable [ $brainstorm; Value://Title
TextStyleAdd ( TEMP::userLibraryName ; "bold" ) & ¶ &
//author and copyright date
TEMP::DEFAULTNodePrimaryName & " (" & Month ( Get ( CurrentDate ) ) & "/" & Day ( Get ( CurrentDate ) ) & "/" &
Year ( Get ( CurrentDate ) ) & "). Copyright " & $copyright & "." & ¶ & ¶ &
"NOTE: This is an unsaved list of " & $numberOfRecordsBeingViewed & " records ordered by date and time of their
creation. Use the Tag Menus' 'brainstorm' option to create custom-ordered, saved, lists of selected thoughts, ideas,
etc." ]
Else
#
#Selected and its linked records if any.
#Set copyright.
Set Variable [ $brainstorm; Value://Title
TEMP::userLibraryName & ¶ &
//author and copyright date
TEMP::DEFAULTNodePrimaryName & " (" & Month ( Get ( CurrentDate ) ) & "/" & Day ( Get ( CurrentDate ) ) & "/" &
Year ( Get ( CurrentDate ) ) & "). Copyright " & $copyright & "." ]
End If
#
Else
#
#Inventory Title
#
If [ $show = "all" ]
#
#All records being viewed.
#Set copyright.
Set Variable [ $brainstorm; Value://Title
TEMP::userLibraryName & ¶ &
//author and copyright date
TEMP::DEFAULTNodePrimaryName & " (" & Month ( Get ( CurrentDate ) ) & "/" & Day ( Get ( CurrentDate ) ) & "/" &
Year ( Get ( CurrentDate ) ) & "). Copyright " & $copyright & "." & ¶ & ¶ &
"NOTE: This is an unsaved list of " & $numberOfRecordsBeingViewed & " records ordered by date and time of their
creation. Use the Tag Menus' 'inventory list' option to create custom-ordered, saved, lists of selected inventory items." ]
Else
#
#Selected and its linked records if any.
#Set copyright.
Set Variable [ $brainstorm; Value://Title
TEMP::userLibraryName & ¶ &
//author and copyright date
TEMP::DEFAULTNodePrimaryName & " (" & Month ( Get ( CurrentDate ) ) & "/" & Day ( Get ( CurrentDate ) ) & "/" &
Year ( Get ( CurrentDate ) ) & "). Copyright " & $copyright & "." ]
End If
End If
#
#
#Add title to list of records.
Set Variable [ $copy; Value://Brainstorm Title and History
$brainstorm & ¶ & ¶ & $copy ]
#
#
#Show just one record so when user scrolls
#the window the header stays at the top.
Enter Find Mode [ ]
Set Field [ testlearn::_Ltestlearn; $$main ]
Perform Find [ ]
#
#Show window with final list.
Go to Layout [ “learnPreviewLayoutView” (testlearn) ]
Move/Resize Window [ Current Window; Height: Get (ScreenHeight); Width: Get (ScreenWidth) / 2; Top: 0; Left: 0 ]
Install Menu Set [ “HGT” ]
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
Set Field [ TEMP::paste; TextSize ( $copy ; 12 ) ]
Go to Field [ ]
Scroll Window
[ Home ]
Select Window [ Name: "Share"; Current file ]
Adjust Window
[ Resize to Fit ]
#
#
#END: SHARE Non-Brainstorm and Inventory Records
#
