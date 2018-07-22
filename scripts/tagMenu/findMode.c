July 21, 2018 14:12:18 Library.fmp12 - findMode -1-
tagMenu: findMode
#
#
#Admin tasks.
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
#
#If not in find mode because user just clicked
#the find button in the Tag Menus window...
If [ $$findMode= "" ]
#
#
#Clear brainstorm and test tags so there conditional
#formatting in the Learn window is removed.
If [ $$citationMatch = "brainstorm" or $$citationMatch = "test" ]
Select Window [ Name: "Learn"; Current file ]
Go to Field [ ]
Set Variable [ $$tagBrainstorm ]
Set Variable [ $$tagtest ]
Set Variable [ $$tagRecordID ]
Set Variable [ $$tagEdit ]
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearn::date; descending
testlearn::timestamp; descending ]
[ Restore; No dialog ]
End If
#
#Return to Tag Menus.
Select Window [ Name: "Tag Menus"; Current file ]
#
#
#If find mode is active then return to browse mode.
If [ Get ( WindowMode ) = 1 ]
#
#If user presses enter find button then perform the
#steps below to complete the find.
#
#Load found tag as a last step.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
#
Perform Find [ ]
#
Go to Layout [ $$findLayout ]
Set Variable [ $$findLayout ]
#
#Sort reference or tag records depending on which
#records user is viewing.
If [ Get (LayoutTableName) = "reference" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagKeywordPrimary::orderOrLock; based on value
list: “order Pulldown List”
tagKeywordPrimary::tag; ascending
reference::referenceShort; ascending ]
[ Restore; No dialog ]
#
#If performing a find for reference tags insure
#that the locked tags are removed.
Constrain Found Set [ Specified Find Requests: Omit Records; Criteria: reference::lock: “lock” ]
[ Restore ]
Set Variable [ $$stopLoadTagRecord ]
Perform Script [ “loadTagRecord (update)” ]
Halt Script
Else
#
If [ $$citationMatch = "learn" ]
If [ TEMP::InventoryLibraryYN = "" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearn::date; descending
testlearn::timestamp; descending ]
[ Restore; No dialog ]
Else
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearn::orderInventoryGroupNumber;
ascending
testlearn::note; ascending ]
[ Restore; No dialog ]
End If
#
Else
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenuGroup::orderOrLibraryType; based on
value list: “order Pulldown List”
tagMenuGroup::name; ascending
tagMenus::orderOrLock; based on value list: “order Pulldown List”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
End If
#
Set Variable [ $$stopLoadTagRecord ]
Perform Script [ “loadTagRecord (update)” ]
Halt Script
End If
#
#If user presses enter find button then perform the
#steps below to complete the find.
End If
#
#If user is not looking at test subjection tags...
If [ Get (LayoutTableName) ≠ "testSubsection" ]
#Ask user if they want to find a tag or find learn items
#tagged with specific tags (except if they are
#on the test Tag Menu layout).
#
#Test subsection tags need to always be shown
#as issues arise if user came from the test
#module and will be going back.
#
#Show different message for learn and reference sections.
If [ Left (Get (LayoutName) ; 9 ) ≠ "reference" ]
Show Custom Dialog [ Message: "Find learn records tagged with these tags?" & ¶ &
"OR" & ¶ &
"Find tag(s)?"; Default Button: “tag(s)”, Commit: “Yes”; Button 2: “learn”, Commit: “No”; Button 3: “cancel”, Commit:
“No” ]
#
Else If [ Left (Get (LayoutName) ; 9 ) = "reference" and $$referenceRecordOne ≠ 2 ]
#
#Eliminate find reference option for citation menu.
If [ $$citationMatch ≠ "cite" and $$stopAdd ≠ 1 ]
Show Custom Dialog [ Message: "Find references tagged with these tags?" & ¶ &
"OR" & ¶ &
"Find tag(s)?"; Default Button: “tag(s)”, Commit: “Yes”; Button 2: “reference”, Commit: “No”; Button 3: “cancel”,
Commit: “No” ]
Else If [ $$stopAdd ≠ 1 ]
Show Custom Dialog [ Message: "Find references tagged with these tags?" & ¶ &
"OR" & ¶ &
"Find tag(s)?"; Default Button: “tag(s)”, Commit: “Yes”; Button 2: “reference”, Commit: “No”; Button 3: “cancel”,
Commit: “No” ]
// Show Custom Dialog [ Message: "Find tag(s)? "; Default Button: “cancel”, Commit: “Yes”; Button 2: “tag(s)”,
Commit: “No” ]
End If
End If
#
#If user selects to find tags enter find mode first.
If [ Get ( LastMessageChoice ) = 1 and $$ClearMessageChoice ≠ 2
 or
$$stopAdd = 1 ]
Enter Find Mode [ ]
#
#Determine if user is looking tag or reference records.
If [ Get (LayoutTableName) = "reference" ]
#
#Get the layout name for the return trip after find is done.
Set Variable [ $$findLayout; Value:Get (LayoutName) ]
#
#Show different layouts for learn and reference tag
#menu items.
If [ Left (Get (LayoutName) ; 9 ) ≠ "reference" ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
Go to Layout [ “learnMenuFINDstuffRef” (reference) ]
Else
Go to Layout [ “learnMenuFINDref” (reference) ]
End If
Else
Go to Layout [ “referenceMenuFINDref” (reference) ]
End If
#
#Limit search to only items user selected to show in
#learn mode if in learn mode.
If [ Left (Get (LayoutName) ; 9 ) ≠ "reference" ]
Set Field [ reference::showInLearn; "show in learn" ]
End If
#
#Select the field where the user needs to enter the
#find information.
If [ TEMP::InventoryLibraryYN ≠ "" ]
// Go to Field [ reference::referenceSTUFF ]
Else
// Go to Field [ reference::referenceForReferenceWindow ]
End If
#
#Pause and wait until user is ready to perform find.
Pause/Resume Script [ Indefinitely ]
#
#Load found tag as a last step.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
#
#If user presses enter key then perform the steps below
#to complete the find.
Perform Find [ ]
#
Go to Layout [ $$findLayout ]
Set Variable [ $$findLayout ]
#
#If performing a find for reference tags insure
#that the locked tags are removed.
Constrain Found Set [ Specified Find Requests: Omit Records; Criteria: reference::lock: “lock” ]
[ Restore ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagKeywordPrimary::orderOrLock; based on
value list: “order Pulldown List”
tagKeywordPrimary::tag; ascending
reference::referenceShort; ascending ]
[ Restore; No dialog ]
Set Variable [ $$stopLoadTagRecord ]
Perform Script [ “loadTagRecord (update)” ]
Halt Script
Exit Script [ ]
#
Else
#Limit search to only items user selected to show in
#learn mode if in learn mode.
Set Field [ tagMenus::match; $$citationMatch ]
Set Variable [ $$findLayout; Value:Get (LayoutName) ]
If [ Left (Get (LayoutName) ; 9 ) ≠ "reference" ]
If [ Left (Get (LayoutName) ; 9 ) = "learnmenu" and Right ( Get (LayoutName) ; 9 ) ≠ "Copyright" and Right
( Get (LayoutName) ; 10 ) ≠ "Brainstorm" ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
Go to Layout [ “learnMenuFINDstuffRefLearn” (testlearn) ]
#Insure that only storage records will be found.
Set Field [ testlearn::brainstormCasePoint; "1" ]
Else
Go to Layout [ “learnMenuFINDrefLearn” (testlearn) ]
End If
#Clear these variables so find will work.
Set Field [ tagMenus::match; "" ]
Else
If [ TEMP::InventoryLibraryYN ≠ "" ]
Go to Layout [ “ltagFINDstuffNK” (tagMenus) ]
Else
Go to Layout [ “ltagFINDNK” (tagMenus) ]
End If
End If
#
Else
#Show all reference items for a section if in
#reference mode.
If [ TEMP::InventoryLibraryYN ≠ "" ]
Go to Layout [ “referenceSFINDNK” (tagMenus) ]
Else
Go to Layout [ “referenceFINDNK” (tagMenus) ]
End If
End If
#
#Select the field where the user needs to enter the
#find information.
If [ Left (Get (LayoutName) ; 5 ) = "learn" ]
// Go to Field [ testlearn::note ]
Else
// Go to Field [ tagMenus::tag ]
End If
#
#Pause and wait until user is ready to perform find.
Pause/Resume Script [ Indefinitely ]
#
#Load found tag as a last step.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
#
#If user presses enter key then perform the steps below
#to complete the find.
Perform Find [ ]
#
Go to Layout [ $$findLayout ]
Set Variable [ $$findLayout ]
#
If [ $$citationMatch = "learn" ]
If [ TEMP::InventoryLibraryYN = "" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearn::date; descending
testlearn::timestamp; descending ]
[ Restore; No dialog ]
Else
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearn::
orderInventoryGroupNumber; ascending
testlearn::note; ascending ]
[ Restore; No dialog ]
End If
#
Else
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenuGroup::orderOrLibraryType;
based on value list: “order Pulldown List”
tagMenuGroup::name; ascending
tagMenus::orderOrLock; based on value list: “order Pulldown List”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
End If
#
Set Variable [ $$stopLoadTagRecord ]
Perform Script [ “loadTagRecord (update)” ]
Exit Script [ ]
End If
#
Else If [ Get ( LastMessageChoice ) = 3 ]
#If user cancels then exit exit.
Exit Script [ ]
End If
End If
#
#
#
#
#So if user wants to find learn records, then go into
#menu for finding learn records by green button tags.
#
#Find must be done for tags, so if user is showing no
#tags when find is activitated then take user to keywords
#tag menu.
If [ Get (LayoutName) = "ReferenceMenuNoTags" ]
Go to Layout [ “ReferenceMenu2keywordOrNode2” (tagMenus) ]
End If
#
Set Variable [ $$findMode; Value:1 ]
Set Variable [ $$findLayout; Value:Get (LayoutName) ]
#
#FIND FOR LEARN MODULE
#
If [ Right ( Get (LayoutName) ; 7 ) = "refcite" and Left ( Get (LayoutName) ; 1 ) = "l" ]
#
If [ TEMP::InventoryLibraryYN = "" ]
#Idea Mode
#
If [ TEMP::layoutLtagLFIND = "" ]
#If no layout preference is set, then on iDevices
#go the layout with no pictures, and to the
#layout with pictures on desktop computers.
If [ Get (SystemPlatform) = 3 ]
Go to Layout [ “learnMenu4NoPicRefCiteFindTL” (testlearn) ]
Set Field [ TEMP::layoutLtagLFIND; "more" & Get (LayoutName) ]
Else
Go to Layout [ “learnMenu4RefCiteFindTL” (testlearn) ]
Set Field [ TEMP::layoutLtagLFIND; "less" & Get (LayoutName) ]
End If
#
Else
#
#Go the layout the user has selected.
Go to Layout [ Middle ( TEMP::layoutLtagLFIND ; 5 ; 42 ) ]
End If
#
Else
#Inventory Mode
#
#Go the layout the user has selected.
Go to Layout [ “learnMenu4RefStuffCiteFindTL” (testlearn) ]
End If
#
Else If [ Right ( Get (LayoutName) ; 9 ) = "Copyright" and Left ( Get (LayoutName) ; 1 ) = "l" ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
Go to Layout [ “learnSFind” (tagMenus) ]
Else
Go to Layout [ “learnFind” (tagMenus) ]
End If
Else If [ Right ( Get (LayoutName) ; 10 ) = "Brainstorm" and Left ( Get (LayoutName) ; 1 ) = "l" ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
Go to Layout [ “learnFindStuffBrainstorm” (tagMenus) ]
Else
Go to Layout [ “learnFindBrainstorm” (tagMenus) ]
End If
Else If [ Left ( Get (LayoutName) ; 6 ) = "ltagNK" and Left ( Get (LayoutName) ; 1 ) = "l" ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
Go to Layout [ “learnKeywordOrNodeSFind” (tagMenus) ]
Else
Go to Layout [ “learnKeywordOrNodeFind” (tagMenus) ]
End If
Else If [ Right ( Get (LayoutName) ; 1 ) = "3" and Left ( Get (LayoutName) ; 1 ) = "l" ]
Go to Layout [ “learnKeywordOrNodeFind” (tagMenus) ]
Else If [ Right ( Get (LayoutName) ; 4 ) = "test" and Left ( Get (LayoutName) ; 1 ) = "l" ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
Go to Layout [ “learnFindSTest” (testSubsectionTemplate) ]
Else
Go to Layout [ “learnFindTest” (testSubsectionTemplate) ]
End If
#
#
#
#
Else If [ Right ( Get (LayoutName) ; 5 ) = "3cite" and Left ( Get (LayoutName) ; 1 ) = "l"
or
Right ( Get (LayoutName) ; 6 ) = "3citeS" and Left ( Get (LayoutName) ; 1 ) = "l" ]
#
#
#If no layout preference is set, then on iDevices
#go the layout with no pictures, and to the
#layout with pictures on desktop computers.
If [ TEMP::layoutLtagRFIND = "" ]
If [ Get (SystemPlatform) = 3 ]
Go to Layout [ “learnFindCiteS” (reference) ]
Set Field [ TEMP::layoutLtagRFIND; "more" & Get (LayoutName) ]
Else
Go to Layout [ “learnFindCite” (reference) ]
Set Field [ TEMP::layoutLtagRFIND; "less" & Get (LayoutName) ]
End If
Else
#
#Go the layout the user has selected.
Go to Layout [ Middle ( TEMP::layoutLtagRFIND ; 5 ; 42 ) ]
End If
#
Else If [ Right ( Get (LayoutName) ; 8 ) = "RefStuff" and Left ( Get (LayoutName) ; 1 ) = "l" ]
Go to Layout [ “learnFindStuffCite” (reference) ]
#
#
#FIND FOR REFERENCE MODULE
#
Else If [ Right ( Get (LayoutName) ; 5 ) = "menu1" and Left ( Get (LayoutName) ; 1 ) = "r" ]
Go to Layout [ “ReferenceMenuFind” (tagMenus) ]
Else If [ Right ( Get (LayoutName) ; 5 ) = "node1" and Left ( Get (LayoutName) ; 1 ) = "r" ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
Go to Layout [ “ReferenceMenu2SkeywordOrNodeFind” (tagMenus) ]
Else
Go to Layout [ “ReferenceMenu2keywordOrNodeFind” (tagMenus) ]
End If
Else If [ Right ( Get (LayoutName) ; 5 ) = "node2" and Left ( Get (LayoutName) ; 1 ) = "r" ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
Go to Layout [ “ReferenceMenu2SkeywordOrNodeFind” (tagMenus) ]
Else
Go to Layout [ “ReferenceMenu2keywordOrNodeFind” (tagMenus) ]
End If
Else If [ Right ( Get (LayoutName) ; 1 ) = "3" and Left ( Get (LayoutName) ; 1 ) = "r" ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
Go to Layout [ “ReferenceMenu2SkeywordOrNodeFind” (tagMenus) ]
Else
Go to Layout [ “ReferenceMenu2keywordOrNodeFind” (tagMenus) ]
End If
Else If [ Middle ( Get ( LayoutName ) ; 14 ; 5 ) = "3cite" and Left ( Get (LayoutName) ; 1 ) = "r" ]
#
#
#If no layout preference is set, then on iDevices
#go the layout with no pictures, and to the
#layout with pictures on desktop computers.
If [ TEMP::layoutRtagCiteFIND = "" ]
If [ Get (SystemPlatform) = 3 ]
Go to Layout [ “ReferenceMenu3CiteFindS” (reference) ]
Set Field [ TEMP::layoutRtagCiteFIND; "more" & Get (LayoutName) ]
Else
Go to Layout [ “ReferenceMenu3CiteFind” (reference) ]
Set Field [ TEMP::layoutRtagCiteFIND; "less" & Get (LayoutName) ]
End If
Else
#
#Go the layout the user has selected.
Go to Layout [ Middle ( TEMP::layoutRtagCiteFIND ; 5 ; 42 ) ]
End If
#
#
Else If [ Right ( Get (LayoutName) ; 9 ) = "Copyright" and Left ( Get (LayoutName) ; 1 ) = "r" ]
Go to Layout [ “ReferenceMenuFind” (tagMenus) ]
End If
#
#Clear the first record question variable so user will
#not be asked if they wish to find or tag reference records.
Set Variable [ $$referenceRecordOne ]
Set Variable [ $$ClearMessageChoice ]
#
#As going to the other window will be involved
#stop the record load script on that window until
#this script is finished to speed things up and
#stop flashing effect.
// Set Variable [ $$stoploadCitation; Value:1 ]
Select Window [ Name: "References"; Current file ]
If [ Get (LayoutName) = "ReferenceEDIT" ]
Go to Layout [ “Reference” (reference) ]
End If
Select Window [ Name: "Learn"; Current file ]
If [ Get (LayoutName) = "Learn4Edit" ]
Go to Layout [ “learn4” (testlearn) ]
End If
Refresh Window
Select Window [ Name: "Tag Menus"; Current file ]
If [ Get ( LayoutTableName ) = "testlearn" and TEMP::InventoryLibraryYN ≠ "" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearn::orderInventoryGroupNumber; ascending
testlearn::note; ascending ]
[ Restore; No dialog ]
End If
If [ Get ( LayoutTableName ) = "testlearn" and TEMP::InventoryLibraryYN = "" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearn::date; descending
testlearn::timestamp; descending ]
[ Restore; No dialog ]
End If
Exit Script [ ]
Else If [ $$findMode= 1 ]
Set Variable [ $$findMode ]
Set Variable [ $$firstFind ]
Set Variable [ $$firstFindOther ]
Set Variable [ $$found ]
Set Variable [ $$foundOther ]
Set Variable [ $$findLayout ]
If [ $$citationmatch = "cite" ]
Perform Script [ “menuCitation (update)” ]
Else If [ $$citationmatch = "key" ]
Perform Script [ “menuKey (udpate)” ]
Else If [ $$citationMatch = "node" ]
Perform Script [ “menuNode (update)” ]
Else If [ $$citationMatch = "medium" ]
Perform Script [ “menuMedium” ]
Else If [ $$citationMatch = "copyright" ]
Perform Script [ “menuCopyright” ]
Else If [ $$citationMatch = "path" ]
Perform Script [ “menuPath” ]
Else If [ $$citationMatch = "publication" ]
Perform Script [ “menuPublication” ]
Else If [ $$citationMatch = "publisher" ]
Perform Script [ “menuPublisher” ]
Else If [ $$citationMatch = "brainstorm" ]
Perform Script [ “menuBrainstorm” ]
Else If [ $$citationMatch = "test" ]
Perform Script [ “menuTest” ]
Else If [ $$citationMatch = "learn" ]
Perform Script [ “menuLearn (udpate)” ]
Else If [ $$citationMatch = "ref" ]
Perform Script [ “menuReference (update)” ]
End If
Set Variable [ $$stoploadCitation ]
Exit Script [ ]
End If
#
