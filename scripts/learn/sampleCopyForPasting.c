learn: sampleCopyForPasting
#
#
#NOTE: 'Brainstorm ' is the new name for sample
#tags. When time permits, the name should be
#changed and all intances of 'sample' found
#and reviewed in the Library DDR.
#
#
#If in find mode, exit script.
If [ $$findMode ≠ "" ]
Show Custom Dialog [ Message: "Exit find mode in the Tag Menus window, then click this button."; Buttons: “OK” ]
Exit Script [ ]
End If
#
#
#If in test mode, exit script. Tests are for
#adding information to tests in the test
#module. Use the Brainstorm or Inventory List
#tag to assemble shareable, custom ordered,
#groups of Learn records.
If [ $$citationMatch = "test" ]
Go to Field [ ]
Exit Script [ ]
End If
#
#
#Admin
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
Close Window [ Name: "Print/Copy"; Current file ]
#
Set Variable [ $$stopLoadCitation; Value:1 ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Set Variable [ $layoutName; Value:Get ( LayoutName ) ]
#
#
#BEGIN: SHARE Brainstorm and Inventory Records
#
#If the Tag Menus window is showing the brainstorm
#or inventory menu when the use clicked 'share'
#then find the records tagged with the currently
#selected brainstorm tag = $$sample variable.
If [ $$citationMatch = "sample" and $layoutName ≠ "learn4EDIT" and $layoutName ≠ "learn4EDITstuff" ]
#
// New Window [ Name: "Print/Copy" ]
New Window [ Name: "Print/Copy"; Height: 1; Width: 1; Top: 10000; Left: 10000 ]
Go to Layout [ “learnPreviewLayout” (testlearn) ]
#
Enter Find Mode [ ]
#
#This keychain contain the item's three-digit
#order number followed by the key of the
#brainstorm or inventory list tag record.
Set Field [ testlearn::kcsample; "***" & $$tagsample ]
Perform Find [ ]
Sort Records [ Specified Sort Order: testlearn::orderTest; based on value list: “order”
testlearn::timestamp; descending ]
[ Restore; No dialog ]
#
#
#Stop the script if no records are found and
#tell the user why.
If [ Get (FoundCount) = 0 ]
If [ TEMP::InventoryLibaryYN = "" ]
Show Custom Dialog [ Message: "When the brainstorm menu is displayed (in the Tag Menus window), clicking 'share'
will share (in the print/copy window) only learn records tagged with a selected brainstorm tag."; Buttons: “OK” ]
Else
Show Custom Dialog [ Message: "When the inventory list menu is displayed (in the Tag Menus window), clicking
'share' will share (in the print/copy window) only learn records tagged with a selected inventory-list tag."; Buttons:
“OK” ]
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
If [ TEMP::InventoryLibaryYN = "" ]
Set Variable [ $copy; Value://previous records
Case ( $copy = "" ; "" ; $copy & ¶ & ¶) &
//text
Case ( testlearn::sampleCasePoint = "" ; $point & "." & $evidence ;
$point & ".1" ) &
//node
TextColor ( " [" & tagTLNodePrimary::tag &
Case ( testlearn::NodeOthers = "" ; "" ; "; " & testlearn::NodeOthers ) &
//timestamp
" " & testlearn::timestamp & "]"
 ; RGB ( 119 ; 119 ; 119 ) ) & ¶ & ¶ &
//main text
TextFont ( testlearn::Caption ; "Georgia" ) & ¶ &
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
Case ( testlearn::sampleCasePoint = "" ; $point & "." & $evidence ;
$point & ".1" ) &
//node
TextColor ( " [" & tagTLNodePrimary::tag &
Case ( testlearn::NodeOthers = "" ; "" ; "; " & testlearn::NodeOthers ) &
//timestamp
" " & testlearn::timestamp & "]"
 ; RGB ( 119 ; 119 ; 119 ) ) & ¶ & ¶ &
//main text
TextFont ( testlearn::Caption ; "Georgia" ) & ¶ &
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
If [ testlearn::sampleCasePoint = "" ]
Set Variable [ $evidence; Value:$evidence + 1 ]
Else
Set Variable [ $evidence; Value:2 ]
End If
#
#Print references if a learn record has any.
If [ testlearn::kcreference ≠ "" ]
If [ refReference::referenceForReferenceWindow ≠ "" or
TEMP::InventoryLibaryYN ≠ "" and refContainerLocation::referenceForReferenceWindow ≠ "" ]
#
#Name reference or inventory location section.
If [ TEMP::InventoryLibaryYN = "" ]
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
If [ TEMP::InventoryLibaryYN = "" ]
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
If [ TEMP::InventoryLibaryYN = "" ]
Set Variable [ $copy; Value:Case ( Right ( $copy ; 10 ) = "References" ;
$copy & ¶ &
//grey text
TextColor ( refReference::referenceForReferenceWindow ; RGB ( 119 ; 119 ; 119 ) ) ;
$copy & ¶ & ¶ &
//grey text
TextColor ( refReference::referenceForReferenceWindow ; RGB ( 119 ; 119 ; 119 ) ) ) ]
Else
Set Variable [ $copy; Value:Case ( refTestLearn::concatenateSTUFF = "" ;
$copy & ¶ &
refReference::referenceSTUFF ;
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
If [ testlearn::sampleCasePoint ≠ "" ]
Set Variable [ $point; Value:$point + 1 ]
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
#Get brainstorm or inventory list tag's title and
#use as the title for this shared list.
If [ $$citationMatch = "Sample" ]
Select Window [ Name: "Tag Menus"; Current file ]
If [ TEMP::InventoryLibaryYN = "" ]
Set Variable [ $sample; Value://Title
TEMP::sectionName & " Library Brainstorm — " & TextStyleAdd ( tagMenus::tag ; Titlecase ) & ¶ &
//author and copyright date
TEMP::DEFAULTNodePrimaryName & " " & Month ( Get ( CurrentDate ) ) & "/" & Day ( Get ( CurrentDate ) ) & "/" &
Year ( Get ( CurrentDate ) ) & " " & $copyright ]
Else
Set Variable [ $sample; Value://Title
TEMP::sectionName & " Library Inventory List — " & TextStyleAdd ( tagMenus::tag ; Titlecase ) & ¶ &
//author and copyright date
TEMP::DEFAULTNodePrimaryName & " " & Month ( Get ( CurrentDate ) ) & "/" & Day ( Get ( CurrentDate ) ) & "/" &
Year ( Get ( CurrentDate ) ) & " " & $copyright ]
End If
Go to Field [ ]
Set Variable [ $copy; Value://Sample Title and History
$sample & ¶ & ¶ & $copy ]
#
#Go to layout for displaying this list.
Select Window [ Name: "Print/Copy"; Current file ]
End If
#
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
#
#Set font size.
Set Field [ TEMP::paste; TextSize ( $copy ; 12 ) ]
Go to Field [ ]
#
#Display list.
Scroll Window
[ Home ]
Move/Resize Window [ Current Window; Height: Get (ScreenHeight); Width: Get (ScreenWidth) / 2; Top: 0; Left: 0 ]
#
Exit Script [ ]
#
#END: SHARE Brainstorm and Inventory Records
#
#
#
Else
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
If [ TEMP::InventoryLibaryYN = "" ]
Show Custom Dialog [ Message: "This record is linked to other learn records (text areas highlighted purple).
Share linked or just this one record?"; Buttons: “linked”, “one”, “cancel” ]
Else
#
#Determine if inventory record is for a container.
If [ testlearn::sampleCasePoint = "" ]
Show Custom Dialog [ Message: "This item record is linked to other inventory records. Show linked too or
just this one record?"; Buttons: “linked”, “one”, “cancel” ]
Else
Show Custom Dialog [ Message: "This storage area, container, etc. record is linked to other inventory. Show
linked too or just one record?"; Buttons: “linked”, “one”, “cancel” ]
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
If [ TEMP::InventoryLibaryYN = "" ]
Show Custom Dialog [ Message: "Share only linked learn records (text areas highlighted purple)?" & ¶ & "OR" &
¶ & "Share all records being viewed? Now viewing " & Get (FoundCount) & "."; Buttons: “linked”, “all”,
“cancel” ]
Else
If [ testlearn::sampleCasePoint = "" ]
Show Custom Dialog [ Message: "Share this item record and its linked storage area, container, etc. record?"
& ¶ & "OR" & ¶ & "Share all records being viewed? Now viewing " & Get (FoundCount) & "."; Buttons:
“linked”, “all”, “cancel” ]
Else
Show Custom Dialog [ Message: "Share this storage area, container, etc. record and inventory records
linked to it?" & ¶ & "OR" & ¶ & "Share all records being viewed? Now viewing " & Get (FoundCount) &
"."; Buttons: “linked”, “all”, “cancel” ]
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
If [ TEMP::InventoryLibaryYN = "" ]
Show Custom Dialog [ Message: "Share all or just this one record? Now viewing " & Get (FoundCount) & ".";
Buttons: “all”, “one”, “cancel” ]
Else
#
#Determine if inventory record is for a container.
If [ testlearn::sampleCasePoint = "" ]
Show Custom Dialog [ Message: "Share all inventory records being viewed or just this one record? Now
viewing " & Get (FoundCount) & "."; Buttons: “all”, “one”, “cancel” ]
Else
Show Custom Dialog [ Message: "Share all inventory records being viewed or just this one storage area,
container, etc. record? Now viewing " & Get (FoundCount) & "."; Buttons: “all”, “one”, “cancel” ]
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
Show Custom Dialog [ Message: "FYI: It may take a minute or more to process this many records."; Buttons: “OK”,
“cancel” ]
#
Else If [ Get ( FoundCount ) > 500 ]
Show Custom Dialog [ Message: "FYI: It may take a minute to process this many records."; Buttons: “OK”, “cancel” ]
End If
#
If [ Get ( LastMessageChoice ) = 2 ]
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
Exit Script [ ]
End If
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
// New Window [ Name: "Print/Copy" ]
New Window [ Name: "Print/Copy"; Height: 1; Width: 1; Top: 10000; Left: 10000 ]
Go to Layout [ “learnPreviewLayout” (testlearn) ]
#
#If user elected to show only selected record,
#then only this record.
If [ $show = "self" ]
Enter Find Mode [ ]
Set Field [ testlearn::_Ltestlearn; $$citation ]
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
Set Field [ testlearn::_Ltestlearn; $$citation ]
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
If [ TEMP::InventoryLibaryYN = "" ]
Show Custom Dialog [ Message: "This record 1) references and is 2) referenced by other Learn records. Show 1 =
Refs or 1 and 2 = Refs+?"; Buttons: “Refs +”, “Refs”, “cancel” ]
Else
If [ testlearn::sampleCasePoint = "" ]
Show Custom Dialog [ Message: "This record 1) references and is 2) referenced by other Learn records. Show 1
= Refs or 1 and 2 = Refs+?"; Buttons: “Refs +”, “Refs”, “cancel” ]
Else
Set Variable [ $showReferencesReferencingMe; Value:1 ]
End If
End If
If [ Get (LastMessageChoice) = 1 ]
Set Variable [ $showReferencesReferencingMe; Value:1 ]
End If
Select Window [ Name: "Print/Copy"; Current file ]
End If
#
#
#Exit script if your clicks cancel.
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
Set Field [ testlearn::kcreference; $$citation ]
Extend Found Set [ ]
#
End If
End If
End If
#
#Put all found records in order.
Sort Records [ Specified Sort Order: testlearn::date; descending
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
If [ TEMP::InventoryLibaryYN = "" ]
Set Variable [ $copy; Value://previous records
Case ( $copy = "" ; "" ; $copy & ¶ & ¶) &
//text
Case ( testlearn::sampleCasePoint = "" ; $point & "." & $evidence ;
$point & ".1" ) &
//node
TextColor ( " [" & tagTLNodePrimary::tag &
Case ( testlearn::NodeOthers = "" ; "" ; "; " & testlearn::NodeOthers ) &
//timestamp
" " & testlearn::timestamp & "]"
 ; RGB ( 119 ; 119 ; 119 ) ) & ¶ & ¶ &
//main text
TextFont ( testlearn::Caption ; "Georgia" ) & ¶ &
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
#Old reference template.
// Set Variable [ $copy; Value://previous records
Case ( $copy = "" ; "" ; $copy & ¶ & ¶) &
//text
Case ( testlearn::sampleCasePoint = "" ; $point & "." & $evidence &
//node
TextColor (
Case ( testlearn::kcitation ≠ "" ; " Quote from cited work below." ;
 " [" &
Case ( tagTLNodePrimary::tag = "" and testlearn::NodeOthers = "" ; TextStyleAdd ( "author not entered" ; Italic ) ;
tagTLNodePrimary::tag ≠ "" ; tagTLNodePrimary::tag ) &
Case ( testlearn::NodeOthers = "" ; "" ; "; " & testlearn::NodeOthers) &
//timestamp
" " & testlearn::timestamp & "]" )
 ; RGB ( 119 ; 119 ; 119 ) ) & ¶ &
//main text
TextFont ( testlearn::Caption ; "Georgia" ) ;
$point & TextFont ( testlearn::Caption ; "Georgia" ) ) & ¶ &
//grey remain text
TextColor (
//keyword
Case ( testlearn::OtherKeyWords ≠ "" or testlearn::kKeywordPrimary ≠ "" ; ¶ &
"keywords - " &
//primary keyword
tagTLKeywordPrimary::tag &
Case ( testlearn::OtherKeyWords = "" ; "" ;
//other keyword
Case ( testlearn::kKeywordPrimary ≠ "" ; ", " & testlearn::OtherKeyWords ; testlearn::OtherKeyWords ) ) ) &
//URL
Case ( testlearn::URL ≠ "" ; ¶ & testlearn::URL &
//URLdate
Case ( testlearn::URLPubDate ≠ "" ; " (link validated " & testlearn::URLPubDate & ")" ; " (link validity unavailable)") ; "" )
//finsih text color
 ; RGB ( 119 ; 119 ; 119 ) ) ]
Else
Set Variable [ $copy; Value://previous records
Case ( $copy = "" ; "" ; $copy & ¶ & ¶) &
//number
Case ( testlearn::sampleCasePoint = "" ; $point & "." & $evidence ;
$point & ".1" ) &
//node
TextColor ( " [" & tagTLNodePrimary::tag &
Case ( testlearn::NodeOthers = "" ; "" ; "; " & testlearn::NodeOthers ) &
//timestamp
" " & testlearn::timestamp & "]"
 ; RGB ( 119 ; 119 ; 119 ) ) & ¶ & ¶ &
//main text
TextFont ( testlearn::Caption ; "Georgia" ) & ¶ &
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
#Increase evidence number if point is required.
If [ testlearn::sampleCasePoint = "" ]
Set Variable [ $evidence; Value:$evidence + 1 ]
Else
Set Variable [ $evidence; Value:1 ]
End If
#
If [ testlearn::kcreference ≠ "" ]
#
#Select portal showing either a scholarly
#reference or inventory items location.
If [ TEMP::InventoryLibaryYN = "" ]
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
If [ TEMP::InventoryLibaryYN = "" ]
Set Variable [ $copy; Value:$copy & ¶ &
//grey text
TextColor (
//references
Case ( testlearn::kcreference ≠ "" ; "References" ; "" )
//finsih text color
 ; RGB ( 119 ; 119 ; 119 ) ) ]
Else
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
If [ TEMP::InventoryLibaryYN = "" ]
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
If [ TEMP::InventoryLibaryYN = "" ]
Set Variable [ $copy; Value:Case ( Right ( $copy ; 10 ) = "References" ;
$copy & ¶ &
//grey text
TextColor ( refReference::referenceForReferenceWindow ; RGB ( 119 ; 119 ; 119 ) ) ;
$copy & ¶ & ¶ &
//grey text
TextColor ( refReference::referenceForReferenceWindow ; RGB ( 119 ; 119 ; 119 ) ) ) ]
Else
Set Variable [ $copy; Value:Case ( refTestLearn::concatenateSTUFF = "" ;
$copy & ¶ &
refReference::referenceSTUFF ;
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
#Increase point number if point is different.
If [ testlearn::sampleCasePoint ≠ "" ]
Set Variable [ $point; Value:$point + 1 ]
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
If [ TEMP::InventoryLibaryYN = "" ]
#
#Reference Title
#
#All records being viewed.
If [ $show = "all" ]
Set Variable [ $sample; Value://Title
TextStyleAdd ( TEMP::sectionName & " Library Brainstorm" ; "bold" ) & ¶ &
//author and copyright date
TEMP::DEFAULTNodePrimaryName & " " & Month ( Get ( CurrentDate ) ) & "/" & Day ( Get ( CurrentDate ) ) & "/" &
Year ( Get ( CurrentDate ) ) & " " & $copyright & ¶ & ¶ &
"NOTE: This is an unsaved list of " & $numberOfRecordsBeingViewed & " records ordered by date and time of their
creation. Use the Tag Menus' 'brainstorms' option to create custom-ordered, saved, lists of selected thoughts, ideas,
etc." ]
Else
#
#Selected and its linked records if any.
Set Variable [ $sample; Value://Title
TEMP::sectionName & " Library Brainstorm" & ¶ &
//author and copyright date
TEMP::DEFAULTNodePrimaryName & " " & Month ( Get ( CurrentDate ) ) & "/" & Day ( Get ( CurrentDate ) ) & "/" &
Year ( Get ( CurrentDate ) ) & " " & $copyright ]
End If
#
Else
#
#Inventory Title
#
If [ $show = "all" ]
#
#All records being viewed.
Set Variable [ $sample; Value://Title
TEMP::sectionName & " Inventory Library" & ¶ &
//author and copyright date
TEMP::DEFAULTNodePrimaryName & " " & Month ( Get ( CurrentDate ) ) & "/" & Day ( Get ( CurrentDate ) ) & "/" &
Year ( Get ( CurrentDate ) ) & " " & $copyright & ¶ & ¶ &
"NOTE: This is an unsaved list of " & $numberOfRecordsBeingViewed & " records ordered by date and time of their
creation. Use the Tag Menus' 'inventory list' option to create custom-ordered, saved, lists of selected inventory items." ]
Else
#
#Selected and its linked records if any.
Set Variable [ $sample; Value://Title
TEMP::sectionName & " Library Inventory" & ¶ &
//author and copyright date
TEMP::DEFAULTNodePrimaryName & " " & Month ( Get ( CurrentDate ) ) & "/" & Day ( Get ( CurrentDate ) ) & "/" &
Year ( Get ( CurrentDate ) ) & " " & $copyright ]
End If
End If
#
#
#Add title to list of records.
Set Variable [ $copy; Value://Sample Title and History
$sample & ¶ & ¶ & $copy ]
#
#
#Show just one record so when user scrolls
#the window the header stays at the top.
Enter Find Mode [ ]
Set Field [ testlearn::_Ltestlearn; $$citation ]
Perform Find [ ]
#
#Show window with final list.
Move/Resize Window [ Current Window; Height: Get (ScreenHeight); Width: Get (ScreenWidth) / 2; Top: 0; Left: 0 ]
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
Set Field [ TEMP::paste; TextSize ( $copy ; 12 ) ]
Go to Field [ ]
Scroll Window
[ Home ]
Select Window [ Name: "Print/Copy"; Current file ]
Move/Resize Window [ Current Window ]
#
#
#END: SHARE Non-Brainstorm and Inventory Records
#
January 11, ଘ౮28 12:34:04 Library.fp7 - sampleCopyForPasting -1-
